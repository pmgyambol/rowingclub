#include <QMainWindow>
#include <QSqlQueryModel>
#include "gymdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GymWindow; }
QT_END_NAMESPACE

class GymWindow : public QMainWindow
{
    Q_OBJECT

public:
    GymWindow(QWidget *parent = nullptr);
    ~GymWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::GymWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
