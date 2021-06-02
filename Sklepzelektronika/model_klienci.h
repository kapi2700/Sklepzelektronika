#pragma once

/*!
* \file
* \brief Definicja klasy model_klienci
*
*Plik zawiera definicję klasy model_klienci
*/

#include <qabstractitemmodel.h>
#include <string>
#include <vector>
#include <qfont>

using namespace std;

class model_klienci :
    public QAbstractTableModel
{
    Q_OBJECT
public:
    model_klienci(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    vector<vector<string>> dane_otrzymane;
};

