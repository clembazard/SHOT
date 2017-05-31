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
    int *recup(0);
    int recupInt = 0;
    recup = &recupInt;

    noeud *arbre = new noeud();

    while (chemin->size() < Constantes::profondeurMax) {
        SimuSHOT *simulation = new SimuSHOT(chemin);
        //        while (!simulation->estTermine()) {
        simulation->simulerSHOT(arbre, (Constantes::budget + (*recup)), recup);
        (*recup) = Constantes::budget - (*recup);

        int bestMove = 0;
        float bestScore = 0;
        noeud *bestSon = nullptr;

        for (noeud *fils : arbre->getFils()) {
            if (fils->getMoyenne() > bestScore) {
                bestScore = fils->getMoyenne();
                bestMove = fils->getDecisionPere();
                bestSon = fils;
            }
        }


//        std::cout << arbre->toString(2, 0) << std::endl;


        chemin->push_back(bestMove);
        arbre = bestSon;

        for (int i = 0; i < chemin->size(); i++) {
            std::cout << (*chemin)[i];
        }
        std::cout << std::endl;
        //        }
        delete simulation;
        //        std::cout << "C'est fini" << std::endl;
    }

    SimuSHOT totodelTata(chemin);
    std::cout << "Score final : " << totodelTata.calculScore() << std::endl;
    recup = new int;
    delete recup;
    delete chemin;
    delete arbre;
}

SHOT::SHOT(const SHOT& orig) {
}

SHOT::~SHOT() {
}

