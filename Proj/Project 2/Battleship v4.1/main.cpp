/* 
 * File:   main.cpp
 * Author: Peter T Ronning
 * Created: 20220530 1454 PST
 * Last Modified: 20221030
 * Purpose:  To battle your ships, duh!
 *Variables should include Name, units, range of entry, and details
 */

//System Level Libraries
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

//User Defined Structures
#include "btlshp.h"                                                  //Header file containing structures for Battleship

//Pre&Post File Conversions and Datatype Transfers

    //Procedural Portions of Game
    //Other
int main() {
    srand(static_cast<int>(time(0)));                           //Basic random number seed for AI ship setup and guesses
    char *Menu = new char;
    bool ldsv = false;
    btlshp data;                        //Runs the constructor into data;

    
    //Menu Select
    while (*Menu!='N' && *Menu!='L' && *Menu!='?')        //Only New Game and Load leave the menu
    {
    string *buff = new string;
    data.MenuOpt();                              //Display Menu Options
    getline(cin,*buff);                     //Receive user's input into a string
    strcpy(Menu,buff->substr(0,1).c_str()); //Copy the first letter of that user's string to a char in Menu
    data.swtch(*Menu,ldsv);            //Send Menu Selection and blank vector into menu function
    delete buff;                            //Clean up nasty memory
    }//if(*Menu=='?'){gamDat.P1Name="Skip";}  //Debug Mode
    delete Menu;
    
    data.setShps();
    
    return 0;                       //Close the game!
}








//Changelog
//v3.1:
//Added new structure element "Games", allowed file to update existing player records,
//fixed player record creation issues from original version, embedded text file
//operations in functions for both winner and loser records
//v3.2:
//Added structures for boards and player save data.  Intend to create a binary file 
//to read the structure for save data so players can resume their game and demonstrate
//the use of placing structure into binary files and retrieving them.  Create a function
//skeleton for saveG for converting data into the structure
//v3.3:
//Converted the entire main into structure-based language, placed text formatting and
//loops to make player data input into individual sections instead of code for each ship
//individually.  Experimental data validation function for AI ship setup in place.
//v3.4:
//Diagnostic testing version to dial in player clipping validation and ship setup.  Game
//now runs but has many errors during player ship set up and AI ship set up.  Actual 
//gameplay after set up should remain the same, just need to fix loops
//v3.5:
//Debugged player ship selection procedures and AI random generation of ship locations.
//Nested large portions of code into functions so main is easier to navigate.
//v3.6:
//Cleaned up file operations and added dynamic buffers for temporary variables.  Added
//new output formatting and prompts.  Updated dmg concept to notify when ship is destroyed
//and what ship it was.  Created binary conversion tool for string 2D arrays to be
//written into binary files.  Plan to add AI hard mode that guesses based on hits.
//v3.7:
//Added binary file writing procedures for game data sufficient to re-start a game
//from any point.  Game saves at the end of each turn automatically.  
//Need to add additional formatting for game display and in-game options for exiting or displaying data.
//v3.8
//Rearranged coding elements to be more organized, ensured deletes and destroys exist as needed, 
//added fresh comments, polished for grading rubric lines, pseudocode, write up, and submission!
//v4.0
//Implemented basis for class addition to game logic - will focus on AI development primarily
//and additional time will be spent converting structures like ShipDat to classes since they
//are more appropriately objects.
//v4.1
//Overhaul of entire system into new class hierarchy.  Still needs constants and actual testing
//but game launches and can load at least the basic menu again.
