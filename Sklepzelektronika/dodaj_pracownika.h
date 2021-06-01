#pragma once

#include <QWidget>
#include "ui_dodaj_pracownika.h"
#include <vector>
#include <mysql.h>
#include <string>

class dodaj_pracownika : public QWidget
{
	Q_OBJECT

public:
	dodaj_pracownika(QWidget *parent = Q_NULLPTR);
	~dodaj_pracownika();

private:
	Ui::dodaj_pracownika ui;
};
