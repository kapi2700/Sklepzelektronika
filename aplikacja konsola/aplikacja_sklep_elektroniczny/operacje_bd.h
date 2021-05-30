#pragma once
#include <mysql.h>
#include <string>

MYSQL* connect_database(MYSQL* conn, std::string &_login);

void wyswietl_liste_klientow(MYSQL *conn);
void dodaj_klienta(MYSQL *conn);
void dodaj_nip(MYSQL* conn);
void dodaj_telefon(MYSQL* conn);
void usun_klienta(MYSQL* conn);
void edytuj_adres_klienta(MYSQL* conn);
void edytuj_telefon_klienta(MYSQL* conn);
void edytuj_personalia_klienta(MYSQL* conn);

void wyswietl_liste_transakcji(MYSQL* conn);
void wyswietl_szczegoly_transakcji(MYSQL* conn);
void reklamuj_transakcje(MYSQL* conn);
void dodaj_date_platnosci(MYSQL* conn);

void wyswietl_liste_produktow(MYSQL* conn);
void dodaj_nowy_produkt(MYSQL* conn);
void dodaj_nowa_kategorie(MYSQL* conn);
void edytuj_produkt(MYSQL* conn);
void aktualizuj_liczbe_produktu(MYSQL* conn);
void przeprowadz_transakcje(MYSQL* conn, std::string _id_pracownika);

void wyswietl_liste_pracownikow(MYSQL* conn);
void dodaj_pracownika(MYSQL* conn);
void zwolnij_pracownika(MYSQL* conn);
void edytuj_pracownika(MYSQL* conn);

bool check_sql_injection(std::string napis, bool litery, bool cyfry, bool spacja, bool kropka, bool myslnik, bool malpa);
bool analizuj_date(std::string _data);
bool analizuj_haslo(std::string passwd);