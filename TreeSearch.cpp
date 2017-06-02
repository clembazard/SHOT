/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeSearch.cpp
 * Author: cremond
 * 
 * Created on 17 mai 2017, 09:40
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "noeud.h"
#include "Constantes.h"
#include "TreeSearch.h"

TreeSearch::TreeSearch() {
    //    bool finDePartie = false;
    //    std::ofstream myfile;
    //    myfile.open("MTCSk01.txt");
    //
    //    for (int k = 0; k < 1000; k++) {



    std::vector<int> *chemin = new std::vector<int>;

    // tq pas en fin de partie
    while (chemin->size() < Constantes::profondeurMax) { // chemin.size < 32 !!!               

        // décider un coup IA

        // arbre représente le noeud sur lequel on se trouve
        noeud * arbre = new noeud();

        //      échantilloner la prochaine décision
        for (int i = 0; i < Constantes::budget; i++) {
            //            cout << "simulation " << i << endl;
            arbre->simuler(chemin);
        }

        //       quel est le meilleur choix à la racine? la branche avec plus de passages
        int meilleurChoix;

        // juste comparer les 2 fils

        int indexMeilleurFils = -1;
        int meilleursCptPassage = 0;
        for (int i = 0; i < arbre->getFils().size(); i++) {
            std::cout << "Branche[" << i << "] -> {cptPassage : " << arbre->getFils()[i]->getCptPassage() << "; moyenne : " << arbre->getFils()[i]->getMoyenne() << " }" << std::endl;

            if (arbre->getFils()[i]->getCptPassage() > meilleursCptPassage) {
                meilleursCptPassage = arbre->getFils()[i]->getCptPassage();
                indexMeilleurFils = i;
            }
        }

        meilleurChoix = indexMeilleurFils;

        // appliquer le meilleur choix

        chemin->push_back(meilleurChoix);


        std::cout << std::endl << "___FIN DE SIMULATION___" << std::endl;

        std::cout << "Chemin final [";
        for (int i = 0; i < chemin->size(); i++) {
            std::cout << (*chemin)[i] << ",";
        }
        std::cout << "]" << std::endl;

        //        std::cout << arbre->toString(Constantes::profondeurMax, 0) << std::endl;


        std::ofstream myfile;
        myfile.open("treeLaTex.txt");
        myfile << arbre->toLatex();
        myfile.close();
        delete arbre;
    }

    // afficher le score réel
    noeud noeudDeCalcul;
    std::cout << "score du jeu : " << noeudDeCalcul.calculScore(chemin) << std::endl;
    //        myfile << k << " " << noeudDeCalcul.calculScore(chemin) << "\n";
    delete chemin;
    //    }
    //    myfile.close();
}

TreeSearch::TreeSearch(const TreeSearch& orig) {
}

TreeSearch::~TreeSearch() {
}

