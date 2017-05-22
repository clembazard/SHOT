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

#include "SimuSHOT.h"

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