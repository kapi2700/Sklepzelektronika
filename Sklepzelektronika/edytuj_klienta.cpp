#include "edytuj_klienta.h"


edytuj_klienta::edytuj_klienta(MYSQL* c,vector<string> data, QWidget* parent)
	: QWidget(parent)
{
	conn = c;
	ui.setupUi(this);

	zakonczono = false;
	zapelnione = false;
	rodzaj_edycji = 0;
	dane = data;


	QString str = QString::fromUtf8(dane[5].c_str());
	ui.miejsc_lbl->setText(str);

	str = QString::fromUtf8(dane[7].c_str());
	ui.dom_lbl->setText(str);

	if (dane[8]=="NULL")
	{
		ui.miesz_lbl->setText("");
	}
	else
	{
		str = QString::fromUtf8(dane[8].c_str());
		ui.miesz_lbl->setText(str);
	}

	str = QString::fromUtf8(dane[6].c_str());
	ui.ul_lbl->setText(str);
	str = QString::fromUtf8(dane[9].c_str());
	ui.kod_lbl->setText(str);


	if (dane[11] == "NULL")
	{
		ui.kon_txt->setText("");
	}
	else
	{
		str = QString::fromUtf8(dane[11].c_str());
		ui.kon_txt->setText(str);
	}

	if (dane[12] == "NULL")
	{
		ui.wew_txt->setText("");
	}
	else
	{
		str = QString::fromUtf8(dane[12].c_str());
		ui.wew_txt->setText(str);
	}

	str = QString::fromUtf8(dane[1].c_str());
	ui.imie_txt->setText(str);

	str = QString::fromUtf8(dane[2].c_str());
	ui.nazwisko_txt->setText(str);

	if (dane[3]=="NULL")
	{
		ui.email_txt->setText("");
	}
	else
	{
		str = QString::fromUtf8(dane[3].c_str());
		ui.email_txt->setText(str);
	}

	if (dane[4] == "NULL")
	{
		ui.opis_txt->setText("");
	}
	else
	{
		str = QString::fromUtf8(dane[4].c_str());
		ui.opis_txt->setText(str);
	}

	connect(ui.potwirdz_btn, &QPushButton::released, this, &edytuj_klienta::potwierdz);
	connect(ui.anuluj_btn, &QPushButton::released, this, &edytuj_klienta::anuluj);
}

edytuj_klienta::~edytuj_klienta()
{
	zakonczono = true;
	zapelnione = false;
}

void edytuj_klienta::edytuj_adres_klienta()
{
	string _imie = dane[1];
	string _nazwisko = dane[2];
	string _nip = dane[10];
	string _miejscowosc = ui.miejsc_lbl->text().toUtf8().constData();
	string _nr_domu =ui.dom_lbl->text().toUtf8().constData();
	string _nr_mieszkania = ui.miesz_lbl->text().toUtf8().constData();
	string _ulica = ui.ul_lbl->text().toUtf8().constData();
	string _kod_pocztowy = ui.kod_lbl->text().toUtf8().constData();

	string zapytanie;
	int status;

	if (_imie != "-")_imie = "\"" + _imie + "\"";
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	if (_nip != "NULL")_nip = "\"" + _nip + "\"";
	if (_miejscowosc != "") _miejscowosc = "\"" + _miejscowosc + "\"";
	else _miejscowosc = "NULL";
	if (_nr_domu != "") _nr_domu = "\"" + _nr_domu + "\"";
	else _nr_domu = "NULL";
	if (_nr_mieszkania != "") _nr_mieszkania = "\"" + _nr_mieszkania + "\"";
	else _nr_mieszkania = "NULL";
	if (_ulica != "") _ulica = "\"" + _ulica + "\"";
	else _ulica = "NULL";
	if (_kod_pocztowy != "") _kod_pocztowy = "\"" + _kod_pocztowy + "\"";
	else _kod_pocztowy = "NULL";


	zapytanie = "call modif_adres(" + _imie + "," + _nazwisko + "," + _nip + "," + _miejscowosc + "," + _nr_domu + "," + _nr_mieszkania + ","
		+ _ulica + "," + _kod_pocztowy + ");";
	status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		zakonczono = true;
		zapelnione = true;
	}
	else {
		zakonczono = true;
		zapelnione = false;
	}
}

void edytuj_klienta::edytuj_telefon_klienta()
{
	string _imie = dane[1];
	string _nazwisko = dane[2];
	string _nip = dane[10];
	string _telefon = dane[11];
	string _wewnetrzny = dane[12];
	string __telefon = ui.kon_txt->text().toUtf8().constData();
	string __wewnetrzny = ui.wew_txt->text().toUtf8().constData();

	if (_imie != "-")_imie = "\"" + _imie + "\"";
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	if (_nip != "NULL")_nip = "\"" + _nip + "\"";
	_telefon = "\"" + _telefon + "\"";
	if (_wewnetrzny != "NULL") _wewnetrzny = "\"" + _wewnetrzny + "\"";
	if (__telefon != "") __telefon = "\"" + __telefon + "\"";
	else __telefon = "NULL";
	if (__wewnetrzny != "") __wewnetrzny = "\"" + __wewnetrzny + "\"";
	else __wewnetrzny = "NULL";

	string zapytanie = "call modif_tel(" + _imie + "," + _nazwisko + "," + _nip + "," + _telefon + "," + _wewnetrzny + "," + __telefon + ","
		+ __wewnetrzny + ");";

	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		zakonczono = true;
		zapelnione = true;
	}
	else {
		zakonczono = true;
		zapelnione = false;
	}
}

void edytuj_klienta::edytuj_personalia_klienta()
{
	string _imie = dane[1];
	string _nazwisko = dane[2];
	string _nip = dane[10];
	string __imie = ui.imie_txt->text().toUtf8().constData();
	string __nazwisko = ui.nazwisko_txt->text().toUtf8().constData();
	string __nip = ui.nip_txt->text().toUtf8().constData();
	string _email = ui.email_txt->text().toUtf8().constData();
	string _opis = ui.opis_txt->toPlainText().toUtf8().constData();

	if (_imie != "-")_imie = "\"" + _imie + "\"";
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	if (_nip != "NULL")_nip = "\"" + _nip + "\"";
	else _nip = "NULL";
	if (__imie != "") __imie = "\"" + __imie + "\"";
	else __imie = "NULL";
	if (__nazwisko != "") __nazwisko = "\"" + __nazwisko + "\"";
	else __nazwisko = "NULL";
	if (__nip != "") __nip = "\"" + __nip + "\"";
	else __nip = "NULL";
	if (_email != "") _email = "\"" + _email + "\"";
	else _email = "NULL";
	if (_opis != "") _opis = "\"" + _opis + "\"";
	else _opis = "NULL";


	string zapytanie = "call modif_client(" + _imie + "," + _nazwisko + "," + _nip + "," + __imie + "," + __nazwisko + "," + _email + "," + _opis + ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		zakonczono = true;
		zapelnione = true;
	}
	else {
		zakonczono = true;
		zapelnione = false;
	}
}

void edytuj_klienta::dodaj_telefon_klienta()
{
	string _imie = dane[1];
	string _nazwisko = dane[2];
	string _nip = dane[10];
	string _telefon = ui.dod_kon_txt->text().toUtf8().constData();
	string _wewnetrzny = ui.dod_wew_txt->text().toUtf8().constData();

	if (_imie != "-")_imie = "\"" + _imie + "\"";
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	if (_nip != "NULL")_nip = "\"" + _nip + "\"";
	else _nip = "NULL";
	if (_telefon != "") _telefon = "\"" + _telefon + "\"";
	else _telefon = "NULL";
	if (_wewnetrzny != "") _wewnetrzny = "\"" + _wewnetrzny + "\"";
	else _wewnetrzny = "NULL";

	string zapytanie = "call add_tel(" + _imie + "," + _nazwisko + "," + _nip + "," + _telefon + "," + _wewnetrzny + ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		zakonczono = true;
		zapelnione = true;
	}
	else {
		zakonczono = true;
		zapelnione = false;
	}
}

void edytuj_klienta::potwierdz()
{
	switch (ui.tabWidget->currentIndex())
	{
	case 0:
		edytuj_adres_klienta();
		hide();
		rodzaj_edycji = 1;
		return;
	case 1:
		edytuj_telefon_klienta();
		hide();
		rodzaj_edycji = 2;
		return;
	case 2:
		dodaj_telefon_klienta();
		hide();
		rodzaj_edycji = 3;
		return;
	case 3:
		edytuj_personalia_klienta();
		hide();
		rodzaj_edycji = 4;
		return;
	}
}

void edytuj_klienta::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
}
