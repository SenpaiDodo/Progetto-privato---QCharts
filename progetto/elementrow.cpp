#include "elementrow.h"
#include <QString>
#include <string>
#include <QSpinBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>

using std::string;

ElementRow::ElementRow(Data* d, int n, QObject *parent, Videogame* game) : QObject(parent), vg(game), data(d), num(n)
{
    title=new QLineEdit();
    title->setText("");
    author=new QLineEdit();
    author->setText("");
    publication=new QLineEdit();
    publication->setText("");
    combo=new QComboBox();
    combo->insertItem(1, "Videogioco principale");
    combo->insertItem(2, "Espansioni/DLC");
    combo->setCurrentIndex(0);
    fixedprice=new QDoubleSpinBox();
    fixedprice->setRange(0,200.0);
    fixedprice->setValue(0.0);
    fixedprice->setAccelerated(true);
    numexpansion=new QSpinBox();
    numexpansion->setValue(0);
    numexpansion->setRange(0,100);
    numexpansion->setAccelerated(true);
    expansionprice=new QDoubleSpinBox();
    expansionprice->setValue(0.0);
    expansionprice->setMinimum(0.0);
    expansionprice->setMaximum(50.0);
    expansionprice->setAccelerated(true);
    fixedprice->setEnabled(true);
    numexpansion->setEnabled(false);
    expansionprice->setEnabled(false);
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeType(int)));
    string temptitle=vg->GetName();
    string tempauthor=vg->GetAuthor();
    string temppublication=vg->GetPublication();
    if(dynamic_cast<MainTitle*>(vg))
    {
        MainTitle* maintitle=dynamic_cast<MainTitle*>(vg);
        double fprice=maintitle->GetFixedPrice();
        title->setText(QString::fromStdString(temptitle));
        author->setText(QString::fromStdString(tempauthor));
        publication->setText(QString::fromStdString(temppublication));
        combo->setCurrentIndex(0);
        fixedprice->setValue(fprice);
    }
    else
    {
        if(dynamic_cast<Expansion*>(vg))
        {
            Expansion* expansion=dynamic_cast<Expansion*>(vg);
            u_int nexpansion=expansion->GetNumExpansion();
            double eprice=expansion->GetExpansionPrice();
            title->setText(QString::fromStdString(temptitle));
            author->setText(QString::fromStdString(tempauthor));
            publication->setText(QString::fromStdString(temppublication));
            combo->setCurrentIndex(1);
            numexpansion->setValue(nexpansion);
            expansionprice->setValue(eprice);
        }
    }
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeTypePointer(int)));
    connect(title, SIGNAL(textChanged(QString)), this, SLOT(ChangeTitle(QString)));
    connect(author, SIGNAL(textChanged(QString)), this, SLOT(ChangeAuthor(QString)));
    connect(publication, SIGNAL(textChanged(QString)), this, SLOT(ChangePublication(QString)));
    connect(fixedprice, SIGNAL(valueChanged(double)), this, SLOT(ChangeFixedPrice(double)));
    connect(numexpansion, SIGNAL(valueChanged(int)), this, SLOT(ChangeNumExpansion(int)));
    connect(expansionprice, SIGNAL(valueChanged(double)), this, SLOT(ChangeExpansionPrice(double)));
}

QLineEdit* ElementRow::GetTitle() const
{
    return title;
}

QLineEdit* ElementRow::GetAuthor() const
{
    return author;
}

QLineEdit* ElementRow::GetPublication() const
{
    return publication;
}

QComboBox* ElementRow::GetType() const
{
    return combo;
}

QDoubleSpinBox* ElementRow::GetFixedPrice() const
{
    return fixedprice;
}

QSpinBox* ElementRow::GetNumExpansion() const
{
    return numexpansion;
}

QDoubleSpinBox* ElementRow::GetExpansionPrice() const
{
    return expansionprice;
}

Videogame* ElementRow::GetVideogame() const
{
    return vg;
}

void ElementRow::ChangeTitle(QString tit)
{
    vg->SetName(tit.toStdString());
}

void ElementRow::ChangeAuthor(QString aut)
{
    vg->SetAuthor(aut.toStdString());
}

void ElementRow::ChangePublication(QString pub)
{
    vg->SetPublication(pub.toStdString());
}

void ElementRow::ChangeType(int t)
{
    if(t==0)
    {
        fixedprice->setEnabled(true);
        numexpansion->setEnabled(false);
        expansionprice->setEnabled(false);
        fixedprice->setValue(0.0);
        numexpansion->setValue(0);
        expansionprice->setValue(0.0);
    }
    else
    {
        if(t==1)
        {
            fixedprice->setEnabled(false);
            numexpansion->setEnabled(true);
            expansionprice->setEnabled(true);
            fixedprice->setValue(0.0);
            numexpansion->setValue(0);
            expansionprice->setValue(0.0);
        }
    }
}

void ElementRow::ChangeTypePointer(int tp)
{
    string temptitle=vg->GetName();
    string tempauthor=vg->GetAuthor();
    string temppublication=vg->GetPublication();
    if(tp==0)
    {
        vg=new MainTitle(temptitle, tempauthor, temppublication, 0.0);
        if(num<data->Size())
            data->Change(num, *vg);
    }
    else
    {
        if(tp==1)
        {
            vg=new Expansion(temptitle, tempauthor, temppublication, 0, 0.0);
            if(num<data->Size())
                data->Change(num, *vg);
        }
    }
    if(num<data->Size())
        emit Change();
}

void ElementRow::ChangeFixedPrice(double fp)
{
    if(dynamic_cast<MainTitle*>(vg))
    {
        MainTitle* maintitle=dynamic_cast<MainTitle*>(vg);
        maintitle->SetFixedPrice(fp);
        if(num<data->Size())
            emit Change();
    }
}

void ElementRow::ChangeNumExpansion(int ne)
{
    if(dynamic_cast<Expansion*>(vg))
    {
        Expansion* expansion=dynamic_cast<Expansion*>(vg);
        expansion->SetNumExpansion(ne);
        if(num<data->Size())
            emit Change();
    }
}

void ElementRow::ChangeExpansionPrice(double ep)
{
    if(dynamic_cast<Expansion*>(vg))
    {
        Expansion* expansion=dynamic_cast<Expansion*>(vg);
        expansion->SetExpansionPrice(ep);
        if(num<data->Size())
            emit Change();
    }
}
