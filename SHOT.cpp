/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SHOT.cpp
 * Author: cremond
 * 
 * Created on 22 mai 2017, 10:58
 */

#include <vector>
#include "Constantes.h"
#include "noeud.h"
#include "SHOT.h"
#include "SimuSHOT.h"

SHOT::SHOT() {
    std::vector<int> *chemin = new std::vector<int>;
    int *recup = 0;

    noeud *arbre = new noeud();

    SimuSHOT *simulation = new SimuSHOT(chemin);

    while (!simulation->estTermine()) {
        //        int calcul = Constantes::budget;
        int calcul = *recup;
        std::cout << calcul << std::endl;
        simulation->simulerSHOT(arbre, Constantes::budget, recup);
        (*recup) = Constantes::budget - (*recup);

        int bestMove = -1;
        float bestScore = -1;
        noeud *bestSon = nullptr;

        for (noeud *fils : arbre->getFils()) {
            if (fils->getMoyenne() > bestScore) {
                bestScore = fils->getMoyenne();
                bestMove = fils->getDecisionPere();
                bestSon = fils;
            }
        }

        chemin->push_back(bestMove);
        arbre = bestSon;

    }
    delete chemin;
    delete simulation;
}

SHOT::SHOT(const SHOT& orig) {
}

SHOT::~SHOT() {
}

