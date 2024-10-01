#include "trainingdialog.h"
#include "ui_trainingdialog.h"

#include <string>
#include <iostream>

using namespace std;

TrainingDialog::TrainingDialog(QWidget *parent, int rid, int mid) :
    QDialog(parent),
    ui(new Ui::TrainingDialog),
    rid(rid),
    mid(mid)
{
    ui->setupUi(this);
    this->setWindowTitle("TrainingDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    QObject::connect(ui->cardioButton, SIGNAL(clicked()), SLOT(cardio()));
    QObject::connect(ui->gymButton,    SIGNAL(clicked()), SLOT(gym()));
    QObject::connect(ui->boatButton,   SIGNAL(clicked()), SLOT(boat()));

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
    if (rid != 0)
    {
        QSqlQuery queryone("select * from training where id = " + QString::number(rid));
        if (queryone.next())
        {
            ui->cardioComboBox->  setCurrentIndex(ui->cardioComboBox->findText(queryone.value(2).toString(),Qt::MatchContains));
            ui->gymComboBox->     setCurrentIndex(ui->gymComboBox->   findText(queryone.value(3).toString(),Qt::MatchContains));
            ui->boatComboBox->    setCurrentIndex(ui->boatComboBox->  findText(queryone.value(4).toString(),Qt::MatchContains));
            ui->coachTextEdit->   setText(queryone.value(5).toString());
            ui->mitgliedTextEdit->setText(queryone.value(6).toString());
            ui->datumDateEdit->   setDate(queryone.value(7).toDate());
        }
        // ui->saveButton->setDisabled(true);
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
    if (rid == 0)
    {
        QSqlQuery insert;
        insert.prepare("insert into training(  fk, cardio, gym, mitboot, coach, mitglied, datum) values \
                                            (:mid,:cardio,:gym,:mitboot,:coach,:mitglied,:datum)");

        insert.bindValue(":mid",      mid);
        insert.bindValue(":datum",    ui->datumDateEdit->date().toString("yyyy-MM-dd").toStdString().c_str());
        insert.bindValue(":gym",      ui->   gymComboBox->currentText());
        insert.bindValue(":cardio",   ui->cardioComboBox->currentText());
        insert.bindValue(":mitboot",  ui->  boatComboBox->currentText());
        insert.bindValue(":coach",    ui->coachTextEdit   ->toPlainText().toStdString().c_str());
        insert.bindValue(":mitglied", ui->mitgliedTextEdit->toPlainText().toStdString().c_str());

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
                        fk=:mid, cardio=:cardio, gym=:gym, mitboot=:mitboot, coach=:coach, mitglied=:mitglied, datum=:datum \
                        where id = " + QString::number(rid));

        update.bindValue(":mid",      mid);
        update.bindValue(":datum",    ui->datumDateEdit->date().toString("yyyy-MM-dd").toStdString().c_str());
        update.bindValue(":gym",      ui->   gymComboBox->currentText());
        update.bindValue(":cardio",   ui->cardioComboBox->currentText());
        update.bindValue(":mitboot",  ui->  boatComboBox->currentText());
        update.bindValue(":coach",    ui->coachTextEdit   ->toPlainText().toStdString().c_str());
        update.bindValue(":mitglied", ui->mitgliedTextEdit->toPlainText().toStdString().c_str());

        if (!update.exec())
        {
            QMessageBox msg;
            msg.setText("Fehler beim Speichern!");
            msg.setWindowTitle("Fehler");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
    }

    // qDebug() << "mid=" << mid << "\n";
    // Window schließen
    verlassen();
}

void TrainingDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (rid != 0) {
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
            QSqlQuery delPerson("delete from training where id = " + QString::number(rid));
            verlassen();
        }
    }
}

void TrainingDialog::verlassen()
{
    this->close();
}


void TrainingDialog::cardio()
{
    QString exe = "select id from cardio where name = '" + ui->cardioComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    // GymDialogen - Window starten
    CardioDialog perwindow(this, id);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der GymDialogenliste
    //sqlquery(false);
}

void TrainingDialog::gym()
{
    QString exe = "select id from gym where name = '" + ui->gymComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    // GymDialogen - Window starten
    GymDialog perwindow(this, id);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der GymDialogenliste
    //sqlquery(false);
}


void TrainingDialog::boat()
{
    QString exe = "select id from mitboot where name = '" + ui->boatComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    // GymDialogen - Window starten
    MitbootDialog perwindow(this, id);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der GymDialogenliste
    //sqlquery(false);
}
