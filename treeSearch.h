/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   treeSearch.h
 * Author: cremond
 *
 * Created on 2 février 2017, 13:27
 */

#ifndef TREESEARCH_H
#define TREESEARCH_H

class treeSearch {
public:
    int budget;

    treeSearch();
    treeSearch(const treeSearch& orig);
    virtual ~treeSearch();


    void creerLaRacine();
    void simuler();
    void prendreLaDecision();

private:
    void descente();
    void expansion();
    void eval();
    void backPropagation();

};

#endif /* TREESEARCH_H */

