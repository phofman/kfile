//
// Based on an original implementation by Razvan Petru
//
#include <QApplication>
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include "kineticscroller.h"

// A number of mouse moves are ignored after a press to differentiate
// it from a press & drag.
static const int gMaxIgnoredMouseMoves = 4;
// The timer measures the drag speed & handles kinetic scrolling. Adjusting
// the timer interval will change the scrolling speed and smoothness.
static const int gTimerInterval = 20;
// The speed measurement is imprecise, limit it so that the scrolling is not
// too fast.
static const int gMaxDecelerationSpeed = 30;
// influences how fast the scroller decelerates
static const int gFriction = 1;

class KineticScrollerImpl
{
public:
   KineticScrollerImpl()
      : scrollArea(0)
      , isPressed(false)
      , isMoving(false)
      , lastMouseYPos(0)
      , lastScrollBarPosition(0)
      , velocity(0)
      , ignoredMouseMoves(0)
      , ignoredMouseActions(0) {}

   void stopMotion()
   {
      isMoving = false;
      velocity = 0;
      kineticTimer.stop();
   }

   QAbstractScrollArea* scrollArea;
   bool isPressed;
   bool isMoving;
   QPoint lastPressPoint;
   int lastMouseYPos;
   int lastScrollBarPosition;
   int velocity;
   int ignoredMouseMoves;
   int ignoredMouseActions;
   QTimer kineticTimer;
};

KineticScroller::KineticScroller(QObject *parent)
   : QObject(parent)
   , d(new KineticScrollerImpl)
{
   connect(&d->kineticTimer, SIGNAL(timeout()), SLOT(onKineticTimerElapsed()));
}

// needed by smart pointer
KineticScroller::~KineticScroller()
{
}

void KineticScroller::enableKineticScrollFor(QAbstractScrollArea* scrollArea)
{
   if( !scrollArea )
   {
      Q_ASSERT_X(0, "kinetic scroller", "missing scroll area");
      return;
   }

   // remove existing association
   if( d->scrollArea )
   {
      d->scrollArea->viewport()->removeEventFilter(this);
      d->scrollArea->removeEventFilter(this);
      d->scrollArea = 0;
   }

   // associate
   scrollArea->installEventFilter(this);
   scrollArea->viewport()->installEventFilter(this);
   d->scrollArea = scrollArea;
}

//! intercepts mouse events to make the scrolling work
bool KineticScroller::eventFilter(QObject* object, QEvent* event)
{
   const QEvent::Type eventType = event->type();
   const bool isMouseAction = QEvent::MouseButtonPress == eventType
      || QEvent::MouseButtonRelease == eventType;
   const bool isMouseEvent = isMouseAction || QEvent::MouseMove == eventType;
   if( !isMouseEvent || !d->scrollArea )
     return false;
   if( isMouseAction && d->ignoredMouseActions-- > 0 ) // don't filter simulated click
     return false;

   QMouseEvent* const mouseEvent = static_cast<QMouseEvent*>(event);
   switch( eventType )
   {
   case QEvent::MouseButtonPress:
      {
         d->isPressed = true;
         d->lastPressPoint = mouseEvent->pos();
         d->lastScrollBarPosition = d->scrollArea->verticalScrollBar()->value();
         if( d->isMoving ) // press while kinetic scrolling, so stop
            d->stopMotion();
      }
      break;
   case QEvent::MouseMove:
      {
         if( !d->isMoving )
         {
            // A few move events are ignored as "click jitter", but after that we
            // assume that the user is doing a click & drag
            if( d->ignoredMouseMoves < gMaxIgnoredMouseMoves )
               ++d->ignoredMouseMoves;
            else
            {
               d->ignoredMouseMoves = 0;
               d->isMoving = true;
               d->lastMouseYPos = mouseEvent->pos().y();
               if( !d->kineticTimer.isActive() )
                  d->kineticTimer.start(gTimerInterval);
            }
         }
         else
         {
            // manual scroll
            const int dragDistance = mouseEvent->pos().y() - d->lastPressPoint.y();
            d->scrollArea->verticalScrollBar()->setValue(
               d->lastScrollBarPosition - dragDistance);
         }
      }
      break;
   case QEvent::MouseButtonRelease:
      {
         d->isPressed = false;
         // Looks like the user wanted a single click. Simulate the click,
         // as the events were already consumed
         if( !d->isMoving )
         {
            QMouseEvent* mousePress = new QMouseEvent(QEvent::MouseButtonPress,
               d->lastPressPoint, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QMouseEvent* mouseRelease = new QMouseEvent(QEvent::MouseButtonRelease,
               d->lastPressPoint, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

            d->ignoredMouseActions = 2;
            QApplication::postEvent(object, mousePress);
            QApplication::postEvent(object, mouseRelease);
         }
      }
      break;
   default:
      break;
   }

   return true; // filter event
}

void KineticScroller::onKineticTimerElapsed()
{
   if( d->isPressed && d->isMoving )
   {
      // the speed is measured between two timer ticks
      const int cursorYPos = d->scrollArea->mapFromGlobal(QCursor::pos()).y();
      d->velocity = cursorYPos - d->lastMouseYPos;
      d->lastMouseYPos = cursorYPos;
   }
   else if( !d->isPressed && d->isMoving )
   {
      // use the previously recorded speed and gradually decelerate
      d->velocity = qBound(-gMaxDecelerationSpeed, d->velocity, gMaxDecelerationSpeed);
      if( d->velocity > 0 )
         d->velocity -= gFriction;
      else if( d->velocity < 0 )
         d->velocity += gFriction;
      if( qAbs(d->velocity) < qAbs(gFriction) )
         d->stopMotion();

      const int scrollBarYPos = d->scrollArea->verticalScrollBar()->value();
      d->scrollArea->verticalScrollBar()->setValue(scrollBarYPos - d->velocity);
   }
   else
      d->stopMotion();
}
