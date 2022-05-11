#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include <qpushbutton.h>
#include "QObject"
QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT
    ///* ---- PARTIE MODÉLE ---------------------------

        ///* Une définition de type �num�r�
    public:
        enum UnCoup {pierre, papier, ciseau, rien};
public:
    QPushButton *bEffacer;
    ChifoumiVue(QWidget *parent = nullptr);
    ~ChifoumiVue();
    // Getters
    UnCoup getCoupJoueur();
        /* retourne le dernier coup jou� par le joueur */
    UnCoup getCoupMachine();
        /* retourne le dernier coup jou� par le joueur */
    unsigned int getScoreJoueur();
        /* retourne le score du joueur */
    unsigned int getScoreMachine();
        /* retourne le score de la machine */
    char determinerGagnant();
        /* d�termine le gagnant 'J' pour joueur, 'M' porur machine, 'N' pou match nul
           en fonction du dernier coup jou� par chacun d'eux */
private:
    Ui::ChifoumiVue *ui;
    UnCoup genererUnCoup();
    /* retourne une valeur al�atoire = pierre, papier ou ciseau.
       Utilis�e pour faire jouer la machine */
    unsigned int scoreJoueur;   // score actuel du joueur
    unsigned int scoreMachine;  // score actuel de la Machine
    UnCoup coupJoueur;          // dernier coup jou� par le joueur
    UnCoup coupMachine;         // dernier coup jou� par la machine
public:
    void setCoupJoueur(UnCoup p_coup);
        /* initialise l'attribut coupJoueur avec la valeur
           du param�tre p_coup */
    void setCoupMachine(UnCoup p_coup);
         /* initialise l'attribut coupmachine avec la valeur
           du param�tre p_coup */
    void setScoreJoueur(unsigned int p_score);
        /* initialise l'attribut scoreJoueur avec la valeur
           du param�tre p_score */
    void setScoreMachine(unsigned int p_score);
         /* initialise l'attribut coupMachine avec la valeur
           du param�tre p_score */

    // Autres modificateurs
     void majScores(char p_gagnant);
        /* Mise � jour des scores en fonction des r�gles de gestion actuelles :
            - 1 point pour le gagnant lorsqu'il y a un gagnant
            - 0 point en cas de match nul
        */
    void initScores();
        /* initialise � 0 les attributs scoreJoueur et scoreMachine
           NON indispensable */
    void initCoups();
        /* initialise � rien les attributs coupJoueur et coupMachine
           NON indispensable */
    void BoutonCoupsEtat(bool etat);
    /*activer Desacter les boutons coups pierre papier ciseau */
    void MiseAJourScoreLabel();
    /*mes a jour le score graphiquement*/
    void NouveauCoupsJoueur();
        /*  */

public slots:
    void Lancementpartie();
    void btn_papier_clicked();
    void btn_pierre_clicked();
    void btn_ciseaux_clicked();

/*
private slots:
    void bouton_CiseauButton_clicked();
    void bouton_PapierButton_clicked();
    void bouton_PierreButton_clicked();
    void NouvellePartieBouton_clicked();*/
};
#endif // CHIFOUMIVUE_H
