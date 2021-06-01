#pragma once

#include <QWidget>
#include "ui_edytuj_towar.h"

class edytuj_towar : public QWidget
{
	Q_OBJECT

public:
	edytuj_towar(QWidget *parent = Q_NULLPTR);
	~edytuj_towar();

private:
	Ui::edytuj_towar ui;
};
