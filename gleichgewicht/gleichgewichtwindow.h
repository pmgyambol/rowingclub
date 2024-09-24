#include <QMainWindow>
#include <QSqlQueryModel>

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
/*
    void neuerKontakt();
    void editKontakt(QModelIndex);
    void plzVerwaltung();
    void suchen();
    void verlassen();
*/
private:
    Ui::GleichgewichtWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};
