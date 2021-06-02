/*!
* \file
* \brief Definicja klasy bazadanych
*
*Plik zawiera definicję klasy bazadanych
*/
#pragma once


#include <qstring.h>
#include <mysql.h>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>

#include "sha256.h"

using namespace std;

class bazadanych
{
public:
	QString nazwa;
	QString rola;
	int stanowisko;

	string login;

	MYSQL* conn;

	int probylogowania = 0;

	/**
	 * Logowanie do bazy danych.
	 * 
	 * \param _login - login
	 * \param _pass - niezahaszowane haslo
	 * \return zwraca zahaszowane haslo
	 */
	string connect_database(const char* _login, const char* _pass);
	/**
	 * Inicjalizuje dane osoby zalogowanej.
	 * 
	 * \return id osoby zalogowanej
	 */
	int dane_zalogowanego();


	/**
	 * Metoda zaglądająca do bazy danych aby odczytac dane pracownikow.
	 *
	 * \return odczytane dane pracownikow
	 */
	vector<vector<string>> wyswietl_pracownikow();
	
	
	/**
	 * Metoda zaglądająca do bazy danych aby odczytac dane produktow.
	 *
	 * \return odczytane dane produktow
	 */
	vector<vector<string>> wyswietl_liste_produktow();
	
	/**
	 * Metoda zaglądająca do bazy danych aby odczytac dane klientow.
	 *
	 * \return odczytane dane klientow
	 */
	vector<vector<string>> wyswietl_liste_klientow();

	/**
	 * Metoda zaglądająca do bazy danych aby odczytac tranzakcje.
	 * 
	 * \return odczytane dane tranzakcji
	 */
	vector<vector<string>> wyswietl_transakcje();
};

