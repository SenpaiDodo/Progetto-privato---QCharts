#ifndef POINTCHART_H
#define POINTCHART_H
#include <QPointF>
#include "chart.h"


class PointChart : public Chart
{
public:
    PointChart(const PriceData& pd, const QPointF& o, double x_dis);
    virtual void Draw(QPainter& qp) const;
};

#endif // POINTCHART_H
