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
    srand(time(NULL));

    bool finDePartie = false;

    vector<int> *chemin = new vector<int>;

    // tq pas en fin de partie
    while (chemin->size() < Constantes::profondeurMax) { // chemin.size < 32 !!!               

        // décider un coup IA

        // arbre représente le noeud sur lequel on se trouve
        noeud * arbre = new noeud();

        //      échantilloner la prochaine décision
        for (int i = 0; i < Constantes::budget; i++) {
            //            cout << "simulation " << i << endl;
            arbre->simuler(Constantes::budget, chemin);

        }

        //       quel est le meilleur choix à la racine? la branche avec plus de passages
        int meilleurChoix;

        // juste comparer les 2 fils


        float moyenneBrancheGauche = arbre->getFils()[0]->getMoyenne();
        cout << "CptPassage gauche :" << arbre->getFils()[0]->getCptPassage() << endl;
        cout << "Moyenne branche gauche : " << moyenneBrancheGauche << endl;

        float moyenneBrancheDroite = arbre->getFils()[1]->getMoyenne();
        cout << "CptPassage droite:" << arbre->getFils()[1]->getCptPassage() << endl;
        cout << "Moyenne branche droite : " << moyenneBrancheDroite << endl;
        
        for(int i;i<2;i++){
            std::cout << arbre->getFils()[i]->getMoyenne() << " ";
            std::cout << (Constantes::k * (2 * sqrt(((log(arbre->getCptPassage() + 1)) / arbre->getFils()[i]->getCptPassage())))) << std::endl;
        }

        if (arbre->getFils()[0]->getCptPassage() > arbre->getFils()[1]->getCptPassage()) {
            meilleurChoix = 0;
        } else {
            meilleurChoix = 1;
        }

        // appliquer le meilleur choix
        // chemin + (choix) ? "g" : "d";

        chemin->push_back(meilleurChoix);


        cout << endl << "___FIN DE SIMULATION___" << endl;

        cout << "Chemin final [";
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

