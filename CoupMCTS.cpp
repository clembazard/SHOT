/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoupMCTS.cpp
 * Author: cremond
 * 
 * Created on 17 mai 2017, 13:04
 */

#include "CoupMCTS.h"

CoupMCTS::CoupMCTS(int valeur) {
    this->valeur = valeur;
}

CoupMCTS::CoupMCTS(const CoupMCTS& orig) {
}

CoupMCTS::~CoupMCTS() {
}

int CoupMCTS::getValeur() {
    return this->valeur;
}

