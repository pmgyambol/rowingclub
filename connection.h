#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QDir>

// diese Methode öffnet die Datenbank
// true => alles OK
// false => Fehler beim Öffnen der DB
static bool createConnection()
{
    // Ausgabe der verfügbaren Datenbank-Treiber
    qDebug() << QSqlDatabase::drivers();
    // hier wird ein DB-Objekt angelegt und der Name des Treibers übergeben
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // Definition des Datenbanknamens
    // relativer Pfad, die db liegt an der gleichen Stelle, wo auch die EXE ist
    db.setDatabaseName("Kontakte.db");
    // Öffnen der Datenbank
    if (!db.open())
    {
        // Fehlerfall
        QMessageBox msg;
        msg.setText("Fehler beim Öffnen der Datenbank " + QDir::currentPath() + "/" + db.databaseName());
        msg.setWindowTitle("Fehler");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return false;
    }
    // Erstellung der Datenbank
    QSqlQuery query;
    // Benutzung von Foreign-Keys einschalten
    query.exec("PRAGMA foreign_keys = ON");
    // Tabelle Postleitzahlen erzeugen
    query.exec("CREATE TABLE if not exists 'Plz' ( \
               'PlzId'	INTEGER NOT NULL, \
               'PlzNummer'	INTEGER NOT NULL UNIQUE, \
               'PlzOrt'	TEXT NOT NULL, \
               PRIMARY KEY('PlzId' AUTOINCREMENT) \
               )");
    // Tabelle Personen erzeugen
    query.exec("CREATE TABLE if not exists 'Personen' ( \
               'PId'	INTEGER NOT NULL, \
               'PName'	TEXT NOT NULL, \
               'PAdr'	TEXT NOT NULL, \
               'PTelnr'	TEXT NOT NULL, \
               'PPlzFK'	INTEGER NOT NULL, \
               PRIMARY KEY('PId' AUTOINCREMENT), \
               FOREIGN KEY('PPlzFK') REFERENCES 'Plz'('PlzId') \
               )");

    // Testdaten erzeugen, diese werden wenn das Programm fertig ist,
    // gelöscht oder unter Kommentar gesetzt
    query.exec("delete from Personen");
    query.exec("delete from Plz");
    query.exec("insert into Plz (PlzNummer,PlzOrt) values (1100,'Wien')");
    query.exec("insert into Plz (PlzNummer,PlzOrt) values (1200,'Wien')");
    query.exec("insert into Plz (PlzNummer,PlzOrt) values (3100,'St.Pölten')");
    query.exec("insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Mary','Weg 1','123', (select PlzId from Plz where PlzNummer=1200))");
    query.exec("insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Peter','Strasse 1','456', (select PlzId from Plz where PlzNummer=1100))");
    query.exec("insert into Personen (PName,PAdr,PTelnr,PPlzFK) values ('Fritz','Weg 2','789', (select PlzId from Plz where PlzNummer=3100))");
    return true;
}

#endif // CONNECTION_H
