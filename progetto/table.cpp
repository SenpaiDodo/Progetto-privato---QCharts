#include "table.h"
#include <QStringList>
#include <string>

using std::string;

Table::Table(Data *d, QWidget *parent) : QTableWidget(parent), data(d)
{
    setColumnCount(7);
    QStringList header;
    header<<"Titolo"<<"Autore"<<"A. Pubblicazione"<<"Tipo"<<"Prezzo"<<"N. Espansioni"<<"Prezzo Espansioni";
    setHorizontalHeaderLabels(header);
    setRowCount(0);
}

Videogame* Table::GetVg(int i)
{
    QList<ElementRow*>::const_iterator it=list.begin()+i;
    return (*it)->GetVideogame();
}

Table::~Table()
{
    for(QList<ElementRow*>::const_iterator it=list.begin(); it!=list.end(); ++it)
        delete *it;
}

void Table::InsertNewData(int i)
{
    insertRow(i);
    ElementRow* element=new ElementRow(data, i, this);
    list.push_back(element);
    connect(element, SIGNAL(Change()), this, SIGNAL(Changed()));
    setCellWidget(i, 0, element->GetTitle());
    setCellWidget(i, 1, element->GetAuthor());
    setCellWidget(i, 2, element->GetPublication());
    setCellWidget(i, 3, element->GetType());
    setCellWidget(i, 4, element->GetFixedPrice());
    setCellWidget(i, 5, element->GetNumExpansion());
    setCellWidget(i, 6, element->GetExpansionPrice());
    setCurrentCell(i,0);
}

void Table::removeRow(int i)
{
    QList<ElementRow*>::iterator it=list.begin()+i;
    if(data->Size()>i)
    {
        data->Delete(i);
        delete *it;
        list.erase(it);
        emit Changed();
    }
    else
    {
        delete (*it)->GetVideogame();
        delete *it;
        list.erase(it);
    }
    QTableWidget::removeRow(i);
}

void Table::NewData()
{
    ClearAll();
    for(int i=0; i<data->Size(); ++i)
    {
        insertRow(i);
        ElementRow* element=new ElementRow(data, i, this, (*data)[i]);
        list.push_back(element);
        connect(element,SIGNAL(Change()),this,SIGNAL(Changed()));
        setCellWidget(i, 0, element->GetTitle());
        setCellWidget(i, 1, element->GetAuthor());
        setCellWidget(i, 2, element->GetPublication());
        setCellWidget(i, 3, element->GetType());
        setCellWidget(i, 4, element->GetFixedPrice());
        setCellWidget(i, 5, element->GetNumExpansion());
        setCellWidget(i, 6, element->GetExpansionPrice());
    }
}

void Table::ClearAll()
{
    for(int i=rowCount(); i>=0; i--)
            QTableWidget::removeRow(i);
    for(QList<ElementRow*>::const_iterator it=list.begin(); it!=list.end();++it)
            delete *it;
    list.clear();
}
