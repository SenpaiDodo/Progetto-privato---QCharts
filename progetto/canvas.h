#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "data.h"
#include "pricedata.h"
#include "pricedatanorm.h"
#include "chart.h"
#include "linechart.h"
#include "barchart.h"
#include "pointchart.h"


class Canvas : public QWidget
{
    Q_OBJECT

private:
    Data* data;
    Chart* chart;
    QPointF origin;
    QPointF pointx;
    QPointF pointy;

public:
    explicit Canvas(Data* d, QWidget *parent = nullptr);
    void SetOrigin(const QPointF& o);
    void SetPointX(const QPointF& px);
    void SetPointY(const QPointF& py);
    ~Canvas();

protected:
     void paintEvent(QPaintEvent*);

public slots:

     void DrawBar();
     void DrawLine();
     void DrawPoint();
     void Refresh();
     void CloseChart();
};

#endif // CANVAS_H
