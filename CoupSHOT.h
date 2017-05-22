/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoupSHOT.h
 * Author: cremond
 *
 * Created on 22 mai 2017, 10:43
 */

#ifndef COUPSHOT_H
#define COUPSHOT_H

class CoupSHOT {
public:
    CoupSHOT(int valeur);
    CoupSHOT(const CoupSHOT& orig);
    virtual ~CoupSHOT();
    
    int getValeur();
private:
    int valeur;
};

#endif /* COUPSHOT_H */

