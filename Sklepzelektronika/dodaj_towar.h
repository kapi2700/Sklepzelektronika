#pragma once

#include <QWidget>
#include "ui_dodaj_towar.h"
#include <vector>
#include <mysql.h>
#include <string>

class dodaj_towar : public QWidget
{
	Q_OBJECT

public:
	dodaj_towar(QWidget *parent = Q_NULLPTR);
	~dodaj_towar();

private:
	Ui::dodaj_towar ui;

};
