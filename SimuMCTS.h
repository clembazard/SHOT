/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuMCTS.h
 * Author: cremond
 *
 * Created on 17 mai 2017, 11:16
 */

#ifndef SIMUMCTS_H
#define SIMUMCTS_H

#include "Simulation.h"
#include "Coup.h"
#include "CoupMCTS.h"

class SimuMCTS : public Simulation {
public:    
    SimuMCTS(std::vector<int> *chemin);
    SimuMCTS(const SimuMCTS& orig);
    virtual ~SimuMCTS();

    std::vector<int> *getCoupsPossibles();
    void jouerCoup(CoupMCTS coup);
    bool estTermine();
    float calculScore();
    
private:

    std::vector<int> *clonerVector(std::vector<int> *chemin);
    std::vector<int> *cheminSim;
    std::vector<int> *coupsPossibles;
    

};

#endif /* SIMUMCTS_H */

