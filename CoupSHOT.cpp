/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoupSHOT.cpp
 * Author: cremond
 * 
 * Created on 22 mai 2017, 10:43
 */

#include "CoupSHOT.h"

CoupSHOT::CoupSHOT(int valeur) {
    this->valeur = valeur;
}

CoupSHOT::CoupSHOT(const CoupSHOT& orig) {
}

CoupSHOT::~CoupSHOT() {
}

int CoupSHOT::getValeur() {
    return this->valeur;
}

