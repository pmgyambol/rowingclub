#ifndef BOATWINDOW_H
#define BOATWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "boatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BoatWindow; }
QT_END_NAMESPACE

class BoatWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoatWindow(QWidget *parent = nullptr);
    ~BoatWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::BoatWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif // BOATWINDOW_H
