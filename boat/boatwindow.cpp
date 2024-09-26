#include "boatwindow.h"
#include "ui_boatwindow.h"

BoatWindow::BoatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BoatWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Bootsliste");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    // QObject::connect(ui->plzButton, SIGNAL(clicked()), SLOT(plzVerwaltung()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

BoatWindow::~BoatWindow()
{
    delete ui;
    delete sql;
}

void BoatWindow::neuerKontakt()
{
    BoatDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der BoatDialogenliste
    sqlquery(false);
}

void BoatWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // BoatDialogen - Window starten
    BoatDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der BoatDialogenliste
    sqlquery(false);
}

void BoatWindow::plzVerwaltung()
{

}

void BoatWindow::suchen()
{
    sqlquery(true);
}

void BoatWindow::verlassen()
{
    this->close();
}

void BoatWindow::sqlquery(bool filter)
{
    QString query = "select id,price,herstelldatum,typ,material,besitz from boats";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "price");
    sql->setHeaderData(2, Qt::Horizontal, "herstelldatum");
    sql->setHeaderData(3, Qt::Horizontal, "typ");
    sql->setHeaderData(4, Qt::Horizontal, "material");
    sql->setHeaderData(5, Qt::Horizontal, "besitz");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
