#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

#include "mitboot/mitbootwindow.h"
#include "cardio/cardiowindow.h"
#include "gym/gymwindow.h"

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingDialog(QWidget *parent = nullptr, int recordId = 0, int memberId = 0);
    ~TrainingDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

    void cardio();
    void gym();
    void boat();

private:
    Ui::TrainingDialog *ui;
    // Primary Key für die Boaten Tabelle
    int rid,
        mid;
};
#endif