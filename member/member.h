#ifndef PERSON_H
#define PERSON_H

#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = nullptr, int pid = 0);
    ~Person();

public slots:
    void save();
    void loeschen();
    void verlassen();

private:
    Ui::Person *ui;
    // Primary Key für die Personen Tabelle
    int pid;
};

#endif // PERSON_H
