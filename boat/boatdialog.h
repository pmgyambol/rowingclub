#ifndef BOATDIALOG_H
#define BOATDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

#include <string>
#include <vector>

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
    // enumerated types
    std::vector<std::string>      typ_types;
    std::vector<std::string> material_types;
    std::vector<std::string>   besitz_types;
};

#endif // BOATDIALOG_H
