/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   noeud.h
 * Author: cremond
 *
 * Created on 2 février 2017, 13:23
 */

#ifndef NOEUD_H
#define NOEUD_H


#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>


#include "decision.h"

class noeud {
public:
    
    int sousNoeudsRestant;
    
    
    // Methods
    noeud();
    noeud(int nbSousNoeuds);
    noeud(noeud* pere);
    noeud(const noeud& orig);
    virtual ~noeud();

    void simuler();
    noeud *getMeilleurFils();
    decision *getDecision();
    void expension();
    void evalutation();

    // getter
    int getCptPassage();
    std::string getDecisionPere();
    noeud *getPere();
    std::vector<noeud> getFils();
    float getMoyenne();

    // setter
    void setCptPassage(int cptPassage);
    void setDecisionPere(std::string decision);
    void setPere(noeud *pere);
    void setFils(std::vector<noeud> fils);
    void setMoyenne(float moyenne);

private:

    std::string LEFT_MOVE = "LEFT_MOVE";
    std::string RIGHT_MOVE = "RIGHT_MOVE";

    std::string decisionDuPere;

    noeud *pere;

    int cptPassage;

    float moyenne;

    std::vector<noeud> fils;

    int randomInt(int min, int max);

    std::string getRandomDecision();
};

#endif /* NOEUD_H */

