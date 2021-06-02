#include "aplikacja_sklepu.h"
#include "ui_aplikacja_sklepu.h"

aplikacja_sklepu::aplikacja_sklepu(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::aplikacja_sklepu)
{
    ui->setupUi(this);

    klienci_model = NULL;
    klient = NULL;
    nowyKlient = NULL;

    pracownicy_model = NULL;
    nowyPracownik = NULL;
    pracownik = NULL;

    nowaKategoria = NULL;

    towar_model = NULL;
    nowyTowar = NULL;
    towar = NULL;

    transakcje_model = NULL;

    zmiany_klienci = false;

    ui->edytujopis_klienci_btn->setDisabled(1);

    wybrany_klient = -1;
    wybrany_pracownik = -1;
    wybrany_towar = -1;

    kosz = NULL;

    id_zalogowanej_osoby = -1;

    //logowanie
    connect(ui->zaloguj_button, &QPushButton::released, this, &aplikacja_sklepu::zaloguj);

    //powrot do menu
    connect(ui->menu_btn, &QPushButton::released, this, &aplikacja_sklepu::menu);


    //menu
    connect(ui->pracownicy_btn, &QPushButton::released, this, &aplikacja_sklepu::pracownicy);
    connect(ui->produkty_btn, &QPushButton::released, this, &aplikacja_sklepu::produkty);
    connect(ui->klienci_btn, &QPushButton::released, this, &aplikacja_sklepu::klienci);
    connect(ui->transakcje_btn, &QPushButton::released, this, &aplikacja_sklepu::transakcje);


    //przeszukiwanie tabel
    connect(ui->szukaj_pracownicy_btn, &QPushButton::released, this, &aplikacja_sklepu::szukaj_pracownicy);
    connect(ui->szukaj_towar_btn, &QPushButton::released, this, &aplikacja_sklepu::szukaj_produkty);
    connect(ui->szukaj_trans_btn, &QPushButton::released, this, &aplikacja_sklepu::szukaj_transakcje);
    connect(ui->szukaj_klienci_btn, &QPushButton::released, this, &aplikacja_sklepu::szukaj_klienci);


    //dodawanie nowych
    connect(ui->dodaj_klienta_btn, &QPushButton::released, this, &aplikacja_sklepu::dodaj_klienta_rel);
    connect(ui->dodaj_pracownicy_btn, &QPushButton::released, this, &aplikacja_sklepu::dodaj_Pracownika);
    connect(ui->dodaj_towar_btn, &QPushButton::released, this, &aplikacja_sklepu::dodaj_Towar);
    connect(ui->kategorie_towar_btn, &QPushButton::released, this, &aplikacja_sklepu::dodaj_Kategorie);

    //wybieranie
    connect(ui->klienci_table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(wybor_klienta()));
    connect(ui->pracownicy_table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(wybor_pracownika()));
    connect(ui->towar_table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(wybor_towaru()));
    connect(ui->transakcje_table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(wybor_transakcji()));
    connect(ui->szczegoly_table, SIGNAL(clicked(const QModelIndex&)), this, SLOT(wybor_szczegolow()));

    //edycja
    connect(ui->edytujopis_klienci_btn, &QPushButton::released, this, &aplikacja_sklepu::edytujKlienta);
    connect(ui->usun_klienta_btn, &QPushButton::released, this, &aplikacja_sklepu::usunKlienta);
    connect(ui->edytuj_pracownicy_btn, & QPushButton::released, this, &aplikacja_sklepu::edytujPracownika);
    connect(ui->edytuj_towar_btn, &QPushButton::released, this, &aplikacja_sklepu::edytujTowar);
    connect(ui->kategorie_towar_btn_2, &QPushButton::released, this, &aplikacja_sklepu::aktualizuj_Towar); //to jest przycisk od ilosci towaru
    connect(ui->usun_pracownicy_btn, &QPushButton::released, this, &aplikacja_sklepu::usunPracownika);


    //koszyk
    connect(ui->koszyk_btn, &QPushButton::released, this, &aplikacja_sklepu::pokazkoszyk);
    connect(ui->wyczysckoszyk_btn, &QPushButton::released, this, &aplikacja_sklepu::wyczysc_koszyk);
    connect(ui->dodajdokoszyka_btn, &QPushButton::released, this, &aplikacja_sklepu::dodajdokoszyka);

    //reklamacja
    //connect(ui->reklamacja_btn, &QPushButton::released, this, &aplikacja_sklepu::reklamuj);

    ui->main_stack->setCurrentIndex(0);

    if (baza.stanowisko == 1)
    {
        ui->dodaj_towar_btn->setDisabled(1);
        ui->kategorie_towar_btn->setDisabled(1);
    }
}

aplikacja_sklepu::~aplikacja_sklepu()
{
    delete ui;
}

void aplikacja_sklepu::zaloguj()
{
    bool wyjdz = false;
    string hasz;

    QString str1;
    QString str2;  
    str1 = (ui->login_logowanie_edit->text());
    str2 = (ui->haslo_logowanie_edit->text());

    pracownicy_model = NULL;
    towar_model = NULL;
    klienci_model = NULL;
    transakcje_model = NULL;

    QByteArray lo = str1.toLocal8Bit();
    const char* log = lo.data();
    QByteArray ha = str2.toLocal8Bit();
    const char* haslo = ha.data();

    baza.conn = mysql_init(0);
    
    hasz = baza.connect_database(log, haslo);


    if (baza.conn)
    {


        ui->main_stack->setCurrentIndex(1);
        id_zalogowanej_osoby = baza.dane_zalogowanego();
        ui->name_lbl->setText(baza.nazwa);
        ui->role_lbl->setText(baza.rola);

        ui->menu_btn->setEnabled(true);


        switch (baza.stanowisko)
        {
        case 1: //wlasciciel
            break;
        case 2: //sprzedawca
            ui->pracownicy_btn->setDisabled(1);
            break;
        case 3: //magazynier
            ui->pracownicy_btn->setDisabled(1);
            ui->transakcje_btn->setDisabled(1);
            ui->klienci_btn->setDisabled(1);
            break;
        }

    }
    else
    {
        if (baza.probylogowania < 3)
        {
            ui->niepoprawnedane_lbl->setText("Niepoprawne dane!");
            baza.probylogowania++;
        }
        else
        {
            ui->niepoprawnedane_lbl->setText("Przekroczono ilosc logowan!");
            Sleep(4000);
            QApplication::quit();
        }
    }
}

void aplikacja_sklepu::pracownicy()
{
    if (pracownicy_model != NULL)
        delete pracownicy_model;

    pracownicy_model = new Model;
    pracownicy_model->dane_otrzymane = baza.wyswietl_pracownikow();
    ui->pracownicy_table->setModel(pracownicy_model);
    ui->main_stack->setCurrentIndex(5);
}

void aplikacja_sklepu::produkty()
{
    if (towar_model != NULL)
        delete towar_model;

    towar_model = new model_towar;
    towar_model->dane_otrzymane = baza.wyswietl_liste_produktow();
    ui->towar_table->setModel(towar_model);
    ui->main_stack->setCurrentIndex(2);
}

void aplikacja_sklepu::klienci()
{
    if (klienci_model != NULL)
        delete klienci_model;

    klienci_model = new model_klienci;
    klienci_model->dane_otrzymane = baza.wyswietl_liste_klientow();
    ui->klienci_table->setModel(klienci_model);
    ui->main_stack->setCurrentIndex(4);
}

void aplikacja_sklepu::transakcje()
{
    if (transakcje_model != NULL)
        delete transakcje_model;

    transakcje_model = new model_transakcje;
    transakcje_model->dane_otrzymane = baza.wyswietl_transakcje();
    ui->transakcje_table->setModel(transakcje_model);
    ui->main_stack->setCurrentIndex(3);
}

void aplikacja_sklepu::menu()
{
    ui->main_stack->setCurrentIndex(1);
}

void aplikacja_sklepu::szukaj_pracownicy()
{
    pracownicy();

    if (pracownik != NULL)
    {
        if (pracownik->zakonczono == false)
            return;
        delete pracownik;
        pracownik = NULL;
    }

    if (nowyPracownik != NULL)
    {
        if (nowyPracownik->zakonczono == false)
            return;
        //else
        //{
        //    delete pracownicy_model;
        //    pracownicy_model = new Model;
        //    pracownicy_model->dane_otrzymane = baza.wyswietl_pracownikow();
        //    ui->pracownicy_table->setModel(pracownicy_model);
        //}
        delete nowyPracownik;
        nowyPracownik = NULL;
    }

    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_pracownicy_txt->text());

    for (int i = 0; i < pracownicy_model->dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < pracownicy_model->dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(pracownicy_model->dane_otrzymane[i][j].c_str());
            pokaz = (str2.contains(str1, Qt::CaseInsensitive));
            if (pokaz)
                break;
        }
        if (!pokaz)
            ui->pracownicy_table->hideRow(i);
        else
            ui->pracownicy_table->showRow(i);
    }
}

void aplikacja_sklepu::szukaj_klienci()
{
    if (klient != NULL)
    {
        if (klient->zakonczono == false)
            return;
        else
        {
            if (klient->zapelnione)
            {
                delete klienci_model;
                klienci_model = new model_klienci;
                klienci_model->dane_otrzymane = baza.wyswietl_liste_klientow();
                ui->klienci_table->setModel(klienci_model);
            }
        }
        delete klient;
        klient = NULL;
    }

    if (zmiany_klienci)
    {
        delete klienci_model;
        klienci_model = new model_klienci;
        klienci_model->dane_otrzymane = baza.wyswietl_liste_klientow();
        ui->klienci_table->setModel(klienci_model);
        zmiany_klienci = false;
    }

    if (nowyKlient != NULL)
    {
        if (nowyKlient->zakonczono == false)
            return;
        else
        {
            if (nowyKlient->zapelnione)
            {
                string zapytanie = "call add_client(";
                for (int i = 0; i < nowyKlient->dane.size(); i++)
                {
                    zapytanie += nowyKlient->dane[i];
                    if (i != (nowyKlient->dane.size() - 1))
                    {
                        zapytanie += ",";
                    }
                }
                zapytanie += ");";

                int status = mysql_query(baza.conn, zapytanie.c_str());
                if (!status)
                {
                    delete klienci_model;
                    klienci_model = new model_klienci;
                    klienci_model->dane_otrzymane = baza.wyswietl_liste_klientow();
                    ui->klienci_table->setModel(klienci_model);
                }
                else
                {
                    return;
                }
            }
            delete nowyKlient;
            nowyKlient = NULL;
        }
    }

    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_klienci_txt->text());

    for (int i = 0; i < klienci_model->dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < klienci_model->dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(klienci_model->dane_otrzymane[i][j].c_str());
            pokaz = (str2.contains(str1, Qt::CaseInsensitive));
            if (pokaz)
                break;
        }
        if (!pokaz)
            ui->klienci_table->hideRow(i);
        else
            ui->klienci_table->showRow(i);
    }
}

void aplikacja_sklepu::szukaj_produkty()
{
    if (towar != NULL)
    {
        if (towar->zakonczono == false)
            return;
        else
        {
            delete towar_model;
            towar_model = new model_towar;
            towar_model->dane_otrzymane = baza.wyswietl_liste_produktow();
            ui->towar_table->setModel(towar_model);
        }
        delete towar;
        towar = NULL;
    }

    if (nowyTowar != NULL)
    {
        if (nowyTowar->zakonczono == false)
            return;
        else
        {
            delete towar_model;
            towar_model = new model_towar;
            towar_model->dane_otrzymane = baza.wyswietl_liste_produktow();
            ui->towar_table->setModel(towar_model);
        }
        delete nowyTowar;
        nowyTowar = NULL;
    }

    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_towar_txt->text());

    for (int i = 0; i < towar_model->dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < towar_model->dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(towar_model->dane_otrzymane[i][j].c_str());
            pokaz = (str2.contains(str1, Qt::CaseInsensitive));
            if (pokaz)
                break;
        }
        if (!pokaz)
            ui->towar_table->hideRow(i);
        else
            ui->towar_table->showRow(i);
    }
}

void aplikacja_sklepu::szukaj_transakcje()
{
    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_trans_txt->text());

    for (int i = 0; i < transakcje_model->dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < transakcje_model->dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(transakcje_model->dane_otrzymane[i][j].c_str());
            pokaz = (str2.contains(str1, Qt::CaseInsensitive));
            if (pokaz)
                break;
        }
        if (!pokaz)
            ui->transakcje_table->hideRow(i);
        else
            ui->transakcje_table->showRow(i);
    }
}

void aplikacja_sklepu::dodaj_klienta_rel()
{
    nowyKlient = new Dodaj_klienta;
    nowyKlient->show();
}

void aplikacja_sklepu::wybor_klienta()
{
    QModelIndex index = ui->klienci_table->currentIndex();
    int i = index.row(); // now you know which record was selected
    string jeden;

    jeden = klienci_model->dane_otrzymane[i][1];
    jeden += " ";
    jeden += klienci_model->dane_otrzymane[i][2];   //imie i nazwisko

    QString str = QString::fromUtf8(jeden.c_str());
    ui->name_klienci_lbl->setText(str);

    jeden = (klienci_model->dane_otrzymane[i][3]);  //email
    str = QString::fromUtf8(jeden.c_str());
    ui->email_klienci_lbl->setText(str);

    jeden = (klienci_model->dane_otrzymane[i][11]); //telefon1
    str = QString::fromUtf8(jeden.c_str());
    ui->telefon1_klienci_lbl->setText(str);

    jeden = (klienci_model->dane_otrzymane[i][12]); //telefon2
    str = QString::fromUtf8(jeden.c_str());
    ui->telefon2_klienci_lbl->setText(str);

    jeden = klienci_model->dane_otrzymane[i][6];
    jeden += " ";
    jeden += klienci_model->dane_otrzymane[i][7];
    if (klienci_model->dane_otrzymane[i][7] != "")
    {
        jeden += "/";
        jeden += klienci_model->dane_otrzymane[i][8];
    }
    jeden += " ";
    jeden += klienci_model->dane_otrzymane[i][9];
    jeden += " ";
    jeden += klienci_model->dane_otrzymane[i][5];

    str = QString::fromUtf8(jeden.c_str());
    ui->adres_klienci_lbl->setText(str);            //adres



    jeden = klienci_model->dane_otrzymane[i][4];    //opis
    str = QString::fromUtf8(jeden.c_str());
    ui->opis_txtbrwsr->setText(str);

    wybrany_klient = i;

    ui->edytujopis_klienci_btn->setDisabled(0);
}


void aplikacja_sklepu::edytujKlienta()
{
    klient = new edytuj_klienta(baza.conn, klienci_model->dane_otrzymane[wybrany_klient], Q_NULLPTR);
    klient->show();
}

void aplikacja_sklepu::usunKlienta()
{
    string _imie = klienci_model->dane_otrzymane[wybrany_klient][1];
    if (_imie != "NULL")_imie = "\"" + _imie + "\"";
    else _imie = "null";
    string _nazwisko = klienci_model->dane_otrzymane[wybrany_klient][2];
    if (_nazwisko != "NULL") _nazwisko = "\"" + _nazwisko + "\"";
    else _nazwisko = "null";
    string _nip = klienci_model->dane_otrzymane[wybrany_klient][10];
    if (_nip != "NULL")_nip = "\"" + _nip + "\"";
    else _nip = "null";
    string zapytanie = "call del_client(" + _imie + "," + _nazwisko + "," + _nip + ");";
    mysql_query(baza.conn, zapytanie.c_str());

    zmiany_klienci = true;
}

void aplikacja_sklepu::dodaj_Pracownika()
{
    nowyPracownik = new dodaj_pracownika(baza.conn, Q_NULLPTR);
    nowyPracownik->show();
}

void aplikacja_sklepu::dodaj_Kategorie()
{
    nowaKategoria = new dodaj_kategorie(baza.conn, Q_NULLPTR);
    nowaKategoria->show();
}

void aplikacja_sklepu::dodaj_Towar()
{
    nowyTowar = new dodaj_towar(baza.conn, Q_NULLPTR);
    nowyTowar->show();
}

void aplikacja_sklepu::aktualizuj_Towar()
{
    towar = new edytuj_towar(baza.conn, towar_model->dane_otrzymane[wybrany_towar], Q_NULLPTR);
    towar->show();
    towar->indeks(1);
}

void aplikacja_sklepu::wyczysc_koszyk()
{
    wkoszyku.clear();
    iloscwkoszyku.clear();
}

void aplikacja_sklepu::usunPracownika()
{
    string _imie = pracownicy_model->dane_otrzymane[wybrany_pracownik][1];
    if (_imie != "NULL")_imie = "\"" + _imie + "\"";
    else _imie = "null";
    string _nazwisko = pracownicy_model->dane_otrzymane[wybrany_pracownik][2];
    if (_nazwisko != "NULL") _nazwisko = "\"" + _nazwisko + "\"";
    else _nazwisko = "null";
    string zapytanie = "call del_worker(" + _imie + "," + _nazwisko + ");";
    mysql_query(baza.conn, zapytanie.c_str());
}

void aplikacja_sklepu::edytujPracownika()
{
    pracownik = new edytuj_pracownika(baza.conn, pracownicy_model->dane_otrzymane[wybrany_pracownik], Q_NULLPTR);
    pracownik->show();
}

void aplikacja_sklepu::wybor_pracownika()
{
    QModelIndex index = ui->pracownicy_table->currentIndex();
    int i = index.row(); // now you know which record was selected

    wybrany_pracownik = i;

    ui->edytuj_pracownicy_btn->setDisabled(0);
    ui->usun_pracownicy_btn->setDisabled(0);
}

void aplikacja_sklepu::wybor_towaru()
{
    QModelIndex index = ui->towar_table->currentIndex();
    int i = index.row(); // now you know which record was selected

    wybrany_towar = i;



    if (baza.stanowisko == 1)
    {
        ui->edytuj_towar_btn->setDisabled(0);
        ui->kategorie_towar_btn_2->setDisabled(0); //to jest przycisk od ilosci towaru
        ui->ilosc_dodawana->setDisabled(0);
        ui->ilosc_dodawana->setMaximum(stoi(towar_model->dane_otrzymane[i][2]));
    }
    if (baza.stanowisko != 3)
    {
        ui->dodajdokoszyka_btn->setDisabled(0);
    }
}


void aplikacja_sklepu::edytujTowar()
{
    towar = new edytuj_towar(baza.conn, towar_model->dane_otrzymane[wybrany_towar], Q_NULLPTR);
    towar->show();
    towar->indeks(0);
}

void aplikacja_sklepu::dodajdokoszyka()
{
    int ilosc;
    ilosc = ui->ilosc_dodawana->value();

    wkoszyku.push_back(towar_model->dane_otrzymane[wybrany_towar][1]);
    iloscwkoszyku.push_back(ilosc);
}

void aplikacja_sklepu::pokazkoszyk()
{
    kosz = new koszyk(id_zalogowanej_osoby, wkoszyku, iloscwkoszyku, baza.conn, Q_NULLPTR);
    kosz->show();
}


void aplikacja_sklepu::wybor_transakcji()
{
    QModelIndex index = ui->transakcje_table->currentIndex();
    int i = index.row(); // now you know which record was selected

    wybrana_transakcja = i;

    ui->szczegoly_table->clearContents();
    ui->szczegoly_table->clear();
    szczegoly_transakcji();
    ui->reklamacja_btn->setEnabled(0);

}

void aplikacja_sklepu::szczegoly_transakcji()
{


    string _id_transakcji;

    _id_transakcji = transakcje_model->dane_otrzymane[wybrana_transakcja][1];
    _id_transakcji = "\"" + _id_transakcji + "\"";

    ui->szczegoly_table->setColumnCount(5);

    string zapytanie = "call view_transaction(" + _id_transakcji + ");";
    int status = mysql_query(baza.conn, zapytanie.c_str());
    int j = 0;
    if (!status) {
        MYSQL_RES* res = mysql_store_result(baza.conn);
        MYSQL_ROW row;
        while (row = mysql_fetch_row(res)) {
            ui->szczegoly_table->insertRow(0);
            for (int i = 0; i < 5; ++i) {
                QTableWidgetItem* nazwa = new QTableWidgetItem(QString::fromStdString(row[i]));
                ui->szczegoly_table->setItem(j, i, nazwa);
            }
            j++;
        }
    }
    else
    {
        ui->bledy_transakcje_lbl->setText(QString::fromUtf8(zapytanie.c_str()));
    }
}

void aplikacja_sklepu::wybor_szczegolow()
{
    QModelIndex index = ui->transakcje_table->currentIndex();
    int i = index.row(); // now you know which record was selected

    wybrane_szczegoly = i;

    ui->reklamacja_btn->setEnabled(1);
}

void aplikacja_sklepu::reklamuj()
{
    string _id_transakcji;

    _id_transakcji = transakcje_model->dane_otrzymane[wybrana_transakcja][1];
    _id_transakcji = "\"" + _id_transakcji + "\"";


    string _id_produktu;

    _id_produktu = transakcje_model->dane_otrzymane[wybrana_transakcja][1];
    _id_produktu = "\"" + _id_produktu + "\"";

    string zapytanie = "SELECT count(*) FROM szczegoly_transakcji WHERE id_transakcji="
        + _id_transakcji + " AND id_produktu=" + _id_produktu + ";";
    int status = mysql_query(baza.conn, zapytanie.c_str());
    int result = -1;
    
    if (!status) {
        MYSQL_RES* res = mysql_store_result(baza.conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        result = atoi(row[0]);
    }

}
