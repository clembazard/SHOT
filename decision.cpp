/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   decision.cpp
 * Author: cremond
 * 
 * Created on 22 mars 2017, 09:04
 */

#include <vector>
#include <string>

#include "decision.h"

decision::decision() {
}

decision::decision(const decision& orig) {
}

decision::~decision() {
}

std::vector<std::string> decision::getDecision() {
    return this->decisions;
}

float decision::getMoyenne() {
    return this->moyenne;
}
void decision::setDecision(std::vector<std::string>) {
    this->decisions = decisions;
}

void decision::setMoyenne(float moyenne) {
    this->moyenne = moyenne;
}
