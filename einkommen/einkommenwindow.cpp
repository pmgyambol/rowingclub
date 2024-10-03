#ifndef EINKOMMENWINDOW_H
#define EINKOMMENWINDOW_H

#include "einkommenwindow.h"
#include "ui_einkommenwindow.h"

EinkommenWindow::EinkommenWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EinkommenWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Einkommen");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    ui->dbView->resizeColumnsToContents();
    ui->dbView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->dbView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

EinkommenWindow::~EinkommenWindow()
{
    delete ui;
    delete sql;
}

void EinkommenWindow::neuerKontakt()
{
    EinkommenDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der EinkommenDialogenliste
    sqlquery(false);
}

void EinkommenWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // EinkommenDialogen - Window starten
    EinkommenDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der EinkommenDialogenliste
    sqlquery(false);
}

void EinkommenWindow::plzVerwaltung()
{

}

void EinkommenWindow::suchen()
{
    sqlquery(true);
}

void EinkommenWindow::verlassen()
{
    this->close();
}

void EinkommenWindow::sqlquery(bool filter)
{
    QString query = "select id, mitgliedsbeitrag, bootsverleih, gastebeitrag, bootshausmieten, foderationssubvention, werbung, \
                     freiearbeit, mitgliedid, boatid, datum from einkommen";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData( 0, Qt::Horizontal, "id");
    sql->setHeaderData( 1, Qt::Horizontal, "mitgliedsbeitrag");
    sql->setHeaderData( 2, Qt::Horizontal, "bootsverleih");
    sql->setHeaderData( 3, Qt::Horizontal, "gastebeitrag");
    sql->setHeaderData( 4, Qt::Horizontal, "bootshausmieten");
    sql->setHeaderData( 5, Qt::Horizontal, "foderationssubvention");
    sql->setHeaderData( 6, Qt::Horizontal, "werbung");
    sql->setHeaderData( 7, Qt::Horizontal, "freiearbeit");
    sql->setHeaderData( 8, Qt::Horizontal, "mitgliedid");
    sql->setHeaderData( 9, Qt::Horizontal, "boatid");
    sql->setHeaderData(10, Qt::Horizontal, "datum");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);

    ui->dbView->resizeColumnsToContents();
    ui->dbView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
#endif
