#ifndef TAB_H
#define TAB_H

#include <QTabWidget>
#include <QScrollArea>
#include "table.h"
#include "canvas.h"
#include "data.h"
#include "error.h"

class Tab : public QTabWidget
{
    Q_OBJECT

private:
    Data* data;
    Table* table;
    Canvas* canvas;
    QScrollArea* area;

public:
    explicit Tab(Data *d, QWidget *parent = nullptr);

signals:
    void Close();
    void Remove();
    void NewRow();
    void InsertOk();
    void RemRow(int i);
    void Last();

public slots:
    void DrawLine();
    void DrawBar();
    void DrawPoint();
    void Open();
    void AddElement();
    void RemoveElement();
    void InsertToData();
    void CloseAll();
};

#endif // TAB_H
