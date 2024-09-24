#include <QMainWindow>
#include <QSqlQueryModel>
#include "einkommendialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EinkommenWindow; }
QT_END_NAMESPACE

class EinkommenWindow : public QMainWindow
{
    Q_OBJECT

public:
    EinkommenWindow(QWidget *parent = nullptr);
    ~EinkommenWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::EinkommenWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
