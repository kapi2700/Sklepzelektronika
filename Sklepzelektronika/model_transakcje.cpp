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
    return 8;
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
            return QString("id klienta");
        case 1:
            return QString("id transakcji");
        case 2:
            return QString("Nazwa produktu");
        case 3:
            return QString("Cena calkowita");
        case 4:
            return QString("Liczba sztuk");
        case 5:
            return QString("id pracownika");
        case 6:
            return QString("Data sprzedazy");
        case 7:
            return Qstring("Data platnosci");
        }
    }
    return QVariant();
}
