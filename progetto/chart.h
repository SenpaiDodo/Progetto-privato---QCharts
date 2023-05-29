#ifndef CHART_H
#define CHART_H
#include<vector>
#include<QPainter>
#include "pricedata.h"
#include "pricedatanorm.h"

using std::vector;

class Chart
{
private:
    PriceData* price_data;
    QPointF origin;
    double xdistance;

protected:
    vector<QPointF> points;

public:
    Chart();
    Chart(const PriceData& pd, const QPointF& o, double x_dis);
    virtual ~Chart();
    int Size() const;
    bool IsEmpty() const;
    double GetDistance() const;
    QPointF GetOrigin() const;
    PriceData& GetPriceData() const;
    virtual double Space() const;
    virtual void Draw(QPainter& qp) const=0;
    virtual QPointF& operator[](int i) const;
};

#endif // CHART_H
