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
#ifndef BATTLESHIPSTRUCTS_H
#define BATTLESHIPSTRUCTS_H
class AI{
private:
    inline const static int Z2 = 2;
    inline const static int Z3 = 3;
    inline const static int Z4 = 4;
    inline const static int Z5 = 5;
    inline const static int Z9 = 9;
    
    
public:
    int gZ2(){return Z2;}
    int gZ3(){return Z3;}
    int gZ4(){return Z4;}
    int gZ5(){return Z5;}
    int gZ9(){return Z9;}
};


struct binXfer {            //Binary Transfer receipt used to send data to binary files
    char *ltr;              //Functions use this receipt differently for different data and files
    char *num;
};
struct BrdSet {             //Set of boards (note master board is not saved as it holds no alterable data)
    const static int sz=9;
    std::string B1S[sz][sz];    //Player 1 Ship board
    std::string B1G[sz][sz];    //Player 1 Guess board
    std::string B2S[sz][sz];    //Player 2 Ship board
    std::string B2G[sz][sz];    //Player 2 Guess board
    std::string MB[sz][sz];     //Master board containing gridsquares [A1-I9]
};
struct shipDat {                //Data for a single ship, to be used as array by plyrSave
    std::string *spcs;          //Gridsquare spaces held by ship
    int size;                   //Number of Spaces ship holds
    short dmg;                  //Not passed in binary file - rarely needed
};
struct plyrSv {               //Necessary information to play a game of battleship
    std::string P1Name, P2Name; //Player Names (used for score keeping)
    shipDat *P1Ships;           //Player 1 Ships and their locations
    shipDat *P2Ships;           //Player 2 Ships and their locations
    short P1Pts,P2Pts;          //Player points
    short turn, tMax;           //Current and maximum turns.  Cannot exceed 81 and loops if under 1 turn
    short ShpDZ;                //Number of ships each player holds (hard value set to 5 usually)
    BrdSet BrdDat;              //Set of boards to compare information and record guesses
};
struct record
            {
        std::string Name;       //player name
        int Vs;                 //Total victories
        int Ps=0;               //Total points accumulated
        int Ts;                 //Total turns player across all games
        int Gs;                 //# games played
            };


#endif /* BATTLESHIPSTRUCTS_H */

