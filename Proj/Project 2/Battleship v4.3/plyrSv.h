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
#include "siffy.h"

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
    void frcN2(){P2Name="AI";}
    void Bin2Brd(binXfer *);                      //Converts a binXfer binary receipt into a Board Set
    void Bin2Dat(binXfer *);                    //Converts a binXfer binary receipt into a set of ship/pts/turn/name data
    
    void Summary();
    binXfer *Dat2Bin ();                                //Converts ship/points/turn/name data into a binXfer binary receipt to write save files
    binXfer *Brd2Bin (BrdSet);                              //Converts a boardset data into a binXfer binary receipt to write save files
    //Game saving functions
    void LdSave (plyrSv &,std::fstream &);                     //Performs all actions necessary to update a freshly created plyrSv with saved data
    void MakSave (std::fstream &);                      //Performs all actions necessary to send basic plyrSv data to restart game to binary file
    binXfer *binRC (std::fstream &,int,std::string);                      //Reads data from a binary file and returns a binXfer receipt structure for conversion
    void destroy (binXfer *,int,char);                               //Destroys nasty memory
    
    
    void binWrt (binXfer *,fstream &,int,string);               //Writes data from a binXfer receipt into a binary file    
    void AIShpSU (int);          //Ship Setup procedures for playing against the computer

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

