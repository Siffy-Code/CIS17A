/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "siffy.h"
using namespace std;
void siffy::IPVal (string &ValBuff)
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
short siffy::turnVal ()
{
    string *buff = new string;
    int *buff2 = new int;
    *buff2=0;
    *buff="";
    while(*buff2<1 || *buff2>81)
    {
    getline(cin,*buff);
    if(*buff=="X"){exit(0);}        //Debug Line for Rapid Testing, implement as menu option in project 2
    stringstream a;                 //Exchange data from buffer into a number
    a<<*buff;
    a>>*buff2;
    if(*buff2<1 || *buff2>81){cout<<"Invalid Turn Length, Try Again"<<endl;}
    }

    short c = *buff2;               //Create variable to return once data is validated
    delete buff;
    delete buff2;
    return c;    
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
