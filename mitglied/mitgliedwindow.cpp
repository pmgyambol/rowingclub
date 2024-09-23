#include "mitgliedwindow.h"
#include "ui_mitgliedwindow.h"

#include <QDebug>

MitgliedWindow::MitgliedWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MitgliedWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Mitgliederblatt");

    QObject::connect(ui->newButton, SIGNAL(clicked()), SLOT(neuerKontakt()));
    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    QObject::connect(ui->dbView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}

MitgliedWindow::~MitgliedWindow()
{
    delete ui;
    delete sql;
}

void MitgliedWindow::neuerKontakt()
{
    MitgliedDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MitgliedDialogenliste
    sqlquery(false);
}

void MitgliedWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // MitgliedDialogen - Window starten
    MitgliedDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MitgliedDialogenliste
    sqlquery(false);
}

void MitgliedWindow::onTableClicked(QModelIndex index)
{
    QString cellText;
    if (index.isValid()) {
        cellText = index.data().toString();        
    }
    qDebug() << cellText.toStdString().c_str();
}


void MitgliedWindow::plzVerwaltung()
{

}

void MitgliedWindow::suchen()
{
    sqlquery(true);
}

void MitgliedWindow::verlassen()
{
    this->close();
}

void MitgliedWindow::sqlquery(bool filter)
{
    QString query = "select id,firstname,lastname,sex,birthdate,nationality,membersince,address,email,typ from mitglied";

    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData( 0, Qt::Horizontal, "id");
    sql->setHeaderData( 1, Qt::Horizontal, "firstname");
    sql->setHeaderData( 2, Qt::Horizontal, "lastname");
    sql->setHeaderData( 3, Qt::Horizontal, "sex");
    sql->setHeaderData( 4, Qt::Horizontal, "birthday");
    sql->setHeaderData( 5, Qt::Horizontal, "nationality");
    sql->setHeaderData( 6, Qt::Horizontal, "membersince");
    sql->setHeaderData( 7, Qt::Horizontal, "address");
    sql->setHeaderData( 8, Qt::Horizontal, "email");
    sql->setHeaderData( 9, Qt::Horizontal, "typ");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}

