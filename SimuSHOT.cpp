/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuSHOT.cpp
 * Author: cremond
 * 
 * Created on 22 mai 2017, 10:42
 */

#include <algorithm>

#include "SimuSHOT.h"
#include "noeud.h"

SimuSHOT::SimuSHOT(std::vector<int> *chemin) {
    this->cheminSim = nullptr;
    this->coupsPossibles = new std::vector<int>;

    // cloner chemin
    this->cheminSim = clonerVector(chemin);
    // init coupsPossibles
    for (int i = 0; i < Constantes::nbBranches; i++) {
        this->coupsPossibles->push_back(i);
    }

}

SimuSHOT::SimuSHOT(const SimuSHOT& orig) {
}

SimuSHOT::~SimuSHOT() {
    delete cheminSim;
    delete coupsPossibles;
}

void SimuSHOT::jouerCoup(CoupSHOT coup) {
    this->cheminSim->push_back(coup.getValeur());
    // suppression du coup choisi, en général ce sera le premier de la liste
    //    this->cheminSim->erase(this->cheminSim->begin());
}

bool SimuSHOT::estTermine() {
    return (this->cheminSim->size() == Constantes::profondeurMax) ? true : false;
}

std::vector<int> * SimuSHOT::clonerVector(std::vector<int> *chemin) {
    std::vector<int> *v = new std::vector<int>;
    for (int i = 0; i < chemin->size(); i++) {
        int value = (*chemin)[i];
        v->push_back(value);
    }
    return v;

}

float SimuSHOT::calculScore() {
    bool winning = true;
    float score = 0;

    for (int i = 0; i < this->cheminSim->size(); i++) {
        if ((*this->cheminSim)[i] == 0) {
            if (winning) {
                score++;
            }
        } else {
            winning = false;
        }
    }
    return score;
}

std::vector<int> *SimuSHOT::getCoupsPossibles() {
    std::vector<int> *v = new std::vector<int>;
    if (this->cheminSim->size() < Constantes::profondeurMax) {
        for (int i = 0; i < Constantes::nbBranches; i++) {
            v->push_back(i);
        }
    }
    return v;
}

// todo : Simulation SHOT

void SimuSHOT::simulerSHOT(noeud* arbre, int budget, int *budgetUtilise) {
    if (this->estTermine()) {
        (*budgetUtilise) = 1;
        arbre->retropropagation(this->calculScore());
        return;
    }
    if (budget == 1) {
        (*budgetUtilise) = 1;
        this->rollout();
        arbre->retropropagation(this->calculScore());
        return;
    }

    // 1. tentative de collection des paires (index, mouvements possibles)

    std::vector<std::pair<int, int>> S;
    for (int i = 0; i < this->getCoupsPossibles()->size(); i++) {
        S.push_back(std::make_pair(i, (*this->getCoupsPossibles())[i]));
    }

    // 2. créer des emplacements pour les fils si necessaire
    if (arbre->getFils().size() == 0) {
        for (int i = 0; i < this->getCoupsPossibles()->size(); i++) {
            arbre->expension();
        }
    }


    // 3. si pas assez de budget pour tous les fils, choisir les moins explorés
    if (budget < sizeof (S)) {


        // todo : faut faire le tri
        std::sort(arbre->getFils().begin(), arbre->getFils().end(), sortByCptPassage);

        int budgetCpt = budget;
        for (int i = 0; i < arbre->getFils().size(); i++) {
            if (budgetCpt > 0) {
                this->jouerCoup(CoupSHOT(i));
                this->rollout();
                arbre->retropropagation(this->calculScore());
                budgetCpt--;
            }
        }
        (*budgetUtilise) = budget;
        return;
    }

    // 4) enough budget: distribute it using sequential halving,
    // so: while there is more than 1 possible move still eligible

    std::vector<std::pair<int, int>> eligible = S; // <- deep copy of S
    while (sizeof (eligible) > 1) {
        //# 5) compute budget (+ previous budget) for sub branch
        //#subBudget = max([1,
        //#                 int((tree.cpt + budget) // (len(S) * math.ceil(math.log(len(tree.pmoves)))))])
        int subBudget = std::max(1, (int) floor((budget / sizeof (S) * ceil(log(this->getCoupsPossibles()->size())))));

        for (int i = 0; i < S.size(); i++) {
            this->jouerCoup(CoupSHOT(S[i].second));
            // 6) create real child node if slot still empty
            if (arbre->getFils()[i] == nullptr) {
                arbre->expension();
            }
            // 7) recurse on child only on budget not only expanded
            // TODO correctedBudget = subBudget - tree.sibblings[i].cpt
            int *childBudgetUsed = 0;
            simulerSHOT(arbre->getFils()[i], subBudget, childBudgetUsed);
            (*budgetUtilise) += (*childBudgetUsed);
        }
        // 8) "remove" worst half of sibblings (sequential halving)

        // création de sortList
        std::vector<std::tuple<int, int, float>> sortList;
        for (auto elem : eligible) {
            sortList.push_back(std::make_tuple(elem.first, elem.second, arbre->getFils()[elem.first]->getMoyenne()));
        }
        // tri de sortList
        std::sort(sortList.begin(), sortList.end(), sortByAscendingScore);
        int nbRemoved = floor(sortList.size() / 2);
        for (auto elem : sortList) {
            std::vector<std::pair<int, int>> im = S[std::get<0>(elem)];
        }

    }


}

void SimuSHOT::rollout() {
    while (!this->estTermine()) {
        this->jouerCoup(CoupSHOT(this->getRandomDecision()));
    }
}

int SimuSHOT::randomInt(int min, int max) {
    return min + ((rand() >> 4) % (int) (max - min + 1));
}

int SimuSHOT::getRandomDecision() {
    int randomNumber = randomInt(0, (Constantes::nbBranches - 1));
    return randomNumber;
}

bool SimuSHOT::sortByCptPassage(noeud* lhs, noeud* rhs) {
    return (lhs->getCptPassage() < rhs->getCptPassage());
}

bool SimuSHOT::sortByAscendingScore(const std::tuple<int, int, float>& lhs, const std::tuple<int, int, float>& rhs) {
    return (std::get<2>(lhs) < std::get<2>(rhs));
}