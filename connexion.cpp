#include "connexion.h"
#include "ui_connexion.h"

connexion::connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexion)
{
    ui->setupUi(this);
    connect(ui->btn_Connection, SIGNAL(clicked()), this, SLOT(_connexion()));
}

connexion::~connexion()
{
    delete ui;
}

QString connexion::getPseudo()
{
    return ui->lineEditUtilisateur->text();
}

bool connexion::_connexion()
{
    bool ok;
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    //mydb.connectOptions(CONNECT_TYPE);
    if(mydb.open()){
        ok= true;
    }else{
        ok = false;
    }
if(ok){

   // bool estInsert = db->insertVilles();
    QSqlQuery q("Select Pseudo, Mot_De_Passe from Chifoumi");
    for (int i=0;q.next() ;i++ ) {
        if(q.value(0) == ui->lineEditUtilisateur->text() && q.value(1) == ui->lineEditMdP->text()){
            this->close();
            return true;
        }

       qDebug() << q.value(0) << q.value(1);
    }
}

}
/*
bool connexion::openDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    //mydb.connectOptions(CONNECT_TYPE);
    if(mydb.open()){
        return true;
    }else{
        return false;
    }

}
*/
