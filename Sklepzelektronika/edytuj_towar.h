#pragma once

/*!
* \file
* \brief Definicja klasy edytuj_towar
*
*Plik zawiera definicję klasy edytuj_towar
*/

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

	void indeks(int i);
private:
	Ui::edytuj_towar ui;
	MYSQL* conn;

	void edytuj();
	void anuluj();
	void aktualizujilosc();
};
