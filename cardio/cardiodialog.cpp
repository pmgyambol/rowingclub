#include "cardiodialog.h"
#include "ui_cardiodialog.h"

#include <string>
#include <iostream>

using namespace std;

CardioDialog::CardioDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::CardioDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("CardioDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    // CardioDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from cardios where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->paddelErgometerCanuLineEdit->setText(queryone.value(1).toString());
            ui->paddelErgometerKayakLineEdit->setText(queryone.value(2).toString());
            ui->runningLineEdit->setText(queryone.value(3).toString());
            ui->byciclingLineEdit->setText(queryone.value(4).toString());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

CardioDialog::~CardioDialog()
{
    delete ui;
}

void CardioDialog::save()
{
    QString paddelErgometerCanu  = ui->paddelErgometerCanuLineEdit->text();
    QString paddelErgometerKayak = ui->paddelErgometerKayakLineEdit->text();
    QString running              = ui->runningLineEdit->text();
    QString bycicling            = ui->byciclingLineEdit->text();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into cardios ( paddelErgometerCanu, paddelErgometerKayak, running, bycicling) values \
                                            (:paddelErgometerCanu,:paddelErgometerKayak,:running,:bycicling)");
        insert.bindValue(":paddelErgometerCanu",  paddelErgometerCanu);
        insert.bindValue(":paddelErgometerKayak", paddelErgometerKayak);
        insert.bindValue(":running",              running);
        insert.bindValue(":bycicling",            bycicling);
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
        update.prepare("update cardios set \
                        paddelErgometerCanu=:paddelErgometerCanu, paddelErgometerKayak=:paddelErgometerKayak, running=:running, bycicling=:bycicling \
                        where id = " + QString::number(pid));
        update.bindValue(":paddelErgometerCanu",  paddelErgometerCanu);
        update.bindValue(":paddelErgometerKayak", paddelErgometerKayak);
        update.bindValue(":running",              running);
        update.bindValue(":bycicling",            bycicling);

        if (!update.exec())
        {
            QMessageBox msg;
            msg.setText("Fehler beim Speichern!");
            msg.setWindowTitle("Fehler");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
        qDebug() << update.lastQuery();
    }
    // Window schließen
    verlassen();
}

void CardioDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("CardioDialog löschen");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from cardios where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void CardioDialog::verlassen()
{
    this->close();
}
