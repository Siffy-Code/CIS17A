/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "shipDat.h"
#include "siffy.h"      //necessary?
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
void shipDat::shipD(int x)
{
    spcs = new string[x];
    for(int Q=0;Q<x;Q++)   //Set all ships to XX as initial spaces
    {
    spcs[Q] = "XX";
    }

    dmg = 0;

    size=x;

}
void shipDat::FillShp (string user)
{
       cout<<"debugfillship0"<<endl;

    siffy *sof = new siffy();
    
    cout<<"debugfillship1"<<endl;
    
    sof->sifS2S(spcs->substr(0,1));                //extract letter from guess
    sof->sifS2I(spcs->substr(1,1));                //extract letter from guess

        cout<<"-----"<<endl;

    while (!sof->useB())                          //while flag is true
    {cout<<"debugfillship2"<<endl;
    if (user.compare("R")==0 || user.compare("r")==0 ||user.compare("L")==0 ||user.compare("l")==0 ||user.compare("U")==0 ||user.compare("u")==0 ||user.compare("D")==0 ||user.compare("d")==0 )
    {sof->flipB();    } //Ensures data is a valid selection flip to flase
    else {cout<<"Invalid Input Please use |L|  |R|  |U|  |D|"<<endl;user=sof->sifScan();}
        cout<<"debugfillship3"<<endl;

        //Ship Orientation Specifics
    if(user=="R" || user=="r") 
    {cout<<"debugfillship4"<<endl;
            if(sof->useS()=="I"){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl; sof->flipB();user=sof->sifScan();}
            else if(sof->useS()=="H"&&size>2){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useS()=="G"&&size>3){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan();}
            else if(sof->useS()=="F"&&size>4){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan();}
        else
        {cout<<"debugfillship5"<<endl;
        for (int i=1 ; i<size ; i++)
            {cout<<"debugfillship6"<<endl;
            
        sof->sifC2CS(const_cast<char*>(sof->useS().c_str()));//Buff=const_cast<char*>(Letter.c_str()); //Allows Buff to embody pointer to Letter String
                    cout<<"debugfillship7"<<sof->useCS()<<endl;
        sof->sifS2S(sof->Cnvt(sof->ppChar(sof->useCS())));
                    cout<<"debugfillship8"<<sof->useS()<<endl;
        spcs[i]=(sof->useS()+to_string(sof->useI()));
                    cout<<"debugfillship9"<<spcs[i]<<" "<<sof->useB()<<endl;
            }
        
        }
    }//End Right
    else if (user=="U" || user=="u")
    {
            if(sof->useI()==1){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;sof->flipB();user=sof->sifScan();}
            else if(sof->useI()==2&&size>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;sof->flipB();user=sof->sifScan();}
            else if(sof->useI()==3&&size>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;sof->flipB();user=sof->sifScan();}
            else if(sof->useI()==4&&size>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
      else
      {  
        for (int i=1 ; i<size ; i++)
        {
        sof->sifI2I(sof->useI()-1);
        spcs[i]=(sof->useS()+to_string(sof->useI()));
        }
      }
    }//End Up
    else if (user=="L" || user=="l")
    {
            if(sof->useS()=="A"){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useS()=="B"&&size>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useS()=="C"&&size>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useS()=="D"&&size>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;sof->flipB();user=sof->sifScan(); }
      else
      {
        for (int i=1 ; i<size ; i++)
        {
        sof->sifS2CS(const_cast<char*>(sof->useS().c_str()));//Buff=const_cast<char*>(Letter.c_str()); //Allows Buff to embody pointer to Letter String
         
        sof->sifS2S(sof->Cnvt(sof->mmChar(sof->useCS())));
        spcs[i]=(sof->useS()+to_string(sof->useI()));
        }
      }
    }//End Left
    else if (user=="D" || user=="d")
    {
            if(sof->useI()==10){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;sof->flipB();user=sof->sifScan();}
            else if(sof->useI()==9&&size>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useI()==8&&size>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;sof->flipB();user=sof->sifScan(); }
            else if(sof->useI()==7&&size>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;sof->flipB();user=sof->sifScan();}
      else
      {
        for (int i=1 ; i<size ; i++)
        {
        sof->sifI2I(sof->useI()+1);
        spcs[i]=(sof->useS()+to_string(sof->useI()));
        }
      }
    }//end Down
    else {cout<<"You are trying to enter a Grid Square instead of a Direction"<<endl;
    cout<<"Use |L|  |R|  |U|  |D|"<<endl;}
    }//end While Loop
        cout<<"ugh"<<endl;
    //destructor for siffy
        delete sof;
}
void shipDat::ICoord ()
{//outputs individual ship coordinates
    cout<<"| ";
    for (int i=0 ; i<size ; i++)
    {
        cout<<spcs[i]<<" | ";
    }
    cout<<endl;
}
string shipDat::AIShpDr (char AIL,int AIN,int ShpZ)
{
    switch(ShpZ)
    {
        case 2: {if(AIN<2 || AIN>8)//Criteria for Selecting Ship Orientation
                {
                    if(AIL<'B'){return "R";}
                    else{return "L";}//Conditional Operator for Grading Purposes
                }
                else 
                {
                    if (rand()%2<1) {return "U";} //Criteria for Selecting Ship Orientation
                    else {return "D";}
                }
                }
        case 3: {
            if(AIN<3 || AIN>7)//Criteria for Selecting Ship Orientation
                {
                    if(AIL>'G'){return "L";}//Criteria for Selecting Ship Orientation
                    else {return "R";}
                }
                else 
                {
                    if (rand()%2<1) {return "D";} //Criteria for Selecting Ship Orientation
                    else {return "U";}
                }
                }
                
        case 4:{
                    if(AIN<4 || AIN>6)//Criteria for Selecting Ship Orientation
                {
                    if(AIL>'F'){return "L";}//Criteria for Selecting Ship Orientation
                    else {return "R";}
                }
                else 
                {   if (rand()%2<1) {return "D";} //Criteria for Selecting Ship Orientation
                    else {return "U";}
                }
                }
        case 5:{
                    if(AIN!=5)//Criteria for Selecting Ship Orientation
                {   if(AIL>'E'){return "L";}//Criteria for Selecting Ship Orientation
                    else {return "R";}
                }
                else 
                {   if (rand()%2<1) {return "U";} //Criteria for Selecting Ship Orientation
                    else {return "D";}
                }
        }
        default:{return "X";}
        }
}
void shipDat::shptxt (int x)
{
    enum ShpTyp {DESTROYER,CRUISER,SUBMARINE,BATTLECRUISER,CARRIER};
    if(x==DESTROYER){         cout<<"-=DESTROYER     -   TWO SPACES=-"<<endl;}
    else if(x==CRUISER){      cout<<"-=CRUISER       - THREE SPACES=-"<<endl;}
    else if(x==SUBMARINE){    cout<<"-=SUBMARINE     - THREE SPACES=-"<<endl;}
    else if(x==BATTLECRUISER){cout<<"-=BATTLECRUISER -  FOUR SPACES=-"<<endl;}
    else if(x==CARRIER){      cout<<"-=CARRIER       -  FIVE SPACES=-"<<endl;}
}


void shipDat::addDmg (shipDat *PShips,int ShpDZ,string guess)
{
    for(int y=0;y<ShpDZ;y++)
    {
        for(int u=0;u<PShips[y].size;u++)
        {
            if(guess==PShips[y].spcs[u])    
            {
                PShips[y].dmg++; 
                if(PShips[y].dmg==PShips[y].size)       //If ship has sustained damage equal to size, display sink text
                    {
                    cout<<"-----You Sunk a Ship!-----"<<endl;
                    shptxt(y);
                    cout<<"--------------------------"<<endl;
                    PShips[y].dmg++;
                    }
                u=PShips[y].size-1; y=ShpDZ-1;
            }
        }
    }
}
