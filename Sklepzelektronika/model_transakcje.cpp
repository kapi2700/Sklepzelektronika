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
    return 6;
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
            return QString("id pracownika");
        case 3:
            return QString("cena calkowita");
        case 4:
            return QString("data sprzedazy");
        case 5:
            return QString("data platnosci");
        }
    }
    return QVariant();
}
