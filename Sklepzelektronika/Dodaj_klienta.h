#pragma once

/*!
* \file
* \brief Definicja klasy Dodaj_klienta
*
*Plik zawiera definicję klasy Dodaj_klienta
*/

#include <QWidget>
#include "ui_Dodaj_klienta.h"
#include <vector>
#include <string>

using namespace std;

class Dodaj_klienta : public QWidget
{
	Q_OBJECT

public:
	Dodaj_klienta(QWidget *parent = Q_NULLPTR);
	~Dodaj_klienta();

	vector<string> dane;
	bool zakonczono;
	bool zapelnione;
private:
	Ui::Dodaj_klienta ui;

	/**
	 * Dodaje klienta.
	 * 
	 */
	void dodaj();
	/**
	 * Anuluje dzialania w oknie.
	 * 
	 */
	void anuluj();
};
