#include "trainingdialog.h"
#include "ui_trainingdialog.h"

#include <string>
#include <iostream>

using namespace std;

TrainingDialog::TrainingDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::TrainingDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("TrainingDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    QSqlQuery queryvisiblegym("select name from gym where visible = 1");
    while(queryvisiblegym.next())
    {
        ui->gymComboBox->addItem(queryvisiblegym.value(0).toString());
    }

    QSqlQuery queryvisiblecardio("select name from cardio where visible = 1");
    while(queryvisiblecardio.next())
    {
        ui->cardioComboBox->addItem(queryvisiblecardio.value(0).toString());
    }

    QSqlQuery queryvisibleboat("select name from mitboot where visible = 1");
    while(queryvisibleboat.next())
    {
        ui->boatComboBox->addItem(queryvisibleboat.value(0).toString());
    }

    // TrainingDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from training where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->cardioComboBox->setCurrentIndex(ui->cardioComboBox->findText(queryone.value(1).toString(),Qt::MatchContains));
            ui->gymComboBox->setCurrentIndex(ui->gymComboBox->findText(queryone.value(2).toString(),Qt::MatchContains));
            ui->boatComboBox->setCurrentIndex(ui->boatComboBox->findText(queryone.value(3).toString(),Qt::MatchContains));
            ui->datumDateEdit->setDate(queryone.value(4).toDate());
            ui->coachTextEdit->setText(queryone.value(5).toString());
            ui->mitgliedTextEdit->setText(queryone.value(6).toString());
            ui->datumDateEdit->setDate(queryone.value(7).toDate());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

TrainingDialog::~TrainingDialog()
{
    delete ui;
}

void TrainingDialog::save()
{
    /*
    QString name           =  ui->nameLineEdit->text();
    QString pushups        =  ui->pushupsLineEdit->text();
    QString plank          =  ui->plankLineEdit->text();
    QString squat          =  ui->squatLineEdit->text();
    QString benchPress     =  ui->benchPressLineEdit->text();
    QString deadlift       =  ui->deadliftLineEdit->text();
    QString pullUp         =  ui->pullUpLineEdit->text();
    QString legPress       =  ui->legPressLineEdit->text();
    QString tricepPushDown =  ui->tricepPushDownLineEdit->text();
    QString dumbbellRow    =  ui->dumbbellRowLineEdit->text();
    QString seatedRow      =  ui->seatedRowLineEdit->text();
    QString visible        =  ui->visibilityLineEdit->text();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into training ( name, pushups, plank, squat, benchPress, deadlift, pullUp, legPress, tricepPushDown, dumbbellRow, seatedRow, visible) values \
                                        (:name,:pushups,:plank,:squat,:benchPress,:deadlift,:pullUp,:legPress,:tricepPushDown,:dumbbellRow,:seatedRow,:visible)");
        insert.bindValue(":name", name);
        insert.bindValue(":pushups", pushups);
        insert.bindValue(":plank", plank);
        insert.bindValue(":squat", squat);
        insert.bindValue(":benchPress", benchPress);
        insert.bindValue(":deadlift", deadlift);
        insert.bindValue(":pullUp", pullUp);
        insert.bindValue(":legPress", legPress);
        insert.bindValue(":tricepPushDown", tricepPushDown);
        insert.bindValue(":dumbbellRow", dumbbellRow);
        insert.bindValue(":seatedRow", seatedRow);
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
        update.prepare("update training set \
                        name=:name, pushups=:pushups, plank=:plank, squat=:squat, benchPress=:benchPress, deadlift=:deadlift, pullUp=:pullUp, \
                        legPress=:legPress, tricepPushDown=:tricepPushDown, dumbbellRow=:dumbbellRow, seatedRow=:seatedRow, visible=:visible  \
                        where id = " + QString::number(pid));
        update.bindValue(":name", name);
        update.bindValue(":pushups", pushups);
        update.bindValue(":plank", plank);
        update.bindValue(":squat", squat);
        update.bindValue(":benchPress", benchPress);
        update.bindValue(":deadlift", deadlift);
        update.bindValue(":pullUp", pullUp);
        update.bindValue(":legPress", legPress);
        update.bindValue(":tricepPushDown", tricepPushDown);
        update.bindValue(":dumbbellRow", dumbbellRow);
        update.bindValue(":seatedRow", seatedRow);
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
*/
}

void TrainingDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("TrainingDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from training where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void TrainingDialog::verlassen()
{
    this->close();
}