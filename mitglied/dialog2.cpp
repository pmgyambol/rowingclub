#include "dialog2.h"

Dialog2::Dialog2(QWidget * parent) : QDialog(parent)
{
    setWindowTitle("dialog2");
    setGeometry(300, 300, 200, 150);
    setModal(true);
}