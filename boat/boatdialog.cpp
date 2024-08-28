#include "boatdialog.h"
#include "ui_boatdialog.h"

BoatDialog::BoatDialog(QWidget *parent, int pid) :
    QDialog(parent),
    ui(new Ui::BoatDialog),
    pid(pid)
{
    ui->setupUi(this);
    this->setWindowTitle("BoatDialog editieren");

    QObject::connect(ui->saveButton, SIGNAL(clicked()), SLOT(save()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()), SLOT(verlassen()));
    QObject::connect(ui->delButton, SIGNAL(clicked()), SLOT(loeschen()));

    // Füllen der Combobox mit Daten aus der Tabelle Plz
    QSqlQuery queryplz("select * from Plz");
    while(queryplz.next())
    {
        // Eintragen in Combobox
        // addItem hat zwei Paramter
        // 1) sichbare Text
        // 2) hier kann ein Key mitgegeben werden
        ui->postleitzahlComboBox->addItem(queryplz.value(1).toString() + " - " + queryplz.value(2).toString(),
                                          queryplz.value(0));
    }
    // BoatDialogen-Datensatz holen
    if (pid != 0)
    {
        QSqlQuery queryone("select * from Personen where PId = " + QString::number(pid));
        if (queryone.next())
        {
            // Daten in die Oberfläche schreiben
            ui->nameLineEdit->setText(queryone.value(1).toString());
            ui->adresseLineEdit->setText(queryone.value(2).toString());
            ui->telefonnummerLineEdit->setText(queryone.value(3).toString());
            // Combobox setzen
            int fk = queryone.value(4).toInt();
            // findData sucht die versteckten Keys durch
            int entry = ui->postleitzahlComboBox->findData(fk);
            ui->postleitzahlComboBox->setCurrentIndex(entry);
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
    QString name = ui->nameLineEdit->text();
    QString adr = ui->adresseLineEdit->text();
    QString telnr = ui->telefonnummerLineEdit->text();
    if (name.isEmpty() || adr.isEmpty() || telnr.isEmpty())
        return;
    // Combobox abfragen
    int currentindex = ui->postleitzahlComboBox->currentIndex();
    QVariant variant = ui->postleitzahlComboBox->itemData(currentindex);
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
