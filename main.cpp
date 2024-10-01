#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <cstdlib>
#include <iostream>

#include "mainwin/mainwindow.h"
#include "db/connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char* mydbvar = getenv("MYDB");

    if( mydbvar == NULL ) {
      cout << "Variable MYDB doesn't exist!" << endl;
      exit(0);
    }
    else {
      if (!createConnection(mydbvar)) return EXIT_FAILURE;
    }

    // Initialize and scale properly the main window
    MainWindow w;
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    w.resize(screenGeometry.width()*0.75, screenGeometry.height()*0.75);
    w.show();
    return a.exec();
}
