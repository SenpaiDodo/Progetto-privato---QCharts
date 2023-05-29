#include "chart.h"
#include<vector>
#include<QPainter>

Chart::Chart() : price_data(0), origin(QPointF(0,0)), xdistance(0.0)
{
}

Chart::Chart(const PriceData& pd, const QPointF& o, double x_dis) : price_data(const_cast<PriceData*>(&pd)), origin(o), xdistance(x_dis)
{
    QPointF start(origin.x()+20, origin.y());
    PriceDataNorm pdn(pd, 450);
    for(int i=0; i<pdn.Size(); ++i)
    {
        QPointF temp_point(start.x()+i*xdistance, start.y()-pdn[i]);
        points.push_back(temp_point);
    }
}

Chart::~Chart()
{
    delete price_data;
}

int Chart::Size() const
{
    return points.size();
}

bool Chart::IsEmpty() const
{
    return points.size()==0;
}

double Chart::GetDistance() const
{
    return xdistance;
}

QPointF Chart::GetOrigin() const
{
    return origin;
}

PriceData& Chart::GetPriceData() const
{
    return *price_data;
}

double Chart::Space() const
{
    return points[points.size()-1].x();
}

QPointF& Chart::operator [](int i) const
{
    vector<QPointF>::const_iterator it=points.begin()+i;
    return const_cast<QPointF&>(*it);
}
