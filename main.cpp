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
    bool finDePartie = false;
    const int budget = 50;

    // creation d'un arbre
    noeud * arbre = new noeud();
    //    cout << arbre << endl;

    // tq pas en fin de partie
    while (!finDePartie) {

        int cptBrancheGauche = 0;
        int cptBrancheDroite = 0;

        //      échantilloner la prochaine décision
        for (int i = 0; i < budget; i++) {
            cout << "simulation " << i << endl;
            arbre->simuler(budget);

            cptBrancheGauche += arbre->getFils()[0]->getCptPassage();
            cptBrancheDroite += arbre->getFils()[1]->getCptPassage();
        }
        
        //       quel est le meilleur choix à la racine? la branche avec plus de passages
        int meilleurChoix;
        if (cptBrancheGauche > cptBrancheDroite) {
            meilleurChoix = 0;
        } else {
            meilleurChoix = 1;
        }
        
        //       affectuer le meilleur choix : déplacer la racine "arbre"
        arbre->getFils()[1 - meilleurChoix]->~noeud(); // on supprime ce qui ne nous sert plus
        arbre = arbre->getFils()[meilleurChoix]; // déplace la racine de l'arbre.
    }
    return 0;
}

