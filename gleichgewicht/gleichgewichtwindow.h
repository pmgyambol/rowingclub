#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui { class GleichgewichtWindow; }
QT_END_NAMESPACE

class GleichgewichtWindow : public QMainWindow
{
    Q_OBJECT

public:
    GleichgewichtWindow(QWidget *parent = nullptr);
    ~GleichgewichtWindow();

public slots:
    float auswand();
    float einkommen();
    void  gleichgewicht();

private:
    Ui::GleichgewichtWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
