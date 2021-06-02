/*!
* \file
* \brief Definicja klasy edytuj_towar
*
*Plik zawiera definicję klasy edytuj_towar
*/

#pragma once

#include <QWidget>
#include "ui_edytuj_towar.h"
#include <string>
#include <vector>
#include <mysql.h>

using namespace std;

class edytuj_towar : public QWidget
{
	Q_OBJECT

public:
	edytuj_towar(MYSQL* c, vector<string> data, QWidget *parent = Q_NULLPTR);
	~edytuj_towar();

	bool zakonczono;
	bool zapelnione;

	vector<string> dane;

	/**
	 * Zmienia widok w oknie.
	 * 
	 * \param i - ktory widok ma byc ustawiony
	 */
	void indeks(int i);
private:
	Ui::edytuj_towar ui;
	MYSQL* conn;

	/**
	 * Zatwierdza akcje w oknie.
	 * 
	 */
	void edytuj();
	/**
	 * Anuluje wszystkie akcje w oknie.
	 * 
	 */
	void anuluj();
	/**
	 * Aktualizuje ilosc towaru.
	 * 
	 */
	void aktualizujilosc();
};
