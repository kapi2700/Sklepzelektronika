#include "edytuj_towar.h"



edytuj_towar::edytuj_towar(MYSQL* c, vector<string> data, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.setupUi(this);

	zakonczono = false;
	zapelnione = false;
	dane = data;

	conn = c;

	connect(ui.edytuj_btn, &QPushButton::released, this, &edytuj_towar::edytuj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &edytuj_towar::anuluj);
	connect(ui.edytuj_btn_2, &QPushButton::released, this, &edytuj_towar::aktualizujilosc); //aktualizuj ilosc
	connect(ui.anuluj_btn_2, &QPushButton::released, this, &edytuj_towar::anuluj);

	ui.ilosc_lbl->setText(QString::fromUtf8(data[2].c_str()));
}

edytuj_towar::~edytuj_towar()
{
}

void edytuj_towar::indeks(int i)
{
	ui.stackedWidget->setCurrentIndex(i);
}

void edytuj_towar::edytuj()
{
	string _produkt = dane[1];
	_produkt = "\"" + _produkt + "\"";

	string _param;
	string _edit = ui.nowa_wartosc_txt->text().toUtf8().constData();

	_param = ui.dane_do_modyfikacji_list->currentItem()->text().toUtf8().constData();

	_edit = "\"" + _edit + "\"";
	_param = "\"" + _param + "\"";

	if (_edit != "")
	{
		string zapytanie = "call edit_product(" + _produkt + "," + _param + "," + _edit + ");";
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

void edytuj_towar::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	hide();
	return;
}

void edytuj_towar::aktualizujilosc()
{
	string _produkt = dane[1];
	_produkt = "\"" + _produkt + "\"";
	string _liczba = ui.ilosc_txt->text().toUtf8().constData();
	_liczba = "\"" + _liczba + "\"";


	string zapytanie = "call zakup_produkt(" + _produkt + "," + _liczba + ");";
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
