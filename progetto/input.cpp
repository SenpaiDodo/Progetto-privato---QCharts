#include "input.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMessageBox>
#include <string>

using std::string;

Input::Input(QWidget* parent, Data *d, int c) : QDialog(parent), dat(d), count(c)
{
    setWindowTitle("Inserimento dati");
    setModal(true);
    resize(1400, 600);
    QDialog::reject();
    QHBoxLayout* invoice=new QHBoxLayout();
    QLabel* title=new QLabel("Titolo");
    QLabel* author=new QLabel("Autore");
    QLabel* publication=new QLabel("A. Pubblicazione");
    QLabel* type=new QLabel("Tipo");
    QLabel* price=new QLabel("Prezzo fisso");
    QLabel* numexpansion=new QLabel("N. Espansioni/DLC");
    QLabel* expansionprice=new QLabel("Prezzo espansioni/DLC");
    invoice->addWidget(title);
    invoice->addWidget(author);
    invoice->addWidget(publication);
    invoice->addWidget(type);
    invoice->addWidget(price);
    invoice->addWidget(numexpansion);
    invoice->addWidget(expansionprice);
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addLayout(invoice);
    QVBoxLayout* container=new QVBoxLayout();
    QWidget *viewport = new QWidget();
    for(int i=0; i<count; i++)
    {
        InputLine* input=new InputLine(this);
        container->addWidget(input);
        list.push_back(input);
    }
    viewport->setLayout(container);
    area=new QScrollArea();
    area->setWidgetResizable(true);
    area->setWidget(viewport);
    layout->addWidget(area);
    QDialogButtonBox* button=new QDialogButtonBox;
    QPushButton* ok=new QPushButton("ok");
    QPushButton* cancel=new QPushButton("Annulla");
    ok->setFont(QFont("Times", 18, QFont::Black));
    cancel->setFont(QFont("Times", 18, QFont::Black));
    button->addButton(ok, QDialogButtonBox::ActionRole);
    button->addButton(cancel, QDialogButtonBox::ActionRole);
    layout->addWidget(button);
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ok, SIGNAL(clicked()), this, SLOT(Create()));
    connect(this, SIGNAL(Ok()), this, SLOT(close()));
    setLayout(layout);
}

bool Input::Isok() const
{
    bool ok=true;
    for(QList<InputLine*>::const_iterator it=list.begin(); it!=list.end() && ok; ++it)
    {
        if((*it)->GetTitle()==""||(*it)->GetAuthor()==""||(*it)->GetPublication()=="")
        {
            ok=false;
        }
    }
    for(QList<InputLine*>::const_iterator it=list.begin()+1; it!=list.end() && ok; it++)
    {
        for(QList<InputLine*>::ConstIterator ite=list.begin(); ite!=it && ok; ite++)
        {
            if(((*it)->GetTitle()==(*ite)->GetTitle()) && (*it)->GetAuthor()==(*ite)->GetAuthor() && (*it)->GetPublication()==(*ite)->GetPublication())
            {
                ok=false;
            }
        }
    }
    return ok;
}

void Input::Create(){
    try
    {
        if(!Isok())
            throw ErrorInput();
        else
        {
            if(dat && dat->Size())
                dat->DeleteAll();
            for(QList<InputLine*>::const_iterator it=list.begin(); it!=list.end(); ++it)
            {
                Videogame* v=0;
                string title=((*it)->GetTitle()).toStdString();
                string author=((*it)->GetAuthor()).toStdString();
                string publication=((*it)->GetPublication()).toStdString();

                if((*it)->IsMainTitle())
                {
                    double price=(*it)->GetFixedPrice();
                    v=new MainTitle(title, author, publication, price);
                }
                if((*it)->IsExpansion())
                {
                    u_int unit=(*it)->GetNumExpansion();
                    double price=(*it)->GetExpansionPrice();
                    v=new Expansion(title, author, publication, unit, price);
                }
                if(dat)
                    dat->Add(*v);
                emit Ok();
            }
        }
    }
    catch(ErrorInput i)
    {
        QMessageBox::critical(0, "Errore!", "Errore nei dati inseriti, e'' stato lasciato un campo vuoto o ripetuto un dato!");
    }
}
