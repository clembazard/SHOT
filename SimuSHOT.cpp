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
    std::cout << "ca rentre" << budget << std::endl;
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

    // 2. créer des emplacements pour les fils si necessaire
    if (arbre->getFils().size() == 0) {
        for (int i = 0; i < this->getCoupsPossibles()->size(); i++) {
            arbre->expension();
        }
    }

    //
    // 3. si pas assez de budget pour tous les fils, choisir les moins explorés
    if (budget < this->getCoupsPossibles()->size()) {


        // todo : faut faire le tri
        //        std::sort(arbre->getFils().begin(), arbre->getFils().end(), sortByCptPassage);

        int index = 0;
        int tmp = budget;

        //        int budgetCpt = budget;
        for (int i = 0; i < this->getCoupsPossibles()->size(); i++) {
            if (tmp > 0) {
                if (arbre->getFils()[i]->getCptPassage() == 0) {
                    this->jouerCoup(CoupSHOT(i));
                    this->rollout();
                    arbre->retropropagation(this->calculScore());
                    tmp--;
                }
            }
            index++;
        }
        (*budgetUtilise) = budget - tmp;
        return;
    }

    // 4) enough budget: distribute it using sequential halving,
    // so: while there is more than 1 possible move still eligible

    std::vector<std::pair<int, int>> S;
    for (int i = 0; i < this->getCoupsPossibles()->size(); i++) {
        S.push_back(std::make_pair(i, (*this->getCoupsPossibles())[i]));
    }

    std::sort(S.begin(), S.end(), sortByAscendingScore);

    while (sizeof (S) > 1) {
        int subBudget = std::max(1, (int) floor(((arbre->getCptPassage() + budget) / (S.size() * ceil(log(this->getCoupsPossibles()->size()))))));

        for (int i = 0; i < S.size(); i++) {
            this->jouerCoup(CoupSHOT(S[i].second));
            if (arbre->getFils()[i] == nullptr) {
                arbre->expension();
            }

            int correctedBudget = subBudget - arbre->getFils()[i]->getCptPassage();
            correctedBudget = std::min(correctedBudget, (budget - (*budgetUtilise)));

            int *childBudgetUsed = 0;
            simulerSHOT(arbre->getFils()[i], subBudget, childBudgetUsed);
            (*budgetUtilise) += (*childBudgetUsed);
        }
        // 8) "remove" worst half of sibblings (sequential halving)

        // création de sortList
        std::sort(S.begin(), S.end(), sortByDescendingScore);

        for (int i = 0; i < floor(S.size() / 2); i++) {
            S.pop_back();
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

bool SimuSHOT::sortByAscendingScore(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    return (lhs.second < rhs.second);
}

bool SimuSHOT::sortByDescendingScore(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    return (lhs.second > rhs.second);
}

std::vector<std::pair<int, int>> SimuSHOT::filtrerEligible(std::vector<std::pair<int, int>> paires) {
    std::vector<std::pair<int, int>> result;
    for (auto elem : paires) {
        if (elem.first != -1) {
            result.push_back(elem);
        }
    }
    return result;
}
