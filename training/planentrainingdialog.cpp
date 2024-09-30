#include "planentrainingdialog.h"
#include "ui_planentrainingdialog.h"

#include <QPushButton>

using namespace std;

PlanenTrainingDialog::PlanenTrainingDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::PlanenTrainingDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("PlanenTrainingDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    QObject::connect(ui->cardioButton, SIGNAL(clicked()), SLOT(cardio()));
    QObject::connect(ui->gymButton,    SIGNAL(clicked()), SLOT(gym()));
    QObject::connect(ui->boatButton,   SIGNAL(clicked()), SLOT(boat()));

    ui->datumDateEdit->setDate(QDate::currentDate());

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

    if (pid != 0)
    {

        QSqlQuery queryone("select * from planentraining where fk = " + QString::number(pid));
        if (queryone.next())
        {
            ui->coachTextEdit->setText(queryone.value(5).toString());
            ui->mitgliedTextEdit->setText(queryone.value(6).toString());
            ui->datumDateEdit->setDate(queryone.value(7).toDate());
/*            
            ui->firstnameLineEdit->setText(queryone.value(1).toString());
            ui->lastnameLineEdit->setText(queryone.value(2).toString());
            ui->sexComboBox->setCurrentIndex(ui->sexComboBox->findText(queryone.value(3).toString(),Qt::MatchContains));
            ui->birthdayDateEdit->setDate(queryone.value(4).toDate());
            ui->nationalityComboBox->setCurrentIndex(ui->nationalityComboBox->findText(queryone.value(5).toString(),Qt::MatchContains));
            ui->membersinceDateEdit->setDate(queryone.value(7).toDate());
            ui->addressLineEdit->setText(queryone.value(8).toString());
            ui->emailLineEdit->setText(queryone.value(9).toString());
            ui->typComboBox->setCurrentIndex(ui->typComboBox->findText(queryone.value(10).toString(),Qt::MatchContains));
*/
        }
    }
    else
        ui->delButton->setDisabled(true);
}

PlanenTrainingDialog::~PlanenTrainingDialog()
{
    delete ui;
}

void PlanenTrainingDialog::save()
{
    QSqlQuery insert;
    insert.prepare("insert into planentraining( fk, cardio, gym, mitboot, coach, mitglied, datum) values \
                                              (:fk,:cardio,:gym,:mitboot,:coach,:mitglied,:datum)");

    insert.bindValue(":fk",       pid);
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

    verlassen();
}

void PlanenTrainingDialog::loeschen()
{
/*
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("PlanenTrainingDialog löschen");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from mitglied where id = " + QString::number(pid));
            verlassen();
        }
    }
*/
}

void PlanenTrainingDialog::verlassen()
{
    this->close();
}


void PlanenTrainingDialog::cardio()
{
    QString exe = "select id from cardio where name = '" + ui->cardioComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    qDebug() << "Choosen cardio: " << id << " " << exe << "\n";

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

void PlanenTrainingDialog::gym()
{
    QString exe = "select id from gym where name = '" + ui->gymComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    qDebug() << "Choosen gym: " << id << " " << exe << "\n";

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


void PlanenTrainingDialog::boat()
{
    QString exe = "select id from mitboot where name = '" + ui->boatComboBox->currentText() + "'";

    QSqlQuery q(exe);
    q.next();
    int id = q.value(0).toInt();

    qDebug() << "Choosen boat: " << id << " " << exe << "\n";

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


void PlanenTrainingDialog::planen_training()
{
/*
    PlanenTrainingDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();
    //sqlquery(false);
*/
}
