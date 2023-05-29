#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QList>
#include "data.h"
#include "elementrow.h"

class Table : public QTableWidget
{
    Q_OBJECT

private:
    Data* data;
    QList<ElementRow*> list;

public:
    explicit Table(Data *d=0, QWidget *parent = nullptr);
    Videogame* GetVg(int i);
    ~Table();

signals:
    void Changed();

public slots:
    void InsertNewData(int i);
    void removeRow(int i);
    void NewData();
    void ClearAll();
};

#endif // TABLE_H
