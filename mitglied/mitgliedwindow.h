#ifndef MITGLIEDWINDOW_H
#define MITGLIEDWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "mitglieddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MitgliedWindow; }
QT_END_NAMESPACE

class MitgliedWindow : public QMainWindow
{
    Q_OBJECT

public:
    MitgliedWindow(QWidget *parent = nullptr);
    ~MitgliedWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void onTableClicked(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::MitgliedWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif // MITGLIEDWINDOW_H
