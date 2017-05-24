/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimuSHOT.h
 * Author: cremond
 *
 * Created on 22 mai 2017, 10:42
 */

#ifndef SIMUSHOT_H
#define SIMUSHOT_H

#include "Simulation.h"
#include "CoupSHOT.h"
#include "Constantes.h"
#include "noeud.h"
#include <tuple>
#include <stdexcept>
#include <math.h>

class SimuSHOT : public Simulation {
public:
    SimuSHOT(std::vector<int> *chemin);
    SimuSHOT(const SimuSHOT& orig);
    virtual ~SimuSHOT();

    std::vector<int> *getCoupsPossibles();
    void jouerCoup(CoupSHOT coup);
    bool estTermine();
    float calculScore();
    void rollout();
    void simulerSHOT(noeud *arbre, int budget, int *budgetUtilise);


private:
    std::vector<int> *cheminSim;
    std::vector<int> *coupsPossibles;

    // Methods
    std::vector<int> *clonerVector(std::vector<int> *chemin);
    int randomInt(int min, int max);
    int getRandomDecision();

    // tris
    static bool sortByCptPassage(noeud *lhs, noeud *rhs);
    static bool sortByAscendingScore(const std::tuple<int, int, float>& lhs, const std::tuple<int, int, float>& rhs);
};

#endif /* SIMUSHOT_H */
