/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   noeud.cpp
 * Author: cremond
 * 
 * Created on 2 février 2017, 13:23
 */

#include "noeud.h"

noeud::noeud() {
    this->moyenne = 0;
    this->cptPassage = 0;
    this->peutContinuerAGagnerDesPoints = true;
}

noeud::noeud(const noeud& orig) {
}

noeud::~noeud() {
}

void noeud::expension() {
    // creation de deux nouveau noeuds

    noeud *noeudGauche = new noeud();
    noeudGauche->setDecisionPere(0);
    noeud *noeudDroite = new noeud();
    noeudDroite->setDecisionPere(1);

    this->fils.push_back(noeudDroite);
    this->fils.push_back(noeudGauche);
}

void noeud::evalutation() {
    noeud::moyenne + 1;
}

int noeud::getCptPassage() {
    return this->cptPassage;
}

int noeud::getDecisionPere() {
    return this->decisionDuPere;
}

noeud *noeud::getPere() {
    return this->pere;
}

std::vector<noeud*> noeud::getFils() {
    return this->fils;
}

float noeud::getMoyenne() {
    return this->moyenne;
}

void noeud::setCptPassage(int cptPassage) {
    this->cptPassage = cptPassage;
}

void noeud::setDecisionPere(int decision) {
    this->decisionDuPere = decision;
}

void noeud::setPere(noeud* pere) {
    this->pere = pere;
}

void noeud::setFils(std::vector<noeud*> fils) {
    this ->fils = fils;
}

void noeud::setMoyenne(float moyenne) {
    this->moyenne = moyenne;
}

int noeud::randomInt(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

int noeud::getRandomDecision() {
    int randomNumber = randomInt(0, 1);
    return randomNumber;
}

void noeud::simuler(int budget) {


    //    this->cptPassage++;
    // descente 
    this->expension();
    int decision = this->getRandomDecision();
    noeud *filsChoisi = this->fils[decision];
    filsChoisi->setDecisionPere(decision);
    filsChoisi->setPere(this);
    filsChoisi->calculMoyenne();


    // tq qu'on peut descendre (il n'y a plus de fils à créer, pas en fin de partie) prendre le plus prometteur
    while (budget > 0) {
//        std::cout << "budget : " << budget << std::endl;

        // expansion
        filsChoisi->cptPassage++;
        filsChoisi->expension();

        // crée un nouveau fils
        int randomDecision = getRandomDecision();
        noeud *filsChoisiDuFilsChoisi = filsChoisi->fils[randomDecision];
        filsChoisiDuFilsChoisi->cptPassage++;
        filsChoisiDuFilsChoisi->setDecisionPere(randomDecision);
        filsChoisiDuFilsChoisi->setPere(filsChoisi);
        filsChoisiDuFilsChoisi->calculMoyenne();

        filsChoisi = filsChoisiDuFilsChoisi;


        // rollout : je complète la partie aléatoirement, sans mémoriser, je récupère le "gain"
        budget--;
    }
    // retropropagation : je m.a.j. l'info sur ce nouveau noeud et ses ancêtres
    this->moyenne = filsChoisi->getMoyenne();
    std::cout << "Rétropropagation " << this->moyenne << std::endl;
}

void noeud::calculMoyenne() {
    if (this->decisionDuPere == 1 || this->pere->peutContinuerAGagnerDesPoints == false) {
        this->moyenne = this->pere->moyenne;
    } else {
        this->moyenne = this->pere->moyenne + 1;
    }
}

void noeud::retropopagation(noeud *branche) {
    if (branche->pere != NULL) {
        branche->pere->setMoyenne(this->moyenne);
        retropopagation(this->pere);
    }
}