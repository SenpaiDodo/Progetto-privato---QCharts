#include "tab.h"
#include <QTabWidget>
#include <QScrollArea>
#include <QMessageBox>
#include <QScrollBar>

Tab::Tab(Data *d, QWidget *parent) : QTabWidget(parent), data(d)
{
    area=new QScrollArea();
    table=new Table(data);
    canvas=new Canvas(data,this);
    area->setWidget(canvas);
    addTab(table,"Dati");
    addTab(area,"Grafico");
    setCurrentWidget(table);
    connect(this, SIGNAL(Close()), canvas, SLOT(CloseChart()));
    connect(this, SIGNAL(InsertOk()), canvas, SLOT(Refresh()));
    connect(this, SIGNAL(Remove()), canvas, SLOT(Refresh()));
    connect(table, SIGNAL(Changed()), canvas, SLOT(Refresh()));
}

void Tab::DrawLine()
{
    canvas->DrawLine();
    if(canvas->isEnabled())
        setCurrentIndex(1);
}
void Tab::DrawBar()
{
    canvas->DrawBar();
    if(canvas->isEnabled())
        setCurrentIndex(1);
}
void Tab::DrawPoint()
{
    canvas->DrawPoint();
    if(canvas->isEnabled())
        setCurrentIndex(1);
}

void Tab::Open()
{
    table->NewData();
    QScrollBar* barv=area->verticalScrollBar();
    QScrollBar* barh=area->horizontalScrollBar();
    barh->setValue(0);
    barv->setValue(0);
}

void Tab::AddElement() {
    try
    {
        int row=table->rowCount();
        if(row<=99)
        {
            table->InsertNewData(row);
            setTabEnabled(1, false);
            emit NewRow();
        }
        else
            throw Max();
    }
    catch(Max m)
    {
        QMessageBox::warning(0, "Attenzione", "E' gia' stato raggiunto il numero massimo di elementi!");
    }
}

void Tab::RemoveElement()
{
    int row=table->currentRow();
    if(row>=0)
    {
        if(row==data->Size())
        {
            emit Last();
            setTabEnabled(1, true);
        }
        table->removeRow(row);
        emit Remove();
        if(!table->rowCount())
            emit Close();
    }
}

void Tab::InsertToData() {
    try
    {
        int row=table->rowCount();
        Videogame* vg=table->GetVg(row-1);
        if(vg->GetName()=="" || vg->GetAuthor()=="" || vg->GetPublication()=="")
            throw ErrorAdd();
        data->Add(*vg);
        setTabEnabled(1, true);
        emit InsertOk();
    }
    catch(ErrorAdd e)
    {
        QMessageBox::warning(0, "Attenzione", "Inserimento del dato non riuscito!");

    }
}

void Tab::CloseAll()
{
    table->ClearAll();
    canvas->CloseChart();
    QScrollBar* barv=area->verticalScrollBar();
    QScrollBar* barh=area->horizontalScrollBar();
    barh->setValue(0);
    barv->setValue(0);
    setTabEnabled(1, true);
    setCurrentIndex(0);
}
