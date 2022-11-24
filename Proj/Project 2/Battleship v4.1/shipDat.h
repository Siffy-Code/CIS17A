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
    void setSpc(string x){spcs[0]=x;}
    //
};

#endif /* SHIPDAT_H */

