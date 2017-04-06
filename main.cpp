/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: cremond
 *
 * Created on 2 février 2017, 13:13
 */

#include <cstdlib>
#include <iostream>
#include "noeud.h"

using namespace std;

const string leftMove = "LEFT_MOVE";
const string rightMove = "RIGHT_MOVE";

/*
 * 
 */
int main(int argc, char** argv) {

    const int budget = 50;
    
    // creation d'un arbre
    noeud * arbre = new noeud(1);
//    cout << arbre << endl;

    // tq pas en fin de partie
    
    //      échantilloner la prochaine cdécsion
    for (int i = 0; i < budget i++) {
        arbre->simuler();
    }
    //       quel est le meilleur choix à la racine? labranch avec plus de passages
    
    //       affectuer le meilleur choix : déplacer la racine "arbre"
    
    // fin tq 
    return 0;
}

