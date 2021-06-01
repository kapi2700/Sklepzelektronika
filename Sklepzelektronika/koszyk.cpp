#include "koszyk.h"

koszyk::koszyk(int id, vector<string> produkty, vector<int> ilosc, MYSQL* c, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ile = ilosc;
	dane = produkty;

	_id_pracownika = to_string(id);
	_id_klienta = "null";

	ui.stackedWidget->setCurrentIndex(0);

	connect(ui.paragon_btn, &QPushButton::released, this, &koszyk::paragon);
	connect(ui.faktura_btn, &QPushButton::released, this, &koszyk::faktura);

	connect(ui.Zatwierdz_klient_btn, &QPushButton::released, this, &koszyk::sprawdzKlienta);
	connect(ui.Anuluj_btn2, &QPushButton::released, this, &koszyk::anuluj);

	connect(ui.zatwierdz_btn, &QPushButton::released, this, &koszyk::zakoncz);
	connect(ui.anuluj_btn, &QPushButton::released, this, &koszyk::anuluj);

	conn = c;
}

koszyk::~koszyk()
{
	zakonczono = true;
	zapelnione = false;
}

void koszyk::faktura()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void koszyk::paragon()
{
	ui.produkty_table->setRowCount(ile.size());
	ui.produkty_table->setColumnCount(2);

	for (int i = 0; i < ile.size(); i++)
	{
		QTableWidgetItem* nazwa=new QTableWidgetItem(QString::fromStdString(dane[i]));
		ui.produkty_table->setItem(i, 0, nazwa);
		nazwa = new QTableWidgetItem(QString::fromStdString(to_string(ile[i])));
		ui.produkty_table->setItem(i, 1, nazwa);
	}

	ui.stackedWidget->setCurrentIndex(2);
}

void koszyk::sprawdzKlienta()
{
	string _imie = ui.imie_txt->text().toUtf8().constData();
	string _nazwisko = ui.nazw_txt->text().toUtf8().constData();
	string _nip = ui.nip_txt->text().toUtf8().constData();


	if (!_nip.empty())
	{
		_nip = "\"" + _nip + "\"";
		string zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		int status = mysql_query(conn, zapytanie.c_str());
		int result = -1;
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
			if (result == 1) {
				zapytanie = "SELECT id_klienta FROM dane_podatkowe WHERE nip=" + _nip + ";";
				status = mysql_query(conn, zapytanie.c_str());
				if (!status) {
					MYSQL_RES* res = mysql_store_result(conn);
					MYSQL_ROW row = mysql_fetch_row(res);
					_id_klienta = row[0];
				}
			}
			else
			{
				ui.blad_lbl->setText("Nie znaleziono klienta");
				return;
			}
		}
	}
	else
	{
		_imie = "\"" + _imie + "\"";
		_nazwisko = "\"" + _nazwisko + "\"";
		string zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		int status = mysql_query(conn, zapytanie.c_str());
		int result = -1;
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);


		if (result == 1) {
			zapytanie = "SELECT id_klienta FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
			int status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);
				_id_klienta = row[0];
			}
		}
		else
		{
			ui.blad_lbl->setText("Nie znaleziono klienta");
			return;
		}
	}
	paragon();
}

void koszyk::zakoncz()
{
	string zapytanie = "INSERT INTO transakcje (id_klienta,id_pracownika,data_sprzedazy) VALUES (" + _id_klienta + ",\"" + _id_pracownika + "\",now());";
	int status = mysql_query(conn, zapytanie.c_str());

	zapytanie = "SELECT id_transakcji FROM transakcje ORDER BY data_sprzedazy DESC LIMIT 1;";
	status = mysql_query(conn, zapytanie.c_str());

	if (!status)
	{
		string _id_transakcji;
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		_id_transakcji = row[0];

		string _produkt;
		string _ilosc;
		for (int i = 0; i < ile.size(); i++)
		{
			_produkt = dane[i];
			_ilosc = to_string(ile[i]);

			_ilosc = "\"" + _ilosc + "\"";
			_produkt = "\"" + _produkt + "\"";


			zapytanie = "call sprz_prod(\"" + _id_transakcji + "\"," + _produkt + "," + _ilosc + ");";
			status = mysql_query(conn, zapytanie.c_str());

			if (!status) {
				zakonczono = true;
				zapelnione = true;
				close();
			}
			else {
				ui.blad_lbl2->setText("Cos poszlo nie tak");
				return;
			}
		}
	}
}

void koszyk::anuluj()
{
	zakonczono = true;
	zapelnione = false;
	this->close();
}
