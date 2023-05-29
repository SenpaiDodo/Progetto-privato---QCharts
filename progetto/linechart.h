#ifndef LINECHART_H
#define LINECHART_H
#include <QPointF>
#include "chart.h"


class LineChart : public Chart
{
public:
    LineChart(const PriceData& pd, const QPointF& o, double x_dis);
    virtual void Draw(QPainter& qp) const;
};

#endif // LINECHART_H
