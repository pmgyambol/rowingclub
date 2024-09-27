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
        //typ_types.push_back(queryboattype.value(1).toString().toStdString());
    }
/*
    QObject::connect(ui->planenTrainingButton, SIGNAL(pressed()), SLOT(planen_training()));

    QSqlQuery querymembershiptype("select * from membershiptype");
    while(querymembershiptype.next())
    {
        ui->typComboBox->addItem(querymembershiptype.value(1).toString());
        typ_types.push_back(querymembershiptype.value(1).toString().toStdString());
    }

    QSqlQuery querysextype("select * from sextype");
    while(querysextype.next())
    {
        ui->sexComboBox->addItem(querysextype.value(1).toString());
        sex_types.push_back(querysextype.value(1).toString().toStdString());
    }

    QSqlQuery querynationalitytype("select * from nationalitytype");
    while(querynationalitytype.next())
    {
        ui->nationalityComboBox->addItem(querynationalitytype.value(1).toString());
        nationality_types.push_back(querynationalitytype.value(1).toString().toStdString());
    }

    // PlanenTrainingDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from mitglied where id = " + QString::number(pid));
        if (queryone.next())
        {
            // Daten in die Oberfläche schreiben
            ui->firstnameLineEdit->setText(queryone.value(1).toString());
            ui->lastnameLineEdit->setText(queryone.value(2).toString());
            ui->sexComboBox->setCurrentIndex(ui->sexComboBox->findText(queryone.value(3).toString(),Qt::MatchContains));
            ui->birthdayDateEdit->setDate(queryone.value(4).toDate());
            ui->nationalityComboBox->setCurrentIndex(ui->nationalityComboBox->findText(queryone.value(5).toString(),Qt::MatchContains));
            ui->membersinceDateEdit->setDate(queryone.value(7).toDate());
            ui->addressLineEdit->setText(queryone.value(8).toString());
            ui->emailLineEdit->setText(queryone.value(9).toString());
            ui->typComboBox->setCurrentIndex(ui->typComboBox->findText(queryone.value(10).toString(),Qt::MatchContains));
        }
    }
    else
        ui->delButton->setDisabled(true);
*/
}

PlanenTrainingDialog::~PlanenTrainingDialog()
{
    delete ui;
}

void PlanenTrainingDialog::save()
{
/*
    QString fname = ui->firstnameLineEdit->text();
    QString lname = ui->lastnameLineEdit->text();
    QString adr   = ui->addressLineEdit->text();
    QString email = ui->emailLineEdit->text();
    if (fname.isEmpty() || adr.isEmpty()) return;

    string birthdate  = ui->birthdayDateEdit->date().toString("yyyy-MM-dd").toStdString();
    string membrdate  = ui->membersinceDateEdit->date().toString("yyyy-MM-dd").toStdString();
    // Combobox abfragen
    int type_id_typ         = ui->typComboBox->currentIndex();
    int type_id_sex         = ui->sexComboBox->currentIndex();
    int type_id_nationality = ui->nationalityComboBox->currentIndex();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into mitglied (firstname, lastname, sex, birthdate, nationality, membersince, address, email, typ) values \
                                            (:firstname,:lastname,:sex,:birthdate,:nationality,:membersince,:address,:email,:typ)");
        // insert.prepare("insert into Personen (PName,PAdr,PTelnr,PPlzFK) values (:name,:adr,:telnr,:fk)");
        insert.bindValue(":firstname", fname);
        insert.bindValue(":lastname", lname);
        insert.bindValue(":address", adr);
        insert.bindValue(":email", email);
        insert.bindValue(":birthdate",      birthdate.c_str());
        insert.bindValue(":membersicedate", membrdate.c_str());
        insert.bindValue(        ":typ",        typ_types[type_id_typ        ].c_str());
        insert.bindValue(        ":sex",        sex_types[type_id_sex        ].c_str());
        insert.bindValue(":nationality",nationality_types[type_id_nationality].c_str());
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
        update.prepare("update mitglied set \
                        firstname=:firstname, lastname=:lastname,sex=:sex,birthdate=:birthdate, \
                        nationality=:nationality,membersince=:membersince,address=:address,email=:email,typ=:typ \
                        where id = " + QString::number(pid));
        update.bindValue(":firstname", fname);
        update.bindValue(":lastname", lname);
        update.bindValue(":address", adr);
        update.bindValue(":email", email);
        update.bindValue(":birthdate",      birthdate.c_str());
        update.bindValue(":membersicedate", membrdate.c_str());
        update.bindValue(        ":typ",        typ_types[type_id_typ        ].c_str());
        update.bindValue(        ":sex",        sex_types[type_id_sex        ].c_str());
        update.bindValue(":nationality",nationality_types[type_id_nationality].c_str());

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

}

void PlanenTrainingDialog::gym()
{

}

void PlanenTrainingDialog::boat()
{

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
