#pragma once

#include <QWidget>
#include "ui_edytuj_klienta.h"
#include <vector>
#include <mysql.h>
#include <string>

using namespace std;

class edytuj_klienta : public QWidget
{
	Q_OBJECT

public:
	edytuj_klienta(MYSQL* c, vector<string> data, QWidget* parent = Q_NULLPTR);
	~edytuj_klienta();

	bool zakonczono;
	bool zapelnione;

	int rodzaj_edycji;
	vector<string> dane;
private:
	Ui::edytuj_klienta ui;
	MYSQL* conn;

	void edytuj_adres_klienta();
	void edytuj_telefon_klienta();
	void edytuj_personalia_klienta();
	void dodaj_telefon_klienta();

	void potwierdz();
	void anuluj();
};
