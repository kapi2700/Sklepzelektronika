#ifndef APLIKACJA_SKLEPU_H
#define APLIKACJA_SKLEPU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class aplikacja_sklepu; }
QT_END_NAMESPACE

class aplikacja_sklepu : public QMainWindow
{
    Q_OBJECT

public:
    aplikacja_sklepu(QWidget *parent = nullptr);
    ~aplikacja_sklepu();

private:
    Ui::aplikacja_sklepu *ui;
};
#endif // APLIKACJA_SKLEPU_H
