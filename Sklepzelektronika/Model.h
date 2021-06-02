/*!
* \file
* \brief Definicja klasy Model
*
*Plik zawiera definicję klasy Model
*/

#pragma once


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
    /**
     * Zwraca wysokosc tabeli.
     *
     * \param parent
     * \return wysokosc tabeli
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * Zwraca szerokosc tabeli.
     *
     * \param parent
     * \return szerokosc tabeli
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * Ustala napis na danym polu tabeli.
     *
     * \param index
     * \param role
     * \return
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    /**
     * Ustalanie wartosci w naglowku tabeli.
     *
     * \param section
     * \param orientation
     * \param role
     * \return
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
    vector<vector<string>> dane_otrzymane;
};

