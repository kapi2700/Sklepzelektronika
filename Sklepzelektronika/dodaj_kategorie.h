/*!
* \file
* \brief Definicja klasy dodaj_kategorie
*
*Plik zawiera definicję klasy dodaj_kategorie
*/
#pragma once


#include <QWidget>
#include "ui_dodaj_kategorie.h"
#include <mysql.h>
#include <string>
#include <vector>

using namespace std;

class dodaj_kategorie : public QWidget
{
	Q_OBJECT

public:
	dodaj_kategorie(MYSQL* c, QWidget* parent = Q_NULLPTR);
	~dodaj_kategorie();


	bool zakonczono;
	bool zapelnione;

private:
	Ui::dodaj_kategorie ui;
	MYSQL* conn;

	/**
	 * Dodaje kategorie.
	 * 
	 */
	void dodaj();
	/**
	 * Anuluje dzialanie w oknie.
	 * 
	 */
	void anuluj();
};
