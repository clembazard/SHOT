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

decision::decision(int budget) {
    this->budget = budget;
}

decision::decision(const decision& orig) {
}

decision::~decision() {
}

void decision::jouer() {
    while (budget != 0) {
        
        
        budget--;
    }

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

int decision::randomInt(int min, int max) {
    return min + (rand() % (int) (max - min + 1));
}

std::string decision::getRandomDecision() {
    int randomNumber = randomInt(0, 1);
    std::string valueToReturn = "";
    if (randomNumber == 0) {
        valueToReturn = LEFT_MOVE;
    } else {
        valueToReturn = RIGHT_MOVE;
    }
    return valueToReturn;
}
