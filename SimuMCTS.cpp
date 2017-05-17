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

SimuMCTS::SimuMCTS(std::vector<int> *chemin) {

    // cloner chemin
    this->cheminSim = clonerVector(chemin);
    // init coupsPossibles
    for (int i = 0; i < Constantes::nbBranches; i++) {
        this->coupsPossibles.push_back(i);
    }


}

SimuMCTS::SimuMCTS(const SimuMCTS& orig) {
}

SimuMCTS::~SimuMCTS() {
}

std::vector<Coup> SimuMCTS::getCoupsPossibles() {
    //    return this->coupsPossibles;
}

void SimuMCTS::jouerCoup(Coup coup) {

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
