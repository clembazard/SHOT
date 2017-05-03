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
    noeud(const noeud& orig);
    virtual ~noeud();

    void simuler(int budget, std::vector<int> chemin);
    noeud *getMeilleurFils();
    decision *getDecision();
    void expension(std::vector<int> cheminSim);
    void evalutation();
    void calculMoyenne();
    void retropropagation(noeud *branche);
    void ajouterDecision(int d);
    noeud * descente(std::vector<int> cheminSim);
    int noeud::rollout(std::vector<int> cheminSim);


    // getter
    int getCptPassage();
    int getDecisionPere();
    noeud * getPere();
    std::vector<noeud*> getFils();
    float getMoyenne();

    // setter
    void setCptPassage(int cptPassage);
    void setDecisionPere(int decision);
    void setPere(noeud * pere);
    void setFils(std::vector<noeud*> fils);
    void setMoyenne(float moyenne);

private:

    // 0 pour gauche
    // 1 pour droite
    int decisionDuPere;

    noeud *pere;

    int cptPassage;

    float moyenne;

    std::vector<noeud *> fils;

    int randomInt(int min, int max);

    int getRandomDecision();

    int budget;

    bool peutContinuerAGagnerDesPoints;

    std::vector<int> tableauDecisions;
};

#endif /* NOEUD_H */

