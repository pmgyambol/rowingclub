#ifndef MITBOOTWINDOW_H
#define MITBOOTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "mitbootdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MitbootWindow; }
QT_END_NAMESPACE

class MitbootWindow : public QMainWindow
{
    Q_OBJECT

public:
    MitbootWindow(QWidget *parent = nullptr);
    ~MitbootWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::MitbootWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif