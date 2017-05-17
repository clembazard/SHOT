/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoupMCTS.h
 * Author: cremond
 *
 * Created on 17 mai 2017, 13:04
 */

#ifndef COUPMCTS_H
#define COUPMCTS_H

#include "Coup.h"


class CoupMCTS : Coup {
public:
    CoupMCTS(int valeur);
    CoupMCTS(const CoupMCTS& orig);
    virtual ~CoupMCTS();
    int getValeur();
    
private:
    int valeur;
};

#endif /* COUPMCTS_H */

