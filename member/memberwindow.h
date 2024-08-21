#ifndef MEMBERWINDOW_H
#define MEMBERWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "memberdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MemberWindow; }
QT_END_NAMESPACE

class MemberWindow : public QMainWindow
{
    Q_OBJECT

public:
    MemberWindow(QWidget *parent = nullptr);
    ~MemberWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::MemberWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
#endif // MEMBERWINDOW_H
