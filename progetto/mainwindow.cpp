#include "mainwindow.h"
#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QString>
#include <QCloseEvent>
#include <QAction>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>
#include <string>

using std::string;
typedef unsigned int u_int;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), dat()
{
    setGeometry(180,100,1300,800);
    setWindowTitle(tr("QCharts"));
    openaction=new QAction(QIcon(":/images/open-file-icon.png"), tr("Apri"), this);
    openaction->setShortcuts(QKeySequence::Open);
    newaction=new QAction(QIcon(":/images/new-file-icon.png"),tr("Nuovo"), this);
    newaction->setShortcuts(QKeySequence::New);
    saveaction=new QAction(QIcon(":/images/save-icon.png"), tr("Salva"), this);
    saveaction->setShortcuts(QKeySequence::Save);
    saveasaction=new QAction(QIcon(":/images/save-as-icon.png"), tr("Salva con nome"), this);
    saveasaction->setShortcut(QKeySequence::SaveAs);
    closeaction=new QAction(QIcon(":/images/close-icon.png"),tr("Chiudi"),this);
    closeaction->setShortcuts(QKeySequence::Close);
    quitaction=new QAction(QIcon(":/images/exit-icon.png"), tr("Esci"), this);
    quitaction->setShortcuts(QKeySequence::Quit);
    barchart=new QAction(QIcon(":/images/barchart-icon.png"), tr("Grafico a barre"), this);
    linechart=new QAction(QIcon(":/images/linechart-icon.png"), tr("Grafico a linea"), this);
    pointchart=new QAction(QIcon(":/images/pointchart-icon.png"), tr("Grafico a punto"), this);
    add=new QAction(QIcon(":/images/add-icon.png"), tr("Aggiungi"), this);
    remove=new QAction(QIcon(":/images/remove-icon.png"), tr("Rimuovi"), this);
    insert=new QAction(QIcon(":/images/symbol-check-icon.png"), tr("Inserisci"), this);
    filemenu =new QMenu(tr("File"), this);
    filemenu->addAction(openaction);
    filemenu->addAction(newaction);
    filemenu->addAction(saveaction);
    filemenu->addAction(saveasaction);
    filemenu->addAction(closeaction);
    filemenu->addAction(quitaction);
    showmenu =new QMenu(tr("Visualizza"), this);
    showmenu->addAction(barchart);
    showmenu->addAction(linechart);
    showmenu->addAction(pointchart);
    editmenu= new QMenu(tr("Modifica"), this);
    editmenu->addAction(add);
    editmenu->addAction(remove);
    editmenu->addAction(insert);
    menuBar()->addMenu(filemenu);
    menuBar()->addMenu(showmenu);
    menuBar()->addMenu(editmenu);
    menuBar()->addSeparator();
    statusBar();
    file=addToolBar(tr("File"));
    file->addAction(openaction);
    file->addAction(newaction);
    file->addAction(saveaction);
    file->addAction(closeaction);
    chart=addToolBar(tr("Chart"));
    chart->addAction(barchart);
    chart->addAction(linechart);
    chart->addAction(pointchart);
    edit=addToolBar(tr("Modifica"));
    edit->addAction(add);
    edit->addAction(remove);
    edit->addAction(insert);
    add->setEnabled(false);
    remove->setEnabled(false);
    insert->setEnabled(false);
    barchart->setEnabled(false);
    linechart->setEnabled(false);
    pointchart->setEnabled(false);
    tab=new Tab(&dat, this);
    setCentralWidget(tab);
    connect(newaction, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(openaction, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(saveaction, SIGNAL(triggered()), this, SLOT(Save()));
    connect(saveasaction, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(closeaction, SIGNAL(triggered()), this, SLOT(CloseFile()));
    connect(closeaction, SIGNAL(triggered()), tab, SLOT(CloseAll()));
    connect(closeaction, SIGNAL(triggered()), this, SLOT(CloseAllAction()));
    connect(quitaction, SIGNAL(triggered()), this, SLOT(close()));
    connect(add, SIGNAL(triggered()), tab, SLOT(AddElement()));
    connect(remove, SIGNAL(triggered()), tab, SLOT(RemoveElement()));
    connect(insert, SIGNAL(triggered()), tab, SLOT(InsertToData()));
    connect(linechart, SIGNAL(triggered()), tab, SLOT(DrawLine()));
    connect(linechart, SIGNAL(triggered()), this, SLOT(ShowLine()));
    connect(barchart, SIGNAL(triggered()), tab, SLOT(DrawBar()));
    connect(barchart, SIGNAL(triggered()), this, SLOT(ShowBar()));
    connect(pointchart, SIGNAL(triggered()), tab, SLOT(DrawPoint()));
    connect(pointchart, SIGNAL(triggered()), this, SLOT(ShowPoint()));
    connect(tab, SIGNAL(Last()), this, SLOT(DeleteLast()));
    connect(tab, SIGNAL(NewRow()), this, SLOT(NewElement()));
    connect(tab, SIGNAL(InsertOk()), this, SLOT(InsertNew()));
    connect(tab, SIGNAL(Close()), this, SLOT(CloseAllAction()));
    statusBar()->showMessage(tr("Pronto"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::OpenXml(QString filename, Data& d)
{
    try
    {
        if(!filename.isEmpty())
        {
            QFile file(filename);
            QXmlStreamReader xmlreader(&file);
            file.open(QIODevice::ReadOnly);
                if(d.Size())
                {
                    d.DeleteAll();
                }
                while(!xmlreader.atEnd() && !xmlreader.hasError())
                {
                    QXmlStreamReader::TokenType token = xmlreader.readNext();
                    if(token==QXmlStreamReader::StartDocument)
                    {
                        continue;
                    }
                    if(xmlreader.isStartElement())
                    {
                        if(xmlreader.name()=="MainTitle")
                        {
                            string title="";
                            string author="";
                            string publication="";
                            double price=0;
                            while(!(xmlreader.tokenType()==xmlreader.EndElement))
                            {
                                if(xmlreader.name()=="Title")
                                {
                                    QString qtitle=xmlreader.readElementText();
                                    title=qtitle.toStdString();
                                }
                                if(xmlreader.name()=="Author")
                                {
                                    QString qauthor=xmlreader.readElementText();
                                    author=qauthor.toStdString();
                                }
                                if(xmlreader.name()=="Publication")
                                {
                                    QString qpublication=xmlreader.readElementText();
                                    publication=qpublication.toStdString();
                                }
                                if(xmlreader.name()=="FixedPrice")
                                {
                                    QString qprice=xmlreader.readElementText();
                                    price=qprice.toDouble();
                                }
                                xmlreader.readNext();
                            }
                            MainTitle* maintitle=new MainTitle(title, author, publication, price);
                            d.Add(*maintitle);
                        }
                        else
                        {
                            if(xmlreader.name()=="Expansion")
                            {
                                string title="";
                                string author="";
                                string publication="";
                                u_int nexp=0;
                                double eprice=0;
                                while(!(xmlreader.tokenType()==xmlreader.EndElement))
                                {
                                    if(xmlreader.name()=="Title")
                                    {
                                        QString qtitle=xmlreader.readElementText();
                                        title=qtitle.toStdString();
                                    }
                                    if(xmlreader.name()=="Author")
                                    {
                                        QString qauthor=xmlreader.readElementText();
                                        author=qauthor.toStdString();
                                    }
                                    if(xmlreader.name()=="Publication")
                                    {
                                        QString qpublication=xmlreader.readElementText();
                                        publication=qpublication.toStdString();
                                    }
                                    if(xmlreader.name()=="NumberExpansions")
                                    {
                                        QString qnexp=xmlreader.readElementText();
                                        nexp=qnexp.toUInt();
                                    }
                                    if(xmlreader.name()=="ExpansionPrice")
                                    {
                                        QString qeprice=xmlreader.readElementText();
                                        eprice=qeprice.toDouble();
                                    }
                                    xmlreader.readNext();
                                }
                                Expansion* expansion=new Expansion(title, author, publication, nexp, eprice);
                                d.Add(*expansion);
                            }
                        }
                    }
                }
                if(xmlreader.hasError() || d.IsEmpty())
                {
                    QString errore="";
                    if(!d.IsEmpty())
                    {
                        errore=xmlreader.errorString();
                        throw ErrorOpen(errore);
                    }
                    else
                    {
                        errore="I dati aperti non sono corretti!";
                        throw ErrorOpen(errore);
                    }
                    file.close();
                    d.DeleteAll();
                    fileopen="";
                }
                else
                {
                    fileopen=filename;
                    file.close();
                    barchart->setEnabled(true);
                    linechart->setEnabled(true);
                    pointchart->setEnabled(true);
                    insert->setEnabled(false);
                    remove->setEnabled(true);
                    add->setEnabled(true);
                    statusBar()->showMessage("Apertura del file", 300);
                    tab->Open();
                }

        }
    }
    catch(ErrorOpen e)
    {
        QMessageBox::critical(0, "Errore!", e.Error());

    }
}

void MainWindow::SaveXml(QFile& file)
{
    try
    {
        QXmlStreamWriter xmlWriter;
        xmlWriter.setDevice(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("QCharts");
        for(int i=0; i<dat.Size() && !xmlWriter.hasError(); i++)
        {
            Videogame* vg=dat[i];
            QString qtitle=QString::fromStdString((vg->GetName()));
            QString qauthor=QString::fromStdString((vg->GetAuthor()));
            QString qpublication=QString::fromStdString((vg->GetPublication()));
            if(dynamic_cast<MainTitle*>(dat[i]))
            {
                MainTitle* maintitle=dynamic_cast<MainTitle*>(dat[i]);
                double price=maintitle->GetFixedPrice();
                QString qprice=QString::number(price);
                xmlWriter.writeStartElement("MainTitle");
                xmlWriter.writeTextElement("Title", qtitle);
                xmlWriter.writeTextElement("Author", qauthor);
                xmlWriter.writeTextElement("Publication", qpublication);
                xmlWriter.writeTextElement("FixedPrice", qprice);
                xmlWriter.writeEndElement();
            }
            else
            {
                if(dynamic_cast<Expansion*>(dat[i]))
                {
                    Expansion* expansion=dynamic_cast<Expansion*>(dat[i]);
                    u_int nexp=expansion->GetNumExpansion();
                    double expp=expansion->GetExpansionPrice();
                    QString qnexp=QString::number(nexp);
                    QString qexpp=QString::number(expp);
                    xmlWriter.writeStartElement("Expansion");
                    xmlWriter.writeTextElement("Title", qtitle);
                    xmlWriter.writeTextElement("Author", qauthor);
                    xmlWriter.writeTextElement("Publication", qpublication);
                    xmlWriter.writeTextElement("NumberExpansions", qnexp);
                    xmlWriter.writeTextElement("ExpansionPrice", qexpp);
                    xmlWriter.writeEndElement();
                }
            }
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        if(xmlWriter.hasError())
        {
            file.close();
            throw ErrorSave();
        }
        else
        {
            statusBar()->showMessage("Salvataggio dei dati", 300);
            file.close();
        }
    }
    catch(ErrorSave es)
    {
        QMessageBox::warning(0, "Attenzione!", "Errore nel salvataggio dei dati!");
    }
}

void MainWindow::SaveAsClose(QCloseEvent * event)
{
    try
    {
        tab->setCurrentIndex(0);
        QString filename = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), "XML files (*.xml)", 0, QFileDialog::DontUseNativeDialog);
        if(!filename.isEmpty())
        {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly))
            {
                SaveXml(file);
                file.close();
                event->accept();
            }
            else
            {
                file.close();
                event->ignore();
                throw OnlyRead();
            }
        }
        else
            event->ignore();
    }
    catch(OnlyRead)
    {
        QMessageBox::warning(0, "Attenzione!", "Il file e aperto in mdoalità di sola lettura!");
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(dat.Size())
    {
        bool different=false;
        if(!fileopen.isEmpty())
        {
            Data datt;
            OpenXml(fileopen, datt);
            if(datt!=dat)
            {
                different=true;
            }
        }
        if(fileopen.isEmpty() || different)
        {
            QMessageBox msgBox;
            msgBox.setText("Il documento e' stato modificato.");
            msgBox.setInformativeText("Vuoi salvare le modifiche?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();
            if(fileopen.isEmpty())
                switch(ret){
                case QMessageBox::Save: SaveAsClose(event); break;
                case QMessageBox::Discard: event->accept(); break;
                case QMessageBox::Cancel: event->ignore(); break;
                default: break;
                }
            else
                switch(ret){
                case QMessageBox::Save: Save(); event->accept(); break;
                case QMessageBox::Discard: event->accept(); break;
                case QMessageBox::Cancel: event->ignore(); break;
                }
        }
        else
            event->accept();
    }
    else
        event->accept();
}

void MainWindow::NewFile()
{
    NewWindow* new_w=new NewWindow(this, &dat);
    connect(new_w, SIGNAL(Bar()), tab, SLOT(DrawBar()));
    connect(new_w, SIGNAL(Bar()), this, SLOT(ShowBar()));
    connect(new_w, SIGNAL(Line()), tab, SLOT(DrawLine()));
    connect(new_w, SIGNAL(Line()), this, SLOT(ShowLine()));
    connect(new_w, SIGNAL(Point()), tab, SLOT(DrawPoint()));
    connect(new_w, SIGNAL(Point()), this, SLOT(ShowPoint()));
    connect(new_w, SIGNAL(New()), tab, SLOT(Open()));
    connect(new_w, SIGNAL(New()), this, SLOT(CreateCorrect()));
    new_w->show();
}

void MainWindow::CloseAllAction()
{
    pointchart->setEnabled(false);
    barchart->setEnabled(false);
    linechart->setEnabled(false);
    insert->setEnabled(false);
    remove->setEnabled(false);
    add->setEnabled(false);
}

void MainWindow::CloseFile()
{
    try
    {
        if(dat.Size())
        {
            dat.DeleteAll();
            fileopen="";
            statusBar()->showMessage("Chiusura del file", 300);
        }
        else
            throw EmptyData(true);
    }
    catch(EmptyData empty)
    {
        if(empty.GetCloseEmpty())
            QMessageBox::warning(0, "Attenzione!", "Non ci sono dati da chiudere!");
    }
}

void MainWindow::CreateCorrect()
{
    add->setEnabled(true);
    remove->setEnabled(true);
    insert->setEnabled(false);
    pointchart->setEnabled(true);
    linechart->setEnabled(true);
    barchart->setEnabled(true);
    statusBar()->showMessage("Caricamento dati in corso..", 400);
    fileopen="";
}

void MainWindow::NewElement()
{
    add->setEnabled(false);
    insert->setEnabled(true);
}

void MainWindow::InsertNew()
{
    add->setEnabled(true);
    insert->setEnabled(false);
}

void MainWindow::OpenFile()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Scegli un file da aprire"), QDir::currentPath(), "XML files (*.xml)", 0, QFileDialog::DontUseNativeDialog);
    if(!filename.isNull())
    {
        tab->CloseAll();
    }
    OpenXml(filename, dat);
}

void MainWindow::Save()
{
    try
    {
        if(dat.Size())
        {
            if(!fileopen.isEmpty())
            {
                QFile file(fileopen);
                if (file.open(QIODevice::WriteOnly))
                {
                    SaveXml(file);
                }
                else
                {
                    QMessageBox::warning(0, "Attenzione!", "Il file è aperto in modalità di sola lettura!");
                }
                file.close();
            }
            else
            {
                tab->setCurrentIndex(0);
                QString filename = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), "XML files (*.xml)", 0, QFileDialog::DontUseNativeDialog);
                if(!filename.isEmpty())
                {
                    QFile file(filename);
                    if (file.open(QIODevice::WriteOnly))
                    {
                        SaveXml(file);
                        fileopen=filename;
                        file.close();
                    }
                    else
                    {
                        file.close();
                        throw OnlyRead();
                    }
                }
            }
        }
        else
        {
            throw EmptyData(true);
        }
    }
    catch(OnlyRead o)
    {
        QMessageBox::warning(0, "Attenzione!", "Il file e aperto in mdoalità di sola lettura!");

    }
    catch(EmptyData e)
    {
        if(e.GetCloseEmpty())
        {
            QMessageBox::warning(0, "Attenzione!", "Non ci sono dati da salvare!");
        }
    }
}

void MainWindow::SaveAs()
{
    try
    {
        if(dat.Size())
        {
            tab->setCurrentIndex(0);
            QString filename = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), "XML files (*.xml)", 0, QFileDialog::DontUseNativeDialog);
            if(!filename.isEmpty())
            {
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly))
                {
                    SaveXml(file);
                    file.close();
                    fileopen=filename;
                }
                else
                {
                    file.close();
                    throw OnlyRead();
                }

            }
        }
        else
        {
            throw(EmptyData(true));
        }
    }
    catch(OnlyRead o)
    {
        QMessageBox::warning(0, "Attenzione!", "Il file e aperto in mdoalità di sola lettura!");
    }
    catch(EmptyData e)
    {
        if(e.GetCloseEmpty())
        {
            QMessageBox::warning(0, "Attenzione!", "Non ci sono dati da salvare!");
        }
    }
}

void MainWindow::DeleteLast()
{
    add->setEnabled(true);
    remove->setEnabled(true);
    insert->setEnabled(false);
}

void MainWindow::ShowBar()
{
    barchart->setEnabled(false);
    linechart->setEnabled(true);
    pointchart->setEnabled(true);
}

void MainWindow::ShowLine()
{
    barchart->setEnabled(true);
    linechart->setEnabled(false);
    pointchart->setEnabled(true);

}

void MainWindow::ShowPoint()
{
    barchart->setEnabled(true);
    linechart->setEnabled(true);
    pointchart->setEnabled(false);

}
