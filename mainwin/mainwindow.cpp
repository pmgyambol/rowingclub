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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
//    dbManager("db/viena.db")
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
    connect(ui->actionNewUser,  SIGNAL(triggered()), this, SLOT(newUser()));
    connect(ui->actionListUser, SIGNAL(triggered()), this, SLOT(listUsers()));
}


void MainWindow::listUsers()
{
    MemberWindow *listUser = new MemberWindow();
    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(listUser);
    subWindow->show();
}


void MainWindow::newUser()
{
//    NewUserDialog newUserDialog(this, &dbManager);
//    newUserDialog.setModal(true);
//    newUserDialog.exec();
}
