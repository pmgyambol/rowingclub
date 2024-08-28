#ifndef MITGLIEDDIALOG_H
#define MITGLIEDDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MitgliedDialog;
}

class MitgliedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MitgliedDialog(QWidget *parent = nullptr, int pid = 0);
    ~MitgliedDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::MitgliedDialog *ui;
    // Primary Key für die Mitglieden Tabelle
    int pid;
};

#endif // MITGLIEDDIALOG_H
