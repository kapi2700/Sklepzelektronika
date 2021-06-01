#include "dodaj_pracownika.h"

dodaj_pracownika::dodaj_pracownika(MYSQL* c, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	conn = c;

	zapelnione = false;
	zakonczono = false;

	connect(ui.dodaj_btn, &QPushButton::released, this, &dodaj_pracownika::dodaj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &dodaj_pracownika::anuluj);
}

dodaj_pracownika::~dodaj_pracownika()
{
	zakonczono = true;
	zapelnione = false;
}

void dodaj_pracownika::dodaj()
{
	string _imie = ui.imie_txt->text().toUtf8().constData();
	string _nazwisko = ui.nazwisko_txt->text().toUtf8().constData();
	string _login = ui.login_txt->text().toUtf8().constData();
	string _haslo = ui.haslo_txt->text().toUtf8().constData();
	string _haslo2 = ui.haslo2_txt->text().toUtf8().constData();
	string _stanowisko = ui.stanowisko_list->currentItem()->text().toUtf8().constData();
	if (_haslo != _haslo2)
	{
		ui.blad_lbl->setText("Bledne hasla");
		return;
	}

	if (!analizuj_haslo(_haslo))
	{
		ui.blad_lbl->setText("Haslo nie spelnia wymagan");
		return;
	}

	_imie = "\"" + _imie + "\"";
	_nazwisko = "\"" + _nazwisko + "\"";
	_login = "\"" + _login + "\"";
	_stanowisko = "\"" + _stanowisko + "\"";

	SHA256 haszuj;
	string _haslo_zahaszowane = haszuj(_haslo);
	string zapytanie = "call add_worker(" + _imie + "," + _nazwisko + "," + _login + ",\"" + _haslo_zahaszowane + "\"," + _stanowisko + ");";
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

void dodaj_pracownika::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
}


bool analizuj_haslo(string passwd) {
	//porzadek:  dlugosc, male lit., wielkie lit., cyfry, specjalne
	int info[5] = { 0,0,0,0,0 };
	for (char sign : passwd) {
		if (sign > 32 && sign < 127) {
			++info[0];
			if (sign >= 'a' && sign <= 'z') ++info[1];
			else if (sign >= 'A' && sign <= 'Z') ++info[2];
			else if (sign >= '0' && sign <= '9') ++info[3];
			else ++info[4];
		}
	}
	if (passwd.length() != info[0]) return false;
	else if ((info[0] < 8) || (info[0] > 32)) return false;
	else if (info[1] < 2) return false;
	else if (info[2] < 2) return false;
	else if (info[3] < 1) return false;
	else if (info[4] < 1) return false;
	else return true;
}