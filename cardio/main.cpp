#include <QApplication>

#include "cardiowindow.h"
#include "../db/connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection("../db/viena.db"))
        return EXIT_FAILURE;
    CardioWindow w;
    w.show();
    return a.exec();
}
