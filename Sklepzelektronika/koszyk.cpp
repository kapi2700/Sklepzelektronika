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
}

koszyk::~koszyk()
{
}

void koszyk::faktura()
{
	
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
	}

	ui.stackedWidget->setCurrentIndex(2);
}

void koszyk::sprawdzKlienta()
{
}

void koszyk::zakoncz()
{
	string zapytanie = "INSERT INTO transakcje (id_klienta,id_pracownika,data_sprzedazy) VALUES (" + _id_klienta + ",\"" + _id_pracownika + "\",now());";
	int status = mysql_query(conn, zapytanie.c_str());


}

void koszyk::anuluj()
{
}
