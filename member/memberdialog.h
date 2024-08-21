#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MemberDialog;
}

class MemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemberDialog(QWidget *parent = nullptr, int pid = 0);
    ~MemberDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::MemberDialog *ui;
    // Primary Key für die Memberen Tabelle
    int pid;
};

#endif // MEMBERDIALOG_H
