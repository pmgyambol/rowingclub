#ifndef EINKOMMENDIALOG_H
#define EINKOMMENDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class EinkommenDialog;
}

class EinkommenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EinkommenDialog(QWidget *parent = nullptr, int pid = 0);
    ~EinkommenDialog();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::EinkommenDialog *ui;
    // Primary Key für die Boaten Tabelle
    int pid;
};
#endif