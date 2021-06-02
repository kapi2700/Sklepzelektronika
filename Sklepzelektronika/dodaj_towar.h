#pragma once

/*!
* \file
* \brief Definicja klasy dodaj_towar
*
*Plik zawiera definicję klasy dodaj_towar
*/

#include <QWidget>
#include "ui_dodaj_towar.h"
#include <vector>
#include <mysql.h>
#include <string>

using namespace std;

class dodaj_towar : public QWidget
{
	Q_OBJECT

public:
	dodaj_towar(MYSQL* c, QWidget* parent = Q_NULLPTR);
	~dodaj_towar();
	bool zakonczono;
	bool zapelnione;

private:
	Ui::dodaj_towar ui;
	MYSQL* conn;

	void dodaj();
	void anuluj();
};
