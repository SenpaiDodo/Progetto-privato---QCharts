#include "newwindow.h"
#include <QWidget>
#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

NewWindow::NewWindow(QWidget *parent, Data *d) : QDialog(parent), c(0), da(d)
{
    setWindowTitle("Crea un nuovo grafico");
    resize(700,400);
    setModal(true);
    QDialog::reject();
    QLabel* label=new QLabel("Inserisci il numero di dati del grafico");
    ndata=new QSpinBox();
    ndata->setRange(0,99);
    ndata->setValue(0);
    ndata->setAccelerated(true);
    QHBoxLayout* inputlayout= new QHBoxLayout();
    inputlayout->addWidget(label);
    inputlayout->addWidget(ndata);
    QGroupBox* typechart=new QGroupBox(tr("Grafico"));
    QLabel* chart=new QLabel("Scegli il tipo di grafico che vuoi creare:");
    linechart=new QRadioButton("Grafico a linea");
    pointchart=new QRadioButton("Grafico a punto");
    barchart=new QRadioButton("Grafico a barre");
    barchart->setCheckable(true);
    linechart->setCheckable(true);
    pointchart->setCheckable(true);
    barchart->setChecked(true);
    linechart->setChecked(false);
    pointchart->setChecked(false);
    QVBoxLayout* buttonchart=new QVBoxLayout();
    buttonchart->addWidget(chart);
    buttonchart->addWidget(linechart);
    buttonchart->addWidget(pointchart);
    buttonchart->addWidget(barchart);
    buttonchart->addStretch();
    ok=new QPushButton(tr("Ok"));
    cancel=new QPushButton(tr("Annulla"));
    ok->setFont(QFont("Times", 18, QFont::Black));
    cancel->setFont(QFont("Times", 18, QFont::Black));
    typechart->setLayout(buttonchart);
    QDialogButtonBox* button=new QDialogButtonBox(Qt::Horizontal);
    button->addButton(ok,QDialogButtonBox::ActionRole);
    button->addButton(cancel, QDialogButtonBox::ActionRole);
    QVBoxLayout* container=new QVBoxLayout();
    container->addLayout(inputlayout);
    container->addWidget(typechart);
    container->addWidget(button);
    setLayout(container);
    connect(ok, SIGNAL(clicked()), this, SLOT(ClickedOk()));
    connect(ndata, SIGNAL(valueChanged(int)), this, SLOT(ChangeEle(int)));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(barchart, SIGNAL(clicked()), this, SLOT(ClickedBarChart()));
    connect(pointchart, SIGNAL(clicked()), this, SLOT(ClickedPointChart()));
    connect(linechart, SIGNAL(clicked()), this, SLOT(ClickedLineChart()));
}

int NewWindow::Value() const
{
    return ndata->value();
}

void NewWindow::ClickedPointChart()
{
    pointchart->setChecked(true);
    linechart->setChecked(false);
    barchart->setChecked(false);
}

void NewWindow::ClickedBarChart()
{
    barchart->setChecked(true);
    linechart->setChecked(false);
    pointchart->setChecked(false);
}

void NewWindow::ClickedLineChart()
{
    linechart->setChecked(true);
    pointchart->setChecked(false);
    barchart->setChecked(false);
}

void NewWindow::ClickedOk()
{
    try
    {
        if(ndata->value()==0)
        {
            throw Zero();
        }
        else{
            Input* input=new Input(this, da, c);
            connect(input, SIGNAL(Ok()), this, SLOT(CreateChart()));
            connect(input, SIGNAL(Ok()), this, SLOT(close()));
            input->show();
        }
    }
    catch(Zero z)
    {

        QMessageBox::critical(this, "Errore!", "Il numero di dati deve essere maggiore di zero!");
    }
}

void NewWindow::ChangeEle(int i)
{
    c=i;
}

void NewWindow::CreateChart()
{
    emit New();
    if(barchart->isChecked())
    {
        emit Bar();
    }
    else
    {
        if(linechart->isChecked())
        {
            emit Line();
        }
        else
        {
            if(pointchart->isChecked())
            {
                emit Point();
            }
        }
    }
}
