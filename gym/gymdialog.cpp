#include "gymdialog.h"
#include "ui_gymdialog.h"

#include <string>
#include <iostream>

using namespace std;

GymDialog::GymDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::GymDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("GymDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    // GymDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from gym where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->pushupsLineEdit->setText(queryone.value(1).toString());
            ui->plankLineEdit->setText(queryone.value(2).toString());
            ui->squatLineEdit->setText(queryone.value(3).toString());
            ui->benchPressLineEdit->setText(queryone.value(4).toString());
            ui->deadliftLineEdit->setText(queryone.value(5).toString());
            ui->pullUpLineEdit->setText(queryone.value(6).toString());
            ui->legPressLineEdit->setText(queryone.value(7).toString());
            ui->tricepPushDownLineEdit->setText(queryone.value(8).toString());
            ui->dumbbellRowLineEdit->setText(queryone.value(9).toString());
            ui->seatedRowLineEdit->setText(queryone.value(10).toString());
        }
    }
    else
        ui->delButton->setDisabled(true);
}

GymDialog::~GymDialog()
{
    delete ui;
}

void GymDialog::save()
{
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

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into gym ( pushups, plank, squat, benchPress, deadlift, pullUp, legPress, tricepPushDown, dumbbellRow, seatedRow) values \
                                        (:pushups,:plank,:squat,:benchPress,:deadlift,:pullUp,:legPress,:tricepPushDown,:dumbbellRow,:seatedRow)");
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
        update.prepare("update gym set \
                        pushups=:pushups, plank=:plank, squat=:squat, benchPress=:benchPress, deadlift=:deadlift, \
                        pullUp=:pullUp, legPress=:legPress, tricepPushDown=:tricepPushDown, dumbbellRow=:dumbbellRow, seatedRow=:seatedRow \
                        where id = " + QString::number(pid));
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

void GymDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("GymDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from gym where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void GymDialog::verlassen()
{
    this->close();
}