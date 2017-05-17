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

}

noeud::~noeud() {
}

noeud * noeud::expension(std::vector<int> *cheminSim) {
    // Si pas de fils, ajouter fils gauche
    // sinon ajouter fils droit
    // ET retourner le noeud fils créé


    int index = this->getFils().size();

    noeud *n = new noeud();
    n->setDecisionPere(index);
    n->setPere(this);
    this->fils.push_back(n);
    cheminSim->push_back(index);
    return n;

    //    if (this->getFils().size() == 0) {
    //        noeud *noeudGauche = new noeud();
    //        noeudGauche->setDecisionPere(0);
    //        noeudGauche->setPere(this);
    //        this->fils.push_back(noeudGauche);
    //        cheminSim->push_back(0);
    //        return noeudGauche;
    //    } else {
    //        noeud *noeudDroite = new noeud();
    //        noeudDroite->setDecisionPere(1);
    //        noeudDroite->peutContinuerAGagnerDesPoints = false;
    //        noeudDroite->setPere(this);
    //        this->fils.push_back(noeudDroite);
    //        cheminSim->push_back(1);
    //        return noeudDroite;
    //    }
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
    return min + ((rand() >> 4) % (int) (max - min + 1));
}

int noeud::getRandomDecision() {
    int randomNumber = randomInt(0, (Constantes::nbBranches - 1));
    return randomNumber;
}

noeud * noeud::descente(std::vector<int> *cheminSim) {
    // arréter si prof max retourner ce noeud feuille 
    if (this->fils.size() < Constantes::nbBranches || cheminSim->size() == Constantes::profondeurMax) { // noeud pas complètement développé
        return this;
    } else {

        std::vector<double> aleas;
        for (int i = 0; i < Constantes::nbBranches; i++) {
            aleas.push_back(this->fils[i]->getMoyenne() + (Constantes::k * (2 * sqrt(((log(this->getCptPassage() + 1)) / this->fils[i]->getCptPassage())))));
        }


        int indexMeilleursAlea = -1;
        double meilleurAlea = 0;

        for (int i = 0; i < aleas.size(); i++) {
            if (aleas[i] > meilleurAlea) {
                meilleurAlea = aleas[i];
                indexMeilleursAlea = i;
            }
        }

        cheminSim->push_back(indexMeilleursAlea);
        return this->fils[indexMeilleursAlea]->descente(cheminSim);


        //        double aleaGauche = this->fils[0]->getMoyenne() + (Constantes::k * (2 * sqrt(((log(this->getCptPassage() + 1)) / this->fils[0]->getCptPassage()))));
        //        double aleaDroite = this->fils[1]->getMoyenne() + (Constantes::k * (2 * sqrt(((log(this->getCptPassage() + 1)) / this->fils[1]->getCptPassage()))));

        //        if (aleaGauche == aleaDroite) {
        //            std::cout << "EGALITE" << std::endl;
        //            int randomDecision = getRandomDecision();
        //            cheminSim->push_back(randomDecision);
        //            return this->fils[randomDecision]->descente(cheminSim);
        //        } else if (aleaGauche > aleaDroite) {
        //            // m.a.j.cheminSim 
        //            cheminSim->push_back(0);
        //            //                std::cout << "descente à gauche " << std::endl;
        //            return this->fils[0]->descente(cheminSim);
        //        } else if (aleaGauche < aleaDroite) {
        //
        //            //            std::cout << "Ca passe à droite !!!!" << std::endl;
        //
        //            cheminSim->push_back(1);
        //            //                std::cout << "descente à droite" << std::endl;
        //            return this->fils[1]->descente(cheminSim);
        //        }
    }
}




// Remonte le score sur les noeuds père

std::vector<int> *noeud::rollout(std::vector<int> *cheminSim) {
    //    std::cout << "ROLLOUT" << std::endl;
    while (cheminSim->size() < Constantes::profondeurMax) {
        cheminSim->push_back(this->getRandomDecision());
    }
    return cheminSim;
}

void noeud::simuler(int budget, std::vector<int> *chemin) {
    std::vector<int> *cheminSim = clonerVector(chemin);
    // descente 
    noeud *n = this->descente(cheminSim);
    // si pas déjà en fin de partie (profMax) alors n est à étendre
    if (chemin->size() < Constantes::profondeurMax) {
        n = n->expension(cheminSim);
        cheminSim = n->rollout(cheminSim); // terminer la partie aléatoirement, score de n = résultat de cette partie
    }
    // Prise en compte du score
    n->retropropagation(calculScore(cheminSim));
}

// Calcul du score 

void noeud::calculMoyenne() {

    if (this->decisionDuPere == 1 || this->pere->peutContinuerAGagnerDesPoints == false) {
        this->moyenne = this->pere->moyenne;
    } else {
        this->moyenne = this->pere->moyenne + 1;
    }
}

int noeud::calculScore(std::vector<int> *chemin) {
    bool winning = true;
    float score = 0;
    for (int i = 0; i < chemin->size(); i++) {
        if ((*chemin)[i] == 0) {
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
    // incrementer cptpassages
    this->cptPassage++;

    this->setMoyenne(this->getMoyenne() + ((leScore - this->getMoyenne()) / this->getCptPassage()));

    // si il y a un pere alors mais qu'on est pas à la racine de l'arbre
    if (this->pere != nullptr) {
        this->pere->retropropagation(this->getMoyenne());
    }
}

std::vector<int> * noeud::clonerVector(std::vector<int> *chemin) {
    std::vector<int> *v = new std::vector<int>;
    for (int i = 0; i < chemin->size(); i++) {
        int value = (*chemin)[i];
        v->push_back(value);

    }
    return v;

}

void noeud::afficherVector(std::vector<int> *chemin) {
    for (int i = 0; i < chemin->size(); i++) {
        std::cout << (*chemin)[i] << " ; ";
    }
    std::cout << std::endl;
}