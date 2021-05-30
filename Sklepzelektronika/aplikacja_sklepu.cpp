#include "aplikacja_sklepu.h"
#include "ui_aplikacja_sklepu.h"

aplikacja_sklepu::aplikacja_sklepu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplikacja_sklepu)
{
    ui->setupUi(this);
}

aplikacja_sklepu::~aplikacja_sklepu()
{
    delete ui;
}

