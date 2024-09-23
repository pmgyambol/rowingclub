#ifndef GYMDIALOG_H
#define GYMDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class GymDialog;
}

class GymDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GymDialog(QWidget *parent = nullptr, int pid = 0);
    ~GymDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::GymDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};
#endif