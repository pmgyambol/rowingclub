#ifndef MITBOOTDIALOG_H
#define MITBOOTDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MitbootDialog;
}

class MitbootDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MitbootDialog(QWidget *parent = nullptr, int pid = 0);
    ~MitbootDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::MitbootDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};
#endif