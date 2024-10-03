#include "mitbootdialog.h"
#include "ui_mitbootdialog.h"

#include <string>
#include <iostream>

using namespace std;

MitbootDialog::MitbootDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::MitbootDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("MitbootDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    // MitbootDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from mitboot where id = " + QString::number(pid));
        if (queryone.next())
        {
            if ( queryone.value(1).toString() == "no work" )
            {
                ui->saveButton->setDisabled(true);
                ui->delButton->setDisabled(true);
            }

            ui->nameLineEdit->      setText(queryone.value(1).toString());
            ui->instructionEdit->   setText(queryone.value(2).toString());
            ui->visibilityLineEdit->setText(queryone.value(3).toString());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

MitbootDialog::~MitbootDialog()
{
    delete ui;
}

void MitbootDialog::save()
{
    QString name        =  ui->nameLineEdit->text();
    QString instruction =  ui->instructionEdit->toPlainText();
    QString visible     =  ui->visibilityLineEdit->text();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into mitboot ( name, instruction, visible) values \
                                            (:name,:instruction,:visible)");
        insert.bindValue(":name", name);
        insert.bindValue(":instruction", instruction);
        insert.bindValue(":visible", visible);

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
        update.prepare("update mitboot set name=:name, instruction=:instruction, visible=:visible where id = " + QString::number(pid));
        update.bindValue(":name", name);
        update.bindValue(":instruction", instruction);
        update.bindValue(":visible", visible);
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

void MitbootDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("MitbootDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from mitboot where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void MitbootDialog::verlassen()
{
    this->close();
}