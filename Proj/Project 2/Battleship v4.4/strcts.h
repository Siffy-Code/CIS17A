/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   strcts.h
 * Author: ptron
 *
 * Created on November 20, 2022, 9:36 PM
 */

#ifndef STRCTS_H
#define STRCTS_H
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

using namespace std;

struct binXfer {            //Binary Transfer receipt used to send data to binary files
    char *ltr;              //Functions use this receipt differently for different data and files
    char *num;
    };
    
    struct BrdSet {             //Set of boards (note master board is not saved as it holds no alterable data)
    const static int Z9=9;
    std::string B1S[Z9][Z9];    //Player 1 Ship board
    std::string B1G[Z9][Z9];    //Player 1 Guess board
    std::string B2S[Z9][Z9];    //Player 2 Ship board
    std::string B2G[Z9][Z9];    //Player 2 Guess board
    std::string MB[Z9][Z9];     //Master board containing gridsquares [A1-I9]
    };
struct record{
    std::string Name;       //player name
    int Vs;                 //Total victories
    int Ps=0;               //Total points accumulated
    int Ts;                 //Total turns player across all games
    int Gs;                 //# games played
    };
    
#endif /* STRCTS_H */

