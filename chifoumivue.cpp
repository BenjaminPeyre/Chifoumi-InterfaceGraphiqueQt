#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include "QDebug"
ChifoumiVue::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
    BoutonCoupsEtat(false);
    connect(ui->NouvellePartieBouton, SIGNAL(clicked()), this, SLOT(Lancementpartie()));
    connect(ui->PapierButton, SIGNAL(clicked()), this, SLOT(btn_papier_clicked()));
    connect(ui->CiseauButton, SIGNAL(clicked()), this, SLOT(btn_ciseaux_clicked()));
    connect(ui->PierreButton, SIGNAL(clicked()), this, SLOT(btn_pierre_clicked()));

    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(btn_Aide_click()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this,SLOT(btn_quit()));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(finJeu()));
    connect(m_chrono, SIGNAL(timeout()), this, SLOT(chrono()));

    connect(ui->bPause, SIGNAL(clicked()), this, SLOT(pause()));
    //v6
    connect(ui->actionparamettre, SIGNAL(triggered()), this, SLOT(btnApropos()));
    m_temps_partie=30000;

    //v7
    this->hide();
    connexion * DialogConnexion= new connexion(this);
    int retour = DialogConnexion->exec();
    if(retour){
       nomUtilisateur = DialogConnexion->getPseudo();
       this->show();
    }

}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

ChifoumiVue::UnCoup ChifoumiVue::getCoupJoueur() {
    return coupJoueur;
}

ChifoumiVue::UnCoup ChifoumiVue::getCoupMachine() {
    return coupMachine;
}

unsigned int ChifoumiVue::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int ChifoumiVue::getScoreMachine() {
    return scoreMachine;
}

char ChifoumiVue::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N'; // J M N

    // il sera modifi� dans l'un des cas suivants
    if(getCoupJoueur() == papier && getCoupMachine() == pierre) gagnantARetourner = 'J';
    if(getCoupJoueur() == papier && getCoupMachine() == papier) gagnantARetourner = 'N';
    if(getCoupJoueur() == papier && getCoupMachine() == ciseau) gagnantARetourner = 'M';

    if(getCoupJoueur() == pierre && getCoupMachine() == pierre) gagnantARetourner = 'N';
    if(getCoupJoueur() == pierre && getCoupMachine() == papier) gagnantARetourner = 'M';
    if(getCoupJoueur() == pierre && getCoupMachine() == ciseau) gagnantARetourner = 'J';

    if(getCoupJoueur() == ciseau && getCoupMachine() == pierre) gagnantARetourner = 'M';
    if(getCoupJoueur() == ciseau && getCoupMachine() == papier) gagnantARetourner = 'J';
    if(getCoupJoueur() == ciseau && getCoupMachine() == ciseau) gagnantARetourner = 'N';



    return gagnantARetourner;
}

         ///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max){
    /* pré-condition : min<max ;
       Le nbre aléatoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

ChifoumiVue::UnCoup ChifoumiVue::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    int min=1;
    int max=4;
    valeurGeneree = rien;
    int choixMachine =randMinMax(min,max);
    switch (choixMachine)
    {
    case 1:
        valeurGeneree = pierre;
        ui->labelCoupMachine->setPixmap(QPixmap(":/chifoumi/images/pierre_115.png"));
        break;
    case 2:
        valeurGeneree = papier;
        ui->labelCoupMachine->setPixmap(QPixmap(":/chifoumi/images/papier_115.png"));
        break;
    case 3:
        valeurGeneree = ciseau;
        ui->labelCoupMachine->setPixmap(QPixmap(":/chifoumi/images/ciseau_115.png"));
        break;

    default:
        break;
    }

    return valeurGeneree;
}

        /// Setters

void ChifoumiVue::setCoupJoueur(UnCoup p_coup) {
    coupJoueur = p_coup;
}

void ChifoumiVue::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void ChifoumiVue::setScoreJoueur(unsigned int p_score) {
    scoreJoueur=p_score;
}

void ChifoumiVue::setScoreMachine(unsigned int p_score) {
    scoreMachine=p_score;
}

void ChifoumiVue::majScores(char p_gagnant)
{
    switch (p_gagnant)
    {
    case 'J':
        scoreJoueur++;
        break;
    case 'M':
        scoreMachine++;
        break;
    default:
        break;
    }
    //Afficher le score sur la fenetre
    MiseAJourScoreLabel();
}

void ChifoumiVue::initScores() {
    scoreJoueur = 0;
    scoreMachine = 0;
}

void ChifoumiVue::initCoups() {
    coupJoueur = rien;
    coupMachine = rien;
}
void ChifoumiVue::BoutonCoupsEtat(bool etat){

ui->CiseauButton->setEnabled(etat);
ui->PapierButton->setEnabled(etat);
ui->PierreButton->setEnabled(etat);
ui->bPause->setEnabled(etat);
}

void ChifoumiVue::MiseAJourScoreLabel()
{
    ui->joueurScoreLabel->setText(QString::number(scoreJoueur));
    ui->MachineScoreLabel->setText(QString::number(scoreMachine));
}

void ChifoumiVue::NouveauCoupsJoueur()
{
    UnCoup mc =genererUnCoup();
    setCoupMachine(mc);
    char gagnant = determinerGagnant();
    majScores(gagnant);
    AtteintScoreFinPartie(gagnant);
}

void ChifoumiVue::Lancementpartie(){
    ui->actionparamettre->setEnabled(false);
    BoutonCoupsEtat(true);
    ChifoumiVue::initScores();
    ChifoumiVue::initCoups();
    m_temps=m_temps_partie/1000;
    ui->Chrono->setText(QString::number(m_temps));
    m_timer->start(m_temps_partie);
    m_chrono->start(1000);
    ChifoumiVue::MiseAJourScoreLabel();
    ui->labelCoupMachine->setPixmap(QPixmap(":/chifoumi/images/rien_115.png"));
    ui->labelCoupJoueur->setPixmap(QPixmap(":/chifoumi/images/rien_115.png"));
}

void ChifoumiVue::btn_papier_clicked()
{
    ui->labelCoupJoueur->setPixmap(QPixmap(":/chifoumi/images/papier_115.png"));
    setCoupJoueur(papier);
    NouveauCoupsJoueur();
}

void ChifoumiVue::btn_pierre_clicked()
{
    ui->labelCoupJoueur->setPixmap(QPixmap(":/chifoumi/images/pierre_115.png"));
    setCoupJoueur(pierre);
    NouveauCoupsJoueur();
}

void ChifoumiVue::btn_ciseaux_clicked()
{
    ui->labelCoupJoueur->setPixmap(QPixmap(":/chifoumi/images/ciseau_115.png"));
    setCoupJoueur(ciseau);
    NouveauCoupsJoueur();

}

void ChifoumiVue::btn_Aide_click()
{
    msgboxE("A propos de cette application.", VERSION_APPLICATION+"\n11/05/2022\n PEYRE BENJAMIN\n LUCA DE BRITO\n LARRALDE REMI" );
}

void ChifoumiVue::btn_quit()
{
    this->close();
}

void ChifoumiVue::msgboxE(QString titreFentre, QString Raison)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(titreFentre);
    msgBox.setText(Raison);
    msgBox.exec();

}

/*V5*/
void ChifoumiVue::finJeu()
{
    ui->actionparamettre->setEnabled(true);
    m_timer->stop();
    m_chrono->stop();
    ui->Chrono->setText("0");
    BoutonCoupsEtat(false);
    if (scoreJoueur>scoreMachine)
    {
        msgboxE("Fin de la partie", "Victoire du Joueur avec un score de "+QString::number(scoreJoueur)+" contre "+QString::number(scoreMachine));
    }
    else if (scoreJoueur<scoreMachine)
    {
        msgboxE("Fin de la partie", "Victoire de la Machine avec un score de "+QString::number(scoreMachine)+" contre "+QString::number(scoreJoueur));
    }
    else
    {
        msgboxE("Fin de la partie", "Egalité entre le Joueur et la Machine avec un score de "+QString::number(scoreMachine));
    }
}

void ChifoumiVue::chrono()
{
    m_temps=m_temps-1;
    ui->Chrono->setText(QString::number(m_temps));
    m_chrono->start(1000);
}

void ChifoumiVue::pause()
{
    if (m_timer->isActive())
    {
        m_tempsrestant=m_timer->remainingTime();
        m_minute=m_chrono->remainingTime();
        m_timer->stop();
        m_chrono->stop();
        ui->bPause->setText("Reprendre");
    }
    else
    {
        m_timer->start(m_tempsrestant);
        m_chrono->start(m_minute);
        ui->bPause->setText("Pause");
    }
}

void ChifoumiVue::btnApropos()
{
    Dialog * maDlg= new Dialog(this);
    int retour = maDlg->exec();
    qDebug() << retour<< Dialog::Accepted;

    switch(retour)
    {

    case Dialog::Accepted :
        if (!maDlg->getNom().isEmpty() && !maDlg->getNbPointsMax().isEmpty() && !maDlg->getTempsMax().isEmpty()){

                m_temps_partie = maDlg->getTempsMax().toInt()*1000;
                NBR_POINT_GAGANT = maDlg->getNbPointsMax().toInt();
                ui->label_Nb_Score_Max->setText(QString::number(NBR_POINT_GAGANT));
                nomUtilisateur = maDlg->getNom();

            }
    break;
    case QDialog::Rejected :
        ui->label_Nb_Score_Max->setText ("Erreur");

        break;
    default:break;

    }
}
/*V4*/
void ChifoumiVue::AtteintScoreFinPartie(char p_gagant)
{

if(scoreJoueur == NBR_POINT_GAGANT || scoreMachine == NBR_POINT_GAGANT){
    if(p_gagant == 'J')
        msgboxE("Fin de partie", "Bravo Le Joueur! Vous gagnez avec "+QString::number(scoreJoueur)+"points." );
    if(p_gagant == 'M')
        msgboxE("Fin de partie", "Bravo La Machine! Vous gagnez avec "+QString::number(scoreMachine) +"points." );
    BoutonCoupsEtat(false);
}
}
