#include "edytuj_pracownika.h"

edytuj_pracownika::edytuj_pracownika(MYSQL* c, vector<string> data, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	zakonczono = false;
	zapelnione = false;
	dane = data;

	conn = c;

	connect(ui.edytuj_btn, &QPushButton::released, this, &edytuj_pracownika::edytuj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &edytuj_pracownika::anuluj);
}

edytuj_pracownika::~edytuj_pracownika()
{
}


void edytuj_pracownika::edytuj()
{
	string _imie = dane[1];
	string _nazwisko = dane[2];

	_imie = "\"" + _imie + "\"";
	_nazwisko = "\"" + _nazwisko + "\"";

	string _pole;
	string _edit = ui.nowa_wartosc_txt->text().toUtf8().constData();

	_pole = ui.dane_do_modyfikacji_list->currentItem()->text().toUtf8().constData();

	if (_pole == "haslo")
	{
		if (!analizuj_haslo(_edit))
		{
			ui.blad_lbl->setText("Haslo nie spelnia wymagan");
			return;
		}
		SHA256 haszuj;
		_edit = "\"" + haszuj(_edit) + "\"";
		_pole = "\"haslo_zaszyfrowane\"";
	}
	else
	{
		_edit = "\"" + _edit + "\"";
		_pole = "\"" + _pole + "\"";
	}
	
	if (_edit != "")
	{
		string zapytanie = "call modif_worker(" + _imie + "," + _nazwisko + "," + _pole + "," + _edit + ");";
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
	else
	{
		ui.blad_lbl->setText("Wartosc nie moze byc pusta");
	}
}

void edytuj_pracownika::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
	return;
}

