#include "model_transakcje.h"


model_transakcje::model_transakcje(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int model_transakcje::rowCount(const QModelIndex& /*parent*/) const
{
    return dane_otrzymane.size();
}

int model_transakcje::columnCount(const QModelIndex& /*parent*/) const
{
    return 16;
}

QVariant model_transakcje::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
        if (row < dane_otrzymane.size())
            if (col < dane_otrzymane[row].size())
                return QString::fromUtf8(dane_otrzymane[row][col].c_str());
        return QString(" ");
        break;
    case Qt::FontRole:
        QFont wielkosc;
        wielkosc.setPointSize(10);
        return wielkosc;
        break;
    }
    return QVariant();
}

QVariant model_transakcje::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Kategoria");
        case 1:
            return QString("Nazwa");
        case 2:
            return QString("Liczba");
        case 3:
            return QString("Cena jednostkowa");
        case 4:
            return QString("Vat");
        case 5:
            return QString("Cecha");
        case 6:
            return QString("Wartosc");
        case 7:
            return QString("Cecha");
        case 8:
            return QString("Wartosc");
        case 9:
            return QString("Cecha");
        case 10:
            return QString("Wartosc");
        case 11:
            return QString("Cecha");
        case 12:
            return QString("Wartosc");
        case 13:
            return QString("Cecha");
        case 14:
            return QString("Wartosc");
        case 15:
            return QString("Opis");
        }
    }
    return QVariant();
}