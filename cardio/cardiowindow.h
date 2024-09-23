#ifndef CARDIOWINDOW_H
#define CARDIOWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "cardiodialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CardioWindow; }
QT_END_NAMESPACE

class CardioWindow : public QMainWindow
{
    Q_OBJECT

public:
    CardioWindow(QWidget *parent = nullptr);
    ~CardioWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::CardioWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif // CARDIOWINDOW_H
