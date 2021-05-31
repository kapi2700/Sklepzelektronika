#pragma once

#include <QWidget>
#include "ui_Dodaj_klienta.h"

class Dodaj_klienta : public QWidget
{
	Q_OBJECT

public:
	Dodaj_klienta(QWidget *parent = Q_NULLPTR);
	~Dodaj_klienta();

private:
	Ui::Dodaj_klienta ui;
};
