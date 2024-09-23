#include "cardiowindow.h"
#include "ui_cardiowindow.h"

CardioWindow::CardioWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CardioWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Cardio");

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

CardioWindow::~CardioWindow()
{
    delete ui;
    delete sql;
}

void CardioWindow::neuerKontakt()
{
    CardioDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der CardioDialogenliste
    sqlquery(false);
}

void CardioWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // CardioDialogen - Window starten
    CardioDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der CardioDialogenliste
    sqlquery(false);
}

void CardioWindow::plzVerwaltung()
{

}

void CardioWindow::suchen()
{
    sqlquery(true);
}

void CardioWindow::verlassen()
{
    this->close();
}

void CardioWindow::sqlquery(bool filter)
{
    QString query = "select id,paddelErgometerCanu,paddelErgometerKayak,running,bycicling from cardios";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "paddelErgometerCanu");
    sql->setHeaderData(2, Qt::Horizontal, "paddelErgometerKayak");
    sql->setHeaderData(3, Qt::Horizontal, "running");
    sql->setHeaderData(4, Qt::Horizontal, "bycicling");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
