#pragma once

/*!
* \file
* \brief Funkcje menu
*
*Plik zawiera funkcje uzywane 
*przy obsludze menu
*/

#include <mysql.h>
#include <string>

//menu glowne
void menu_wlasciciela(MYSQL *conn, std::string _id_pracownika);
void menu_sprzedawcy(MYSQL* conn, std::string _id_pracownika);
void menu_magazyniera(MYSQL* conn);

//podmenu
void menu_klientow(MYSQL *conn);
void menu_produktow_W(MYSQL* conn, std::string _id_pracownika);
void menu_produktow_S(MYSQL* conn, std::string _id_pracownika);
void menu_produktow_M(MYSQL* conn);
void menu_pracownikow(MYSQL* conn);
void menu_transakcji(MYSQL* conn);
