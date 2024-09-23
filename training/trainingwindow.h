#include <QMainWindow>
#include <QSqlQueryModel>
#include "trainingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TrainingWindow; }
QT_END_NAMESPACE

class TrainingWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrainingWindow(QWidget *parent = nullptr);
    ~TrainingWindow();

public slots:
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();

private:
    Ui::TrainingWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
