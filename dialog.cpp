#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accept()), this, SLOT(CloseMe()));
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getNom()
{
    return ui->Nom->text();
}

QString Dialog::getNbPointsMax()
{
    return ui->NbPointsMax->text();
}

QString Dialog::getTempsMax()
{
    return ui->TempsMax->text();
}



