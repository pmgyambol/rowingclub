#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class QAction;
class QMdiArea;
class QMenu;
}
QT_END_NAMESPACE


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateActions()));
    createActions();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateActions()
{
}


void MainWindow::createActions()
{
    connect(ui->actionNewMitglied,  SIGNAL(triggered()), this, SLOT(newMitglied()));
    connect(ui->actionListMitglied, SIGNAL(triggered()), this, SLOT(listMitglied()));
    connect(ui->actionAddBoat,      SIGNAL(triggered()), this, SLOT(addBoat()));
    connect(ui->actionListBoat,     SIGNAL(triggered()), this, SLOT(listBoat()));

    connect(ui->actionListGym,      SIGNAL(triggered()), this, SLOT(listGym()));
    connect(ui->actionListCardio,   SIGNAL(triggered()), this, SLOT(listCardio()));
    connect(ui->actionListMitboot,  SIGNAL(triggered()), this, SLOT(listMitboot()));

    connect(ui->actionListIncome,   SIGNAL(triggered()), this, SLOT(listEinkommen()));
    connect(ui->actionListExpense,  SIGNAL(triggered()), this, SLOT(listAufwand()));
    connect(ui->actionShowBalance,  SIGNAL(triggered()), this, SLOT(showGleichgewicht()));
}


void MainWindow::listMitglied()
{
    MitgliedWindow *mitgliedWindow = new MitgliedWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(mitgliedWindow);
    subWindow->show();
}


void MainWindow::newMitglied()
{
    MitgliedDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();
}


void MainWindow::addBoat()
{
    BoatDialog perwindow;
    // Modales Window:
    // Es ist das oberste Window
    // alle anderen Windows sind nicht bedienbar
    perwindow.setModal(true);
    perwindow.show();
    perwindow.exec();
}


void MainWindow::listBoat()
{
    BoatWindow *boatWindow = new BoatWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(boatWindow);
    subWindow->show();
}


void MainWindow::listGym()
{
    GymWindow *gymWindow = new GymWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(gymWindow);
    subWindow->show();
}

void MainWindow::listCardio()
{
    CardioWindow *cardioWindow = new CardioWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(cardioWindow);
    subWindow->show();
}


void MainWindow::listMitboot()
{
    MitbootWindow *mitbootWindow = new MitbootWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(mitbootWindow);
    subWindow->show();
}


void MainWindow::listEinkommen()
{
    EinkommenWindow *einkommenWindow = new EinkommenWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(einkommenWindow);
    subWindow->show();
}


void MainWindow::listAufwand()
{
    AufwandWindow *aufwandWindow = new AufwandWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(aufwandWindow);
    subWindow->show();
}


void MainWindow::showGleichgewicht()
{
    GleichgewichtWindow *gleichgewichtWindow = new GleichgewichtWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(gleichgewichtWindow);
    subWindow->show();
}
