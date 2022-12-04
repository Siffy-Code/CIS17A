/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "siffy.h"
using namespace std;
void siffy::IPVal (string &ValBuff)
{//Start Input Validation check function
    do
    {//Begin do-while loop for human input - does not allow invalid inputs
    if (ValBuff.length()!=5) //Determines if within appropriate bounds
    {cout<<"Input Invalid!"<<endl;cin>>ValBuff;}
    }while (ValBuff.length()!=5); //Loops if not within appropriate bounds
}
char* siffy::chrStr(string x)
{
    char *y = new char[x.length()];
    for(int i=0;i<x.length();i++)
    {
        char *buff = new char[1];
        strcpy(buff,x.substr(i,1).c_str());
        y[i]=*buff;
        delete buff;
    }
    return y;
}
int siffy::toNum(string x)
{
    int z;
    stringstream a;
    a<<x;
    a>>z;
    return z;
}
short BSV::turnVal ()
{
    bool *flg = new bool;
    *flg=false;
    short c;
    while(!*flg)
    {
        int *temp = new int;
        sifCIN(*temp);
        try{chkTrn(*flg,*temp);}
        catch(BSV::OOB){errTxt1();}
        c=*temp;
        delete temp;
    }
    delete flg;
    cout<<"Returning "<<c<<endl;
    return c;    
}
void BSV::IPVal (string &ValBuff)
{//Start Input Validation check function
    string ColChk; //Buffer to check column letter
    int RowChk;     //Buffer to check row number
    do
    {//Begin do-while loop for human input - does not allow invalid inputs
    ColChk=ValBuff.substr(0,1); //Set Column Buffer to letter input
    stringstream Row(ValBuff.substr(1,1)); //Convert number in string to a (lovely) integer
    Row>>RowChk; //Send Row string to RowChk integer
      
    if (ValBuff.length()!=2 || ColChk>"I" || ColChk<"A" || RowChk>9 || RowChk<1) //Determines if within appropriate bounds
    {cout<<"Input Invalid, please use one Capital Letter followed by one Number!"<<endl;cin>>ValBuff;}
    }while (ValBuff.length()!=2 || ColChk>"I" || ColChk<"A" || RowChk>9 || RowChk<1); //Loops if not within appropriate bounds
}
