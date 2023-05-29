#include "linechart.h"
#include <QPointF>

LineChart::LineChart(const PriceData& pd, const QPointF& o, double x_dis) : Chart(pd, o, x_dis)
{
}

void LineChart::Draw(QPainter& qp) const
{
    qp.setPen(Qt::darkGreen);
    for(int i=0; i<Size()-1; ++i)
    {
        QLineF line(points[i], points[i+1]);
        qp.drawLine(line);
    }
    if(Size()>1)
    {
        for(int i=0; i<Size(); ++i)
        {
            QString index;
            index.setNum(i+1);
            qp.setPen(QPen(Qt::black, 3));
            QPointF point(points[i].x(), GetOrigin().y()+20);
            qp.drawText(point, index);
            QPointF py1(GetOrigin().x()+5, points[i].y());
            QPointF py2(GetOrigin().x()-5, points[i].y());
            qp.setPen(QPen(Qt::black, 3));
            qp.drawLine(QLineF(py1, py2));
        }
        for(int i=0; i<Size(); ++i)
        {
            qp.setFont(QFont("arial", 7, Qt::black));
            QString value(QString::number(GetPriceData()[i]));
            qp.drawText(QPointF(GetOrigin().x()-25, points[i].y()), value);
        }
    }
}
