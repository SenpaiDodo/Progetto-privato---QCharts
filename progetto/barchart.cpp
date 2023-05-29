#include "barchart.h"
#include <QPointF>

BarChart::BarChart(const PriceData& pd, const QPointF& o, double x_dis, double w) : Chart(pd, QPoint(o.x(), o.y()-4), x_dis+w), width(w)
{
}

void BarChart::Draw(QPainter& qp) const
{
    for(int i=0;i<Size();i++)
        {
            qp.setPen(QPen(Qt::red, 3));
            QSizeF size(width, GetOrigin().y()-points[i].y());
            QRectF rect(points[i], size);
            qp.drawRect(rect);
            QRectF rect1(points[i]+QPointF(1,1), QSize(width-1, (GetOrigin().y()-points[i].y()-1)));
            qp.fillRect(rect1, QBrush(QColor(Qt::darkBlue), Qt::SolidPattern));
            qp.setPen(Qt::black);
            QString index;
            index.setNum(i+1);
            QPointF point(points[i].x()+width/2-1, GetOrigin().y()+20);
            qp.drawText(point, index);
            QPointF py1(GetOrigin().x()+5, points[i].y());
            QPointF py2(GetOrigin().x()-5, points[i].y());
            qp.drawLine(QLineF(py1, py2));
        }
        for(int i=0;i<Size();++i)
        {
            qp.setFont(QFont("arial", 7, Qt::black));
            QString value(QString::number(GetPriceData()[i]));
            qp.drawText(QPointF(GetOrigin().x()-25, points[i].y()), value);
        }
}

double BarChart::Space() const
{
        return points[points.size()-1].x()+width;
}

double BarChart::GetWidth() const
{
    return width;
}
