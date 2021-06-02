/*!
* \file
* \brief Definicja klasy dodaj_pracownika
*
*Plik zawiera definicję klasy dodaj_pracownika
*/
#pragma once


#include <QWidget>
#include "ui_dodaj_pracownika.h"
#include <vector>
#include <mysql.h>
#include <string>
#include "sha256.h"

using namespace std;

class dodaj_pracownika : public QWidget
{
	Q_OBJECT

public:
	dodaj_pracownika(MYSQL* c, QWidget* parent = Q_NULLPTR);
	~dodaj_pracownika();

	bool zakonczono;
	bool zapelnione;

private:
	Ui::dodaj_pracownika ui;
	MYSQL* conn;

	/**
	 * Dodaje pracownika.
	 * 
	 */
	void dodaj();
	/**
	 * Anuluje dzialania w oknie.
	 * 
	 */
	void anuluj();
};


bool analizuj_haslo(string passwd);
