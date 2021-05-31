#pragma once

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

	void dodaj();
	void anuluj();
};
