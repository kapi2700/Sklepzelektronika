#pragma once

/*!
* \file
* \brief Definicja klasy Model
*
*Plik zawiera definicję klasy Model
*/

#include <qabstractitemmodel>
#include <qfont.h>
#include <qbrush.h>
#include <vector>
#include <string>

using namespace std;

class Model :
    public QAbstractTableModel
{
    Q_OBJECT
public:
    Model(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
    vector<vector<string>> dane_otrzymane;
};

