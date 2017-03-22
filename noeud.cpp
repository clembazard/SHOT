/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   noeud.cpp
 * Author: cremond
 * 
 * Created on 2 février 2017, 13:23
 */

#include "noeud.h"

noeud::noeud() {
    this->moyenne = 0;
}

noeud::noeud(const noeud& orig) {
}

noeud::~noeud() {
}

void noeud::expension() {
    // creation de deux nouveau noeuds

    noeud noeudGauche;
    noeudGauche.setDecisionPere(this->LEFT_MOVE);
    noeud noeudDroite;
    noeudDroite.setDecisionPere(this->RIGHT_MOVE);

    this->fils.push_back(noeudDroite);
    this->fils.push_back(noeudGauche);
}

void noeud::evalutation() {
    noeud::moyenne + 1;
}

int noeud::getCptPassage() {
    return this->cptPassage;
}

std::string noeud::getDecisionPere() {
    return this->decisionDuPere;
}

noeud *noeud::getPere() {
    return this->pere;
}

std::vector<noeud> noeud::getFils() {
    return this->fils;
}

float noeud::getMoyenne() {
    return this->moyenne;
}

void noeud::setCptPassage(int cptPassage) {
    this->cptPassage = cptPassage;
}

void noeud::setDecisionPere(std::string decision) {
    this->decisionDuPere = decision;
}

void noeud::setPere(noeud* pere) {
    this->pere = pere;
}

void noeud::setFils(std::vector<noeud> fils) {
    this ->fils = fils;
}

void noeud::setMoyenne(float moyenne) {
    this->moyenne = moyenne;
}

int noeud::randomInt(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

std::string noeud::getRandomDecision() {
    int randomNumber = randomInt(0, 1);
    std::string valueToReturn = "";
    if (randomNumber == 0) {
        valueToReturn = LEFT_MOVE;
    } else {
        valueToReturn = RIGHT_MOVE;
    }
    return valueToReturn;
}
