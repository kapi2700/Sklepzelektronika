/*!
* \file
* \brief Definicja klasy aplikacja_sklepu
*
*Plik zawiera definicję klasy aplikacja_sklepu
*/
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
    /**
     * Logowanie do aplikacji i bazy danych.
     */
    void zaloguj();
    /**
     * Wyswietla pracownikow.
     * 
     */
    void pracownicy();
    /**
     * Wyswietla produkty.
     * 
     */
    void produkty();
    /**
     * Wyswietla klientow.
     * 
     */
    void klienci();
    /**
     * Wyswietla transakcje.
     * 
     */
    void transakcje();
    /**
     * Wyswietla menu.
     * 
     */
    void menu();
    /**
     * Wyszukuje pracownika z tabeli.
     * 
     */
    void szukaj_pracownicy();
    /**
     * Wyszukuje klienta z tabeli.
     * 
     */
    void szukaj_klienci();
    /**
     * Wyszukuje produkty z tabeli.
     * 
     */
    void szukaj_produkty();
    /**
     * Wyszukiwanie tranzakcji z tabeli.
     * 
     */
    void szukaj_transakcje();

    /**
     * Dodaje nowego klienta.
     * 
     */
    void dodaj_klienta_rel();
    /**
     * Wybiera klienta z tabeli.
     * 
     */
    void wybor_klienta();
    /**
     * Edytuje dane klienta.
     * 
     */
    void edytujKlienta();
    /**
     * Usuwanie klienta z bazy danych.
     * 
     */
    void usunKlienta();

    /**
     * Dodaje nowego pracownika.
     * 
     */
    void dodaj_Pracownika();
    /**
     * Edycja wybranego pracownika.
     * 
     */
    void edytujPracownika();
    /**
     * Wybor pracownika z tabeli.
     * 
     */
    void wybor_pracownika();

    /**
     * Wybor towaru z tabeli.
     * 
     */
    void wybor_towaru();
    /**
     * Edytuje dane towaru.
     * 
     */
    void edytujTowar();
    /**
     * Dodaje produkt do koszyka.
     * 
     */
    void dodajdokoszyka();
    /**
     * Pokaz zawartosc koszyka, prowadzi do wystawienia paragonu.
     * 
     */
    void pokazkoszyk();
    /**
     * Wybór tranzakcji z tabeli.
     * 
     */
    void wybor_transakcji();
    /**
     * Inicjalizacja tabeli ze szczegółami tranzakcji.
     * 
     */
    void szczegoly_transakcji();
    /**
     * Wybor szczegolow tranzakcji z tabeli.
     * 
     */
    void wybor_szczegolow();
    /**
     * Reklamacja towaru w tranzakcji.
     * 
     */
    void reklamuj();
    /**
     * Dodawanie nowej kategorii.
     * 
     */
    void dodaj_Kategorie();
    /**
     * Dodawanie nowego towaru.
     * 
     */
    void dodaj_Towar();
    /**
     * Aktualizuje ilosc towaru.
     * 
     */
    void aktualizuj_Towar();
    /**
     * Czyszczenie zawartosci koszyka.
     * 
     */
    void wyczysc_koszyk();

    /**
     * Usuwanie pracownika.
     *
     */
    void usunPracownika();
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

    int id_zalogowanej_osoby;
    
    bool zmiany_klienci;

    int wybrany_klient;
    int wybrany_pracownik;
    int wybrany_towar;
    int wybrana_transakcja;
    int wybrane_szczegoly;

    vector<string> wkoszyku;
    vector<int> iloscwkoszyku;
};
#endif // APLIKACJA_SKLEPU_H
