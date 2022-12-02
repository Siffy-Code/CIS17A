/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   plyrSv.h
 * Author: ptron
 *
 * Created on November 20, 2022, 9:33 PM
 */

#ifndef PLYRSV_H
#define PLYRSV_H
#include "shipDat.h"
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
class plyrSv {
private:                        //Necessary information to play a game of battleship
    inline static const int ShpDZ = 5;
    std::string P1Name,P2Name; //Player Names (used for score keeping)
    shipDat P1Ships[ShpDZ];           //Player 1 Ships and their locations
    shipDat P2Ships[ShpDZ];           //Player 2 Ships and their locations
    short P1Pts,P2Pts;          //Player points
    short turn, tMax;           //Current and maximum turns.  Cannot exceed 81 and loops if under 1 turn
    BrdSet BrdDat;              //Set of boards to compare information and record guesses
public:
    void setN1(){getline(cin,P1Name);}
    void setN2(){getline(cin,P2Name);}
    void setTrn(short x){tMax=x;}
    plyrSv();                  //Creates basic game data using board fills and dynamic memory allocation
    
    void Bin2Brd(binXfer *);                      //Converts a binXfer binary receipt into a Board Set
    void Bin2Dat(binXfer *);                    //Converts a binXfer binary receipt into a set of ship/pts/turn/name data
    
    
    binXfer *Dat2Bin ();                                //Converts ship/points/turn/name data into a binXfer binary receipt to write save files
    binXfer *Brd2Bin (BrdSet);                              //Converts a boardset data into a binXfer binary receipt to write save files
    //Game saving functions
    void LdSave (plyrSv &,std::fstream &);                     //Performs all actions necessary to update a freshly created plyrSv with saved data
    void MakSave (std::fstream &);                      //Performs all actions necessary to send basic plyrSv data to restart game to binary file
    binXfer *binRC (std::fstream &,int,std::string);                      //Reads data from a binary file and returns a binXfer receipt structure for conversion
    void destroy (binXfer *,int,char);                               //Destroys nasty memory
    
    
    void binWrt (binXfer *,fstream &,int,string);               //Writes data from a binXfer receipt into a binary file    
    void AIShpSU (int ,BrdSet &);          //Ship Setup procedures for playing against the computer

    void MBdFill ();                            //fills master board
    void BBdFill (string [][9]);                            //fills boards initially with tildes (waves!)
    void DisBrd (string [][9]);                             //displays a board
    void UpdBS(shipDat,std::string [][9]);  //updates ship boards
    
    
    
    string getN(int x){if(x==1){return P1Name;}else{return P2Name;}}
    short getPts(int x){if(x==1){return P1Pts;}else{return P2Pts;}}
    short getTMAX(){return tMax;}
    short getDZ(){return ShpDZ;}
    void Shoot (string ,string [][9],string [][9],short &);   //Checks a player's input to determine if their guess was a hit or miss

    //Parent Functions
    void shwBS1(){DisBrd(BrdDat.B1S);}
    void shwBS2(){DisBrd(BrdDat.B2S);}
    void P1Shps(int x){PSetUp(x,P1Name,BrdDat.B1S,P1Ships);}
    void P2Shps(int x){PSetUp(x,P2Name,BrdDat.B2S,P2Ships);}

    
    
    shipDat* P2Shps(){return P2Ships;}
    void PSetUp (int,std::string,std::string [][9],shipDat *);  //Player Ship Setup loop
    void UpdGBrd (string,string[][9],bool);    //updates guess boards
    
    
    
    
    void plyGam (string &,fstream &);   //Actual gameplay loop that really only requires the plyrSv data


};


#endif /* PLYRSV_H */

