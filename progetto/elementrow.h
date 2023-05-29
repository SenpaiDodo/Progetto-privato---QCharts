#ifndef ELEMENTROW_H
#define ELEMENTROW_H

#include <QObject>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QString>
#include "data.h"


class ElementRow : public QObject
{
    Q_OBJECT

private:
    QLineEdit* title;
    QLineEdit* author;
    QLineEdit* publication;
    QComboBox* combo;
    QDoubleSpinBox* fixedprice;
    QSpinBox* numexpansion;
    QDoubleSpinBox* expansionprice;
    Videogame* vg;
    Data* data;
    int num;

public:
    explicit ElementRow(Data *d, int n, QObject *parent = nullptr, Videogame *game=new MainTitle());
    QLineEdit* GetTitle() const;
    QLineEdit* GetAuthor() const;
    QLineEdit* GetPublication() const;
    QComboBox* GetType() const;
    QDoubleSpinBox* GetFixedPrice() const;
    QSpinBox* GetNumExpansion() const;
    QDoubleSpinBox* GetExpansionPrice() const;
    Videogame* GetVideogame() const;

private slots:
    void ChangeTitle(QString tit);
    void ChangeAuthor(QString aut);
    void ChangePublication(QString pub);
    void ChangeType(int t);
    void ChangeTypePointer(int tp);
    void ChangeFixedPrice(double fp);
    void ChangeNumExpansion(int ne);
    void ChangeExpansionPrice(double ep);

signals:
    void Change();

};

#endif // ELEMENTROW_H
