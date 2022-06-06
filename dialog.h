#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
     QString getNom();
     QString getNbPointsMax();
     QString getTempsMax();
public slots:
          bool verifNom();
private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
