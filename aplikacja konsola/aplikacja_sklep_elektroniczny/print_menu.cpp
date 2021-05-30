#include <iostream>

using namespace std;

void print_menu_wlasciciel() {
	cout << "Dostepne opcje:" << endl
		<< "k - lista klientow" << endl
		<< "t - lista transakcji" << endl
		<< "p - lista produktow" << endl
		<< "w - lista pracownikow" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - wyloguj sie z bazy danych" << endl;
}

void print_menu_sprzedawca() {
	cout << "Dostepne opcje:" << endl
		<< "k - lista klientow" << endl
		<< "t - lista transakcji" << endl
		<< "p - lista produktow" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - wyloguj sie z bazy danych" << endl;
}

void print_menu_magazynier() {
	cout << "Dostepne opcje:" << endl
		<< "p - lista produktow" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - wyloguj sie z bazy danych" << endl;
}

void print_menu_klienci() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista klientow" << endl
		<< "c - dodaj nowego klienta" << endl
		<< "n - dodaj NIP klientowi" << endl
		<< "t - dodaj telefon klientowi" << endl
		<< "u - usun dane klienta" << endl
		<< "a - modyfikuj dane zamieszkania klienta" << endl
		<< "k - modyfikuj telefon klienta" << endl
		<< "d - modyfikuj imie, nazwisko, email lub opis klienta" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}

void print_menu_produkty_W() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista produktow" << endl
		<< "a - dodaj nowy produkt do asortymentu" << endl
		<< "b - dodaj nowa kategorie produktow" << endl
		<< "e - edytuj dane produktu" << endl
		<< "d - zaaktualizuj liczbe sztuk asortymentu" << endl
		<< "t - rozpocznij nowa transakcje" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}

void print_menu_produkty_S() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista produktow" << endl
		<< "t - rozpocznij now¹ transakcje" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}

void print_menu_produkty_M() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista produktow" << endl
		<< "d - zaaktualizuj liczbe sztuk asortymentu" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}

void print_menu_transakcje() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista transakcji" << endl
		<< "s - wyswietl szczegoly transakcji" << endl
		<< "r - reklamacja transakcji" << endl
		<< "d - dodaj date platnosci" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}

void print_menu_pracownicy() {
	cout << "Dostepne opcje:" << endl
		<< "l - lista pracownikow" << endl
		<< "n - zatrudnij nowego pracownika" << endl
		<< "z - zwolnij pracownika" << endl
		<< "a - modyfikuj dane pracownika" << endl
		<< "m - wyswietl to menu" << endl
		<< "q - powrot" << endl;
}