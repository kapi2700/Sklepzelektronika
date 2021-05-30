#include "Model.h"


Model::Model(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int Model::rowCount(const QModelIndex& /*parent*/) const
{
    return dane_otrzymane.size();
}

int Model::columnCount(const QModelIndex& /*parent*/) const
{
    return 4;
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called

    switch (role) {
    case Qt::DisplayRole:
        if (row < dane_otrzymane.size())
            if (col < dane_otrzymane[row].size())
                return QString::fromUtf8(dane_otrzymane[row][col].c_str());
        if (col == 3)
        {
            return QString("Edytuj");
        }
        break;
    case Qt::FontRole:
        QFont wielkosc;
        wielkosc.setPointSize(16);
        return wielkosc;
        break;
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Imie");
        case 1:
            return QString("Nazwisko");
        case 2:
            return QString("Rola");
        }
    }
    return QVariant();
}