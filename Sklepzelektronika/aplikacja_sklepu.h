#ifndef APLIKACJA_SKLEPU_H
#define APLIKACJA_SKLEPU_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <mysql.h>
#include <Windows.h>
#include <qtableview>

#include "bazadanych.h"
#include "Model.h"
#include "model_towar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class aplikacja_sklepu; }
QT_END_NAMESPACE

class aplikacja_sklepu : public QMainWindow
{
    Q_OBJECT
public:
    aplikacja_sklepu(QWidget *parent = nullptr);
    ~aplikacja_sklepu();
private slots:
    void zaloguj();
    void pracownicy();
    void produkty();
    void klienci();
    void transakcje();
    void menu();
private:    
    Ui::aplikacja_sklepu *ui;
    Model pracownicy_model;
    model_towar towar_model;
    bazadanych baza;
};
#endif // APLIKACJA_SKLEPU_H
