#ifndef BARCHART_H
#define BARCHART_H
#include <QPointF>
#include "chart.h"


class BarChart : public Chart
{
private:
    double width;

public:
    BarChart(const PriceData& pd, const QPointF& o, double x_dis, double w);
    virtual void Draw(QPainter& qp) const;
    virtual double Space() const;
    double GetWidth() const;
};

#endif // BARCHART_H
