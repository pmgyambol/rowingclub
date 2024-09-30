#include <QApplication>
#include <QDesktopWidget>
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

    QDesktopWidget dw;
    int x=dw.width() *0.75;
    int y=dw.height()*0.75;

    MainWindow w;
    w.resize(x,y);
    w.show();
    return a.exec();
}
