#include "inputline.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>

InputLine::InputLine(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* inputline=new QHBoxLayout();
    title=new QLineEdit();
    author=new QLineEdit();
    publication=new QLineEdit();
    combo=new QComboBox();
    combo->insertItem(1, "Videogioco principale");
    combo->insertItem(2, "Espansioni/DLC");
    combo->setCurrentIndex(0);
    fixedprice=new QDoubleSpinBox();
    fixedprice->setValue(0.0);
    fixedprice->setMinimum(0.0);
    fixedprice->setMaximum(200.0);
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
    inputline->addWidget(title);
    inputline->addWidget(author);
    inputline->addWidget(publication);
    inputline->addWidget(combo);
    inputline->addWidget(fixedprice);
    inputline->addWidget(numexpansion);
    inputline->addWidget(expansionprice);
    setLayout(inputline);
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(Change(int)));
}

QString InputLine::GetTitle() const
{
    return title->text();
}

QString InputLine::GetAuthor() const
{
    return author->text();
}

QString InputLine::GetPublication() const
{
    return publication->text();
}

double InputLine::GetFixedPrice() const
{
    return fixedprice->value();
}

int InputLine::GetNumExpansion() const
{
    return numexpansion->value();
}

double InputLine::GetExpansionPrice() const
{
    return expansionprice->value();
}

void InputLine::Change(int i)
{
    if(i==0)
    {
        fixedprice->setEnabled(true);
        numexpansion->setEnabled(false);
        expansionprice->setEnabled(false);
        numexpansion->setValue(0);
        expansionprice->setValue(0);
    }
    else
    {
        if(i==1)
        {
            fixedprice->setEnabled(false);
            numexpansion->setEnabled(true);
            expansionprice->setEnabled(true);
            fixedprice->setValue(0);
        }
    }
}

bool InputLine::IsMainTitle() const
{
    return combo->currentIndex()==0;
}

bool InputLine::IsExpansion() const
{
    return combo->currentIndex()==1;
}
