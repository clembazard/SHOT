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

noeud * noeud::expension(std::vector<int> cheminSim) {
    // Si pas de fils, ajouter fils gauche
    // sinon ajouter fils droit
    // ET retourner le noeud fils créé

    if (this->getFils().size() == 0) {
        noeud *noeudGauche = new noeud();
        noeudGauche->setDecisionPere(0);
        this->fils.push_back(noeudGauche);
        return noeudGauche;
    } else {
        noeud *noeudDroite = new noeud();
        noeudDroite->setDecisionPere(1);
        this->fils.push_back(noeudDroite);
        return noeudDroite;
    }
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

void noeud::ajouterDecision(int d) {
    this->tableauDecisions.push_back(d);
}

int noeud::randomInt(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

int noeud::getRandomDecision() {
    int randomNumber = randomInt(0, 1);
    return randomNumber;
}

noeud * noeud::descente(std::vector<int> cheminSim) {

    // TODO: arréter si prof max retourner ce noeud feuille 
    if (this->fils.size() < 2) // noeud pas complètement développé
        return this;

    // descendre sur fils le +prometteur
    // ajouter de l'aléa
    if (this->fils[0].moyenne >this->this->fils[1]->moyenne) {
        return this->fils[0].descente(cheminSim);
        // m.a.j.cheminSim ????
    } else {
        return this->fils[1]->descente(cheminSim);
    }
    //TODO ....
}


// Remonte le score sur les noeuds père
int noeud::rollout(std::vector<int> cheminSim) { 
    
}

void noeud::simuler(int budget, std::vector<int> chemin) {

    // copie chemin
    std::vector<int> cheminSim = chemin;

    // descente 
    noeud *n = descente(cheminSim);

    // TODO si pas déjà en fin de partie (profMax) alors n est à étendre
    if () {
        n = n->expension(cheminSim);
        n->rollout(cheminSim) // terminer la partie aléatoirement, score de n = résultat de cette partie
    }

    // Prise en compte du score
    n->retropropagation(calculMoyenne(cheminSim));

    // FIN


    int decision = this->getRandomDecision();
    noeud *filsChoisi = this->fils[decision];
    filsChoisi->setDecisionPere(decision);
    filsChoisi->setPere(this);
    filsChoisi->calculMoyenne();


    // tq qu'on peut descendre (il n'y a plus de fils à créer, pas en fin de partie) prendre le plus prometteur
    while (budget > 0) {
        //std::cout << "budget : " << budget << std::endl;

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

// Calcul du score 
void noeud::calculMoyenne() {
    if (this->decisionDuPere == 1 || this->pere->peutContinuerAGagnerDesPoints == false) {
        this->moyenne = this->pere->moyenne;
    } else {
        this->moyenne = this->pere->moyenne + 1;
    }
}

void noeud::retropropagation(int lescore) {
    if (this->getCptPassage() == 0) // nouveau noeud feuille
        this->setMoyenne(lescore);
    else // sur un ancetre de la feuille
        // regarder wikipedia moyenne cumulative
        ;
    // incrementer cptpassages

    // si il y a un pere alors this->pere->retropropagation(score)

    //this->pere->setMoyenne(this->moyenne);
    //this->retropopagation(this->pere);
}