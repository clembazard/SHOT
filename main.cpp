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
#include "Constantes.h"

using namespace std;

/*
 * 
 */



int main(int argc, char** argv) {
    
    // Initialisation de la graine aléatoire
    //srand(time(NULL));
    
    bool finDePartie = false;

    vector<int> *chemin = new vector<int>;

    // tq pas en fin de partie
    while (chemin->size() < Constantes::profondeurMax) { // chemin.size < 32 !!!               

        // décider un coup IA

        // creation d'un arbre
        noeud * arbre = new noeud();

        //      échantilloner la prochaine décision
        for (int i = 0; i < Constantes::budget; i++) {
            cout << "simulation " << i << endl;
            arbre->simuler(Constantes::budget, chemin);

        }

        //       quel est le meilleur choix à la racine? la branche avec plus de passages
        int meilleurChoix;

        // juste comparer les 2 fils
        int cptBrancheGauche = arbre->getFils()[0]->getCptPassage();
        int cptBrancheDroite = arbre->getFils()[1]->getCptPassage();

        if (cptBrancheGauche > cptBrancheDroite) {
            meilleurChoix = 0;
        } else {
            meilleurChoix = 1;
        }

        // appliquer le meilleur choix
        // chemin + (choix) ? "g" : "d";

        chemin->push_back(meilleurChoix);

        //       affectuer le meilleur choix : déplacer la racine "arbre"
        //arbre->getFils()[1 - meilleurChoix]->~noeud(); // on supprime ce qui ne nous sert plus
        //arbre = arbre->getFils()[meilleurChoix]; // déplace la racine de l'arbre.

        cout << "chemin [";
        for (int i = 0; i < chemin->size(); i++) {
            cout << (*chemin)[i] << ",";
        }
        cout << "]" << endl;

        delete arbre;
    }

    // afficher le score réel
    noeud noeudDeCalcul;
    cout << "score du jeu : " << noeudDeCalcul.calculScore(chemin) << endl;

    return 0;
}

