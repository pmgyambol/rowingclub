#include "mitglieddialog.h"
#include "ui_mitglieddialog.h"

#include <QPushButton>

using namespace std;

MitgliedDialog::MitgliedDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::MitgliedDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("MitgliedDialog editieren");

    QObject::connect(ui->saveButton,  SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton,  SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,   SIGNAL(clicked()), SLOT(loeschen()));
    QObject::connect(ui->trainButton, SIGNAL(clicked()), SLOT(train()));

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

    // MitgliedDialogen-Datensatz holen
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
    {
        ui->delButton->setDisabled(true);
        ui->trainButton->setDisabled(true);
    }
}

MitgliedDialog::~MitgliedDialog()
{
    delete ui;
}

void MitgliedDialog::save()
{
    QString fname = ui->firstnameLineEdit->text();
    QString lname = ui->lastnameLineEdit->text();
    QString adr   = ui->addressLineEdit->text();
    QString email = ui->emailLineEdit->text();
    if (fname.isEmpty() || adr.isEmpty()) return;

    string birthdate   = ui->birthdayDateEdit->   date().toString("yyyy-MM-dd").toStdString();
    string membersince = ui->membersinceDateEdit->date().toString("yyyy-MM-dd").toStdString();
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

        insert.bindValue(":firstname", fname);
        insert.bindValue(":lastname", lname);
        insert.bindValue(":address", adr);
        insert.bindValue(":email", email);
        insert.bindValue(":birthdate",     birthdate.c_str());
        insert.bindValue(":membersince", membersince.c_str());
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
        update.bindValue(":birthdate",     birthdate.c_str());
        update.bindValue(":membersince", membersince.c_str());
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
    }
    // Window schließen
    verlassen();
}

void MitgliedDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("MitgliedDialog löschen");
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
}

void MitgliedDialog::verlassen()
{
    this->close();
}


void MitgliedDialog::train()
{
    // TrainingDialogen - Window starten
    TrainingDialog perwindow(this, 0, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();
}