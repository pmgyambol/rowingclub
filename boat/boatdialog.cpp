#include "boatdialog.h"
#include "ui_boatdialog.h"

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
        typ_types.push_back(queryboattype.value(1).toString().toStdString());
    }

    QSqlQuery querymaterialtype("select * from materialtype");
    while(querymaterialtype.next())
    {
        ui->materialComboBox->addItem(querymaterialtype.value(1).toString());
        material_types.push_back(querymaterialtype.value(1).toString().toStdString());
    }

    QSqlQuery querybesitztype("select * from besitztype");
    while(querybesitztype.next())
    {
        ui->besitzComboBox->addItem(querybesitztype.value(1).toString());
        besitz_types.push_back(querybesitztype.value(1).toString().toStdString());
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
    int price = ui->priceComboBox->text().toInt();
    if( price <= 0 ) return;
    string date  = ui->herstelldatumDateEdit->date().toString("yyyy-MM-dd").toStdString();

    // Combobox abfragen
    int type_id_typ      = ui->typComboBox->currentIndex();
    int type_id_material = ui->materialComboBox->currentIndex();
    int type_id_besitz   = ui->besitzComboBox->currentIndex();

    if (pid == 0)
    {
        // INSERT
        QSqlQuery insert;
        insert.prepare("insert into boats (price,herstelldatum,typ,material,besitz) values (:price,:date,:typ,:material,:besitz)");
        insert.bindValue(":price", price);
        insert.bindValue(":date", date.c_str());
        insert.bindValue(     ":typ",      typ_types[type_id_typ     ].c_str());
        insert.bindValue(":material", material_types[type_id_material].c_str());
        insert.bindValue(  ":besitz",   besitz_types[type_id_besitz  ].c_str());

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
        // UPDATE
        QSqlQuery update;
        update.prepare("update boats set \
                        price=:price, herstelldatum=:date, typ=:typ, material=:material, besitz=:besitz \
                        where id = " + QString::number(pid));
        update.bindValue(":price", price);
        update.bindValue(":date", date.c_str());
        update.bindValue(     ":typ",      typ_types[type_id_typ     ].c_str());
        update.bindValue(":material", material_types[type_id_material].c_str());
        update.bindValue(  ":besitz",   besitz_types[type_id_besitz  ].c_str());

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

void BoatDialog::loeschen()
{
    // Löschen macht nur Sinn, bei einem vorhandenen Datensatz
    if (pid != 0) {
        QMessageBox msg;
        msg.setText("Willst du wirklich löschen?");
        msg.setWindowTitle("BoatDialog löschen");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // Datensatz löschen
            QSqlQuery delPerson("delete from boats where id = " + QString::number(pid));
            verlassen();
        }
    }
}

void BoatDialog::verlassen()
{
    this->close();
}
