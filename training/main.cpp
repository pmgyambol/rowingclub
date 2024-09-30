#include <QApplication>

#include "trainingwindow.h"
#include "../db/connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection("../db/viena.db"))
        return EXIT_FAILURE;
    TrainingWindow w;
    w.show();
    return a.exec();
}
