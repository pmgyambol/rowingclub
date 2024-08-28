#ifndef BOATDIALOG_H
#define BOATDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class BoatDialog;
}

class BoatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BoatDialog(QWidget *parent = nullptr, int pid = 0);
    ~BoatDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::BoatDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};

#endif // BOATDIALOG_H
