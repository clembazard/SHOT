/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulation.h
 * Author: cremond
 *
 * Created on 17 mai 2017, 10:56
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <cstdlib>
#include <vector>
#include"Coup.h"

class Simulation {
public:
    Simulation();
    Simulation(const Simulation& orig);
    virtual ~Simulation();
    virtual std::vector<Coup> coupsPossibles() = 0;
    virtual void jouerCoup(Coup coup) = 0;
    virtual bool estTermine() = 0;

private:
};

#endif /* SIMULATION_H */

