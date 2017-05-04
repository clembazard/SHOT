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

#include <stdbool.h>

#include "noeud.h"
#include "Constantes.h"

noeud::noeud() {
    this->moyenne = 0;
    this->cptPassage = 0;
    this->peutContinuerAGagnerDesPoints = true;
}

noeud::noeud(const noeud& orig) {
    //    this->moyenne = orig.moyenne;
    //    this->cptPassage = orig.cptPassage;
    //    this->peutContinuerAGagnerDesPoints = orig.peutContinuerAGagnerDesPoints;
    //    this->decisionDuPere = orig.decisionDuPere;
    //    this->pere = orig->pere;
    //    this->fils = orig->fils;
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
        noeudGauche->setPere(this);
        noeudGauche->calculMoyenne();
        this->fils.push_back(noeudGauche);
        std::cout << "Branche gauche créée" << std::endl;
        return noeudGauche;
    } else {
        noeud *noeudDroite = new noeud();
        noeudDroite->setDecisionPere(1);
        noeudDroite->peutContinuerAGagnerDesPoints = false;
        noeudDroite->setPere(this);
        noeudDroite->calculMoyenne();
        this->fils.push_back(noeudDroite);
        std::cout << "Branche droite créée" << std::endl;
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

int noeud::randomInt(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

int noeud::getRandomDecision() {
    int randomNumber = randomInt(0, 1);
    return randomNumber;
}

noeud * noeud::descente(std::vector<int> cheminSim) {

    // arréter si prof max retourner ce noeud feuille 
    if (this->fils.size() < 2 || cheminSim.size() == Constantes::profondeurMax) { // noeud pas complètement développé
        return this;
    } else {
        // descendre sur fils le +prometteur
        // todo : ajouter de l'aléa
        if (this->fils[0]->getMoyenne() > this->fils[1]->getMoyenne()) {
            // m.a.j.cheminSim 
            cheminSim.push_back(0);
            std::cout << "descente à gauche " << std::endl;
            return this->fils[0]->descente(cheminSim);
        } else {
            cheminSim.push_back(1);
            std::cout << "descente à droite" << std::endl;
            return this->fils[1]->descente(cheminSim);
        }
    }
}



// Remonte le score sur les noeuds père

int noeud::rollout(std::vector<int> cheminSim) {
    std::cout << "ROLLOUT" << std::endl;
    //    std::vector<int> simulation = cheminSim;
    //    while (simulation.size() < Constantes::profondeurMax) {
    //        simulation.push_back(this->getRandomDecision());
    //    }
    //    return 0;
}

void noeud::simuler(int budget, std::vector<int> chemin) {

    // copie chemin
    std::vector<int> cheminSim = chemin;

    // descente 
    noeud *n = this->descente(cheminSim);

    // si pas déjà en fin de partie (profMax) alors n est à étendre
    if (chemin.size() < Constantes::profondeurMax) {
        n = n->expension(cheminSim);
        n->rollout(cheminSim); // terminer la partie aléatoirement, score de n = résultat de cette partie
    }

    // Prise en compte du score
    //n->retropropagation(calculMoyenne(cheminSim));
    n->retropropagation(calculScore(cheminSim));

    // FIN

    //
    //    int decision = this->getRandomDecision();
    //    noeud *filsChoisi = this->fils[decision];
    //    filsChoisi->setDecisionPere(decision);
    //    filsChoisi->setPere(this);
    //    filsChoisi->calculMoyenne();
    //
    //
    //    // tq qu'on peut descendre (il n'y a plus de fils à créer, pas en fin de partie) prendre le plus prometteur
    //    while (budget > 0) {
    //        //std::cout << "budget : " << budget << std::endl;
    //
    //        // expansion
    //        filsChoisi->cptPassage++;
    //        // **** filsChoisi->expension();
    //
    //        // crée un nouveau fils
    //        int randomDecision = getRandomDecision();
    //        noeud *filsChoisiDuFilsChoisi = filsChoisi->fils[randomDecision];
    //        filsChoisiDuFilsChoisi->cptPassage++;
    //        filsChoisiDuFilsChoisi->setDecisionPere(randomDecision);
    //        filsChoisiDuFilsChoisi->setPere(filsChoisi);
    //        filsChoisiDuFilsChoisi->calculMoyenne();
    //
    //        filsChoisi = filsChoisiDuFilsChoisi;
    //
    //
    //        // rollout : je complète la partie aléatoirement, sans mémoriser, je récupère le "gain"
    //        budget--;
    //    }
    //    // retropropagation : je m.a.j. l'info sur ce nouveau noeud et ses ancêtres
    //    this->moyenne = filsChoisi->getMoyenne();
    //    std::cout << "Rétropropagation " << this->moyenne << std::endl;
}

// Calcul du score 

void noeud::calculMoyenne() {
    if (this->decisionDuPere == 1 || this->pere->peutContinuerAGagnerDesPoints == false) {
        this->moyenne = this->pere->moyenne;
    } else {
        this->moyenne = this->pere->moyenne + 1;
    }
}

float noeud::calculScore(std::vector<int> chemin) {
    bool winning = true;
    float score = 0;
    for (int i = 0; i < chemin.size(); i++) {
        if (chemin[i] == 0) {
            if (winning) {
                score++;
            }
        } else {
            winning = false;
        }
    }
    return score;
}

void noeud::retropropagation(int leScore) {
    if (this->getCptPassage() == 0) // nouveau noeud feuille
        this->setMoyenne(leScore);
    else {
        // sur un ancetre de la feuille
        this->setMoyenne((this->getMoyenne() + leScore) / 2);
    }

    // regarder wikipedia moyenne cumulative

    // incrementer cptpassages
    this->cptPassage++;
    // si il y a un pere alors this->pere->retropropagation(score)
    if (this->pere != nullptr) {
        this->pere->retropropagation(this->getMoyenne());
    }

    //this->pere->setMoyenne(this->moyenne);
    //this->retropopagation(this->pere);
}