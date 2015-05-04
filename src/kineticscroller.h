#pragma once

#include <QObject>
#include <QScopedPointer>
class KineticScrollerImpl;
class QAbstractScrollArea;
class QEvent;

class KineticScroller: public QObject
{
   Q_OBJECT
public:
   KineticScroller(QObject* parent = 0);
   ~KineticScroller();
   void enableKineticScrollFor(QAbstractScrollArea* scrollArea);

protected:
   bool eventFilter(QObject* object, QEvent* event);

private slots:
   void onKineticTimerElapsed();

private:
   QScopedPointer<KineticScrollerImpl> d;
};

