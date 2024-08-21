#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

// #include "sql/sqlitedb.h"
//#include "newuser/newuserdialog.h"
//#include "listuser/listuser.h"
#include "member/memberwindow.h"
#include "member/memberdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class QMdiArea;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void newUser();
    void listUsers();
    void updateActions();

private:
    Ui::MainWindow *ui;
//    SQLiteDB dbManager;

    void createMenus();
    void createActions();

    QMdiArea *mdiArea;

    QMenu    *usersMenu;

    QAction  *newUserAction;
    QAction  *listUserAction;
};
#endif // MAINWINDOW_H
