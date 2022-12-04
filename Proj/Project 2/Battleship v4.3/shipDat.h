/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   shipDat.h
 * Author: ptron
 *
 * Created on November 20, 2022, 8:32 PM
 */

#ifndef SHIPDAT_H
#define SHIPDAT_H
#include "strcts.h"
#include "siffy.h"


using namespace std;
class shipDat { 
private:    //Data for a single ship, to be used as array by plyrSave
    inline const static int Z2 = 2;
    inline const static int Z3 = 3;
    inline const static int Z4 = 4;
    inline const static int Z5 = 5;
    
    std::string *spcs;          //Gridsquare spaces held by ship
    int size;                   //Number of Spaces ship holds
    short dmg;                  //Not passed in binary file - rarely needed
public:
    void shptxt (int );                                                                                     //Displays the text for a ship based on the size of the ship array
    void ICoord();                                                                        //outputs individual ship coordinates
    void FillShp (std::string);                                                           //fills ships with nested data validation to ensure no ships go off the board
    void addDmg (shipDat *,int ,std::string );                                                              //adds damage to structured element to provide 'ship destroyed' notification text (not passed in Binary file save)
    void shipD(int);              //Base constructor called by new game function
    int gZ2(){return Z2;}       
    int gZ3(){return Z3;}
    int gZ4(){return Z4;}
    int gZ5(){return Z5;}
    string AIShpDr (char ,int ,int );                           //Determines direction for ships when playing against the computer
    
    int getSZ()const{return size;}
    std::string getSpc(int x)const{return spcs[x];}
    void frcSpc(int x,string y){spcs[x]=y;}
    void setSpc(string x){spcs[0]=x;}
    //
};

#endif /* SHIPDAT_H */

