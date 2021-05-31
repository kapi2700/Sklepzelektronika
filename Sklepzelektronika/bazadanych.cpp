#include "bazadanych.h"

string bazadanych::connect_database(const char* _login, const char* _pass)
{
    SHA256 haszuj;
    string zahaszowane = haszuj(_pass);
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", _login, zahaszowane.c_str(), "elektroniczny", 3306, NULL, 0);
    //conn = mysql_real_connect(conn, "localhost", "root", "kapi2798", "elektroniczny", 3306, NULL, 0);

    login = _login;

    return zahaszowane;
}

int bazadanych::dane_zalogowanego()
{
    string _imie;
    string _nazwisko;
    string _id_pracownika;
    string _tmp;
    string _rola;

    string zapytanie = "SELECT imie,nazwisko,stanowisko,id_pracownika from pracownicy WHERE login=\"" + login + "\";";
    mysql_query(conn, zapytanie.c_str());

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    

    row = mysql_fetch_row(res);
    _imie = row[0];
    _nazwisko = row[1];
    _rola = row[2];
    _id_pracownika = row[3];



    rola = QString::fromStdString(_rola);

    if (strcmp(row[2], "Wlasciciel") == 0) stanowisko = 1;
    else if (strcmp(row[2], "Sprzedawca") == 0) stanowisko = 2;
    else if (strcmp(row[2], "Magazynier") == 0) stanowisko = 3;

    _tmp = (_imie + " " + _nazwisko);

    nazwa = QString::fromStdString(_tmp);
}

vector<vector<string>>  bazadanych::wyswietl_pracownikow()
{
    vector<string> pom;
    vector<vector<string>> ret;

    string zapytanie = "SELECT imie,nazwisko,stanowisko FROM pracownicy";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 3; ++i) {
                pom.push_back((row[i] == nullptr ? "NULL" : row[i]));
            }
            ret.push_back(pom);
            pom.clear();
        }
    }

    return ret;
}

vector<vector<string>> bazadanych::wyswietl_liste_produktow()
{
    vector<string> pom;
    vector<vector<string>> ret;

    string zapytanie = "SELECT nazwa_kategorii,nazwa,liczba_sztuk_na_stanie,cena_jednostkowa,stawka_VAT,nazwa_1,cecha_1,nazwa_2,cecha_2,nazwa_3,cecha_3,nazwa_4,cecha_4,nazwa_5,cecha_5,opis FROM produkty,cechy where produkty.id_kategorii = cechy.id_kategorii;";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 16; ++i) {
                pom.push_back(row[i] == nullptr ? "NULL" : row[i]);
            }
            ret.push_back(pom);
            pom.clear();
        }
    }

    return ret;
}


vector<vector<string>> bazadanych::wyswietl_liste_klientow()
{
    vector<string> pom;
    vector<vector<string>> ret;
    
    string zapytanie = "SELECT imie,nazwisko,email,miejscowosc,ulica,nr_domu,nr_mieszkania,kod_pocztowy,NIP,telefon,wewnetrzny FROM Klienci,Adresy,Dane podatkowe,Telefony";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 11; ++i) {
                pom.push_back(row[i] == nullptr ? "NULL" : row[i]);
            }
            ret.push_back(pom);
            pom.clear();
        }
    }
    return ret;
}




vector<vector<string>> bazadanych::wyswietl_transakcje()
{
    vector<string> pom;
    vector<vector<string>> ret;
    
    string zapytanie = "SELECT id_klienta,id_transakcji,nazwa,cena_calkowita,liczba_sztuk,id_pracownika,data_sprzedazy,data_platnosci FROM Klienci,Transakcje,Produkty,Szczegoly transakcji where (Klienci.id_klienta = Transakcje.id_klienta AND Produkty.id_produktu = Szczegoly transakcji.id_produktu);";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 8; ++i) {
                pom.push_back(row[i] == nullptr ? "NULL" : row[i]);
            }
            ret.push_back(pom);
            pom.clear();
        }
    }
    return ret;
}