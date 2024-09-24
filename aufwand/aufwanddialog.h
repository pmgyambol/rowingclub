#ifndef AUFWANDDIALOG_H
#define AUFWANDDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class AufwandDialog;
}

class AufwandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AufwandDialog(QWidget *parent = nullptr, int pid = 0);
    ~AufwandDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::AufwandDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};
#endif