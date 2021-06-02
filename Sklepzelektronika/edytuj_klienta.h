/*!
* \file
* \brief Definicja klasy edytuj_klienta
*
*Plik zawiera definicję klasy edytuj_klienta
*/
#pragma once


#include <QWidget>
#include "ui_edytuj_klienta.h"
#include <vector>
#include <mysql.h>
#include <string>

using namespace std;

class edytuj_klienta : public QWidget
{
	Q_OBJECT

public:
	edytuj_klienta(MYSQL* c, vector<string> data, QWidget* parent = Q_NULLPTR);
	~edytuj_klienta();

	bool zakonczono;
	bool zapelnione;

	int rodzaj_edycji;
	vector<string> dane;
private:
	Ui::edytuj_klienta ui;
	MYSQL* conn;

	/**
	 * Edycja adresu klienta.
	 * 
	 */
	void edytuj_adres_klienta();
	/**
	 * Edycja wybranego telefonu klienta.
	 * 
	 */
	void edytuj_telefon_klienta();
	/**
	 * Edycja personali klienta.
	 * 
	 */
	void edytuj_personalia_klienta();
	/**
	 * Dodawanie numeru telefonu do klienta.
	 * 
	 */
	void dodaj_telefon_klienta();

	/**
	 * Zatwierdza dzialania w oknie.
	 * 
	 */
	void potwierdz();
	/**
	 * Anuluje wszystkie akcje w oknie.
	 *
	 */
	void anuluj();
};
