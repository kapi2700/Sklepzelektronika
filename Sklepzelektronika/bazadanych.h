#pragma once

/*!
* \file
* \brief Definicja klasy bazadanych
*
*Plik zawiera definicję klasy bazadanych
*/

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

	string connect_database(const char* _login, const char* _pass);
	int dane_zalogowanego();

	vector<vector<string>> wyswietl_pracownikow();
	vector<vector<string>> wyswietl_liste_produktow();
	vector<vector<string>> wyswietl_liste_klientow();
	vector<vector<string>> wyswietl_transakcje();
};

