#ifndef PLANENTRAININGDIALOG_H
#define PLANENTRAININGDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

#include <string>
#include <vector>

#include "mitboot/mitbootwindow.h"
#include "cardio/cardiowindow.h"
#include "gym/gymwindow.h"

namespace Ui {
class PlanenTrainingDialog;
}

class PlanenTrainingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlanenTrainingDialog(QWidget *parent = nullptr, int pid = 0);
    ~PlanenTrainingDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

    void cardio();
    void gym();
    void boat();

    void planen_training();

private:
    Ui::PlanenTrainingDialog *ui;
    // Primary Key für die Mitglieden Tabelle
    int pid;
    // enumerated types
    std::vector<std::string>          typ_types;
    std::vector<std::string>          sex_types;
    std::vector<std::string>  nationality_types;
};
#endif