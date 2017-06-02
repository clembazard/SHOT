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
#include "TreeSearch.h"
#include "SHOT.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    // Initialisation de la graine aléatoire
    srand(time(NULL));

    std::cout <<"____________________________Execution de MCTS____________________________" << std::endl;
    
    //     execution du MCTS
        TreeSearch mcts;    

        std::cout <<"____________________________Execution de SHOT____________________________" << std::endl;
    // execution du SHOT
    SHOT shot;

    //    arbreEnDur();
    return 0;
}
