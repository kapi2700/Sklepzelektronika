#pragma once

#include <QWidget>
#include "ui_koszyk.h"

class koszyk : public QWidget
{
	Q_OBJECT

public:
	koszyk(QWidget *parent = Q_NULLPTR);
	~koszyk();

private:
	Ui::koszyk ui;
};
