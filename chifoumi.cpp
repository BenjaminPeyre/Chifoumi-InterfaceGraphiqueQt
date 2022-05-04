/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    De Brito Luca, Larralde Remi, Peyre Benjamin
 * Created:   28/03/2022
 * Description : classe m�tier (= mod�le) Chifoumi-v0
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>

///* ---- PARTIE MOD�LE ---------------------------

Chifoumi::Chifoumi()
{
    //ctor
    // partie modèle
    Chifoumi::initScores();
    Chifoumi::initCoups();
}

Chifoumi::~Chifoumi()
{
    //dtor
}

/// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
	return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N'; // J M N

    // il sera modifi� dans l'un des cas suivants
    if (getCoupJoueur() == papier && getCoupMachine() == pierre)
    {
        gagnantARetourner = 'J';
    }
    if (getCoupJoueur() == papier && getCoupMachine() == papier)
        gagnantARetourner = 'N';
    if (getCoupJoueur() == papier && getCoupMachine() == ciseau)
        gagnantARetourner = 'M';

    if (getCoupJoueur() == pierre && getCoupMachine() == pierre)
        gagnantARetourner = 'N';
    if (getCoupJoueur() == pierre && getCoupMachine() == papier)
        gagnantARetourner = 'M';
    if (getCoupJoueur() == pierre && getCoupMachine() == ciseau)
        gagnantARetourner = 'J';

    if (getCoupJoueur() == ciseau && getCoupMachine() == pierre)
        gagnantARetourner = 'M';
    if (getCoupJoueur() == ciseau && getCoupMachine() == papier)
        gagnantARetourner = 'J';
    if (getCoupJoueur() == ciseau && getCoupMachine() == ciseau)
        gagnantARetourner = 'N';

    return gagnantARetourner;
}

         ///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max){
    /* pré-condition : min<max ;
       Le nbre aléatoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    int min=1;
    int max=3;
    valeurGeneree = rien;
    int choixMachine =randMinMax(min,max);
    switch (choixMachine)
    {
    case 1:
        valeurGeneree = pierre;
        break;
    case 2:
        valeurGeneree = papier;
        break;
    case 3:
        valeurGeneree = ciseau;
        break;

    default:
        break;
    }

    return valeurGeneree;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
}

void Chifoumi::majScores(char p_gagnant) {
}

void Chifoumi::initScores() {
}

void Chifoumi::initCoups() {
}
