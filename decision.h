/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   decision.h
 * Author: cremond
 *
 * Created on 22 mars 2017, 09:04
 */

#ifndef DECISION_H
#define DECISION_H

class decision {
public:

    int budget;

    decision(int budget);
    decision(const decision& orig);
    virtual ~decision();
    
    void jouer();

    // getter
    std::vector<std::string> getDecision();
    float getMoyenne();

    //setter
    void setDecision(std::vector<std::string> decision);
    void setMoyenne(float moyenne);
private:

    std::string LEFT_MOVE = "LEFT_MOVE";
    std::string RIGHT_MOVE = "RIGHT_MOVE";


    // must true for LEFT
    // end false for RIGHT
    std::vector<std::string> decisions;
    float moyenne;
    bool finish();

    int randomInt(int min, int max);

    std::string getRandomDecision();

};

#endif /* DECISION_H */

