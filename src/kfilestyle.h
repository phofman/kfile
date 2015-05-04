#pragma once

#include <QCleanlooksStyle>

class KFileStyle: public QCleanlooksStyle
{
  Q_OBJECT

  public:
  
  int pixelMetric (PixelMetric metric, const QStyleOption * option = 0, 
          const QWidget * widget = 0 ) const 
    {
    int s;
    if (metric == QStyle::PM_SmallIconSize) 
      s = 32;
    else if (metric == QStyle::PM_ScrollBarSliderMin)
      s = 32;
    else if (metric == QStyle::PM_SliderThickness)
      s = 32;
    else if (metric == QStyle::PM_SliderControlThickness)
      s = 32;
    else if (metric == QStyle::PM_ScrollBarExtent)
      s = 32;
    else
      s = QCleanlooksStyle::pixelMetric(metric, option, widget);
  return s;
  }
};
