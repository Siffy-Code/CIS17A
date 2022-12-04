/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   RNG.h
 * Author: ptron
 *
 * Created on December 2, 2022, 7:45 PM
 */

#ifndef RNG_H
#define RNG_H
#include "siffy.h"
using namespace std;

class RNG{//abstract class
protected:
    int rngVal;     //basic inherent value to be passed on as private
public:
    void setVal(int x){rngVal = ((x+x)/3);} //basic RNG modifier
    //set template functions
    virtual string mix() = 0;                   //Abstract class callout for returning value as a string
    virtual void LIM() = 0;                     //Abstract class function callout for limiting random number
    RNG(){rngVal = 0;}                          //Constructor
    int getVal(){return rngVal;}                
};



class BSAI:public RNG{                          //Derived class from RNG for battleship
private:
    char rngChr;        //Additional Variable for Battleship (character for grid square)
    bool aHit;          //If in "search" mode (got hit, looking for axis)
    bool bHit;          //If in "travel" mode (found ship axis)
    bool zHit;          //If in "return" mode (finished travel mode, checking other direction)
    char chStr;         //storage for character to base modes on
    int iStr;           //storage for integer to base modes on
    int zCnt;           //Counter to keep guesses in-axis (switch fodder)
    int dmgCnt;         //Returns to random guesses if AI is not functioning or has gotten 5 hits in a row
public:
    BSAI(){dmgCnt=0;rngVal=0;rngChr='0';aHit=false;bHit=false;zHit=false;chStr='0';iStr=0;zCnt=0;}
    void reset(){rngVal=0;rngChr='0';aHit=false;bHit=false;zHit=false;chStr='0';iStr=0;zCnt=0;dmgCnt=0;}
    string mix(){                         //Combines random char/int for gridsquare
                    siffy sif =siffy();   //Polymorphic use of Siffy utility class
                    sif.sifC2C(rngChr);
                    sif.sifI2I(rngVal);
                    sif.sifS2S(sif.sndC2S()+sif.sndI2S());
                    return sif.useS();
                    }
    
    void LIM(){if(rngVal<0){rngVal=rngVal*(-1);} rngVal = ((rngVal%9) + 1);}            //Returns number 1-9
    void LIMc(int x){ rngChr = ((x%9) + 1 + 64);}    //Returns char A-I, should have integer dropped into char argument
    string AIrun(int x,int y){  //Nested runtime function for random values
        setVal(x);
        
        LIM();
        LIMc(y);
        chStr = rngChr;iStr=rngVal;
        cout<<rngVal<<" and "<<rngChr<<endl;        
        cout<<iStr<<" and "<<chStr<<endl;

        return mix();
    }
        
        string AIguess(bool x,int n,int y){
          
            if(x){dmgCnt++;}    //error prevention system, also tells AI when to start random guessing
            
            
            if((aHit && bHit && zHit && !x) || dmgCnt>5){   //AI has hit end of programmed segment
            reset();                                        //Reset Values
            return AIrun(n,y);                              //Pass random numbers through
            }
            else if(aHit && bHit && zHit && x)              //AI is doubling back still
            {
            switch(zCnt){
                case 0:{rngChr=rngChr-1;return mix();}
                case 1:{rngVal=rngVal+1;return mix();}
                case 2:{rngChr=rngChr+1;return mix();}
                case 3:{rngVal=rngVal-1;return mix();}
                        }
            }
            else if(aHit && bHit && !zHit && !x)            //AI has hit the end of the hit-streak and will double back
            {
            zHit=true;
            rngChr=chStr;rngVal=iStr;
            switch(zCnt){
                case 0:{rngChr=rngChr-1;return mix();}
                case 1:{rngVal=rngVal+1;return mix();}
                case 2:{rngChr=rngChr+1;return mix();}
                case 3:{rngVal=rngVal-1;return mix();}
                        }
            }
            else if(aHit && bHit && !zHit && x)             //AI is still running down the primary axis hit-streak
            {
            switch(zCnt){
                case 0:{rngChr=rngChr+1;rngVal=iStr;return mix();}
                case 1:{rngVal=rngVal-1;rngChr=chStr;return mix();}
                case 2:{rngChr=rngChr-1;rngVal=iStr;return mix();}
                case 3:{rngVal=rngVal+1;rngChr=chStr;return mix();}
                        }
            }
            else if(aHit && !bHit && !zHit && x)            //AI located the axis of the ship last turn
            {
                bHit=true;
            switch(zCnt){
                case 0:{rngChr=rngChr+1;rngVal=iStr;return mix();}
                case 1:{rngVal=rngVal-1;rngChr=chStr;return mix();}
                case 2:{rngChr=rngChr-1;rngVal=iStr;return mix();}
                case 3:{rngVal=rngVal+1;rngChr=chStr;return mix();}
                        }
            }
            else if(aHit && !bHit && !zHit && !x)           //AI is still searching for the axis of the ship
            {if(zCnt<3){zCnt++;}else{zCnt=0;};cout<<"1000 "<<zCnt<<endl;
                        
                switch(zCnt){
                case 0:{rngChr=chStr+1;rngVal=iStr;return mix();}
                case 1:{rngVal=iStr-1;rngChr=chStr;return mix();}
                case 2:{rngChr=chStr-1;rngVal=iStr;return mix();}
                case 3:{rngVal=iStr+1;rngChr=chStr;return mix();}
                            }
                }
            else if(!aHit && !bHit && !zHit && x)           //AI is setting initial hit to begin guess routine
                {
                
                aHit=true;
                if(iStr != 1 && iStr!=9 && chStr == 'I'){zCnt=1;}       //Start guessing at orientation 1 if against wall I
                if(iStr != 1 && iStr!=9 && chStr == 'A'){zCnt=3;}       //Start guessing at orientation 3 if against wall A
                if(iStr == 1 && chStr != 'I' && chStr!='A'){zCnt=2;}    //Start guessing at orientation 2 if against wall 1
                if(iStr == 9 && chStr != 'I' && chStr!='A'){zCnt=0;}    //Start guessing at orientation 0 if against wall 9
                                   
                
                switch(zCnt){                                           //Checks each orientation around the hit to find the rest of the ship
                case 0:{rngChr=chStr+1;rngVal=iStr;return mix();}
                case 1:{rngVal=iStr-1;rngChr=chStr;return mix();}
                case 2:{rngChr=chStr-1;rngVal=iStr;return mix();}
                case 3:{rngVal=iStr+1;rngChr=chStr;return mix();}
                            }
                }
            else  {return AIrun(n,y);}                                  //Standard AI performance without a previous hit
            cout<<"Unpossible, Now you Face Mogor!"<<endl;              //Impossible to reach - critical error
            return "X0";
        }

    
};


#endif /* RNG_H */

