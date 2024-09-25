#include "aufwanddialog.h"
#include "ui_aufwanddialog.h"

#include <string>
#include <iostream>

using namespace std;

AufwandDialog::AufwandDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::AufwandDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("AufwandDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    // AufwandDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from aufwand where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->fixedcostLineEdit->setText(queryone.value(1).toString());
            ui->salariesLineEdit->setText(queryone.value(2).toString());
            ui->rentLineEdit->setText(queryone.value(3).toString());
            ui->electricityLineEdit->setText(queryone.value(4).toString());
            ui->waterLineEdit->setText(queryone.value(5).toString());
            ui->heatingLineEdit->setText(queryone.value(6).toString());
            ui->amortizationLineEdit->setText(queryone.value(7).toString());
            ui->gekauftesMaterialLineEdit->setText(queryone.value(8).toString());
            ui->datumDateEdit->setDate(queryone.value(9).toDate());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

AufwandDialog::~AufwandDialog()
{
    delete ui;
}

void AufwandDialog::save()
{
    QString fixedcost         = ui->fixedcostLineEdit->text();
    QString salaries          = ui->salariesLineEdit->text();
    QString rent              = ui->rentLineEdit->text();
    QString electricity       = ui->electricityLineEdit->text();
    QString water             = ui->waterLineEdit->text();
    QString heating           = ui->heatingLineEdit->text();
    QString amortization      = ui->amortizationLineEdit->text();
    QString gekauftesMaterial = ui->gekauftesMaterialLineEdit->text();

    string  datum             = ui->datumDateEdit->date().toString("yyyy-MM-dd").toStdString();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into aufwand ( fixedcost, salaries, rent, electricity, water, heating, amortization, gekauftesMaterial, datum) values \
                                            (:fixedcost,:salaries,:rent,:electricity,:water,:heating,:amortization,:gekauftesMaterial,:datum)");
        insert.bindValue(":fixedcost", fixedcost);
        insert.bindValue(":salaries", salaries);
        insert.bindValue(":rent", rent);
        insert.bindValue(":electricity", electricity);
        insert.bindValue(":water", water);
        insert.bindValue(":heating", heating);
        insert.bindValue(":amortization", amortization);
        insert.bindValue(":gekauftesMaterial", gekauftesMaterial);
        insert.bindValue(":datum", datum.c_str());

        if (!insert.exec())
        {
            QMessageBox msg;
            msg.setText("Fehler beim Speichern!");
            msg.setWindowTitle("Fehler");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
    }
    else {
        // UPDATE table_name
        // SET column1 = value1, column2 = value2, ...
        // WHERE condition;
        QSqlQuery update;
        update.prepare("update aufwand set \
                        fixedcost=:fixedcost, salaries=:salaries, rent=:rent, electricity=:electricity, water=:water, \
                        heating=:heating, amortization=:amortization, gekauftesMaterial=:gekauftesMaterial, datum=:datum \
                        where id = " + QString::number(pid));
        update.bindValue(":fixedcost", fixedcost);
        update.bindValue(":salaries", salaries);
        update.bindValue(":rent", rent);
        update.bindValue(":electricity", electricity);
        update.bindValue(":water", water);
        update.bindValue(":heating", heating);
        update.bindValue(":amortization", amortization);
        update.bindValue(":gekauftesMaterial", gekauftesMaterial);
        update.bindValue(":datum", datum.c_str());

        if (!update.exec())
        {
            QMessageBox msg;
            msg.setText("Fehler beim Speichern!");
            msg.setWindowTitle("Fehler");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
        // qDebug() << update.lastQuery();
    }

    // Window schließen
    verlassen();
}

void AufwandDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("AufwandDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from aufwand where id = " + QString::number(pid));
            verlassen();
        }
    }
}


void AufwandDialog::verlassen()
{
    this->close();
}