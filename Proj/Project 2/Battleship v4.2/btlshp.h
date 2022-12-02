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
#include <iostream>  //Input-Output Library
#include <iomanip> //for using setprecision(_)<<fixed for decimals - 
                   //via google 20220218 1718 PST
                   //verified 0 memory usage to add #include lines 20220223
#include <string>  //added 20220223 1101 PST from CIS-5 Lecture 2 24:37
                   //allows use of string variables; Ex. use to update outputs
                   //with new names
#include <cstdlib> //Added 20220223 1251 PST from CIS-5 Lab 2 9:49
                   //allows use of "random" functions 
                   //|srand(static_cast<int>(time(0)));|
#include <ctime>   //Added 20220223 1251 PST from CIS-5 Lab 2 9:50
                   //Time to set random number to; successive runs will produce
                   //successive results
#include <cmath>   //Added 20220310 1908 PST for exponents with variables
                   //ex, pow(function,exponent)
#include <sstream> //Added 20220501 1746 PST for stringstream to convert text
                   //to numbers
#include <fstream> //Added 20220513 1200 PST for file input/output
#include <vector>  //Added 20220604 for Scores
#include <cstring>
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

