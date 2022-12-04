/* 
 * File:   main.cpp
 * Author: Peter T Ronning
 * Created: 20220530 1454 PST
 * Last Modified: 20221030
 * Purpose:  To battle your ships, duh!
 *Variables should include Name, units, range of entry, and details
 */

//System Level Libraries

#include "btlshp.h"                                                  //Header file containing structures for Battleship

using namespace std;

//User Defined Structures

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
    
    if(!ldsv){
    data.setShps();
    data.chkTrns();
    }
    
    data.runGam();
    data.EGScr();
    
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
//4.2
//Gameplay is restored for two human players. Load game and AI are not implemented.  Scores
//function correctly and gameplay is accurate.  Menu functions are functional.
//v4.3
//Gameplay is fully functional for one or two players.  Load game and AI function
//completely.  In-game text is minimal and summary debug still shows when loading.
//Needs turn-by-turn menu still and destroy functions implemented.
