#ifndef CARDIODIALOG_H
#define CARDIODIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class CardioDialog;
}

class CardioDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CardioDialog(QWidget *parent = nullptr, int pid = 0);
    ~CardioDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::CardioDialog *ui;
    // Primary Key für die Cardioen Tabelle
    int pid;
};

#endif // CARDIODIALOG_H
