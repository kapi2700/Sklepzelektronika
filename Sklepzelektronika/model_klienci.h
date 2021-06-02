/*!
* \file
* \brief Definicja klasy model_klienci
*
*Plik zawiera definicję klasy model_klienci
*/
#pragma once


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

