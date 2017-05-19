/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuMCTS.cpp
 * Author: cremond
 * 
 * Created on 17 mai 2017, 11:16
 */

#include "SimuMCTS.h"
#include "Constantes.h"

SimuMCTS::SimuMCTS(std::vector<int> *chemin){
    // instanciation
//    this->cheminSim = new std::vector<int>;
//    this->coupsPossibles = new std::vector<int>;
    this->cheminSim = nullptr;
    this->coupsPossibles = new std::vector<int>;
    
    // cloner chemin
    this->cheminSim = clonerVector(chemin);
    // init coupsPossibles
    for (int i = 0; i < Constantes::nbBranches; i++) {
        this->coupsPossibles->push_back(i);
    }
}

SimuMCTS::SimuMCTS(const SimuMCTS& orig) {
}

SimuMCTS::~SimuMCTS() {
    delete cheminSim;
    delete coupsPossibles;
}

std::vector<int> *SimuMCTS::getCoupsPossibles() {
    return this->coupsPossibles;
}

void SimuMCTS::jouerCoup(CoupMCTS coup) {
    this->cheminSim->push_back(coup.getValeur());
    // suppression du coup choisi, en général ce sera le premier de la liste
//    this->cheminSim->erase(this->cheminSim->begin());
}

bool SimuMCTS::estTermine() {
    return (this->cheminSim->size() == Constantes::profondeurMax) ? true : false;
}

std::vector<int> * SimuMCTS::clonerVector(std::vector<int> *chemin) {
    std::vector<int> *v = new std::vector<int>;
    for (int i = 0; i < chemin->size(); i++) {
        int value = (*chemin)[i];
        v->push_back(value);
    }
    return v;

}


int SimuMCTS::calculScore() {
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
