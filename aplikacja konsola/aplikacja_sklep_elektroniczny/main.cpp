#include <iostream>
#include "sha256.h"
#include <mysql.h>
#include "operacje_bd.h"
#include "menu.h"
#include <string>
#include <cstring>

using namespace std;

int main()
{
    cout << "Aplikacja obslugujaca baze danych sklepu elektronicznego." << endl;
    MYSQL *conn;
    conn = mysql_init(0);
    string login="a";
    conn = connect_database(conn, login);
    //conn = mysql_real_connect(conn, "localhost", "root", "HASLO","sklep elektroniczny", 3306, NULL, 0);
    if (login == "a") {
        exit(1);
    }
    cout << "Pomyslnie polaczono z baza danych" << endl;
    string zapytanie = "SELECT imie,nazwisko,stanowisko,id_pracownika from pracownicy WHERE login=\""+login+"\";";
    int status;
    status = mysql_query(conn, zapytanie.c_str());
    //*/
    // imie, nazwisko i stanowisko zalogowanego
    string _imie,_nazwisko,_id_pracownika;
    int _stanowisko=0;
    //string _imie = "root";
    //string _nazwisko="root";
    //int _stanowisko=1;
    //string _id_pracownika = "0";
    if (!status)    {
        MYSQL_RES *res = mysql_store_result(conn);
        MYSQL_ROW row;
        row = mysql_fetch_row(res);
        _imie = row[0];
        _nazwisko = row[1];
        _id_pracownika = row[3];
        if (strcmp(row[2],"Wlasciciel")==0) _stanowisko = 1;
        else if (strcmp(row[2],"Sprzedawca")==0) _stanowisko = 2;
        else if (strcmp(row[2],"Magazynier")==0) _stanowisko = 3;
    }
    else{
        cout << "Zapytanie wykonane niepoprawanie" << endl;
    }
    //*/
    cout << "Zalogowany jako: " << _imie << " " << _nazwisko << " (" << 
        (_stanowisko==1?"Wlasciciel":(_stanowisko==2?"Sprzedawca":(_stanowisko==3?"Magazynier":"niezdefinowany")))
        << ")" << endl;

    switch (_stanowisko) {
    case 1:
        menu_wlasciciela(conn,_id_pracownika);
        break;
    case 2:
        menu_sprzedawcy(conn,_id_pracownika);
        break;
    case 3:
        menu_magazyniera(conn);
        break;
    default:
        cout << "Blad: nie rozpoznano stanowiska. Nastapi wylogowanie z bazy." << endl;
        break;
    }
    cout << "Wylogowano z bazy danych" << endl;
    mysql_close(conn);

    return 0;
}
