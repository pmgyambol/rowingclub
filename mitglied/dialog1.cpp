#include "dialog1.h"
#include "dialog2.h"
#include <QPushButton>

Dialog1::Dialog1(Dialog2 * dialog2, QWidget * parent) : QDialog(parent)
{
    setWindowTitle("dialog1");
    setGeometry(200, 200, 300, 200);
    setModal(true);

    QPushButton * pushButton = new QPushButton("show dialog2", this);
    pushButton->setGeometry(50, 50, 75, 25);
    connect(pushButton, &QPushButton::pressed, this, [=](){ dialog2->show(); });
}