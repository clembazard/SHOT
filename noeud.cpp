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
#include <sstream>
#include "noeud.h"
#include "SimuSHOT.h"

noeud::noeud() {
    this->moyenne = 0;
    this->cptPassage = 0;
    this->pere = nullptr;
    this->name = "";    
}

noeud::noeud(const noeud& orig) {
}

noeud::~noeud() {
    for (int i = 0; i < this->fils.size(); i++) {
        delete this->fils[i];
    }
    //    delete this->pere;
}

void noeud::nameIt(){
    if (this->pere != nullptr) {
        this->name = this->pere->getName() + std::to_string(this->decisionDuPere);
    }
}

noeud * noeud::expension() {
    // Si pas de fils, ajouter fils gauche
    // sinon ajouter fils droit
    // ET retourner le noeud fils créé

    int index = this->getFils().size();

    noeud *n = new noeud();
    n->setDecisionPere(index);
    n->setPere(this);
    n->nameIt();
    this->fils.push_back(n);    
    //    cheminSim->push_back(index);
    return n;
}

int noeud::getCptPassage() {
    return this->cptPassage;
}

int noeud::getDecisionPere() {
    return this->decisionDuPere;
}

noeud * noeud::getPere() {
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

void noeud::setPere(noeud * pere) {
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

noeud * noeud::descente(SimuMCTS * simulation) {
    // arréter si prof max retourner ce noeud feuille 
    if (this->fils.size() < Constantes::nbBranches || simulation->estTermine()) { // noeud pas complètement développé
        return this;
    } else {

        std::vector<double> UCBs;
        for (int i = 0; i < this->fils.size(); i++) {
            UCBs.push_back(this->fils[i]->getMoyenne() + (Constantes::k * (2 * sqrt(((log(this->getCptPassage() + 1)) / this->fils[i]->getCptPassage())))));
        }

        int indexMeilleursAlea = -1;
        double meilleurAlea = 0;

        for (int i = 0; i < UCBs.size(); i++) {
            if (UCBs[i] > meilleurAlea) {
                meilleurAlea = UCBs[i];
                indexMeilleursAlea = i;
            }
        }

        //        cheminSim->push_back(indexMeilleursAlea);
        simulation->jouerCoup(CoupMCTS(indexMeilleursAlea));
        return this->fils[indexMeilleursAlea]->descente(simulation);
    }
}






// Remonte le score sur les noeuds père

SimuMCTS * noeud::rollout(SimuMCTS * simulation) {
    //    std::cout << "ROLLOUT" << std::endl;
    while (!simulation->estTermine()) {
        simulation->jouerCoup(CoupMCTS(this->getRandomDecision()));
    }
    return simulation;
}
//
//SimuSHOT * noeud::rollout(SimuSHOT * simulation) {
//    //    std::cout << "ROLLOUT" << std::endl;
//    while (!simulation->estTermine()) {
//        simulation->jouerCoup(CoupSHOT(this->getRandomDecision()));
//    }
//    return simulation;
//}

void noeud::simuler(std::vector<int> *chemin) {
    //    std::vector<int> *cheminSim = clonerVector(chemin_

    SimuMCTS *simulation = new SimuMCTS(chemin);
    // descente 
    noeud *n = this->descente(simulation);
    // si pas déjà en fin de partie (profMax) alors n est à étendre
    if (chemin->size() < Constantes::profondeurMax) {
        n = n->expension();
        //        cheminSim = n->rollout(cheminSim); // terminer la partie aléatoirement, score de n = résultat de cette partie
        simulation = n->rollout(simulation); // terminer la partie aléatoirement, score de n = résultat de cette partie
    }
    // Prise en compte du score
    n->retropropagation(simulation->calculScore());
    delete simulation;
}

// Calcul du score 

int noeud::calculScore(std::vector<int> *chemin) {
    float best = 0;
    float score = 0;
    for (int i = 0; i < chemin->size(); i++) {
        if ((*chemin)[i] == 0) {
            score++;
            if (score > best) {
                best = score;
            }
        } else {
            score = 0;
        }
    }
    return best;

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

std::string noeud::toString(int depth, int tabs) {
    std::string s = "\n";
    if (depth == 0) {
        return s;
    }
    for (int i = 0; i < tabs; i++) {
        s += "\t";
        s += "#" + std::to_string(this->cptPassage) + "/" + this->name;
    }
    for (auto elem : this->fils) {
        s += elem->toString(depth - 1, tabs + 1);
    }
    return s;
}

std::string noeud::getName() {
    return this->name;
}

std::string noeud::toLatexAux(std::vector<int> *width, int depth, std::string name, std::string father) {
    std::stringstream s;
    if (width->size() <= depth) {
        width->push_back(0);
    }
    s << "\\node[noeud] (" << name << ") at ({(" << (*width)[0] << ")*\\InterFeuilles},";
    s << "{\\Niveau" << (char) (((int) 'A') + depth) << "}) {" << this->cptPassage << "/" << (int) (this->moyenne * 100 / 100) << "};\n";
    (*width)[0]++;
    if (father != "") {
        s << "\\draw[fleche] (" << father << ")--(" << name << ") node[etiquette] {$" << this->decisionDuPere << "$};\n";
    }
    for (int i = 0; i < this->fils.size(); i++) {
        s << this->fils[i]->toLatexAux(width, depth + 1, name + std::to_string(i), name);
    }
    return s.str();
}

std::string noeud::toLatex() {
    std::stringstream s;
    s << "\\begin{center}\n";
    s << "\\begin{tikzpicture}[xscale=1,yscale=1]\n";
    s << "\\tikzstyle{fleche}=[->,>=latex,thick]\n";
    s << "\\tikzstyle{noeud}=[fill=yellow,circle,draw]\n";
    s << "\\tikzstyle{etiquette}=[midway,fill=white,draw]\n";
    //    """% Dimensions (MODIFIABLES)"""
    s << "\\def\\DistanceInterNiveaux{3}\n";
    for (int numLetter = 0; numLetter < 26; numLetter++) {
        s << "\\def\\Niveau" << (char) (((int) 'A') + numLetter);
        s << "{(-" << numLetter << ")*\\DistanceNiveaux}\n";
    }
    s << "\\def\\InterFeuilles{(1)*\\DistanceInterFeuilles}\n";

    std::vector<int> *width = new std::vector<int>;

    s << this->toLatexAux(width, 0, "root", "");
    s << "\\end{tikepicture}\n";
    s << "\\end{center}\\n";
    s << "\\rule[0.5ex]{\\textwidth}{0.1mm}\n";

    return s.str();
}