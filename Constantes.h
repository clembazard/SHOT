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
    static const int budget = 100;
    static const int profondeurMax = 64;
    static constexpr double k = 1; // 0.1 | 0.3 | 1 -> 0.3 semmble plus approprié pour une prodondeur max de 32 et un budget de 50

    Constantes();
    Constantes(const Constantes& orig);
    virtual ~Constantes();
private:

};

#endif /* CONSTANTES_H */

