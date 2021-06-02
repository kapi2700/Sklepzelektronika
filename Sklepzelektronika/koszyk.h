/*!
* \file
* \brief Definicja klasy koszyk
*
*Plik zawiera definicję klasy koszyk
*/
#pragma once


#include <QWidget>
#include "ui_koszyk.h"
#include <vector>
#include <string>
#include <mysql.h>

using namespace std;

class koszyk : public QWidget
{
	Q_OBJECT

public:
	koszyk(int id, vector<string> produkty, vector<int> ilosc, MYSQL* c, QWidget* parent = Q_NULLPTR);
	~koszyk();

	bool zakonczono;
	bool zapelnione;

	vector<string> dane;
	vector<int> ile;
	string _id_klienta;
	string _id_pracownika;
private:
	Ui::koszyk ui;
	MYSQL* conn;

	/**
	 * Daje mozliwosc wprowadzenia danych klienta przed dokonaniem tranzakcji.
	 * 
	 */
	void faktura();
	/**
	 * Tworzy tranzakcje, bez podawania danych klienta.
	 * 
	 */
	void paragon();
	/**
	 * Sprawdza czy klient istnieje.
	 * 
	 */
	void sprawdzKlienta();
	/**
	 * Zakańcza kupno produktow, tworzy tranzakcje.
	 * 
	 */
	void zakoncz();
	/**
	 * Anuluje kupowanie produktow.
	 * 
	 */
	void anuluj();
};
