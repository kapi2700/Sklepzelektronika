#include "aplikacja_sklepu.h"
#include "ui_aplikacja_sklepu.h"

aplikacja_sklepu::aplikacja_sklepu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplikacja_sklepu)
{
    ui->setupUi(this);

    connect(ui->zaloguj_button, &QPushButton::released, this, &aplikacja_sklepu::zaloguj);

    connect(ui->menu_btn, &QPushButton::released, this, &aplikacja_sklepu::menu);

    connect(ui->pracownicy_btn, &QPushButton::released, this, &aplikacja_sklepu::pracownicy);
    connect(ui->produkty_btn, &QPushButton::released, this, &aplikacja_sklepu::produkty);
    connect(ui->klienci_btn, &QPushButton::released, this, &aplikacja_sklepu::klienci);
    connect(ui->transakcje_btn, &QPushButton::released, this, &aplikacja_sklepu::transakcje);
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
    ui->main_stack->setCurrentIndex(4);
}

void aplikacja_sklepu::transakcje()
{
    ui->main_stack->setCurrentIndex(3);
}



void aplikacja_sklepu::menu()
{
    ui->main_stack->setCurrentIndex(1);
}

