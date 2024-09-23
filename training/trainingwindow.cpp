#include "trainingwindow.h"
#include "ui_trainingwindow.h"

TrainingWindow::TrainingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainingWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Trainigs Program");

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

TrainingWindow::~TrainingWindow()
{
    delete ui;
    delete sql;
}

void TrainingWindow::neuerKontakt()
{
    TrainingDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der TrainingDialogenliste
    sqlquery(false);
}

void TrainingWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int pid = ui->dbView->model()->index(row, 0).data().toInt();

    // TrainingDialogen - Window starten
    TrainingDialog perwindow(this, pid);
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();

    // hier wurde das Window wieder geschlossen
    // Update der TrainingDialogenliste
    sqlquery(false);
}

void TrainingWindow::plzVerwaltung()
{

}

void TrainingWindow::suchen()
{
    sqlquery(true);
}

void TrainingWindow::verlassen()
{
    this->close();
}

void TrainingWindow::sqlquery(bool filter)
{
    QString query = "select id,boat,gym,cardio from training";
    if (filter)
    {
        QString name = ui->searchTextEdit->text();
        if (!name.isEmpty())
            query += " where PName like '" + name + "%'";
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "id");
    sql->setHeaderData(1, Qt::Horizontal, "boat");
    sql->setHeaderData(2, Qt::Horizontal, "gym");
    sql->setHeaderData(3, Qt::Horizontal, "cardio");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
}
