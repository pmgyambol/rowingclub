#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingDialog(QWidget *parent = nullptr, int pid = 0);
    ~TrainingDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::TrainingDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};
#endif