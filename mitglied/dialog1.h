#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>

class Dialog2;

class Dialog1 : public QDialog
{
public:
    Dialog1(Dialog2 * dialog2, QWidget * parent = nullptr);
};

#endif // DIALOG1_H