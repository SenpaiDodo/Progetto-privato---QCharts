#ifndef INPUTLINE_H
#define INPUTLINE_H
#include <QWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QString>


class InputLine : public QWidget
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

public:
    explicit InputLine(QWidget *parent = nullptr);
    QString GetTitle() const;
    QString GetAuthor() const;
    QString GetPublication() const;
    double GetFixedPrice() const;
    int GetNumExpansion() const;
    double GetExpansionPrice() const;
    bool IsMainTitle() const;
    bool IsExpansion() const;

public slots:
    void Change(int i);
};

#endif // INPUTLINE_H
