#ifndef AUFWANDWINDOW_H
#define AUFWANDWINDOW_H

#include "aufwandwindow.h"
#include "ui_aufwandwindow.h"

AufwandWindow::AufwandWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AufwandWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Trainigs Program");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

AufwandWindow::~AufwandWindow()
{
    delete ui;
    delete sql;
}

void AufwandWindow::neuerKontakt()
{
    AufwandDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der AufwandDialogenliste
    sqlquery(false);
}

void AufwandWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // AufwandDialogen - Window starten
    AufwandDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der AufwandDialogenliste
    sqlquery(false);
}

void AufwandWindow::plzVerwaltung()
{

}

void AufwandWindow::suchen()
{
    sqlquery(true);
}

void AufwandWindow::verlassen()
{
    this->close();
}

void AufwandWindow::sqlquery(bool filter)
{
    QString query = "select id, fixedcost, salaries, rent, electricity, water, heating, amortization, gekauftesMaterial, datum from aufwand";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData( 0, Qt::Horizontal, "id");
    sql->setHeaderData( 1, Qt::Horizontal, "fixedcost");
    sql->setHeaderData( 2, Qt::Horizontal, "salaries");
    sql->setHeaderData( 3, Qt::Horizontal, "rent");
    sql->setHeaderData( 4, Qt::Horizontal, "electricity");
    sql->setHeaderData( 5, Qt::Horizontal, "water");
    sql->setHeaderData( 6, Qt::Horizontal, "heating");
    sql->setHeaderData( 7, Qt::Horizontal, "amortization");
    sql->setHeaderData( 8, Qt::Horizontal, "gekauftesMaterial");
    sql->setHeaderData( 9, Qt::Horizontal, "datum");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
#endif
