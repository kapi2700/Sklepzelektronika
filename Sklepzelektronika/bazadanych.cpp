#include "bazadanych.h"

string bazadanych::connect_database(const char* _login, const char* _pass)
{
    SHA256 haszuj;
    string zahaszowane = haszuj(_pass);
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", _login, zahaszowane.c_str(), "elektroniczny", 3306, NULL, 0);

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
    int status = mysql_query(conn, zapytanie.c_str());

    if (!status)
    {
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
    }
    else
    {
        return -1;
    }
    _tmp = (_imie + " " + _nazwisko);

    nazwa = QString::fromStdString(_tmp);

    int id = stoi(_id_pracownika);
    return id;
}

vector<vector<string>>  bazadanych::wyswietl_pracownikow()
{
    vector<string> pom;
    vector<vector<string>> ret;

    string zapytanie = "SELECT id_pracownika,imie,nazwisko,stanowisko FROM pracownicy";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 4; ++i) {
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
    
    string zapytanie = "SELECT * FROM dane_klientow;";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 13; ++i) {
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
    
    string zapytanie = "SELECT * FROM transakcje ORDER BY data_sprzedazy DESC;";
    int status = mysql_query(conn, zapytanie.c_str());
    if (!status) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < 6; ++i) {
                pom.push_back(row[i] == nullptr ? "NULL" : row[i]);
            }
            ret.push_back(pom);
            pom.clear();
        }
    }
    return ret;
}

