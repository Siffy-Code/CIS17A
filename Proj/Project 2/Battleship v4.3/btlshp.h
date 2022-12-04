/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   BattleshipStructs.h
 * Author: ptron
 *
 * Created on October 29, 2022, 7:42 PM
 */
#ifndef BTLSHP_H
#define BTLSHP_H
#include "shipDat.h"
#include "siffy.h"
#include "plyrSv.h"
#include "strcts.h"

using namespace std;
class btlshp{  //basic game functions
private:
      
    plyrSv gamDat;
    vector<record> Scrs;        //Score storage and display medium in-game.  Placed in text file otherwise
    //siffy to be the multiple inheritance?
    fstream file;
    int maxSpc;
    string Win;
public:
    
    void chkTrns();
    void runGam(){gamDat.plyGam(Win,file);}
    //initialize win as "null"
    //player selection at each turn function
    void SUtxt1 (string);                                       //Setup Text for Player Instructions
    void MenuOpt ();                                            //Displays menu options
    void swtch(char,bool &);         //The Welcome Screen Menu (score operations and passthrough)
    btlshp();
    void setShps();
        //Initialization Functions - should be grouped into a master function and called once
    
    
    void EGScr(); //End of game operations to create or update player records - should delete data in plyrsv
    void DisScre();                             //Displays Scores
    record *newscre (string,string,int,int);                    //Creates a new Player score record for text file output
    void updscre (string ,string ,int ,int ,int);              //Updates a players score if found during search
    void txtRd ();                    //Reads text file score details
    void txtWrt ();                   //Writes text file score details

    
};




#endif /* BTLSHP_H */

