#include "Dodaj_klienta.h"

Dodaj_klienta::Dodaj_klienta(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	zapelnione = false;
	zakonczono = false;

	connect(ui.dodaj_btn, &QPushButton::released, this, &Dodaj_klienta::dodaj);
	connect(ui.anuluj_btn, &QPushButton::released, this, &Dodaj_klienta::anuluj);
}

Dodaj_klienta::~Dodaj_klienta()
{
}

void Dodaj_klienta::dodaj()
{
	zapelnione = false;

	QString wejscie;
	QByteArray wej;

	if (ui.imie_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.imie_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());


	if (ui.nazwisko_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.nazwisko_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());



	if (ui.email_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.email_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());


	if (ui.opis_txt->toPlainText().isEmpty())
	{
		dane.push_back("null");
	}
	else
	{
		wejscie = ui.opis_txt->toPlainText();
		wej = wejscie.toLocal8Bit();
		dane.push_back(wej.data());
	}


	if (ui.miejsc_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.miejsc_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());


	if (ui.dom_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.dom_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());



	if (ui.mieszkanie_txt->text().isEmpty())
	{
		dane.push_back("null");
	}
	else
	{
		wejscie = ui.mieszkanie_txt->text();
		wej = wejscie.toLocal8Bit();
		dane.push_back(wej.data());
	}

	if (ui.ul_txt->text().isEmpty())
	{
		dane.push_back("null");
	}
	else
	{
		wejscie = ui.ul_txt->text();
		wej = wejscie.toLocal8Bit();
		dane.push_back(wej.data());
	}

	if (ui.kod_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.kod_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());


	if (ui.nip_txt->text().isEmpty())
	{
		dane.push_back("null");
	}
	else
	{
		wejscie = ui.nip_txt->text();
		wej = wejscie.toLocal8Bit();
		dane.push_back(wej.data());
	}

	if (ui.kont_txt->text().isEmpty())
	{
		ui.niepoprawnedane_lbl->setText("Podano niepoprawne dane");
		return;
	}
	wejscie = ui.kont_txt->text();
	wej = wejscie.toLocal8Bit();
	dane.push_back(wej.data());

	if (ui.wew_txt->text().isEmpty())
	{
		dane.push_back("null");
	}
	else
	{
		wejscie = ui.wew_txt->text();
		wej = wejscie.toLocal8Bit();
		dane.push_back(wej.data());
	}
	
	for (int i = 0; i < dane.size(); i++)
	{
		if (dane[i] != "null")
		{
			dane[i] = ("\"" + dane[i] + "\"");
		}
	}
	
	
	zapelnione = true;
	zakonczono = true;
	this->hide();
}

void Dodaj_klienta::anuluj()
{
	zapelnione = false;
	zakonczono = true;
	this->hide();

}
