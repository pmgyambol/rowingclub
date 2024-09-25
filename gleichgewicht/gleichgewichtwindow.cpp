#include "gleichgewichtwindow.h"
#include "ui_gleichgewichtwindow.h"

using namespace std;

#define FIRST_COLUMN  110
#define SECOND_COLUMN 220

GleichgewichtWindow::GleichgewichtWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GleichgewichtWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Gleichgewicht");

    ui->datumEndLabel->setFixedWidth(FIRST_COLUMN);
    ui->datumSrtLabel->setFixedWidth(FIRST_COLUMN);
    ui->einkommenPushButton->setFixedWidth(FIRST_COLUMN);
    ui->auswandPushButton->setFixedWidth(FIRST_COLUMN);
    ui->gleichgewichtPushButton->setFixedWidth(FIRST_COLUMN);

    ui->datumEndDateEdit->setFixedWidth(SECOND_COLUMN);
    ui->datumSrtDateEdit->setFixedWidth(SECOND_COLUMN);
    ui->einkommenLineEdit->setFixedWidth(SECOND_COLUMN);
    ui->auswandLineEdit->setFixedWidth(SECOND_COLUMN);
    ui->gleichgewichtLineEdit->setFixedWidth(SECOND_COLUMN);

    ui->datumSrtDateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
    ui->datumEndDateEdit->setDate(QDate::currentDate());

    QObject::connect(ui->auswandPushButton,       SIGNAL(clicked()), SLOT(auswand()));
    QObject::connect(ui->einkommenPushButton,     SIGNAL(clicked()), SLOT(einkommen()));
    QObject::connect(ui->gleichgewichtPushButton, SIGNAL(clicked()), SLOT(gleichgewicht()));
}

GleichgewichtWindow::~GleichgewichtWindow()
{
    delete ui;
}

// https://stackoverflow.com/questions/71143936/sql-select-statement-that-creates-calculated-column-then-uses-calculated-column
// https://www.qtcentre.org/threads/46695-How-to-get-value-from-a-query-statement
// https://www.w3schools.com/sql/sql_sum.asp

float GleichgewichtWindow::auswand()
{
    QString datumSrt = ui->datumSrtDateEdit->date().toString("yyyy-MM-dd");
    QString datumEnd = ui->datumEndDateEdit->date().toString("yyyy-MM-dd");

    QString execute  =
        "select \
         sum(fixedcost) + sum(salaries) + sum(rent) + sum(electricity) + sum(water) + sum(heating) + sum(amortization) + sum(gekauftesMaterial) \
         from aufwand \
         where datum <= '" + datumEnd + "' and '" + datumSrt + "' <= datum";
    qDebug() << execute.toStdString().c_str() << "\n";

    QSqlQuery q(execute);
	q.next();
    QVariant res = q.value(0);
    ui->auswandLineEdit->setText(res.toString());

    return res.toFloat();
}

float GleichgewichtWindow::einkommen()
{
    QString datumSrt = ui->datumSrtDateEdit->date().toString("yyyy-MM-dd");
    QString datumEnd = ui->datumEndDateEdit->date().toString("yyyy-MM-dd");

    QString execute  =
        "select \
         sum(mitgliedsbeitrag) + sum(bootsverleih) + sum(gastebeitrag) + sum(bootshausmieten) + sum(foderationssubvention) + sum(werbung) + sum(freiearbeit) \
         from einkommen \
         where datum <= '" + datumEnd + "' and '" + datumSrt + "' <= datum";
    qDebug() << execute.toStdString().c_str() << "\n";

    QSqlQuery q(execute);
	q.next();
    QVariant res = q.value(0);
    ui->einkommenLineEdit->setText(res.toString());

    return res.toFloat();
}

void GleichgewichtWindow::gleichgewicht()
{
    ui->gleichgewichtLineEdit->setText(QString::number(einkommen() - auswand()));    
}
