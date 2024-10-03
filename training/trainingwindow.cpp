#include "trainingwindow.h"
#include "ui_trainingwindow.h"

TrainingWindow::TrainingWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainingWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Trainigs Program");

    QObject::connect(ui->searchButton, SIGNAL(clicked()), SLOT(suchen()));
    //QObject::connect(ui->actionNeuer_Kontakt, SIGNAL(triggered()), SLOT(neuerKontakt()));
    QObject::connect(ui->actionVerwaltung_Postleitzahlen, SIGNAL(triggered()), SLOT(plzVerwaltung()));
    QObject::connect(ui->actionVerlassen, SIGNAL(triggered()), SLOT(verlassen()));
    QObject::connect(ui->dbView, SIGNAL(clicked(QModelIndex)), SLOT(editKontakt(QModelIndex)));

    QObject::connect(ui->nachPushButton, SIGNAL(clicked()), SLOT(nachDatum()));
    QObject::connect(ui-> vorPushButton, SIGNAL(clicked()), SLOT( vorDatum()));

    ui->dbView->resizeColumnsToContents();
    ui->dbView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->dbView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    nach =  true; nachDatum();
    vor  = false;  vorDatum();

    ui->nachDateEdit->setDate(QDate::currentDate());
    ui-> vorDateEdit->setDate(QDate::currentDate());

    sql = new QSqlQueryModel();
    // DB-Anzeigen
    sqlquery(false);
}


TrainingWindow::~TrainingWindow()
{
    delete ui;
    delete sql;
}


void TrainingWindow::editKontakt(QModelIndex index)
{
    // Zeile in der Tableview, auf die geklickt wurde
    int row = index.row();
    // wir holen mit der Zeile die versteckte PId heraus
    int rid = ui->dbView->model()->index(row, 0).data().toInt();
    int mid = ui->dbView->model()->index(row, 1).data().toInt();

    // TrainingDialogen - Window starten
    TrainingDialog perwindow(this, rid, mid);
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
    QString query = "select \
                        training.id, training.fk, mitglied.firstname, mitglied.lastname, \
                        training.cardio, training.gym, training.mitboot, training.coach, training.mitglied, training.datum \
                     from training join mitglied on training.fk = mitglied.id";
    if (filter)
    {
        QString where = nullptr;
        QString name  = ui->searchTextEdit->text();
        if (!name.isEmpty())
            where = " where (firstname like '%" + name + "%' or  lastname like '%" + name + "%')";
        if ( !nach )
        {
            if ( where == nullptr )
                where  =          " where '" + ui->nachDateEdit->date().toString("yyyy-MM-dd") + "' <= datum";
            else
                where +=            " and '" + ui->nachDateEdit->date().toString("yyyy-MM-dd") + "' <= datum";
        }
        if ( !vor )
        {
            if ( where == nullptr )
                where  = " where datum <= '" + ui-> vorDateEdit->date().toString("yyyy-MM-dd") + "'";
            else
                where +=   " and datum <= '" + ui-> vorDateEdit->date().toString("yyyy-MM-dd") + "'";
        }
        if ( where != nullptr )
            query += where;
    }

    // qDebug() << query << "\n";

    sql->setQuery(query);
    sql->setHeaderData( 0, Qt::Horizontal, "id");
    sql->setHeaderData( 1, Qt::Horizontal, "fk");
    sql->setHeaderData( 2, Qt::Horizontal, "firstname");
    sql->setHeaderData( 3, Qt::Horizontal, "lastname");
    sql->setHeaderData( 4, Qt::Horizontal, "cardio");
    sql->setHeaderData( 5, Qt::Horizontal, "gym");
    sql->setHeaderData( 6, Qt::Horizontal, "mitboot");
    sql->setHeaderData( 7, Qt::Horizontal, "coach");
    sql->setHeaderData( 8, Qt::Horizontal, "mitglied");
    sql->setHeaderData( 9, Qt::Horizontal, "datum");

    // Verbinden des Models mit der View
    ui->dbView->setModel(sql);
    // Id unterdrücken
    ui->dbView->hideColumn(0);
    ui->dbView->hideColumn(1);

    ui->dbView->resizeColumnsToContents();
    ui->dbView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void TrainingWindow::nachDatum()
{
    QPalette pal = QPalette();

    if( nach )
    {
        nach = false;
        pal.setColor(QPalette::Window, Qt::black);
    }
    else
    {
        nach = true;
        pal.setColor(QPalette::Window, Qt::red);        
    }

    ui->nachDateEdit->setAutoFillBackground(true); 
    ui->nachDateEdit->setPalette(pal);
    ui->nachDateEdit->show();
}

void TrainingWindow::vorDatum()
{
    QPalette pal = QPalette();

    if( vor )
    {
        vor = false;
        pal.setColor(QPalette::Window, Qt::black);
    }
    else
    {
        vor = true;
        pal.setColor(QPalette::Window, Qt::red);        
    }

    ui->vorDateEdit->setAutoFillBackground(true); 
    ui->vorDateEdit->setPalette(pal);
    ui->vorDateEdit->show();
}
