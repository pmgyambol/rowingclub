#include "einkommendialog.h"
#include "ui_einkommendialog.h"

#include <string>
#include <iostream>

using namespace std;

EinkommenDialog::EinkommenDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::EinkommenDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("EinkommenDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    ui->datumDateEdit->setDate(QDate::currentDate());

    // EinkommenDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from einkommen where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->mitgliedsbeitragLineEdit->setText(queryone.value(1).toString());
            ui->bootsverleihLineEdit->setText(queryone.value(2).toString());
            ui->gastebeitragLineEdit->setText(queryone.value(3).toString());
            ui->bootshausmietenLineEdit->setText(queryone.value(4).toString());
            ui->foderationssubventionLineEdit->setText(queryone.value(5).toString());
            ui->werbungLineEdit->setText(queryone.value(6).toString());
            ui->freiearbeitLineEdit->setText(queryone.value(7).toString());
            ui->mitgliedLineEdit->setText(queryone.value(8).toString());
            ui->boatLineEdit->setText(queryone.value(9).toString());
            ui->datumDateEdit->setDate(queryone.value(10).toDate());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

EinkommenDialog::~EinkommenDialog()
{
    delete ui;
}

void EinkommenDialog::save()
{
    QString mitgliedsbeitrag      =  ui->mitgliedsbeitragLineEdit->text();
    QString bootsverleih          =  ui->bootsverleihLineEdit->text();
    QString gastebeitrag          =  ui->gastebeitragLineEdit->text();
    QString bootshausmieten       =  ui->bootshausmietenLineEdit->text();
    QString foderationssubvention =  ui->foderationssubventionLineEdit->text();
    QString werbung               =  ui->werbungLineEdit->text();
    QString freiearbeit           =  ui->freiearbeitLineEdit->text();
    QString mitgliedid            =  ui->mitgliedLineEdit->text();
    QString boatid                =  ui->boatLineEdit->text();

    string  datum                 = ui->datumDateEdit->date().toString("yyyy-MM-dd").toStdString();

    if ( mitgliedsbeitrag.toInt() < 0  || bootsverleih.toInt() < 0 || gastebeitrag.toInt() < 0 || bootshausmieten.toInt() < 0 || 
         foderationssubvention.toInt() < 0 || werbung.toInt() < 0 || freiearbeit.toInt() < 0 || mitgliedid.toInt() < 0 || boatid.toInt() < 0 )
    {
        return;
    }

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into einkommen \
                        ( mitgliedsbeitrag, bootsverleih, gastebeitrag, bootshausmieten, foderationssubvention, werbung, freiearbeit, mitgliedid, boatid, datum) values \
                        (:mitgliedsbeitrag,:bootsverleih,:gastebeitrag,:bootshausmieten,:foderationssubvention,:werbung,:freiearbeit,:mitgliedid,:boatid,:datum)");
        insert.bindValue(":mitgliedsbeitrag", mitgliedsbeitrag);
        insert.bindValue(":bootsverleih", bootsverleih);
        insert.bindValue(":gastebeitrag", gastebeitrag);
        insert.bindValue(":bootshausmieten", bootshausmieten);
        insert.bindValue(":foderationssubvention", foderationssubvention);
        insert.bindValue(":werbung", werbung);
        insert.bindValue(":freiearbeit", freiearbeit);
        insert.bindValue(":mitgliedid", mitgliedid);
        insert.bindValue(":boatid", boatid);
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
        update.prepare("update einkommen set \
                        mitgliedsbeitrag=:mitgliedsbeitrag, bootsverleih=:bootsverleih, gastebeitrag=:gastebeitrag, \
                        bootshausmieten=:bootshausmieten, foderationssubvention=:foderationssubvention, \
                        werbung=:werbung, freiearbeit=:freiearbeit, mitgliedid=:mitgliedid, boatid=:boatid, datum=:datum \
                        where id = " + QString::number(pid));

        update.bindValue(":mitgliedsbeitrag", mitgliedsbeitrag);
        update.bindValue(":bootsverleih", bootsverleih);
        update.bindValue(":gastebeitrag", gastebeitrag);
        update.bindValue(":bootshausmieten", bootshausmieten);
        update.bindValue(":foderationssubvention", foderationssubvention);
        update.bindValue(":werbung", werbung);
        update.bindValue(":freiearbeit", freiearbeit);
        update.bindValue(":mitgliedid", mitgliedid);
        update.bindValue(":boatid", boatid);
        update.bindValue(":datum", datum.c_str());

        if (!update.exec())
        {
            QMessageBox msg;
            msg.setText("Fehler beim Speichern!");
            msg.setWindowTitle("Fehler");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
    }

    // Window schließen
    verlassen();
}

void EinkommenDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("EinkommenDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from einkommen where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void EinkommenDialog::verlassen()
{
    this->close();
}