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

SHOT::SHOT() {
    std::vector<int> *chemin = new std::vector<int>;
    
    while (chemin->size() < Constantes::profondeurMax) {
        noeud *arbre = new noeud();
        
        for (int i = 0; i < Constantes::budget; i++) {
            

        }

    }
    delete chemin;
}

SHOT::SHOT(const SHOT& orig) {
}

SHOT::~SHOT() {
}

