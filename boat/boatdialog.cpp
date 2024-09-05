#include "boatdialog.h"
#include "ui_boatdialog.h"

#include <string>
#include <iostream>

using namespace std;

BoatDialog::BoatDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::BoatDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("BoatDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton,  SIGNAL(clicked()), SLOT(loeschen()));

    QSqlQuery queryboattype("select * from boattype");
    while(queryboattype.next())
    {
        ui->typComboBox->addItem(queryboattype.value(1).toString());
    }

    QSqlQuery querymaterialtype("select * from materialtype");
    while(querymaterialtype.next())
    {
        ui->materialComboBox->addItem(querymaterialtype.value(1).toString());
    }

    QSqlQuery querybesitz("select * from besitztype");
    while(querybesitz.next())
    {
        ui->besitzComboBox->addItem(querybesitz.value(1).toString());
    }

    // BoatDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from boats where id = " + QString::number(pid));
        if (queryone.next())
        {
            ui->priceComboBox->setText(queryone.value(1).toString());
            ui->herstelldatumDateEdit->setDate(queryone.value(2).toDate());
            ui->typComboBox->setCurrentIndex(ui->typComboBox->findText(queryone.value(3).toString(),Qt::MatchContains));
            ui->materialComboBox->setCurrentIndex(ui->materialComboBox->findText(queryone.value(4).toString(),Qt::MatchContains));
            ui->besitzComboBox->setCurrentIndex(ui->besitzComboBox->findText(queryone.value(5).toString(),Qt::MatchContains));
        }
    }
    else
        ui->delButton->setDisabled(true);
}

BoatDialog::~BoatDialog()
{
    delete ui;
}

void BoatDialog::save()
{
    QString price = ui->priceComboBox->text();
    QString date  = ui->herstelldatumDateEdit->text();
    int typeInd   = ui->typComboBox->currentIndex();
    string s = ui->typComboBox->itemData(typeInd).toString().toStdString() ;
    // qDebug() << s;
    cout << "Test: " << s;
/*
    QString telnr = ui->telefonnummerLineEdit->text();
    if (name.isEmpty() || adr.isEmpty() || telnr.isEmpty())
        return;
    // Combobox abfragen
    int currentindex = ui->materialComboBox->currentIndex();
    QVariant variant = ui->materialComboBox->itemData(currentindex);
    int plzid = variant.toInt();

    if (pid == 0)
    {
        // Speichern in die Datenbank
        QSqlQuery insert;
        insert.prepare("insert into Personen (PName,PAdr,PTelnr,PPlzFK) values (:name,:adr,:telnr,:fk)");
        insert.bindValue(":name", name);
        insert.bindValue(":adr", adr);
        insert.bindValue(":telnr", telnr);
        insert.bindValue(":fk", plzid);
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
        update.prepare("update Personen set \
                        PName=:name, PAdr=:adr, PTelnr=:telnr, PPlzFK=:fk \
                        where PId = " + QString::number(pid));
        update.bindValue(":name", name);
        update.bindValue(":adr", adr);
        update.bindValue(":telnr", telnr);
        update.bindValue(":fk", plzid);
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
*/
    // Window schließen
    verlassen();
}

void BoatDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("BoatDialog löschen");
        // msg.addButton("Ok", QMessageBox::AcceptRole);
        // msg.addButton("Cancel", QMessageBox::NoRole);
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from Personen where PId = " + QString::number(pid));
            verlassen();
        }
    }
}

void BoatDialog::verlassen()
{
    this->close();
}
