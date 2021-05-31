#include "aplikacja_sklepu.h"
#include "ui_aplikacja_sklepu.h"

aplikacja_sklepu::aplikacja_sklepu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplikacja_sklepu)
{
    ui->setupUi(this);


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
    pracownicy_model.dane_otrzymane = baza.wyswietl_pracownikow();
    ui->pracownicy_table->setModel(&pracownicy_model);
    ui->main_stack->setCurrentIndex(5);
}

void aplikacja_sklepu::produkty()
{
    towar_model.dane_otrzymane = baza.wyswietl_liste_produktow();
    ui->towar_table->setModel(&towar_model);
    ui->main_stack->setCurrentIndex(2);
}

void aplikacja_sklepu::klienci()
{
    klienci_model.dane_otrzymane = baza.wyswietl_liste_klientow();
    ui->klienci_table->setModel(&klienci_model);
    ui->main_stack->setCurrentIndex(4);
}

void aplikacja_sklepu::transakcje()
{
    transakcje_model.dane_otrzymane = baza.wyswietl_transakcje();
    ui->transakcje_table->setModel(&transakcje_model);
    ui->main_stack->setCurrentIndex(3);
}

void aplikacja_sklepu::menu()
{
    ui->main_stack->setCurrentIndex(1);
}

void aplikacja_sklepu::szukaj_pracownicy()
{
    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_pracownicy_txt->text());

    for (int i = 0; i < pracownicy_model.dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < pracownicy_model.dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(pracownicy_model.dane_otrzymane[i][j].c_str());
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
    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_klienci_txt->text());

    for (int i = 0; i < klienci_model.dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < klienci_model.dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(klienci_model.dane_otrzymane[i][j].c_str());
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
    QString str1, str2;
    bool pokaz = false;

    str1 = (ui->szukaj_towar_txt->text());

    for (int i = 0; i < towar_model.dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < towar_model.dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(towar_model.dane_otrzymane[i][j].c_str());
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

    for (int i = 0; i < transakcje_model.dane_otrzymane.size(); i++)
    {
        pokaz = false;
        for (int j = 0; j < transakcje_model.dane_otrzymane[i].size(); j++)
        {
            str2 = QString::fromUtf8(transakcje_model.dane_otrzymane[i][j].c_str());
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
    Dodaj_klienta nowyKlient;

    nowyKlient.show();
}


