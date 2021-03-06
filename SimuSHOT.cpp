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
    //    this->cheminOrigine = chemin;
//    this->cheminSim = nullptr;
//    this->coupsPossibles = new std::vector<int>;

    // cloner chemin
    this->cheminSim = clonerVector(chemin);
    this->cheminOrigine = clonerVector(chemin);
    // init coupsPossibles
//    for (int i = 0; i < Constantes::nbBranches; i++) {
//        this->coupsPossibles.push_back(i);
//    }
}

SimuSHOT::SimuSHOT(const SimuSHOT& orig) {
}

SimuSHOT::~SimuSHOT() {
//    delete cheminSim;
//    delete coupsPossibles;
}

void SimuSHOT::jouerCoup(CoupSHOT coup) {
    this->cheminSim.push_back(coup.getValeur());
}

bool SimuSHOT::estTermine() {
    // std::cout << this->cheminSim->size() << std::endl;
    return !(this->cheminSim.size() < Constantes::profondeurMax);
}

std::vector<int> SimuSHOT::clonerVector(std::vector<int> *chemin) {
    std::vector<int> v;
    for (int i = 0; i < chemin->size(); i++) {
        int value = (*chemin)[i];
        v.push_back(value);
    }
    return v;
}

float SimuSHOT::calculScore() {
    float best = 0;
    float score = 0;
    for (int i = 0; i < this->cheminSim.size(); i++) {
        if (this->cheminSim[i] == 0) {
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

std::vector<int> SimuSHOT::getCoupsPossibles() {
    std::vector<int> v ;
    if (this->cheminSim.size() < Constantes::profondeurMax) {
        for (int i = 0; i < Constantes::nbBranches; i++) {
            v.push_back(i);
        }
    }
    return v;
}

// todo : Simulation SHOT

void SimuSHOT::simulerSHOT(noeud* arbre, int budget, int *budgetUtilise) {
    //    std::cout << "ca rentre : " << budget << std::endl;
    if (this->estTermine()) {
        (*budgetUtilise) = 1;
        arbre->retropropagation(this->calculScore());
        return;
    }
    if (budget == 1) {
        (*budgetUtilise) = 1;
        //        this->cheminSim = clonerVector(cheminOrigine);
        this->rollout();
        arbre->retropropagation(this->calculScore());
        return;
    }

    // 2. créer des emplacements pour les fils si necessaire
    if (arbre->getFils().size() == 0) {
        for (int i = 0; i < this->getCoupsPossibles().size(); i++) {
            arbre->expension();
        }
    }

    //
    // 3. si pas assez de budget pour tous les fils, choisir les moins explorés
    if (budget < this->getCoupsPossibles().size()) {


        // todo : faut faire le tri
        //        std::sort(arbre->getFils().begin(), arbre->getFils().end(), sortByCptPassage);

        int index = 0;
        int tmp = budget;

        //        int budgetCpt = budget;
        for (int i = 0; i < this->getCoupsPossibles().size(); i++) {
            if (tmp > 0) {
                if (arbre->getFils()[i]->getCptPassage() == 0) {
//                                        this->cheminSim = clonerVector(cheminOrigine);
                    
                    this->jouerCoup(CoupSHOT(i));
                    this->rollout();
                    arbre->retropropagation(this->calculScore());
                    this->cheminSim.pop_back();
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
    for (int i = 0; i < this->getCoupsPossibles().size(); i++) {
        S.push_back(std::make_pair(i, this->getCoupsPossibles()[i]));
    }

    std::sort(S.begin(), S.end(), sortByAscendingScore);

    while (S.size() > 1) {
        //        int subBudget = std::max(1, (int) ((arbre->getCptPassage() + budget) / (S.size() * ceil(log(this->getCoupsPossibles()->size())))));
        int subBudget = std::max(1, (int) ((arbre->getCptPassage() + budget) / (S.size() * ceil((log(this->getCoupsPossibles().size()) / log(2))))));

        for (int i = 0; i < S.size(); i++) {
            //            this->cheminSim = clonerVector(cheminOrigine);
            
            this->jouerCoup(CoupSHOT(S[i].second));
            if (arbre->getFils()[i] == nullptr) {
                arbre->expension();
            }

            int correctedBudget = subBudget - arbre->getFils()[i]->getCptPassage();
            correctedBudget = std::min(correctedBudget, (budget - (*budgetUtilise)));

            int *childBudgetUsed = nullptr;
            int initValue = 0;
            childBudgetUsed = &initValue;

            simulerSHOT(arbre->getFils()[i], subBudget, childBudgetUsed);
            (*budgetUtilise) += (*childBudgetUsed);
//            delete childBudgetUsed;
            this->cheminSim.pop_back();
        }
        // 8) "remove" worst half of sibblings (sequential halving)

        // création de sortList
        std::sort(S.begin(), S.end(), sortByDescendingScore);

        for (int i = 0; i < (int)(S.size() / 2); i++) {
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

std::vector<int> SimuSHOT::getCheminSim() {
    return this->cheminSim;
}