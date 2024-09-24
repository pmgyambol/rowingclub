#include <QMainWindow>
#include <QSqlQueryModel>

#include "aufwanddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AufwandWindow; }
QT_END_NAMESPACE

class AufwandWindow : public QMainWindow
{
    Q_OBJECT

public:
    AufwandWindow(QWidget *parent = nullptr);
    ~AufwandWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::AufwandWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
