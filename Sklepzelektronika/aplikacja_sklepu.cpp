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

    //edycja
    connect(ui->edytujopis_klienci_btn, &QPushButton::released, this, &aplikacja_sklepu::edytujKlienta);
    connect(ui->usun_klienta_btn, &QPushButton::released, this, &aplikacja_sklepu::usunKlienta);
    connect(ui->edytuj_pracownicy_btn, & QPushButton::released, this, &aplikacja_sklepu::edytujPracownika);
    connect(ui->edytuj_towar_btn, &QPushButton::released, this, &aplikacja_sklepu::edytujTowar);
    connect(ui->kategorie_towar_btn_2, &QPushButton::released, this, &aplikacja_sklepu::aktualizuj_Towar); //to jest przycisk od ilosci towaru

    ui->main_stack->setCurrentIndex(0);
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

     
    //conn = mysql_real_connect(conn, "localhost", "root", "kapi2798", "sklep elektroniczny", 3306, NULL, 0);
    baza.conn = mysql_init(0);
    
    hasz = baza.connect_database(log, haslo);

    if (baza.conn)
    {
        ui->main_stack->setCurrentIndex(1);
        baza.dane_zalogowanego();
        ui->name_lbl->setText(baza.nazwa);
        ui->role_lbl->setText(baza.rola);

        ui->menu_btn->setEnabled(true);

        switch (baza.stanowisko)
        {
        case 1: //wlasciciel
            break;
        case 2: //sprzedawca
            ui->pracownicy_btn->setEnabled(false);
            break;
        case 3: //magazynier
            ui->pracownicy_btn->setEnabled(false);
            ui->transakcje_btn->setEnabled(false);
            ui->klienci_btn->setEnabled(false);
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
    if (pracownik != NULL)
    {
        if (pracownik->zakonczono == false)
            return;
        else
        {
            delete pracownicy_model;
            pracownicy_model = new Model;
            pracownicy_model->dane_otrzymane = baza.wyswietl_pracownikow();
            ui->pracownicy_table->setModel(pracownicy_model);
        }
        delete pracownik;
        pracownik = NULL;
    }

    if (nowyPracownik != NULL)
    {
        if (nowyPracownik->zakonczono == false)
            return;
        else
        {
            delete pracownicy_model;
            pracownicy_model = new Model;
            pracownicy_model->dane_otrzymane = baza.wyswietl_pracownikow();
            ui->pracownicy_table->setModel(pracownicy_model);
        }
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
}

void aplikacja_sklepu::wybor_towaru()
{
    QModelIndex index = ui->towar_table->currentIndex();
    int i = index.row(); // now you know which record was selected

    wybrany_towar = i;

    ui->edytuj_towar_btn->setDisabled(0);
    ui->kategorie_towar_btn_2->setDisabled(0); //to jest przycisk od ilosci towaru
}


void aplikacja_sklepu::edytujTowar()
{
    towar = new edytuj_towar(baza.conn, towar_model->dane_otrzymane[wybrany_towar], Q_NULLPTR);
    towar->show();
    towar->indeks(0);
}