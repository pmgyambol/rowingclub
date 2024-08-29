#include <QApplication>
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
    MainWindow w;
    w.show();
    return a.exec();
}
