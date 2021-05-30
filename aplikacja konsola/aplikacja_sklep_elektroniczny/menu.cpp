#include "menu.h"
#include "print_menu.h"
#include "operacje_bd.h"
#include <iostream>

using namespace std;

//done
void menu_wlasciciela(MYSQL *conn, string _id_pracownika) {
	string wybor= "1";
	print_menu_wlasciciel();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'k') {
			cout << "Menu klientow" << endl;
			menu_klientow(conn);
		}
		else if (wybor[0] == 't') {
			cout << "Menu transakcji" << endl;
			menu_transakcji(conn);
		}
		else if (wybor[0] == 'p') {
			cout << "Menu produktow" << endl;
			menu_produktow_W(conn,_id_pracownika);
		}
		else if (wybor[0] == 'w') {
			cout << "Menu pracownikow" << endl;
			menu_pracownikow(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_wlasciciel();
		}
		else{
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
}

//done
void menu_sprzedawcy(MYSQL* conn, string _id_pracownika) {
	string wybor = "1";
	print_menu_sprzedawca();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'k') {
			cout << "Menu klientow" << endl;
			menu_klientow(conn);
		}
		else if (wybor[0] == 't') {
			cout << "Menu transakcji" << endl;
			menu_transakcji(conn);
		}
		else if (wybor[0] == 'p') {
			cout << "Menu produktow" << endl;
			menu_produktow_S(conn, _id_pracownika);
		}
		else if (wybor[0] == 'm') {
			print_menu_sprzedawca();
		}
		else {
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
}

//done
void menu_magazyniera(MYSQL* conn) {
	string wybor = "1";
	print_menu_magazynier();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'p') {
			cout << "Menu produktow" << endl;
			menu_produktow_M(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_magazynier();
		}
		else {
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
}

//done
void menu_klientow(MYSQL* conn) {
	string wybor = "1";
	print_menu_klienci();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista klientow" << endl;
			wyswietl_liste_klientow(conn);
		}
		else if (wybor[0] == 'c') {
			cout << "Dodawanie nowego klienta" << endl;
			dodaj_klienta(conn);
		}
		else if (wybor[0] == 'n') {
			cout << "Dodawanie NIP istniejacemu klientowi" << endl;
			dodaj_nip(conn);
		}
		else if (wybor[0] == 't') {
			cout << "Dodawanie telefonu klientowi" << endl;
			dodaj_telefon(conn);
		}
		else if (wybor[0] == 'u') {
			cout << "Usuwanie danch klienta" << endl;
			usun_klienta(conn);
		}
		else if (wybor[0] == 'a') {
			cout << "Edycja danych adresowych klienta" << endl;
			edytuj_adres_klienta(conn);
		}
		else if (wybor[0]=='k'){
			cout << "Edycja danych kontaktowych klienta" << endl;
			edytuj_telefon_klienta(conn);
		}
		else if (wybor[0] == 'd') {
			cout << "Edycja danych personalnych klienta" << endl;
			edytuj_personalia_klienta(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_klienci();
		}
		else {
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

//done
void menu_transakcji(MYSQL* conn) {
	string wybor = "1";
	print_menu_transakcje();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista zawartych transakcji" << endl;
			wyswietl_liste_transakcji(conn);
		}
		else if (wybor[0] == 's') {
			cout << "Szczegoly wybranej transakcji" << endl;
			wyswietl_szczegoly_transakcji(conn);
		}
		else if (wybor[0] == 'r') {
			cout << "Reklamacja transakcji" << endl;
			reklamuj_transakcje(conn);
		}
		else if (wybor[0] == 'd') {
			cout << "Dodawanie daty platnosci" << endl;
			dodaj_date_platnosci(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_transakcje();
		}
		else{
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

//done
void menu_produktow_W(MYSQL* conn, string _id_pracownika) {
	string wybor= "1";
	print_menu_produkty_W();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista produktow" << endl;
			wyswietl_liste_produktow(conn);
		}
		else if (wybor[0] == 'a') {
			cout << "Dodawanie nowego produktu do asortymentu" << endl;
			dodaj_nowy_produkt(conn);
		}
		else if (wybor[0] == 'b') {
			cout << "Dodawanie nowej kategorii produktu" << endl;
			dodaj_nowa_kategorie(conn);
		}
		else if (wybor[0] == 'e') {
			cout << "Edycja danych produktu" << endl;
			edytuj_produkt(conn);
		}
		else if (wybor[0] == 'd') {
			cout << "Aktualizacja licby sztuk asortymentu" << endl;
			aktualizuj_liczbe_produktu(conn);
		}
		else if (wybor[0] == 't') {
			cout << "Nowa transakcja kupna-sprzedazy" << endl;
			przeprowadz_transakcje(conn,_id_pracownika);
		}
		else if (wybor[0] == 'm') {
			print_menu_produkty_W();
		}
		else{
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

//done
void menu_pracownikow(MYSQL* conn) {
	string wybor = "1";
	print_menu_pracownicy();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista pracownikow" << endl;
			wyswietl_liste_pracownikow(conn);
		}
		else if (wybor[0] == 'n') {
			cout << "Dodawanie nowego pracownika" << endl;
			dodaj_pracownika(conn);
		}
		else if (wybor[0] == 'z') {
			cout << "Zwolnienie pracownika" << endl;
			zwolnij_pracownika(conn);
		}
		else if (wybor[0] == 'a') {
			cout << "Edycja danych pracownika" << endl;
			edytuj_pracownika(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_pracownicy();
		}
		else{
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

//done
void menu_produktow_S(MYSQL* conn, string _id_pracownika) {
	string wybor = "1";
	print_menu_produkty_S();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista produktow" << endl;
			wyswietl_liste_produktow(conn);
		}
		else if (wybor[0] == 't') {
			cout << "Nowa transakcja kupna-sprzedazy" << endl;
			przeprowadz_transakcje(conn, _id_pracownika);
		}
		else if (wybor[0] == 'm') {
			print_menu_produkty_S();
		}
		else {
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

//done
void menu_produktow_M(MYSQL* conn) {
	string wybor = "1";
	print_menu_produkty_W();
	cout << "Twoj wybor: ";
	getline(cin, wybor);
	while (wybor[0] != 'q') {
		if (wybor[0] == 'l') {
			cout << "Lista produktow" << endl;
			wyswietl_liste_produktow(conn);
		}
		else if (wybor[0] == 'd') {
			cout << "Aktualizacja licby sztuk asortymentu" << endl;
			aktualizuj_liczbe_produktu(conn);
		}
		else if (wybor[0] == 'm') {
			print_menu_produkty_W();
		}
		else {
			cout << "Niepoprawna opcja, sprobuj ponownie." << endl;
		}
		cout << "Twoj wybor (m - opcje): ";
		getline(cin, wybor);
	}
	cout << "Powrot do menu wyboru tabeli" << endl;
}

