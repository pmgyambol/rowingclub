#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "mitglied/mitgliedwindow.h"
#include "mitglied/mitglieddialog.h"

#include "boat/boatwindow.h"
#include "boat/boatdialog.h"

#include "gym/gymwindow.h"
#include "gym/gymdialog.h"

#include "cardio/cardiowindow.h"
#include "cardio/cardiodialog.h"

#include "mitboot/mitbootwindow.h"
#include "mitboot/mitbootdialog.h"

#include "training/trainingwindow.h"
#include "training/trainingdialog.h"

#include "einkommen/einkommenwindow.h"
#include "einkommen/einkommendialog.h"

#include "aufwand/aufwandwindow.h"
#include "aufwand/aufwanddialog.h"

#include "gleichgewicht/gleichgewichtwindow.h"

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
    void newMitglied();
    void listMitglied();
    void addBoat();
    void listBoat();
    void training();
    void listGym();
    void listCardio();
    void listMitboot();
    void listEinkommen();
    void listAufwand();
    void showGleichgewicht();

    void updateActions();

private:
    Ui::MainWindow *ui;

    void createMenus();
    void createActions();

    QMdiArea *mdiArea;
};
#endif // MAINWINDOW_H
