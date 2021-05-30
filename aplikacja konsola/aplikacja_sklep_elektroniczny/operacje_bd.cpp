#include "operacje_bd.h"
#include "sha256.h"
#include <iostream>

using namespace std;

//done
MYSQL* connect_database(MYSQL* conn, string &_login) {
	string login;
	string haslo;
	int n_prob = 0;
	bool connected = false;
	while (!connected && n_prob < 3) {
		cout << "Login: ";
		getline(cin, login);
		cout << "Haslo: ";
		getline(cin, haslo);
		SHA256 haszuj;
		string zahaszowane = haszuj(haslo);
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", login.c_str(), zahaszowane.c_str(), "sklep elektroniczny", 3306, NULL, 0);
		if (conn) {
			_login = login;
			connected = true;
		}
		else {
			++n_prob;
			cout << "Bledne dane, sprobuj ponownie." << endl;
		}
	}
	if (!connected) {
		cout << "Przekroczono dozwolona liczbe prob logowania" << endl;
	}
	return conn;
}

//done
void wyswietl_liste_klientow(MYSQL *conn) {
	string zapytanie = "SELECT * FROM dane_klientow;";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		cout << "id_klienta - imie - nazwisko - email - opis - miejscowowsc - "
			<< "ulica - nr_domu - nr_mieszkania - kod_pocztowy - NIP - telefon"
			<< " - wewnetrzny" << endl;
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < 12; ++i) {
				cout << (row[i]==nullptr?"NULL":row[i]) << " - ";
			}
			cout << (row[12] == nullptr ? "NULL" : row[12]) << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void dodaj_klienta(MYSQL *conn) {
	string _imie, _nazwisko, _email, _opis, _miejscowosc, _nr_domu, _nr_mieszkania, _ulica, _kod_pocztowy, _nip, _telefon, _wewnetrzny;
	//imie
	cout << "Podaj imie: "; getline(cin, _imie);
	while (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	_imie = "\"" + _imie + "\"";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	_nazwisko = "\"" + _nazwisko + "\"";
	//email
	cout << "Podaj email: "; getline(cin, _email);
	while (!check_sql_injection(_email, 1, 1, 0, 1, 1, 1)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj email: "; getline(cin, _email);
	}
	_email = "\"" + _email + "\"";
	//miejscowosc
	cout << "Podaj miejscowosc zamieszkania: "; getline(cin, _miejscowosc);
	while (!check_sql_injection(_miejscowosc, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj miejscowosc zamieszkania: ";  getline(cin, _miejscowosc);
	}
	_miejscowosc = "\"" + _miejscowosc + "\"";
	//nr domu
	cout << "Podaj numer domu: "; getline(cin, _nr_domu);
	while (!check_sql_injection(_nr_domu, 1, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj numer domu: "; getline(cin, _nr_domu);
	}
	_nr_domu = "\"" + _nr_domu + "\"";
	//nr mieszkania
	cout << "Podaj numer mieszkania ('-' jezeli nie posiada): "; getline(cin, _nr_mieszkania);
	while ((_nr_mieszkania != "-") && (!check_sql_injection(_nr_mieszkania, 1, 1, 0, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj numer mieszkania ('-' jezeli nie posiada): "; getline(cin, _nr_mieszkania);
	}
	if (_nr_mieszkania != "-") _nr_mieszkania = "\"" + _nr_mieszkania + "\"";
	else _nr_mieszkania = "null";
	//ulica
	cout << "Podaj ulice ('-' jezeli nie posiada): "; getline(cin, _ulica);
	while ((_ulica!="-") && (!check_sql_injection(_ulica, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj ulice ('-' jezeli nie posiada): "; getline(cin, _ulica);
	}
	if (_ulica != "-") _ulica = "\"" + _ulica + "\"";
	else _ulica = "null";
	//kod pocztowy
	cout << "Podaj kod pocztowy: "; getline(cin, _kod_pocztowy);
	while ((!check_sql_injection(_kod_pocztowy, 0, 1, 0, 0, 0, 0)) || (_kod_pocztowy.length() !=  5)) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj kod pocztowy: "; getline(cin, _kod_pocztowy);
	}
	_kod_pocztowy = "\"" + _kod_pocztowy + "\"";
	//nip
	cout << "Podaj NIP ('-' jezeli nie posiada): "; getline(cin, _nip);
	while  ((_nip!="-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip == "-") _nip = "null";
	else _nip = "\"" + _nip + "\"";
	//telefon
	cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
	while ((!check_sql_injection(_telefon, 0, 1, 0, 0, 0, 0)) || (_telefon.length() != 9)) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
	}
	_telefon = "\"" + _telefon + "\"";
	//wewnetrzny
	cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
	while ((_wewnetrzny != "-") && (!check_sql_injection(_wewnetrzny, 0, 1, 0, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
	}
	if (_wewnetrzny != "-") _wewnetrzny = "\"" + _wewnetrzny + "\"";
	else _wewnetrzny = "null";
	//opis
	cout << "Podaj opis klienta ('-' jezeli nie chcesz): ";  getline(cin, _opis);
	while ((_opis != "-") && (!check_sql_injection(_opis, 1, 1, 1, 1, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj opis klienta ('-' jezeli nie chcesz): "; getline(cin, _opis);
	}
	if (_opis != "-") _opis = "\"" + _opis + "\"";
	else _opis = "null";

	//zapytanie
	string zapytanie = "call add_client(" + _imie + "," + _nazwisko + "," + _email + "," + _opis + "," + _miejscowosc + "," + _nr_domu + "," + _nr_mieszkania + "," + _ulica
		+ "," + _kod_pocztowy + "," + _nip + "," + _telefon + "," + _wewnetrzny + ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		cout << "Zapytanie wykonane poprawnie." << endl;
	}	
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}

}

//done
void dodaj_nip(MYSQL* conn) {
	string _imie, _nazwisko, _nip;
	//imie
	cout << "Podaj imie: "; getline(cin, _imie);
	while (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	_imie = "\"" + _imie + "\"";
	//nazwisko
	cout << "Podaj nazwisko: ";  getline(cin, _nazwisko);
	while (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	_nazwisko = "\"" + _nazwisko + "\"";
	//sprawdzenie czy istnieje klient
	string zapytanie = "SELECT count(*) FROM dane_klientow WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		if (strcmp(row[0],"1")==0) {
			//nip
			cout << "Podaj NIP: "; getline(cin, _nip);
			while ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10)) {
				cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
				cout << "Podaj NIP: "; getline(cin, _nip);
			}
			_nip = "\"" + _nip + "\"";
			//zapytanie
			zapytanie = "call add_nip("+_imie+","+_nazwisko+","+_nip+");";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonano poprawnie." << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie." << endl;
			}
		}
		else {
			cout << "Blad: klient o podanym imieniu i/lub nazwisku nie istnieje." << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}

}

//done
void dodaj_telefon(MYSQL* conn) {
	string _imie, _nazwisko, _nip, zapytanie;
	//imie
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz)" << endl;
	cout << "Podaj imie: "; getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: ";  getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int result = -1;
	int status;
	if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip="+_nip+";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko="+_nazwisko+";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (result == 1) {
		//wczytaj telefon
		string _telefon, _wewnetrzny;
		cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
		while ((!check_sql_injection(_telefon, 0, 1, 0, 0, 0, 0)) || (_telefon.length() != 9)) {
			cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
			cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
		}
		_telefon = "\"" + _telefon + "\"";
		//wewnetrzny
		cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
		while ((_wewnetrzny != "-") && (!check_sql_injection(_wewnetrzny, 0, 1, 0, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
		}
		if (_wewnetrzny != "-") _wewnetrzny = "\"" + _wewnetrzny + "\"";
		else _wewnetrzny = "null";
		//zapytanie
		zapytanie = "call add_tel(" + _imie + "," + _nazwisko + "," + _nip + "," + _telefon + "," + _wewnetrzny + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonano poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonano niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono klienta" << endl;
	}
}

//done
void usun_klienta(MYSQL* conn) {
	string _imie, _nazwisko, _nip, zapytanie;
	//imie
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz)" << endl;
	cout << "Podaj imie: "; getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int result = -1;
	int status;
	if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (result == 1) {
		zapytanie = "call del_client(" + _imie + "," + _nazwisko + "," + _nip + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonano poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonano niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono klienta" << endl;
	}

}

//done
void edytuj_adres_klienta(MYSQL* conn) {
	string _imie, _nazwisko, _nip, zapytanie;
	//imie
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz)" << endl;
	cout << "Podaj imie: "; getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: ";  getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int result = -1;
	int status;
	if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (result == 1) {
		string _miejscowosc, _nr_domu, _nr_mieszkania, _ulica, _kod_pocztowy;
		cout << "Podaj nowe dane. Jesli nie chcesz edytowac tej danej, wstaw znak '-'" << endl;
		//miejscowosc
		cout << "Podaj miejscowosc: ";  getline(cin, _miejscowosc);
		while ((_miejscowosc != "-") && (!check_sql_injection(_miejscowosc, 1, 0, 1, 0, 1, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj miejscowosc: ";  getline(cin, _miejscowosc);
		}
		if (_miejscowosc != "-") _miejscowosc = "\"" + _miejscowosc + "\"";
		else _miejscowosc = "null";
		//nr domu
		cout << "Podaj numer domu: "; getline(cin, _nr_domu);
		while ((_nr_domu != "-") && (!check_sql_injection(_nr_domu, 1, 1, 0, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj miejscowosc: "; getline(cin, _nr_domu);
		}
		if (_nr_domu != "-") _nr_domu = "\"" + _nr_domu + "\"";
		else _nr_domu = "null";
		//nr mieszkania
		cout << "Podaj numer mieszkania: "; getline(cin, _nr_mieszkania);
		while ((_nr_mieszkania != "-") && (!check_sql_injection(_nr_mieszkania, 1, 1, 0, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj numer mieszkania: "; getline(cin, _nr_mieszkania);
		}
		if (_nr_mieszkania != "-") _nr_mieszkania = "\"" + _nr_mieszkania + "\"";
		else _nr_mieszkania = "null";
		//ulica
		cout << "Podaj ulice: ";  getline(cin, _ulica);
		while ((_ulica != "-") && (!check_sql_injection(_ulica, 1, 0, 1, 0, 1, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj ulice: ";  getline(cin, _ulica);
		}
		if (_ulica != "-") _ulica = "\"" + _ulica + "\"";
		else _ulica = "null";
		//kod pocztowy
		cout << "Podaj kod pocztowy: "; getline(cin, _kod_pocztowy);
		while ((_kod_pocztowy != "-") && ((!check_sql_injection(_kod_pocztowy, 0, 1, 0, 0, 0, 0)) || (_kod_pocztowy.length()!=5))) {
			cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
			cout << "Podaj kod pocztowy: "; getline(cin, _kod_pocztowy);
		}
		if (_kod_pocztowy != "-") _kod_pocztowy = "\"" + _kod_pocztowy + "\"";
		else _kod_pocztowy = "null";
		//zapytanie
		zapytanie = "call modif_adres(" + _imie + "," + _nazwisko + "," + _nip + "," + _miejscowosc + "," + _nr_domu + "," + _nr_mieszkania + ","
			+ _ulica + "," + _kod_pocztowy + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono klienta" << endl;
	}
}

//done
void edytuj_telefon_klienta(MYSQL* conn) {
	string _imie, _nazwisko, _nip, zapytanie;
	//imie
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz)" << endl;
	cout << "Podaj imie: ";  getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: ";  getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int result = -1;
	int status;
	if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (result == 1) {
		//szukanie telefonu
		cout << "Podaj telefon, ktory chcesz zmodyfikowac" << endl;
		string _telefon, _wewnetrzny, __telefon, __wewnetrzny;
		cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
		while ((!check_sql_injection(_telefon, 0, 1, 0, 0, 0, 0)) || (_telefon.length() != 9)) {
			cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
			cout << "Podaj telefon kontaktowy: "; getline(cin, _telefon);
		}
		_telefon = "\"" + _telefon + "\"";
		//wewnetrzny
		cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
		while ((_wewnetrzny != "-") && (!check_sql_injection(_wewnetrzny, 0, 1, 0, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj telefon wewnetrzny ('-' jezeli nie posiada): "; getline(cin, _wewnetrzny);
		}
		if (_wewnetrzny != "-") _wewnetrzny = "\"" + _wewnetrzny + "\"";
		else _wewnetrzny = "null";
		//nowe dane
		cout << "Podaj dane nowego telefonu (jeslii nie chcesz modyfikowac, wpis znak '-')" << endl;
		cout << "Podaj telefon: "; getline(cin, __telefon);
		while ((__telefon != "-") && ((!check_sql_injection(__telefon, 0, 1, 0, 0, 0, 0)) || (__telefon.length()!= 9 ))) {
			cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
			cout << "Podaj telefon: "; getline(cin, __telefon);
		}
		if (__telefon != "-") __telefon = "\"" + __telefon + "\"";
		else __telefon = "null";
		//nr domu
		cout << "Podaj numer wewnetrzny: "; getline(cin, __wewnetrzny);
		while ((__wewnetrzny != "-") && (!check_sql_injection(__wewnetrzny, 0, 1, 0, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj numer wewnetrzny: "; getline(cin, __wewnetrzny);
		}
		if (__wewnetrzny != "-") __wewnetrzny = "\"" + __wewnetrzny + "\"";
		else __wewnetrzny = "null";
		//zapytanie
		zapytanie = "call modif_tel(" + _imie + "," + _nazwisko + "," + _nip + ","+ _telefon + "," + _wewnetrzny + "," + __telefon + ","
			+ __wewnetrzny + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
		
		//czy znaleziono telefon
	}
	else {
		cout << "Blad: nie znaleziono klienta" << endl;
	}
}

//done
void edytuj_personalia_klienta(MYSQL* conn) {
	string _imie, _nazwisko, _nip, zapytanie;
	//imie
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz)" << endl;
	cout << "Podaj imie: ";  getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: ";  getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: ";  getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int result = -1;
	int status;
	if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (result == 1) {
		string __imie, __nazwisko, _email, _opis;
		cout << "Podaj nowe dane. Jesli nie chcesz edytowac tej danej, wstaw znak '-'" << endl;
		//imie
		cout << "Podaj imie: ";  getline(cin, __imie);
		while ((__imie != "-") && (!check_sql_injection(__imie, 1, 0, 1, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj imie: ";  getline(cin, __imie);
		}
		if (__imie != "-") __imie = "\"" + __imie + "\"";
		else __imie = "null";
		//nr domu
		cout << "Podaj nazwisko: ";  getline(cin, __nazwisko);
		while ((__nazwisko != "-") && (!check_sql_injection(__nazwisko, 1, 0, 1, 0, 1, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj nazwisko: ";  getline(cin, __nazwisko);
		}
		if (__nazwisko != "-") __nazwisko = "\"" + __nazwisko + "\"";
		else __nazwisko = "null";
		//email
		cout << "Podaj email: "; getline(cin, _email);
		while ((_email != "-") && (!check_sql_injection(_email, 1, 1, 0, 1, 1, 1))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj email: "; getline(cin, _email);
		}
		if (_email != "-") _email = "\"" + _email + "\"";
		else _email = "null";
		//opis
		cout << "Podaj opis: ";  getline(cin, _opis);
		while ((_opis != "-") && (!check_sql_injection(_opis, 1, 1, 1, 1, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj opis: ";  getline(cin, _opis);
		}
		if (_opis != "-") _opis = "\"" + _opis + "\"";
		else _opis = "null";
		
		//zapytanie
		zapytanie = "call modif_client(" + _imie + "," + _nazwisko + "," + _nip + "," + __imie + "," + __nazwisko + "," + _email + "," + _opis + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono klienta" << endl;
	}
}


//done
void wyswietl_liste_transakcji(MYSQL* conn) {
	string zapytanie = "SELECT * FROM transakcje ORDER BY data_sprzedazy DESC;";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		cout << "id_klienta - id_transakcji - id_pracownika - cena_calkowita - data_sprzedazy - data_platnosci" << endl;
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < 5; ++i) {
				cout << (row[i] == nullptr ? "NULL" : row[i]) << " - ";
			}
			cout << (row[5] == nullptr ? "NULL" : row[5]) << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void wyswietl_szczegoly_transakcji(MYSQL* conn) {
	string _id_transakcji;
	cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	while (!check_sql_injection(_id_transakcji, 0, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	}
	_id_transakcji = "\"" + _id_transakcji + "\"";
	string zapytanie = "call view_transaction("+ _id_transakcji + ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		cout << "id_produktu - nazwa - liczba_sztuk - cena_sprzedazy - stawka_VAT" << endl;
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < 4; ++i) {
				cout << (row[i] == nullptr ? "NULL" : row[i]) << " - ";
			}
			cout << (row[4] == nullptr ? "NULL" : row[4]) << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void reklamuj_transakcje(MYSQL* conn) {
	string _id_transakcji, _id_produktu;
	//id_transakcji
	cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	while (!check_sql_injection(_id_transakcji, 0, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	}
	_id_transakcji = "\"" + _id_transakcji + "\"";
	//id_produktu
	cout << "Podaj id produktu: "; getline(cin, _id_produktu);
	while (!check_sql_injection(_id_produktu, 0, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj id produktu: "; getline(cin, _id_produktu);
	}
	_id_produktu = "\"" + _id_produktu + "\"";
	//zapytanie
	string zapytanie = "SELECT count(*) FROM szczegoly_transakcji WHERE id_transakcji="
		+ _id_transakcji + " AND id_produktu=" + _id_produktu + ";";
	cout << zapytanie << endl;
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
	if (result == 1) {
		string wybor;
		cout << "Wybierz 1, by usunac produkt; 2, by zmodyfikowac liczbe; 3, by zmodyfikowac cene" << endl;
		cout << "Twoj wybor: "; getline(cin, wybor);
		while (!(wybor == "1" || wybor == "2" || wybor == "3")) {
			cout << "Blad: podano niepoprawna opcje. Sprobuj ponownie" << endl;
			cout << "Twoj wybor: "; getline(cin, wybor);
		}
		if (wybor == "1") {
			zapytanie = "DELETE FROM szczegoly_transakcji WHERE id_transakcji=" + _id_transakcji + " AND id_produktu=" + _id_produktu + ";";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonane poprawnie" << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie" << endl;
			}
		}
		else if (wybor == "2") {
			string _liczba;
			cout << "Podaj liczbe sztuk sprzedanego produktu po reklamacji: "; getline(cin, _liczba);
			while (!check_sql_injection(_liczba, 0, 1, 0, 0, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj liczbe sztuk sprzedanego produktu po reklamacji: "; getline(cin, _liczba);
			}
			_liczba = "\"" + _liczba + "\"";
			//zapytanie
			zapytanie = "UPDATE szczegoly_transakcji SET liczba_sztuk=" + _liczba + " WHERE id_transakcji=" + _id_transakcji
				+ " AND id_produktu=" + _id_produktu + ";";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonane poprawnie" << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie" << endl;
			}
		}
		else if (wybor == "3") {
			string _cena;
			cout << "Podaj cene sprzedazy produktu po reklamacji: "; getline(cin, _cena);
			while (!check_sql_injection(_cena, 0, 1, 0, 1, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj cene sprzedanego produktu po reklamacji: "; getline(cin, _cena);
			}
			_cena = "\"" + _cena + "\"";
			//zapytanie
			zapytanie = "UPDATE szczegoly_transakcji SET cena_sprzedazy_brutto=" + _cena + " WHERE id_transakcji=" + _id_transakcji
				+ " AND id_produktu=" + _id_produktu + ";";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonane poprawnie" << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie" << endl;
			}
		}
		else {
			cout << "Wystapil nieznany blad" << endl;
		}
	}
	else {
		cout << "Nie znaleziono danego produktu w danej transakcji." << endl;
	}
}

//done
void dodaj_date_platnosci(MYSQL* conn) {
	string _id_transakcji;
	cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	while (!check_sql_injection(_id_transakcji, 0, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj id transakcji: "; getline(cin, _id_transakcji);
	}
	_id_transakcji = "\"" + _id_transakcji + "\"";
	//zapytanie
	string zapytanie = "SELECT count(*) FROM transakcje WHERE id_transakcji=" + _id_transakcji + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
	if (result == 1) {
		string _data_platnosci;
		cout << "Podaj date platnosci w formacie YYYY-MM-DD HH:MM:SS : "; getline(cin, _data_platnosci);
		while (!(analizuj_date(_data_platnosci))) {
			cout << "Bledny format daty, sprobuj ponownie" << endl;
			cout << "Podaj date platnosci w formacie YYYY-MM-DD HH:MM:SS : "; getline(cin, _data_platnosci);
		}
		//mamy date
		string zapytanie = "UPDATE transakcje SET data_platnosci=\"" + _data_platnosci + "\" where id_transakcji=" + _id_transakcji + ";";
		int status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie." << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono transakcji" << endl;
	}
}


//done
void wyswietl_liste_produktow(MYSQL* conn) {
	string zapytanie = "SELECT nazwa_kategorii,nazwa,liczba_sztuk_na_stanie,cena_jednostkowa,stawka_VAT,nazwa_1,cecha_1,nazwa_2,cecha_2,";
	zapytanie += "nazwa_3,cecha_3,nazwa_4,cecha_4,nazwa_5,cecha_5,opis FROM produkty,cechy where produkty.id_kategorii = cechy.id_kategorii;";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		cout << "karegoria - nazwa - liczba sztuk na stanie - cena jednostkowa - stawka VAT - cecha - ";
		cout << "wartosc - cecha - wartosc - cecha - wartosc - cecha - wartosc - cecha - wartosc - opis" << endl;
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < 15; ++i) {
				cout << (row[i] == nullptr ? "NULL" : row[i]) << " - ";
			}
			cout << (row[15] == nullptr ? "NULL" : row[15]) << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void dodaj_nowy_produkt(MYSQL* conn) {
	string zapytanie, _kategoria;
	cout << "Podaj kategorie dodawanego produktu: "; getline(cin, _kategoria);
	while (!check_sql_injection(_kategoria, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj kategorie dodawanego produktu: ";  getline(cin, _kategoria);
	}
	_kategoria = "\"" + _kategoria + "\"";
	zapytanie = "SELECT count(*) FROM cechy WHERE nazwa_kategorii=" + _kategoria + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
	if (result == 1) {
		string _cecha[5], _id_kategorii, _rzut[5];
		zapytanie = "SELECT nazwa_1,nazwa_2,nazwa_3,nazwa_4,nazwa_5,id_kategorii,rzut_na_liczbe_1,rzut_na_liczbe_2,rzut_na_liczbe_3,";
		zapytanie += "rzut_na_liczbe_4,rzut_na_liczbe_5 FROM cechy WHERE nazwa_kategorii=" + _kategoria + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			for (int i = 0; i < 5; ++i) {
				_cecha[i] = (row[i] == nullptr ? "null" : row[i]);
				_rzut[i] = (row[i + 6] == nullptr ? "null" : row[i + 6]);
			}
			_id_kategorii = row[5];
			string _nazwa, _cena, _vat, _opis, __cecha[5];
			//nazwa
			cout << "Podaj nazwe dodawanego produktu: ";  getline(cin, _nazwa);
			while (!check_sql_injection(_nazwa, 1, 1, 1, 1, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj nazwe dodawanego produktu: ";  getline(cin, _nazwa);
			}
			_nazwa = "\"" + _nazwa + "\"";
			//cena
			cout << "Podaj cene dodawanego produktu: "; getline(cin, _cena);
			while (!check_sql_injection(_cena, 0, 1, 0, 1, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj cene dodawanego produktu: "; getline(cin, _cena);
			}
			_cena= "\"" + _cena + "\"";
			//stawka VAT
			cout << "Podaj stawke VAT dodawanego produktu: "; getline(cin, _vat);
			while (!check_sql_injection(_vat, 0, 1, 0, 0, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj stawke VAT dodawanego produktu: "; getline(cin, _vat);
			}
			_vat= "\"" + _vat + "\"";
			//cechy
			for (int i = 0; i < 5; ++i) {
				if (_cecha[i] != "null") {
					cout << "Podaj ceche " << _cecha[i] << " dodawanego produktu: "; getline(cin, __cecha[i]);
					if (_rzut[i] == "0") {
						while (!check_sql_injection(__cecha[i], 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj ceche " << _cecha[i] << "dodawanego produktu: "; getline(cin, __cecha[i]);
						}
					}
					else {
						while (!check_sql_injection(__cecha[i], 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj ceche " << _cecha[i] << "dodawanego produktu: "; getline(cin, __cecha[i]);
						}
					}
					__cecha[i] = "\"" + __cecha[i] + "\"";
				}
				else {
					__cecha[i] = "null";
				}
			}
			//opis
			cout << "Podaj opis produktu ('-' jezeli nie posiada): ";  getline(cin, _opis);
			while ((_opis != "-") && (!check_sql_injection(_opis, 1, 0, 1, 0, 1, 0))) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj opis produktu ('-' jezeli nie posiada): "; getline(cin, _opis);
			}
			if (_opis != "-") _opis = "\"" + _opis + "\"";
			else _opis = "null";
			//zapytanie i dodanie produktu
			zapytanie = "INSERT INTO produkty (nazwa,liczba_sztuk_na_stanie,cena_jednostkowa,stawka_VAT,id_kategorii,cecha_1,cecha_2,cecha_3,cecha_4,cecha_5,opis) VALUES (";
			zapytanie = zapytanie + _nazwa + ",\"0\"," + _cena + "," + _vat + "," + _id_kategorii + ",";
			for (int i = 0; i < 5; ++i) zapytanie = zapytanie + __cecha[i] + ",";
			zapytanie = zapytanie + _opis + ");";
			int status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonane poprawnie" << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie." << endl;
			}
		}
		else {
			cout << "Blad: zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono kategorii. Jezeli nie istnieje, to dodaj ja najpierw" << endl;
	}
}

//done
void dodaj_nowa_kategorie(MYSQL* conn) {
	string _nazwa_kat, _nazwa[5], _rzut[5];
	//nazwa
	cout << "Podaj nazwe kategorii: "; getline(cin, _nazwa_kat);
	while (!check_sql_injection(_nazwa_kat, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwe kategorii: "; getline(cin, _nazwa_kat);
	}
	_nazwa_kat = "\"" + _nazwa_kat + "\"";
	//kolejne 5 cech i rzuty
	cout << "Podaj nazwe minimum jednej cechy produktu" << endl;
	for (int i = 0; i < 5; ++i) {
		cout << "Podaj nazwe cechy ('-' gdy koniec cech): ";  getline(cin, _nazwa[i]);
		while ((_nazwa[i] != "-") && (!check_sql_injection(_nazwa[i], 1, 0, 1, 0, 0, 0))) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Podaj nazwe cechy: ";  getline(cin, _nazwa[i]);
		}
		if (_nazwa[i] != "-") {
			_nazwa[i] = "\"" + _nazwa[i] + "\"";
			//rzut na liczbe
			cout << "Czy jest to parametr liczbowy (1-tak, 0-nie, w przypadku bledu 0): "; getline(cin, _rzut[i]);
			if ((_rzut[i] != "0") && (_rzut[i] != "1")) _rzut[i] = "0";
		}
		else {
			_nazwa[i] = "null";
			_rzut[i] = "null";
		}
	}
	//zapytanie
	string zapytanie = "INSERT INTO cechy (nazwa_kategorii,nazwa_1,rzut_na_liczbe_1,nazwa_2,rzut_na_liczbe_2,nazwa_3,rzut_na_liczbe_3,";
	zapytanie += "nazwa_4,rzut_na_liczbe_4,nazwa_5,rzut_na_liczbe_5) VALUES (" + _nazwa_kat;
	for (int i = 0; i < 5; ++i) zapytanie = zapytanie + "," + _nazwa[i] + "," + _rzut[i];
	zapytanie += ");";
	cout << zapytanie << endl;
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		cout << "Zapytanie wykonane poprawnie" << endl;
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void edytuj_produkt(MYSQL* conn) {
	string _produkt, zapytanie;
	cout << "Podaj nazwe edytowanego produktu: "; getline(cin, _produkt);
	while (!check_sql_injection(_produkt, 1, 1, 1, 1, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwe edytowanego produktu: "; getline(cin, _produkt);
	}
	_produkt = "\"" + _produkt + "\"";
	//zapytanie
	zapytanie = "SELECT count(*) FROM produkty WHERE nazwa=" + _produkt + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES * res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonano niepoprawnie" << endl;
	}
	if (result == 1) {
		//znajdz cechy
		zapytanie = "SELECT id_kategorii FROM produkty WHERE nazwa=" + _produkt + ";";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			string _id_kategorii;
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			_id_kategorii = row[0];
			//cechy
			zapytanie = "SELECT nazwa_1,rzut_na_liczbe_1,nazwa_2,rzut_na_liczbe_2,nazwa_3,rzut_na_liczbe_3,nazwa_4,rzut_na_liczbe_4,nazwa_5,rzut_na_liczbe_5";
			zapytanie = zapytanie + " FROM cechy WHERE id_kategorii=" + _id_kategorii + ";";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				string _nazwa[5], _rzut[5];
				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW row = mysql_fetch_row(res);
				for (int i = 0; i < 5; ++i) {
					_nazwa[i] = (row[2 * i] == nullptr ? "null" : row[2 * i]);
					_rzut[i] = (row[2 * i + 1] == nullptr ? "null" : row[2 * i + 1]);
				}
				//print menu
				int max = -1;
				string wybor;
				cout << "Dostepne modyfikacje: 1-nazwa, 2-cena, 3-stawka VAT";
				for (int i = 0; i < 5; ++i) {
					if (_nazwa[i] != "null") {
						cout << ", " << i + 4 << "-" << _nazwa[i];
						max = i + 4;
					}
				}
				cout << endl;
				cout << "Twoj wybor:"; getline(cin, wybor);
				string _edit = "a",_param;
				if (wybor == "1") {
					//modyfikacja nazwy
					cout << "Podaj nowa nazwe produktu: "; getline(cin, _edit);
					while (!check_sql_injection(_edit, 1, 1, 1, 1, 0, 0)) {
						cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
						cout << "Podaj nowa nazwe produktu: "; getline(cin, _edit);
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"nazwa\"";
				}
				else if (wybor == "2"){
					//modyfiakcja ceny
					cout << "Podaj nowa cene produktu: "; getline(cin, _edit);
					while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
						cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
						cout << "Podaj nowa cene produktu: "; getline(cin, _edit);
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cena_jednostkowa\"";
				}
				else if (wybor == "3") {
					//modyfikacja vat
					cout << "Podaj nowa stawke VAT produktu: "; getline(cin, _edit);
					while (!check_sql_injection(_edit, 0, 1, 0, 0, 0, 0)) {
						cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
						cout << "Podaj nowa stawke VAT produktu: "; getline(cin, _edit);
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"stawka_VAT\"";
				}
				else if (wybor == "4" && atoi(wybor.c_str()) <= max) {
					//modyfikacja param1
					cout << "Podaj nowa ceche " << _nazwa[0] << " produktu: "; getline(cin, _edit);
					if (_rzut[0] == "1") {
						while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[0] << " produktu: "; getline(cin, _edit);
						}
					}
					else {
						while (!check_sql_injection(_edit, 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[0] << " produktu: "; getline(cin, _edit);
						}
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cecha_1\"";

				}
				else if (wybor == "5" && atoi(wybor.c_str()) <= max) {
					//modyfikacja param2
					cout << "Podaj nowa ceche " << _nazwa[1] << " produktu: "; getline(cin, _edit);
					if (_rzut[1] == "1") {
						while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[1] << " produktu: "; getline(cin, _edit);
						}
					}
					else {
						while (!check_sql_injection(_edit, 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[1] << " produktu: "; getline(cin, _edit);
						}
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cecha_2\"";
				}
				else if (wybor == "6" && atoi(wybor.c_str()) <= max) {
					//modyfikacja param3
					cout << "Podaj nowa ceche " << _nazwa[2] << " produktu: "; getline(cin, _edit);
					if (_rzut[2] == "1") {
						while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[2] << " produktu: "; getline(cin, _edit);
						}
					}
					else {
						while (!check_sql_injection(_edit, 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[2] << " produktu: "; getline(cin, _edit);
						}
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cecha_3\"";
				}
				else if (wybor == "7" && atoi(wybor.c_str()) <= max) {
					//modyfikacja param4
					cout << "Podaj nowa ceche " << _nazwa[3] << " produktu: "; getline(cin, _edit);
					if (_rzut[3] == "1") {
						while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[3] << " produktu: "; getline(cin, _edit);
						}
					}
					else {
						while (!check_sql_injection(_edit, 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[3] << " produktu: "; getline(cin, _edit);
						}
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cecha_4\"";
				}
				else if (wybor == "8" && atoi(wybor.c_str()) <= max) {
					//modyfikacja param5
					cout << "Podaj nowa ceche " << _nazwa[4] << " produktu: "; getline(cin, _edit);
					if (_rzut[4] == "1") {
						while (!check_sql_injection(_edit, 0, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[4] << " produktu: "; getline(cin, _edit);
						}
					}
					else {
						while (!check_sql_injection(_edit, 1, 1, 0, 1, 0, 0)) {
							cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
							cout << "Podaj nowa ceche " << _nazwa[4] << " produktu: "; getline(cin, _edit);
						}
					}
					_edit = "\"" + _edit + "\"";
					_param = "\"cecha_5\"";
				}
				else {
					cout << "Niepoprawny wybor: nie dokonano modyfikacji" << endl;
				}
				if (_edit != "a") {
					zapytanie = "call edit_product(" + _produkt + "," + _param + "," + _edit + ");";
					status = mysql_query(conn, zapytanie.c_str());
					if (!status) {
						cout << "Zapytanie wykonane poprawnie" << endl;
					}
					else {
						cout << "Zapytanie wykonane niepoprawnie" << endl;
					}
				}
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie" << endl;
			}
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono produktu" << endl;
	}
}

//done
void aktualizuj_liczbe_produktu(MYSQL* conn) {
	string _produkt, zapytanie;
	cout << "Podaj nazwe edytowanego produktu: "; getline(cin, _produkt);
	while (!check_sql_injection(_produkt, 1, 1, 1, 1, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwe edytowanego produktu: "; getline(cin, _produkt);
	}
	_produkt = "\"" + _produkt + "\"";
	//zapytanie
	zapytanie = "SELECT count(*) FROM produkty WHERE nazwa=" + _produkt + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonano niepoprawnie" << endl;
	}
	if (result == 1) {
		//dodaj liczbe
		string _liczba;
		cout << "Wprowadz liczbe sztuk produktu wprowadzanego na stan: "; getline(cin, _liczba);
		while (!check_sql_injection(_liczba, 0, 1, 0, 0, 0, 0)) {
			cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
			cout << "Wprowadz liczbe sztuk produktu wprowadzanego na stan: "; getline(cin, _liczba);
		}
		_liczba = "\"" + _liczba + "\"";
		//zapytanie
		zapytanie = "call zakup_produkt(" + _produkt + "," + _liczba + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonano niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono produktu" << endl;
	}
}

//done
void przeprowadz_transakcje(MYSQL* conn, string _id_pracownika) {
	string _imie, _nazwisko, _nip, zapytanie;
	//
	cout << "Podaj imie i nazwisko lub NIP ('-' jesli nie podajesz), jesli klient chce fakture (wtedy wpisz trzykrotnie znak '-')." << endl;
	cout << "Podaj imie: ";  getline(cin, _imie);
	while ((_imie != "-") && (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: ";  getline(cin, _imie);
	}
	if (_imie != "-")_imie = "\"" + _imie + "\"";
	else _imie = "null";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while ((_nazwisko != "-") && (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0))) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	if (_nazwisko != "-") _nazwisko = "\"" + _nazwisko + "\"";
	else _nazwisko = "null";
	//nip
	cout << "Podaj NIP: "; getline(cin, _nip);
	while ((_nip != "-") && ((!check_sql_injection(_nip, 0, 1, 0, 0, 0, 0)) || (_nip.length() != 10))) {
		cout << "Napis zawiera niedozwolone znaki badz jest zlej dlugosci, sprobuj ponownie." << endl;
		cout << "Podaj NIP: "; getline(cin, _nip);
	}
	if (_nip != "-")_nip = "\"" + _nip + "\"";
	else _nip = "null";
	//szukanie
	int status;
	string _id_klienta;
	if (_imie == "null" && _nazwisko == "null" && _nip == "null") {
		_id_klienta = "null";
	}
	else if (_nip != "null") {
		zapytanie = "SELECT count(*) FROM dane_podatkowe WHERE nip=" + _nip + ";";
		status = mysql_query(conn, zapytanie.c_str());
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
				else {
					cout << "Zapytanie wykonane niepoprawnie" << endl;
				}
			}
			else {
				cout << "Blad: nie znaleziono klienta" << endl;
			}
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		zapytanie = "SELECT count(*) FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
		status = mysql_query(conn, zapytanie.c_str());
		int result = -1;
		if (!status) {
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			result = atoi(row[0]);
			if (result == 1) {
				zapytanie = "SELECT id_klienta FROM klienci WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
				status = mysql_query(conn, zapytanie.c_str());
				if (!status) {
					MYSQL_RES* res = mysql_store_result(conn);
					MYSQL_ROW row = mysql_fetch_row(res);
					_id_klienta = row[0];
				}
				else {
					cout << "Zapytanie wykonane niepoprawnie" << endl;
				}
			}
			else {
				cout << "Blad: nie znaleziono klienta" << endl;
			}
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	if (_id_klienta != "null") _id_klienta = "\"" + _id_klienta + "\"";
	//wprowadz transakcje
	zapytanie = "INSERT INTO transakcje (id_klienta,id_pracownika,data_sprzedazy) VALUES (" + _id_klienta + ",\"" + _id_pracownika + "\",now());";
	status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		cout << "Zapytanie wykonane poprawnie" << endl;
		//pobierz id trasakcji
		zapytanie = "SELECT id_transakcji FROM transakcje ORDER BY data_sprzedazy DESC LIMIT 1;";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			string _id_transakcji;
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW row = mysql_fetch_row(res);
			_id_transakcji = row[0];
			//dodawanie produktow
			string _produkt;
			cout << "Wprowadz nazwy produktow, zakoncz wpisujac 'q'." << endl;
			cout << "Podaj nazwe produktu: "; getline(cin, _produkt);
			while (_produkt!="q") {
				if (!check_sql_injection(_produkt, 1, 1, 1, 1, 0, 0)) {
					cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				}
				else {
					//dodaj produkt do trasakcji
					string _ilosc;
					cout << "Podaj liczbe sprzedawanych sztuk: "; getline(cin, _ilosc);
					while (!check_sql_injection(_ilosc, 0, 1, 0, 0, 0, 0)) {
						cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
						cout << "Podaj liczbe sprzedawanych sztuk: "; getline(cin, _ilosc);
					}
					_ilosc = "\"" + _ilosc + "\"";
					_produkt = "\"" + _produkt + "\"";
					//zapytanie
					zapytanie = "call sprz_prod(\"" + _id_transakcji + "\"," + _produkt + "," + _ilosc + ");";
					status = mysql_query(conn, zapytanie.c_str());
					if (!status) {
						cout << "Zapytanie wykonane poprawnie" << endl;
					}
					else {
						cout << "Zapytanie wykonane niepoprawnie" << endl;
					}
				}
				cout << "Podaj nazwe produktu: ";  getline(cin, _produkt);
			}
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie" << endl;
	}
}


//done
void wyswietl_liste_pracownikow(MYSQL* conn) {
	string zapytanie = "SELECT imie,nazwisko,stanowisko FROM pracownicy";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row;
		cout << "imie - nazwisko - stanowisko" << endl;
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < 2; ++i) {
				cout << (row[i] == nullptr ? "NULL" : row[i]) << " - ";
			}
			cout << (row[2] == nullptr ? "NULL" : row[2]) << endl;
		}
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie." << endl;
	}
}

//done
void dodaj_pracownika(MYSQL* conn) {
	string _imie, _nazwisko, _login, _haslo, _stanowisko;
	cout << "Podaj imie: "; getline(cin, _imie);
	while (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	_imie = "\"" + _imie + "\"";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	_nazwisko = "\"" + _nazwisko + "\"";
	cout << "Podaj login: "; getline(cin, _login);
	while (!check_sql_injection(_login, 1, 1, 0, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj login: "; getline(cin, _login);
	}
	_login = "\"" + _login + "\"";
	//nazwisko
	cout << "Podaj haslo: "; getline(cin, _haslo);
	while (!analizuj_haslo(_haslo)) {
		cout << "Haslo niepoprawne (min 2 duze litery, 2 male litery, 1 cyfra, 1 znak specjalny, dlugosc 8-32 znakow), sprobuj ponownie." << endl;
		cout << "Podaj haslo: "; getline(cin, _haslo);
	}
	//stanowisko
	cout << "Podaj stanowisko (1-wlasciciel, 2-sprzedawca, 3-magazynier): "; getline(cin, _stanowisko);
	while (_stanowisko != "1" && _stanowisko != "2" && _stanowisko != "3") {
		cout << "Nieprawidlowe dane, sprobuj ponownie." << endl;
		cout << "Podaj stanowisko (1-wlasciciel, 2-sprzedawca, 3-magazynier): "; getline(cin, _stanowisko);
	}
	if (_stanowisko == "1") {
		_stanowisko = "\"Wlasciciel\"";
	}
	else if (_stanowisko == "2") {
		_stanowisko = "\"Sprzedawca\"";
	}
	else if (_stanowisko == "3") {
		_stanowisko = "\"Magazynier\"";
	}
	else {
		cout << "Wystapil nieoczekiwany blad" << endl;
	}
	//haszowanie hasla i zapytanie
	SHA256 haszuj;
	string _haslo_zahaszowane = haszuj(_haslo);
	string zapytanie = "call add_worker(" + _imie + "," + _nazwisko + "," + _login + ",\"" + _haslo_zahaszowane + "\"," + _stanowisko + ");";
	int status = mysql_query(conn, zapytanie.c_str());
	if (!status) {
		cout << "Zapytanie wykonane poprawnie" << endl;
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie" << endl;
	}

}

//done
void zwolnij_pracownika(MYSQL* conn) {
	string _imie, _nazwisko;
	cout << "Podaj imie: "; getline(cin, _imie);
	while (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	_imie = "\"" + _imie + "\"";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	_nazwisko = "\"" + _nazwisko + "\"";
	//czy pracownik istnieje
	string zapytanie = "SELECT count(*) FROM pracownicy WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie" << endl;
	}
	if (result == 1) {
		zapytanie = "call del_worker(" + _imie + "," + _nazwisko + ");";
		status = mysql_query(conn, zapytanie.c_str());
		if (!status) {
			cout << "Zapytanie wykonane poprawnie" << endl;
		}
		else {
			cout << "Zapytanie wykonane niepoprawnie" << endl;
		}
	}
	else {
		cout << "Blad: nie znaleziono pracownika" << endl;
	}
}

void edytuj_pracownika(MYSQL* conn) {
	string _imie, _nazwisko;
	cout << "Podaj imie: "; getline(cin, _imie);
	while (!check_sql_injection(_imie, 1, 0, 1, 0, 0, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj imie: "; getline(cin, _imie);
	}
	_imie = "\"" + _imie + "\"";
	//nazwisko
	cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	while (!check_sql_injection(_nazwisko, 1, 0, 1, 0, 1, 0)) {
		cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
		cout << "Podaj nazwisko: "; getline(cin, _nazwisko);
	}
	_nazwisko = "\"" + _nazwisko + "\"";
	//czy pracownik istnieje
	string zapytanie = "SELECT count(*) FROM pracownicy WHERE imie=" + _imie + " AND nazwisko=" + _nazwisko + ";";
	int status = mysql_query(conn, zapytanie.c_str());
	int result = -1;
	if (!status) {
		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW row = mysql_fetch_row(res);
		result = atoi(row[0]);
	}
	else {
		cout << "Zapytanie wykonane niepoprawnie" << endl;
	}
	if (result == 1) {
		//wybierz pole i wartosc
		string _pole, _edit="";
		cout << "Wybierz dana do modyfikacji (1-imie, 2-nazwisko, 3-haslo): "; getline(cin, _pole);
		if (_pole == "1") {
			cout << "Podaj nowe imie: "; getline(cin, _edit);
			while (!check_sql_injection(_edit, 1, 0, 1, 0, 0, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj nowe imie: "; getline(cin, _edit);
			}
			_edit = "\"" + _edit + "\"";
			_pole = "\"imie\"";
		}
		else if (_pole == "2") {
			cout << "Podaj nowe nazwisko: "; getline(cin, _edit);
			while (!check_sql_injection(_edit, 1, 0, 1, 0, 1, 0)) {
				cout << "Napis zawiera niedozwolone znaki, sprobuj ponownie." << endl;
				cout << "Podaj nowe nazwisko: "; getline(cin, _edit);
			}
			_edit = "\"" + _edit + "\"";
			_pole = "\"nazwisko\"";
		}
		else if (_pole == "3") {
			cout << "Podaj nowe haslo: "; getline(cin, _edit);
			while (!analizuj_haslo(_edit)) {
				cout << "Haslo niepoprawne (min 2 duze litery, 2 male litery, 1 cyfra, 1 znak specjalny, dlugosc 8-32 znakow), sprobuj ponownie." << endl;
				cout << "Podaj nowe haslo: "; getline(cin, _edit);
			}
			SHA256 haszuj;
			_edit = "\"" + haszuj(_edit) + "\"";
			_pole = "\"haslo_zaszyfrowane\"";
		}
		else {
			cout << "Wybrano niepoprawna opcje" << endl;
		}
		//realizacja
		if (_edit != "") {
			zapytanie = "call modif_worker(" + _imie + "," + _nazwisko + "," + _pole + "," + _edit + ");";
			status = mysql_query(conn, zapytanie.c_str());
			if (!status) {
				cout << "Zapytanie wykonane poprawnie" << endl;
			}
			else {
				cout << "Zapytanie wykonane niepoprawnie" << endl;
			}
		}

	}
	else {
		cout << "Blad: nie znaleziono pracownika" << endl;
	}
}

//false - jest ryzyko, true - nie ma ryzyka,  DONE
bool check_sql_injection(std::string napis, bool litery, bool cyfry, bool spacja, bool kropka, bool myslnik, bool malpa) {
	bool kryteria[6];
	for (char znak : napis) {
		for (int i = 0; i < 6; ++i) kryteria[i] = false;
		if ((znak >= 'a' && znak <= 'z') || (znak >= 'A' && znak <= 'Z')) kryteria[0] = true;
		if (znak >= '0' && znak <= '9') kryteria[1] = true;
		if (znak == ' ') kryteria[2] = true;
		if (znak == '.') kryteria[3] = true;
		if (znak == '-') kryteria[4] = true;
		if (znak == '@') kryteria[5] = true;

		if (!((kryteria[0] && litery) || (kryteria[1] && cyfry) || (kryteria[2] && spacja) || (kryteria[3] && kropka) || (kryteria[4] && myslnik) || (kryteria[5] && malpa))) return false;
	}
	return true;
}

//false=bad, true=ok, DONE
bool analizuj_date(string _data) {
	if (_data.length() != 19) return false;
	for (int i = 0; i < 19; ++i) {
		if (i == 4 || i == 7) {
			if (_data[i] != '-') return false;
		}
		else if (i == 10) {
			if (_data[i] != ' ') return false;
		}
		else if (i == 13 || i == 16) {
			if (_data[i] != ':') return false;
		}
		else {
			if (_data[i] < '0' || _data[i]>'9') return false;
		}
	}
	return true;
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
	else if ((info[0] < 8) || (info[0]>32)) return false;
	else if (info[1] < 2) return false;
	else if (info[2] < 2) return false;
	else if (info[3] < 1) return false;
	else if (info[4] < 1) return false;
	else return true;
}