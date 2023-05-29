#include "canvas.h"
#include <QPainter>
#include <QString>

Canvas::Canvas(Data* d, QWidget *parent) : QWidget(parent), data(d), chart(0), origin(50, 550), pointx(800, 550), pointy(50, 20)
{
    resize(1000,650);
}

void Canvas::SetOrigin(const QPointF & o)
{
    origin=o;
    update();
}

void Canvas::SetPointX(const QPointF & px)
{
    pointx=px;
    update();
}

void Canvas::SetPointY(const QPointF & py)
{
    pointy=py;
    update();
}

Canvas::~Canvas()
{
    delete chart;
}

void Canvas::paintEvent(QPaintEvent*)
{
    if(chart)
    {
        if(chart->Space()>=pointx.x()-30)
        {
            QPointF newpointx(chart->Space()+50, pointx.y());
            SetPointX(newpointx);
            resize(newpointx.x()+100,650);
        }
        else if(chart->Space()<pointx.x()+500)
        {
            QPointF newpointx(chart->Space()+50, pointx.y());
            SetPointX(newpointx);
            resize(newpointx.x()+100, 650);
        }
    }
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 4));
    QLineF xaxes(pointx, origin);
    QLineF yaxes(origin, pointy);
    painter.drawLine(xaxes);
    painter.drawLine(yaxes);
    painter.drawText(origin.x()-15, origin.y()+15,"O");
    painter.drawText(pointx.x()-10, pointx.y()+20,"X");
    painter.drawText(pointy.x()-20, pointy.y()+10,"Y");
    if(chart)
        chart->Draw(painter);
}

void Canvas::DrawBar()
{
    if(chart)
        delete chart;
    PriceData* pricedata=new PriceData(*data);
    chart=new BarChart(*pricedata, origin, 20, 30);
    update();
}

void Canvas::DrawLine()
{
    if(chart)
        delete chart;
    PriceData* pricedata=new PriceData(*data);
    chart=new LineChart(*pricedata, origin, 50);
    update();
}

void Canvas::DrawPoint()
{
    if(chart)
        delete chart;
    PriceData* pricedata=new PriceData(*data);
    chart=new PointChart(*pricedata, origin, 50);
    update();
}

void Canvas::Refresh()
{
    if(dynamic_cast<LineChart*>(chart))
    {
        double distance=chart->GetDistance();
        delete chart;
        PriceData* pricedata=new PriceData(*data);
        chart=new LineChart(*pricedata, origin, distance);
    }
    else
    {
        if(dynamic_cast<BarChart*>(chart))
        {
            BarChart* bar=dynamic_cast<BarChart*>(chart);
            double distance=bar->GetDistance();
            double width=bar->GetWidth();
            delete chart;
            PriceData* pricedata=new PriceData(*data);
            chart=new BarChart(*pricedata, origin, distance-width, width);
        }
        else
        {
            if(dynamic_cast<PointChart*>(chart))
            {
                double distance=chart->GetDistance();
                delete chart;
                PriceData* pricedata=new PriceData(*data);
                chart=new PointChart(*pricedata, origin, distance);
            }
        }
    }
    update();
}

void Canvas::CloseChart()
{
    resize(1000,650);
    delete chart;
    chart=0;
    origin=QPointF(50, 550);
    pointx=QPointF(800, 550);
    pointy=QPointF(50, 20);
    update();
}
