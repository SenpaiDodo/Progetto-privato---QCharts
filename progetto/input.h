#ifndef INPUT_H
#define INPUT_H
#include <QWidget>
#include <QDialog>
#include <QList>
#include <QScrollArea>
#include "inputline.h"
#include "data.h"
#include "error.h"


class Input : public QDialog
{
    Q_OBJECT

private:
    QScrollArea* area;
    Data* dat;
    int count;
    QList<InputLine*> list;

public:
     explicit Input(QWidget* parent = nullptr, Data* d=0, int c=0);
     bool Isok() const;

signals:
     void Ok();

private slots:
     void Create();
};

#endif // INPUT_H
