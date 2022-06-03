#ifndef CONNEXION_H
#define CONNEXION_H


#include <QSqlDatabase>
#include    <QSqlQuery>
#include <QDebug>
#define DATABASE_NAME "PersoDb"
#define CONNECT_TYPE "QODBC"
#include <QDialog>

namespace Ui {
class connexion;
}

class connexion : public QDialog
{
    Q_OBJECT

public:
    explicit connexion(QWidget *parent = nullptr);
    ~connexion();
    QString getPseudo();

private:
    Ui::connexion *ui;
    QSqlDatabase mydb;
    QSqlQuery *query;
   // bool openDataBase();

public slots:
    bool _connexion();
};

#endif // CONNEXION_H
