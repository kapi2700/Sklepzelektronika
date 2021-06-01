#include "dodaj_towar.h"

dodaj_towar::dodaj_towar(MYSQL* c, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	conn = c;

	zapelnione = false;
	zakonczono = false;

	connect(ui.dodaj_btn, &QPushButton::released, this, &dodaj_towar::dodaj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &dodaj_towar::anuluj);
}

dodaj_towar::~dodaj_towar()
{
	zakonczono = true;
	zapelnione = false;
}

void dodaj_towar::dodaj()
{
	string zapytanie, _kategoria;
	_kategoria = ui.kategoria_txt->text().toUtf8().constData();
	_kategoria = "\"" + _kategoria + "\"";

	zapytanie = "SELECT count(*) FROM cechy WHERE nazwa_kategorii=" + _kategoria + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	if (result != 1)
	{
		ui.blad_lbl->setText("Niepoprawna nazwa kategorii");
		return;
	}
	else
	{
		string _cecha[5];
		string _id_kategorii;
		string _rzut[5];

		zapytanie = "SELECT nazwa_1,nazwa_2,nazwa_3,nazwa_4,nazwa_5,id_kategorii,rzut_na_liczbe_1,rzut_na_liczbe_2,rzut_na_liczbe_3,";
		zapytanie += "rzut_na_liczbe_4,rzut_na_liczbe_5 FROM cechy WHERE nazwa_kategorii=" + _kategoria + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			for (int i = 0; i < 5; ++i) {
				_cecha[i] = (row[i] == nullptr ? "null" : row[i]);
				_rzut[i] = (row[i + 6] == nullptr ? "null" : row[i + 6]);
			}
			_id_kategorii = row[5];

			string _nazwa = ui.kategoria_txt->text().toUtf8().constData();
			string _cena = ui.cena_txt->text().toUtf8().constData();
			string _vat = ui.vat_txt->text().toUtf8().constData();
			string _opis = ui.opis_txt->text().toUtf8().constData();
			string __cecha[5];
			__cecha[0] = ui.cecha1_txt->text().toUtf8().constData();
			__cecha[1] = ui.cecha2_txt->text().toUtf8().constData();
			__cecha[2] = ui.cecha3_txt->text().toUtf8().constData();
			__cecha[3] = ui.cecha4_txt->text().toUtf8().constData();
			__cecha[4] = ui.cecha5_txt->text().toUtf8().constData();
			for (int i = 0; i < 5; i++)
			{
				if (__cecha[i] != "")
					__cecha[i] = "\"" + __cecha[i] + "\"";
				else
					__cecha[i] = "NULL";
			}

			if (_nazwa != "")_nazwa = "\"" + _nazwa + "\"";
			if (_cena != "")_cena = "\"" + _cena + "\"";
			if (_vat != "")_vat = "\"" + _vat + "\"";
			if (_opis != "")_opis = "\"" + _opis + "\"";
			else _opis = "NULL";

			zapytanie = "INSERT INTO produkty (nazwa,liczba_sztuk_na_stanie,cena_jednostkowa,stawka_VAT,id_kategorii,cecha_1,cecha_2,cecha_3,cecha_4,cecha_5,opis) VALUES (";
			zapytanie = zapytanie + _nazwa + ",\"0\"," + _cena + "," + _vat + "," + _id_kategorii + ",";
			for (int i = 0; i < 5; ++i) zapytanie = zapytanie + __cecha[i] + ",";
			zapytanie = zapytanie + _opis + ");";
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
	}
}

void dodaj_towar::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
}
