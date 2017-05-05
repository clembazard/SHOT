/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constantes.h
 * Author: cremond
 *
 * Created on 4 mai 2017, 09:40
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

class Constantes {
public:
    static const int budget = 20;
    static const int profondeurMax = 16;


    Constantes();
    Constantes(const Constantes& orig);
    virtual ~Constantes();
private:

};

#endif /* CONSTANTES_H */

