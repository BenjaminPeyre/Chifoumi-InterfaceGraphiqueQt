#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    connect(ui->buttonBox, SIGNAL(accept()), this, SLOT(CloseMe()));
    connect(ui->Nom, SIGNAL(textChanged()), this, SLOT(verifnom()));
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

bool Dialog::verifNom()
{
    if(ui->Nom->text().isEmpty()){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}



