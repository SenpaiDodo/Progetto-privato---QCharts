#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QString>
#include <QCloseEvent>
#include <QAction>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "newwindow.h"
#include "data.h"
#include "error.h"
#include "tab.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString fileopen;
    Data dat;
    Tab* tab;
    QAction* newaction;
    QAction* openaction;
    QAction* saveaction;
    QAction* saveasaction;
    QAction* closeaction;
    QAction* quitaction;
    QAction* barchart;
    QAction* linechart;
    QAction* pointchart;
    QAction* add;
    QAction* remove;
    QAction* insert;
    QMenu* filemenu;
    QMenu* showmenu;
    QMenu* editmenu;
    QToolBar* file;
    QToolBar* chart;
    QToolBar* edit;
    void OpenXml(QString filename, Data& d);
    void SaveXml(QFile& file);
    void SaveAsClose(QCloseEvent* event);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
     virtual void closeEvent(QCloseEvent* event);

private  slots:
     void NewFile();
     void CloseAllAction();
     void CloseFile();
     void CreateCorrect();
     void NewElement();
     void InsertNew();
     void OpenFile();
     void Save();
     void SaveAs();
     void DeleteLast();
     void ShowBar();
     void ShowLine();
     void ShowPoint();
};

#endif // MAINWINDOW_H
