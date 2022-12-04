/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   siffy.h
 * Author: ptron
 *
 * Created on November 19, 2022, 8:32 PM
 * This class is the personal take-away from my time learning at Riverside City
 * College.  It includes several utility functions for basic C++ hinderances, to
 * include basic data validation that can be tailored for any programs' need.
 */

#ifndef SIFFY_H
#define SIFFY_H

#include <iostream>//Input-Output Library
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
class bogus{
private:
    int *pointme;
public:
    bogus(){pointme = new int;*pointme=0;}
    void setV(int x){*pointme=x;}
    ~bogus(){delete pointme;}
    int getV(){return *pointme;}
};
class siffy{
protected:
    string siffyS;         //string buffer
    char        *siffyCS;
    char        siffyC;
    int         siffyI;
    bool        siffyB;
public:
    int toNum (string);                                                                //Converts a string to a number
    char* chrStr (string);                                                             //Converts a string to a char*
    void IPVal (string &);                                     //Verifies input to be letter-number when necessary
    
    string sifScan(){string x;getline(cin,x);return x;}
    void sifREC(){string *x = new string;getline(cin,*x);IPVal(*x);siffyS=*x;delete x;}                                 //Constructor with data validation
    void charREC(){string *x = new string;getline(cin,*x);siffyS=*x;delete x;}
    void intREC(int x){}
    void ovride(){siffyI++;}        //++ for pointer siffys
    void operator++(){siffyI++;}    //++ for grading purposes
    //don't forget constants
    string Cnvt(char rec){string Buff;Buff=rec;return Buff;}  //Converts a char to a string (handy dandy little function for adding chars)
    string CvtI2S(int x){return to_string(x);}
    string sndI2S(){return to_string(siffyI);}
    string sndC2S(){return Cnvt(siffyC);}
    
    siffy(){siffyI=0;siffyB=0;siffyC='0';siffyS="0";}    //needs allocation of dynamic memory
    void sifC2CS(char *x){siffyCS=x;}
    void sifC2C(char x){siffyC=x;}
    void sifS2S(string x){siffyS=x;}
    void sifS2I(string x){siffyI=toNum(x);}
    void sifI2I(int x){siffyI=x;}
    void sifS2CS(string x){siffyCS=chrStr(x);}
    
    char ppChar(char *x){
        char y;
        y=*x;
        y++;
        return y;
       }     //adds one to a char array
    char mmChar(char *x){char y;y=*x;y--;return y;}     //adds one to a char array
        
    void flipB(){if(siffyB==false){siffyB=true;}else{siffyB=false;}}
    void flipF(){siffyB=false;}
    
    void sifIClr(){siffyI=0;}
    void sifCClr(){siffyC='0';}
    void sifSClr(){siffyS="0";}
    
    char useC()const{return siffyC;}
    int useI()const{return siffyI;}
    string useS()const{return siffyS;}
    char* useCS()const{return siffyCS;}
    bool useB()const{return siffyB;}
    
    class OOB{public:};
    
    template<class X>           //Single datatype comparison
    X getMax(X a, X b)
    {
        if(a>b){return a;}
        else if(a<b){return b;}
        else {return 0;}        //Return no value if same
    }
    template<class X>           //Single datatype comparison
    X getMin(X a, X b)
    {
        if(a>b){return b;}
        else if(a<b){return a;}
        else {return 0;}        //Return no value if same
    }
    
    
    
    
    void sifCIN(int &IB){   //Siffy's unbreakable CIN (modded for int)
    string *SB = new string;    //Possible template function to return detected type
    getline(cin,*SB);
    stringstream a; 
    a<<*SB;
    a>>IB;
    delete SB;}
};
class BSV:public siffy
{
public:
    BSV(){siffy();}
    short turnVal ();                                               //Validates input is sufficient for possible number of turns
    void IPVal (string &);                                     //Verifies input to be letter-number when necessary
    void sifREC(){string *x = new string;getline(cin,*x);IPVal(*x);siffyS=*x;delete x;}                                 //Constructor with data validation
    void chkTrn(bool &x,int y){if(y>0 && y<82){x=true;}else{throw OOB();}}
    void errTxt1(){cout<<"Invalid Input - Turns cannot exceed more spaces than board"<<endl;
    cout<<"Set number of turns to play for: ";}
};

#endif /* SIFFY_H */

