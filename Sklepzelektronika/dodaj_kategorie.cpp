#include "dodaj_kategorie.h"



dodaj_kategorie::dodaj_kategorie(MYSQL* c, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	conn = c;

	zapelnione = false;
	zakonczono = false;

	connect(ui.dodaj_btn, &QPushButton::released, this, &dodaj_kategorie::dodaj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &dodaj_kategorie::anuluj);
}

dodaj_kategorie::~dodaj_kategorie()
{
	zakonczono = true;
	zapelnione = false;
}

void dodaj_kategorie::dodaj()
{
	string _nazwa_kat = ui.nazwa_txt->text().toUtf8().constData();
	string _nazwa[5], _rzut[5];
	bool rzut[5];

	_nazwa[0] = ui.cecha1_txt->text().toUtf8().constData();
	_nazwa[1] = ui.cecha2_txt->text().toUtf8().constData();
	_nazwa[2] = ui.cecha3_txt->text().toUtf8().constData();
	_nazwa[3] = ui.cecha4_txt->text().toUtf8().constData();
	_nazwa[4] = ui.cecha5_txt->text().toUtf8().constData();

	rzut[0] = ui.checkBox->isChecked();
	rzut[1] = ui.checkBox_2->isChecked();
	rzut[2] = ui.checkBox_3->isChecked();
	rzut[3] = ui.checkBox_4->isChecked();
	rzut[4] = ui.checkBox_5->isChecked();
	for (int i = 0; i < 5; i++)
	{
		if (_nazwa[i] != "")
		{
			_nazwa[i] = "\"" + _nazwa[i] + "\"";
		}
		else _nazwa[i] = "NULL";

		if (rzut[i])
		{
			_rzut[i] = "1";
		}
		else
		{
			_rzut[i] = "0";
		}
	}
	_nazwa_kat = "\"" + _nazwa_kat + "\"";

	string zapytanie = "INSERT INTO cechy (nazwa_kategorii,nazwa_1,rzut_na_liczbe_1,nazwa_2,rzut_na_liczbe_2,nazwa_3,rzut_na_liczbe_3,";
	zapytanie += "nazwa_4,rzut_na_liczbe_4,nazwa_5,rzut_na_liczbe_5) VALUES (" + _nazwa_kat;
	for (int i = 0; i < 5; ++i) zapytanie = zapytanie + "," + _nazwa[i] + "," + _rzut[i];
	zapytanie += ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		zakonczono = true;
		zapelnione = true;
		hide();
		return;
	}
	else {
		zakonczono = true;
		zapelnione = false;
		hide();
		return;
	}
}

void dodaj_kategorie::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
}
