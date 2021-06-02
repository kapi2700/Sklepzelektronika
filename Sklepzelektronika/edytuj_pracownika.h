/*!
* \file
* \brief Definicja klasy edytuj_pracownika
*
*Plik zawiera definicję klasy edytuj_pracownika
*/
#pragma once


#include <QWidget>
#include "ui_edytuj_pracownika.h"
#include <string>
#include <vector>
#include <mysql.h>
#include "dodaj_pracownika.h"

using namespace std;

class edytuj_pracownika : public QWidget
{
	Q_OBJECT

public:
	edytuj_pracownika(MYSQL* c, vector<string> data, QWidget* parent = Q_NULLPTR);
	~edytuj_pracownika();

	bool zakonczono;
	bool zapelnione;

	vector<string> dane;
private:
	Ui::edytuj_pracownika ui;
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
};
