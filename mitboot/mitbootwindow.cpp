#include "mitbootwindow.h"
#include "ui_mitbootwindow.h"

MitbootWindow::MitbootWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MitbootWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Trainigs Program");

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

MitbootWindow::~MitbootWindow()
{
    delete ui;
    delete sql;
}

void MitbootWindow::neuerKontakt()
{
    MitbootDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MitbootDialogenliste
    sqlquery(false);
}

void MitbootWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // MitbootDialogen - Window starten
    MitbootDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der MitbootDialogenliste
    sqlquery(false);
}

void MitbootWindow::plzVerwaltung()
{

}

void MitbootWindow::suchen()
{
    sqlquery(true);
}

void MitbootWindow::verlassen()
{
    this->close();
}

void MitbootWindow::sqlquery(bool filter)
{
    QString query = "select id, name, instruction, visible from mitboot";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "name");
    sql->setHeaderData(2, Qt::Horizontal, "instruction");
    sql->setHeaderData(3, Qt::Horizontal, "visible");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);

    ui->dbView->resizeColumnsToContents();
    ui->dbView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
