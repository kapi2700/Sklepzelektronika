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
#include "model_klienci.h"
#include "model_transakcje.h"
#include "Dodaj_klienta.h"
#include "edytuj_klienta.h"
#include "dodaj_pracownika.h"
#include "dodaj_towar.h"
#include "edytuj_pracownika.h"
#include "edytuj_towar.h"
#include "dodaj_kategorie.h"
#include "koszyk.h"

QT_BEGIN_NAMESPACE
namespace Ui { class aplikacja_sklepu; }
QT_END_NAMESPACE

class aplikacja_sklepu : public QMainWindow
{
    Q_OBJECT
public:
    aplikacja_sklepu(QWidget* parent = nullptr);
    ~aplikacja_sklepu();
private slots:
    void zaloguj();
    void pracownicy();
    void produkty();
    void klienci();
    void transakcje();
    void menu();
    void szukaj_pracownicy();
    void szukaj_klienci();
    void szukaj_produkty();
    void szukaj_transakcje();

    void dodaj_klienta_rel();
    void wybor_klienta();
    void edytujKlienta();
    void usunKlienta();

    void dodaj_Pracownika();
    void edytujPracownika();
    void wybor_pracownika();

    void wybor_towaru();
    void edytujTowar();
    void dodajdokoszyka();
    void pokazkoszyk();
    void dodaj_Kategorie();
    void dodaj_Towar();
    void aktualizuj_Towar();
private:
    Ui::aplikacja_sklepu* ui;
    Model* pracownicy_model;
    model_towar* towar_model;
    model_klienci* klienci_model;
    model_transakcje* transakcje_model;
    bazadanych baza;

    Dodaj_klienta* nowyKlient;
    edytuj_klienta* klient;

    dodaj_pracownika* nowyPracownik;
    edytuj_pracownika* pracownik;

    dodaj_towar* nowyTowar;
    edytuj_towar* towar;

    dodaj_kategorie* nowaKategoria;

    koszyk* kosz;

    int wybrany_klient;
    bool zmiany_klienci;

    int wybrany_pracownik;

    int id_zalogowanej_osoby;

    int wybrany_towar;

    vector<string> wkoszyku;
    vector<int> iloscwkoszyku;
};
#endif // APLIKACJA_SKLEPU_H
