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

/*
 * 
 */
int main(int argc, char** argv) {
    bool finDePartie = false;
    const int budget = 50;
    
    string chemin; // coups joués
               
 
    // tq pas en fin de partie
    while (!finDePartie) { // chemin.size < 32 !!!
        // décider un coup IA
        
        // creation d'un arbre
        noeud * arbre = new noeud();
        //    cout << arbre << endl;

        //int cptBrancheGauche = 0;
        //int cptBrancheDroite = 0;

        //      échantilloner la prochaine décision
        for (int i = 0; i < budget; i++) {
            cout << "simulation " << i << endl;
            arbre->simuler(budget, chemin);

        }
        
        //       quel est le meilleur choix à la racine? la branche avec plus de passages
        int meilleurChoix;
            // juste comparer les 2 fils
            cptBrancheGauche += arbre->getFils()[0]->getCptPassage();
            cptBrancheDroite += arbre->getFils()[1]->getCptPassage();
        if (cptBrancheGauche > cptBrancheDroite) {
            meilleurChoix = 0;
        } else {
            meilleurChoix = 1;
        }
        
        // appliquer le meilleur choix
            chemin + (choix) ? "g" : "d";
            
            
            
        //       affectuer le meilleur choix : déplacer la racine "arbre"
        //arbre->getFils()[1 - meilleurChoix]->~noeud(); // on supprime ce qui ne nous sert plus
        //arbre = arbre->getFils()[meilleurChoix]; // déplace la racine de l'arbre.
        delete arbre;
    }
    // afficher le score réel
    
    return 0;
}

