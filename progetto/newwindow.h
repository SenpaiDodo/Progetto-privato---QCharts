#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include "data.h"
#include "input.h"
#include "error.h"


class NewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr, Data* d=0);
    int Value() const;

private:
     int c;
     Data* da;
     QSpinBox* ndata;
     QPushButton* ok;
     QPushButton* cancel;
     QRadioButton* pointchart;
     QRadioButton* linechart;
     QRadioButton* barchart;

private slots:
     void ClickedPointChart();
     void ClickedBarChart();
     void ClickedLineChart();
     void ClickedOk();
     void ChangeEle(int i);
     void CreateChart();

signals:
     void Point(); //creato un PointChart
     void Bar();//creato un BarChart
     void Line();//creato un LineChart
     void New();
};

#endif // NEWWINDOW_H
