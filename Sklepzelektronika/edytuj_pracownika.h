#pragma once

#include <QWidget>
#include "ui_edytuj_pracownika.h"

class edytuj_pracownika : public QWidget
{
	Q_OBJECT

public:
	edytuj_pracownika(QWidget *parent = Q_NULLPTR);
	~edytuj_pracownika();

private:
	Ui::edytuj_pracownika ui;
};
