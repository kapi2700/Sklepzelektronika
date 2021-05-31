#include "model_klienci.h"


model_klienci::model_klienci(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int model_klienci::rowCount(const QModelIndex& /*parent*/) const
{
    return dane_otrzymane.size();
}

int model_klienci::columnCount(const QModelIndex& /*parent*/) const
{
    return 11;
}

QVariant model_klienci::data(const QModelIndex& index, int role) const
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

QVariant model_klienci::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Imie");
        case 1:
            return QString("Nazwisko");
        case 2:
            return QString("email");
        case 3:
            return QString("Miejscowosc");
        case 4:
            return QString("Ulica");
        case 5:
            return QString("nr domu");
        case 6:
            return QString("nr mieszkania");
        case 7:
            return QString("kod pocztowy");
        case 8:
            return QString("NIP");
        case 9:
            return QString("Telefon");
        case 10:
            return QString("Telefon wewnętrzny");
        }
    }
    return QVariant();
}
