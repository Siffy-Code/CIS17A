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
#include "BattleshipStructs.h"                                                  //Header file containing structures for Battleship
//Global Constants from Science/Engineering/Mathematics

//Function Prototypes
    //Output Formatting
void SUtxt1 (string);                                       //Setup Text for Player Instructions
void MenuOpt ();                                            //Displays menu options
void DisScre(vector<record> &);                             //Displays Scores
void ICoord (string *,int);                                 //outputs individual ship coordinates
void DisBrd (string [][9],int);                             //displays a board
void shptxt (int );                                         //Displays the text for a ship based on the size of the ship array
    //Pre&Post File Conversions and Datatype Transfers
void Bin2Brd(BrdSet &,int ,binXfer *);                      //Converts a binXfer binary receipt into a Board Set
binXfer *Shp2Bin (plyrSv);                                //Converts ship/points/turn/name data into a binXfer binary receipt to write save files
void Bin2Shp(plyrSv &,int ,binXfer *);                    //Converts a binXfer binary receipt into a set of ship/pts/turn/name data
binXfer *Brd2Bin (BrdSet,int);                              //Converts a boardset data into a binXfer binary receipt to write save files
string Cnvt (char);                                         //Converts a char to a string (handy dandy little function for adding chars)
    //Initialization Functions
void MBdFill (string [][9],int);                            //fills master board
void BBdFill (string [][9],int);                            //fills boards initially with tildes (waves!)
plyrSv NewGam(int,int,int,int,int,int&);                  //Creates basic game data using board fills and dynamic memory allocation
record *newscre (string,string,int,int);                    //Creates a new Player score record for text file output
    //Input Validation Functions
short turnVal ();                                           //Validates input is sufficient for possible number of turns
void IPVal (string &);                                      //Verifies input to be letter-number when necessary
    //Internal Formatting
void updscre (string ,string ,int ,int ,int,vector<record> &);              //Updates a players score if found during search
void FillShp (string *,int,string);                         //fills ships with nested data validation to ensure no ships go off the board
void UpdSBrd (string *,int,string [][9],int,string [][9]);  //updates ship boards
void UpdGBrd (string,string[][9],int,string [][9],bool);    //updates guess boards
void addDmg (shipDat *,int ,string );                       //adds damage to structured element to provide 'ship destroyed' notification text (not passed in Binary file save)
void AIShpSU (int ,shipDat *,BrdSet &,string &,int ,int ,string );          //Ship Setup procedures for playing against the computer
void Shoot (string ,string [][9],int ,string [][9],string [][9],short &);   //Checks a player's input to determine if their guess was a hit or miss
string AIShpDr (char ,int ,int );                           //Determines direction for ships when playing against the computer
    //File Operations
void LdSave (plyrSv &,fstream &,int);                     //Performs all actions necessary to update a freshly created plyrSv with saved data
void MakSave (plyrSv,fstream &,int);                      //Performs all actions necessary to send basic plyrSv data to restart game to binary file
binXfer *binRC (fstream &,int,string);                      //Reads data from a binary file and returns a binXfer receipt structure for conversion
void destroy (binXfer *,int);                               //Destroys nasty memory
void binWrt (binXfer *,fstream &,int,string);               //Writes data from a binXfer receipt into a binary file
void txtRd (vector<record> &,fstream &);                    //Reads text file score details
void txtWrt (vector<record> &,fstream &);                   //Writes text file score details
    //Procedural Portions of Game
void swtch(vector<record> &,fstream &,char,bool &);         //The Welcome Screen Menu (score operations and passthrough)
void pShpSU (int ,string [][9],string [][9],string &,int ,int ,string ,shipDat *);  //Player Ship Setup loop
void plyGam (string &,plyrSv &,string &,int,fstream &);   //Actual gameplay loop that really only requires the plyrSv data
void EGScr (plyrSv &,string ,vector<record> &,fstream &); //End of game operations to create or update player records
    //Other
void IOProof (fstream &);                                   //Proof for ios::in | ios::out simultaneous action
int main() {
    srand(static_cast<int>(time(0)));                           //Basic random number seed for AI ship setup and guesses
    
    //Declare Variables
            fstream file;               //File operations
            vector<record> Scrs;        //Score storage and display medium in-game.  Placed in text file otherwise
            char *Menu = new char;      //User Menu Select Option, Valid options are listed in MenuOpt, validation only allows single letters
            string  Win,                //Placeholder for winning player or tie determination
                    ValBuff;            //Value Buffer - universal input medium for most of the game
            int     maxSpc=0;           //Maximum number of possible spaces in the game taken up by one players ships (17 currently)
            bool ldSv=false;            //Flag for whether to load a save game or create a new game
        const static int    Z2=2,       //Sizes for arrays throughout game
                            Z3=3, 
                            Z4=4, 
                            Z5=5, 
                            Z9=9; 
    plyrSv gamDat = NewGam(Z2,Z3,Z4,Z5,Z9,maxSpc);    //Create a set of untouched boards and dynamic memory for ships
    
    //Welcome Screen
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~~Welcome to Battleship!~~~~~~~~~~~~~~"<<endl;
    cout<<"Play against an opponent or AI for up to 81 rounds"<<endl;
    cout<<"~~~~~~~~~~~~~~~Highest Score wins!~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    //Menu Select
    while (*Menu!='N' && *Menu!='L' && *Menu!='?')        //Only New Game and Load leave the menu
    {
    string *buff = new string;
    MenuOpt();                              //Display Menu Options
    getline(cin,*buff);                     //Receive user's input into a string
    strcpy(Menu,buff->substr(0,1).c_str()); //Copy the first letter of that user's string to a char in Menu
    swtch(Scrs,file,*Menu,ldSv);            //Send Menu Selection and blank vector into menu function
    delete buff;                            //Clean up nasty memory
    }if(*Menu=='?'){gamDat.P1Name="Skip";}  //Debug Mode
    delete Menu;
    //--------------------------------------------------------------------------
    //Player Set-Up
    if(!ldSv)                               //If player is not loading a game, conduct walkthrough prompts
    {
    if(gamDat.P1Name!="Skip")               //Debug mode or "Invincible" mode
    {
    cout<<"Type a name for Player 1"<<endl;
    getline (cin,gamDat.P1Name); 
    cout<<"Type a name for Player 2"<<endl;
    cout<<"To play against the computer, type AI"<<endl;
    getline (cin,gamDat.P2Name);
    cout<<endl;
    }else{gamDat.P2Name="AI";cout<<"IO File Proof - Check GradeMe.txt for new line.  First Line of file is:";(IOProof(file));cout<<endl;}
    //Player 1 Set Up
    if (gamDat.P2Name!="AI") 
    {
    SUtxt1(gamDat.P2Name);                  //Output Formatting
    }
    if (gamDat.P1Name!="Skip")              //Skip player setup during Debug mode - player has no valid ships the AI can guess against
    {
    pShpSU(gamDat.ShpDZ,gamDat.BrdDat.B1S,gamDat.BrdDat.MB,ValBuff,maxSpc,Z9,gamDat.P1Name,gamDat.P1Ships); //Runs ship setup loop for one player
    cout<<"Your Ship Locations"<<endl;
    DisBrd(gamDat.BrdDat.B1S,Z9);  
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"Shrink the Window to below this line to hide your ships!"<<endl;
    }
    //Player 2 Set Up
    if (gamDat.P2Name!="AI") //Bypassed by AI player
    {
    SUtxt1(gamDat.P1Name); 
    pShpSU(gamDat.ShpDZ,gamDat.BrdDat.B2S,gamDat.BrdDat.MB,ValBuff,maxSpc,Z9,gamDat.P2Name,gamDat.P2Ships); //Runs ship setup loop for one player
    cout<<"Your Ship Locations"<<endl;
    DisBrd(gamDat.BrdDat.B2S,Z9);  
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"Shrink the Window to below this line to hide your ships!"<<endl;
    cin.ignore();   //Stops the spilling from player 2 inputting ships before the turn number
    }else{AIShpSU(maxSpc,gamDat.P2Ships,gamDat.BrdDat,ValBuff,gamDat.ShpDZ,Z9,gamDat.P1Name);}  //If not human, run AI ship setup
    
    //---------------------------------------------------------------------
    
    //Transition to Gameplay prompt to put space between player 2's final board
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    cout<<"- All ships were set up correctly.  Commence! -"<<endl;
    cout<<"- - - - - - - - - - - - - - - - - - - - - - - -"<<endl;
    cout<<endl;
    cout<<"Ready, Steady, Go!"<<endl;
    //End Transition to Gameplay
    gamDat.turn=1;              //Ensure turns start at 1 and initialize basic values
    gamDat.P1Pts=0;
    gamDat.P2Pts=0;
    gamDat.tMax=0;
    cout<<"Input number of Turns to play"<<endl;
    cout<<"Game will End after final turn or when all Ships are Destroyed!"<<endl;
    gamDat.tMax=turnVal();  //player inputs turns for game with data validation function
    MakSave(gamDat,file,Z9);        //Create Backup Save File
    }else{LdSave(gamDat,file,Z9);}  //Load Save if Menu Option is Selected
    //----------------------------------------------------------------------
    bool *val = new bool;           //For those who want to try and break the game
    *val=true;
    while(*val)                     //Loop if players points add up to 0
    {
    Win="null";                         //Force loop to run inside gameplay function
    plyGam(Win,gamDat,ValBuff,Z9,file); //Actual gameplay function
    if((gamDat.P1Pts+gamDat.P2Pts)!=0){*val=false;} //You can't end a game with 0 points
    }
    delete val;
    cout<<"x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl;
    cout<<endl;
    cout<<"GAME OVER"<<endl;
    cout<<gamDat.P1Name<<" has "<<gamDat.P1Pts<<" Points"<<endl;
    cout<<gamDat.P2Name<<" has "<<gamDat.P2Pts<<" Points"<<endl;
    cout<<Win<<" wins!"<<endl;
    EGScr(gamDat,Win,Scrs,file);    //write score to plan text file based on winner and existing scores
    return 0;                       //Close the game!
}
void IPVal (string &ValBuff)
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
void FillShp (string a[],int SIZE, string user)
{
    string Letter;      //String Buffer
    char* Buff, act;    //String to Char conversion assistants
    int Num;    //Number Buffer
    bool Flip;  //Gate for input validation
    Flip=true;
    Letter=a[0].substr(0,1);                //extract letter from guess
    stringstream NumBuff(a[0].substr(1,1)); //extract number from guess
    NumBuff>>Num;                           //fill Number buffer
    
    while (Flip)
    {
    if (user.compare("R")==0 || user.compare("r")==0 ||user.compare("L")==0 ||user.compare("l")==0 ||user.compare("U")==0 ||user.compare("u")==0 ||user.compare("D")==0 ||user.compare("d")==0 )
    {Flip=false;    } //Ensures data is a valid selection
    else {cout<<"Invalid Input Please use |L|  |R|  |U|  |D|"<<endl;cin>>user;}
        //Ship Orientation Specifics
    if(user=="R" || user=="r") 
    {
            if(Letter=="I"){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="H"&&SIZE>2){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="G"&&SIZE>3){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="F"&&SIZE>4){cout<<"Your Selection goes Off the Board!  Please Use |L|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
        else
        {
        for (int i=1 ; i<SIZE ; i++)
            {
           Buff=const_cast<char*>(Letter.c_str()); //Allows Buff to embody pointer to Letter String
           act=*Buff; //Converts the Char* pointer to an actual variable 
           act++;
          Letter=act;
          a[i]=(Letter+to_string(Num));
            }
        }
    }//End Right
    else if (user=="U" || user=="u")
    {
            if(Num==1){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Num==2&&SIZE>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Num==3&&SIZE>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Num==4&&SIZE>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |D|"<<endl;Flip=true; cin>>user; }
      else
      {  
        for (int i=1 ; i<SIZE ; i++)
        {
        Num--;
        a[i]=(Letter+to_string(Num));
        }
      }
    }//End Up
    else if (user=="L" || user=="l")
    {
            if(Letter=="A"){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="B"&&SIZE>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="C"&&SIZE>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
            else if(Letter=="D"&&SIZE>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |U|, or |D|"<<endl;Flip=true; cin>>user; }
      else
      {
        for (int i=1 ; i<SIZE ; i++)
        {
        Buff=const_cast<char*>(Letter.c_str());
        act=*Buff;
        act--;
        Letter=act;
        a[i]=(Letter+to_string(Num));
        }
      }
    }//End Left
    else if (user=="D" || user=="d")
    {
        if(Num==10){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;Flip=true; cin>>user; }
            else if(Num==9&&SIZE>2){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;Flip=true; cin>>user; }
            else if(Num==8&&SIZE>3){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;Flip=true; cin>>user; }
            else if(Num==7&&SIZE>4){cout<<"Your Selection goes Off the Board!  Please Use |R|, |L|, or |U|"<<endl;Flip=true; cin>>user; }
      else
      {
        for (int i=1 ; i<SIZE ; i++)
        {
        Num++;
        a[i]=(Letter+to_string(Num));
        }  
      }
    }//end Down
    else {cout<<"You are trying to enter a Grid Square instead of a Direction"<<endl;
    cout<<"Use |L|  |R|  |U|  |D|"<<endl;}
    }//end While Loop
}
void ICoord (string *a,int SIZE)
{//outputs individual ship coordinates
    cout<<"| ";
    for (int i=0 ; i<SIZE ; i++)
    {
        cout<<a[i]<<" | ";
    }
    cout<<endl;
}
void UpdSBrd (string *a,int aSIZE,string b[][9],int bSIZE,string m[][9]) //updates ship boards
{
    for(int i=0 ; i<aSIZE ; i++)
    {
    for(int q=0 ; q<bSIZE; q++)
    {
        for(int w=0 ; w<bSIZE; w++)
        {
            if(a[i]==m[w][q])
            {
                b[w][q]="||";
            }
        }
    }
    }
}
void UpdGBrd (string user,string b[][9],int bSIZE,string m[][9],bool hit) //updates guess boards
{
    for(int i=0 ; i<bSIZE ; i++)
    {
        for(int q=0 ; q<bSIZE; q++)
        {
            if(m[i][q]==user)
            {
                if(hit==true)
                {b[i][q]="XX";}
                else if(b[i][q]!="XX")
                { b[i][q]="OO";}
            }
        }
    }
}
void MBdFill (string b[][9],int SIZE)
{//Fills Master Board with Grid Locations
    string Ltr="A";     //grid starts with this letter
    char act;
    char *Buff = new char;
    int Num=1;
    for(int q=0 ; q<SIZE; q++)
    {    
        for(int w=0 ; w<SIZE; w++)
        {
            b[w][q]=(Ltr+to_string(Num));
            Buff=const_cast<char*>(Ltr.c_str()); //Allows Buff to embody pointer to Letter String
            act=*Buff; //Converts the Char* pointer to an actual variable 
            act++; //Adds one to Char, sending it down alphabetically
            Ltr=act;
        }
        Num++;      //next row numbers
        Ltr="A"; //reset columns for next row
    }
    delete Buff;
}
void DisBrd (string b[][9],int SIZE)
{//Displays any board with nice formatting
    cout<<"    A  B  C  D  E  F  G  H  I"<<endl;
    cout<<"    -------------------------"<<endl;
    for(int q=0 ; q<SIZE; q++)
    {
        cout<<q+1<<" | ";
        for(int w=0 ; w<SIZE; w++)
        {cout<<b[w][q]<<" ";}
        cout<<endl;
    }
    cout<<"    -------------------------"<<endl;
}
void BBdFill (string b[][9],int bSIZE)
{//Fills a player board with waves - it's the ocean!
    for(int q=0 ; q<bSIZE; q++)
    {
        for(int w=0 ; w<bSIZE; w++)
        {
          b[w][q]="~~"; //Ride on those waves!
        }
    }
}
void Shoot (string user,string b[][9],int bSIZE,string m[][9],string g[][9],short &pts)
{
    bool hit; //input for updating guess boards with X's or O's
    for(int i=0 ; i<bSIZE ; i++)
    {
    for(int q=0 ; q<bSIZE; q++)
    {
        if(m[i][q]==user)
        {
            if(b[i][q]=="||")
            {
                b[i][q]="XX";
                pts++;
                hit=true;
                cout<<"++++++"<<endl;
                cout<<"+Hit!+"<<endl;
                cout<<"++++++"<<endl;
            }
            else
            {   
                cout<<"-------"<<endl;
                cout<<"-Miss!-"<<endl;
                cout<<"-------"<<endl;
                hit=false;
            }
        }
    }
    }
    UpdGBrd(user,g,bSIZE,m,hit); //update guess board for player
}
void DisScre(vector<record> &Scrs)  //Displays Vector contents
{   cout<<"--------Player Scores---------------------------------------------"<<endl;
    cout<<"Name"<<"\t"<<"\t"<<"W/L"<<"\t"<<"Pts"<<"\t"<<"Turns"<<"\t"<<"Games"<<endl;
            for(int h=0;h<(Scrs.size());h++)
            {
                cout<<Scrs[h].Name<<"\t";
                if(Scrs[h].Name.length()<8){cout<<"\t";}
                cout<<Scrs[h].Vs<<"\t"<<Scrs[h].Ps<<"\t"<<Scrs[h].Ts<<"\t"<<Scrs[h].Gs<<endl;
            }cout<<"------------------------------------------------------------------"<<endl;
}
string Cnvt (char rec)
{   string Buff;
    Buff=rec;
    return Buff;
}
record *newscre (string name,string Win,int Pts,int Len)
{
    record *temp=new record;
    if(name==Win)
    {   
          //create winner record
            (*temp).Name=Win;
            (*temp).Vs=1;
            (*temp).Ps=Pts;
            (*temp).Ts=Len;
            (*temp).Gs=1;
    }
    else
    {
          //create loser or tie record
            (*temp).Name=name;
            (*temp).Vs=0;
            (*temp).Ps=Pts;
            (*temp).Ts=Len;
            (*temp).Gs=1;
    }
    return temp;
}
void updscre (string name,string Win,int Pts,int Len,int e,vector<record> &temp)
{
    if(name==Win)
    {   
          //update winner record
            temp[e].Vs++;
            temp[e].Ps+=Pts;
            temp[e].Ts+=Len;
            temp[e].Gs++;
    }
    else 
    {
          //update loser or tie record
            temp[e].Ps+=Pts;
            temp[e].Ts+=Len;
            temp[e].Gs++;
    }
}
void shptxt (int x)
{
    enum ShpTyp {DESTROYER,CRUISER,SUBMARINE,BATTLECRUISER,CARRIER};
    if(x==DESTROYER){         cout<<"-=DESTROYER     -   TWO SPACES=-"<<endl;}
    else if(x==CRUISER){      cout<<"-=CRUISER       - THREE SPACES=-"<<endl;}
    else if(x==SUBMARINE){    cout<<"-=SUBMARINE     - THREE SPACES=-"<<endl;}
    else if(x==BATTLECRUISER){cout<<"-=BATTLECRUISER -  FOUR SPACES=-"<<endl;}
    else if(x==CARRIER){      cout<<"-=CARRIER       -  FIVE SPACES=-"<<endl;}
    }

string AIShpDr (char AIL,int AIN,int ShpZ)
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
void pShpSU (int ShpDZ,string BS[][9],string MB[][9],string &ValBuff,int maxSpc,int Z9,string P1Name,shipDat *P1Ships)
{
    cout<<"Let's set up your ships, "<<P1Name<<"!"<<endl;
    string *valLst = new string[maxSpc];            //Buffer to hold all spaces occupied by players' ships while setting up
    int lstCnt = 0;                                 //Counter for buffer array
    bool bad;                                       //Flag for clipping
    bad=false;
    
    for(int a=0;a<ShpDZ;a++)                        //Loop for size of total number of ships per player
    {
        cout<<endl;
        cout<<endl;
        DisBrd(BS,Z9);  
        cout<<"-=Ship "<<(a+1)<<" of "<<ShpDZ<<"=-"<<endl;
        cout<<"Input a Grid Square to initialize Ship Placement"<<endl;
        shptxt(a);
        cout<<"Use one Capital Letter from A-I followed by one Number 1-9"<<endl;
        cout<<"(Examples: A1, B6, I8, G9)"<<endl;
        cin>>ValBuff;
        IPVal (ValBuff);                        //Validation Function to Loop Player Input until within [A1,I9]
        for(int c=0;c<maxSpc;c++)               //Validate player selection against existing ships placed
        {
            if(ValBuff==valLst[c]){
                cout<<"##################### ERROR ######################"<<endl;
                cout<<"Selection Overlaps Existing Ship, Please try again"<<endl;
                cout<<"##################### ERROR ######################"<<endl;
                c=maxSpc;bad=true;}             //Error Text, loop quit, flag notification
        }

        if(!bad){P1Ships[a].spcs[0]=ValBuff;}   //Set initial value of Array to Player Input
        ValBuff="0";
        if(!bad)
        {
            cout<<"Set up direction starting at: "<<P1Ships[a].spcs[0]<<endl;
            shptxt(a);
            cout<<"Type |L| for Left, |R| for Right, |U| for Up, and |D| for down"<<endl;
            cin>>ValBuff;

            FillShp(P1Ships[a].spcs,P1Ships[a].size,ValBuff);   //Sends player to Fill Ship function, data validation nested
            for(int h=0;h<P1Ships[a].size;h++)                  //Loop to load space buffer with proposed ship spaces
                {
                    valLst[lstCnt]=P1Ships[a].spcs[h];
                    lstCnt++;
                }
            for(int w=0;w<lstCnt;w++)                           //Loop to check if Fill Ship was valid or if it needs to be re-run
                {
                for(int c=0;c<lstCnt;c++)                       //Inner loop of search procedures
                    {
                    if(w!=c){                                   //As long as it is not counting itself,
                    if(valLst[c]==valLst[w]){                   //check if space already exists
                        cout<<"##################### ERROR ######################"<<endl;
                        cout<<"Ships Overlap - Please select again"<<endl;
                        cout<<"##################### ERROR ######################"<<endl;
                        c=lstCnt;w=lstCnt;bad=true;lstCnt-=P1Ships[a].size;}//Error Text, loop quit, flag notification, reset counter for buffer array
                        }
                    }
                }
            if(!bad){
            cout<<"Your Ship's Coordinates Are:"<<endl;
            ICoord(P1Ships[a].spcs,P1Ships[a].size);            //Outputs individual ship coordinates
            UpdSBrd(P1Ships[a].spcs,P1Ships[a].size,BS,Z9,MB);  //Updates Ship Board for validation
                    }
        }
        if(bad){a--;}                                           //Repeat loop if flag is hit
        bad=false;                                              //Reset flag for next loop
    }
    delete[] valLst;                                            //Clean up nasty memory
}
void AIShpSU (int maxSpc,shipDat *P2Ships,BrdSet &BrdDat,string &ValBuff,int ShpDZ,int Z9,string P1Name)
{
    char AIL;
    int AIN;
    string *valLst = new string[maxSpc];                        //Buffer for AI ship selection values to verify against
        int lstCnt = 0;
        bool bad;
        bad=false;
        for(int f=0;f<ShpDZ;f++)                                //Similar loop logic for players but separated so it can be adjusted for
        {                                                       //better functionality and precision
        AIL=(rand()%9+1+64);    //set random Char for column guess A-I A=65?
        AIN=(rand()%9+1);       //set random Number for Row guess 1-9 
            for(int c=0;c<maxSpc;c++)                                           //Run for number of ship sizes
            {
            if(((Cnvt(AIL))+to_string(AIN))==valLst[c]){c=maxSpc;bad=true;}                     //Ships overlap during AI setup, run again
            }
            P2Ships[f].spcs[0]=(Cnvt(AIL))+to_string(AIN); //combine Column/Row for input
            ValBuff=AIShpDr(AIL,AIN,P2Ships[f].size);
            FillShp(P2Ships[f].spcs,P2Ships[f].size,ValBuff);
            for(int h=0;h<P2Ships[f].size;h++)
                {
                valLst[lstCnt]=P2Ships[f].spcs[h];                                                  
                lstCnt++;
                }
            for(int w=0;w<lstCnt;w++)
            {
                for(int c=0;c<lstCnt;c++)
                {
                    if(w!=c){
                    if(valLst[c]==valLst[w]){c=lstCnt;w=lstCnt;bad=true;lstCnt-=P2Ships[f].size;}   //Ships overlap during AI setup, run again
                    }
                }
            }
            if(!bad){UpdSBrd(P2Ships[f].spcs,P2Ships[f].size,BrdDat.B2S,Z9,BrdDat.MB);} //If valid, update ship board
            AIL=0; AIN=0; //Reset Buffers for next ship
            if(bad){f--;}                       //If bad, retract counter and collect data again
            bad=false;                          //Reset flag
        }
        delete[] valLst;
        if(P1Name=="Skip")
        {
        cout<<"AI Ship Setup Has Run"<<endl;                                //DEBUG LINES
        }
        if(P1Name=="Skip")
        {
        DisBrd(BrdDat.B2S,Z9);                                              //Shows AI Ship board to player after set up during debug mode
        for(int q=0;q<ShpDZ;q++){ICoord(P2Ships[q].spcs,P2Ships[q].size);}  //DEBUG LINES
        }
}
void swtch (vector<record> &Scrs,fstream &file,char Menu,bool &ld)
{
    switch (Menu)
    { //Start Switch (Menu) Box
case 'N':   {ld=false;break;} //Passes through
case 'L':   {ld=true;break;} //Loads a new game from a binary file based on a string
case 'S':   {//High Score Display
            txtRd(Scrs,file);
            DisScre(Scrs);
            cout<<endl;
            Scrs={};
break;}
case 'R':   {//Reset Score
            Scrs={};
            txtWrt(Scrs,file);
break;}
case 'X': {cout<<"Goodbye!"<<endl;exit(0); break;}
case 'A':   { //Sort Scores Alphabetically (Selection Sort)
            Scrs={};
            txtRd(Scrs,file);
            record *BF = new record;
            for(int i=0 ; i<Scrs.size() ; i++)
            {
                for(int n=i+1 ; n<Scrs.size() ; n++)
                {
                    if(Scrs[i].Name>Scrs[n].Name)
                    {
                        *BF=Scrs[i];
                        Scrs[i]=Scrs[n];
                        Scrs[n]=*BF;
                        *BF={};
                    }
                }
            }
            cout<<endl;
            txtWrt(Scrs,file);
            Scrs={};       
            delete BF;
break;}
case 'H':   {//Sort Scores by High Score (Bubble Sort)
            Scrs={};
            txtRd(Scrs,file);
            record *BF = new record;
            for(int i=0 ; i<Scrs.size()-1 ; i++)
            {
                for(int n=0 ; n<Scrs.size()-i-1 ; n++)
                {
                    if(Scrs[n].Ps<Scrs[n+1].Ps)
                    {
                        *BF=Scrs[n];
                        Scrs[n]=Scrs[n+1];
                        Scrs[n+1]=*BF;
                        *BF={};
                    }
                }
            }
            cout<<endl;
            txtWrt(Scrs,file);
            Scrs={};  
            delete BF;
break;}       
case 'F':   {//Search Scores using Linear Search
            string *Srch = new string;
            cout<<"Please type the desired name"<<endl;
            cin>>*Srch;
            Scrs={};
            txtRd(Scrs,file);
                for(int h=0;h<Scrs.size();h++)
                {
                    if (Scrs[h].Name==*Srch)
                    {
                    cout<<"------------PLAYER RECORD------------"<<endl;
                    cout<<"Name"<<"\t"<<"\t"<<"W/L"<<"\t"<<"Pts"<<"\t"<<"Turns"<<"\t"<<"Games"<<endl;
                    cout<<Scrs[h].Name<<"\t";
                    if(Scrs[h].Name.length()<8){cout<<"\t";}
                    cout<<Scrs[h].Vs<<"\t"<<Scrs[h].Ps<<"\t"<<Scrs[h].Ts<<"\t"<<Scrs[h].Gs<<endl;
                    cout<<"-------------------------------------"<<endl;
                    h=Scrs.size();
                    }
                    else if(h==(Scrs.size()-1)){cout<<"-----NO RECORD FOUND-----"<<endl;}
                }
            cout<<endl;
            txtWrt(Scrs,file);
            Scrs={};       
            delete Srch;
            cin.ignore();
break;}
        case '?':{break;}   //Debug Mode
    }//End Switch (Menu) Box 
    if(Menu!='N' && Menu!='L' && Menu!='S' && Menu!='R' && Menu!='A' && Menu!='H' && Menu!='F' && Menu!='?')
    {
        cout<<"######################################################"<<endl;
        cout<<"Invalid selection - check your CAPS LOCK and try again"<<endl;
        cout<<"It is recommended to play this game with CAPS LOCK on"<<endl;
        cout<<"========CAPS LOCK IS CRUISE CONTROL FOR COOL========="<<endl;
        cout<<"######################################################"<<endl;
        cout<<endl;
    } 
}
void plyGam (string &Win,plyrSv &gamDat,string &ValBuff,int Z9,fstream &file)               //Plays a game of Battleship with a loaded plyrSv
{
    int *cnt = new int;
    *cnt=0;
    string *noregus = new string[gamDat.tMax];              //Creates an array to ensure AI doesn't re-guess (NO RE-GUESS, sounds like "no Regus", kinda funny)
    if(gamDat.P2Name!="AI"){delete[] noregus;delete cnt;}   //Cleans up memory immediately if non-AI player.
    string guess;
    while (Win=="null") //Run forced while loop until winner is declared
    {    
            for (; gamDat.turn<=gamDat.tMax; )  //Due to save/load features, now relies on minimal data.  Counter increments at bottom before game saves
            {
                //Begin New Turn Transition Text
                cout<<"           ----------"<<endl;
                cout<<"          | Turn #"<<gamDat.turn<<"/"<<gamDat.tMax<<" |"<<endl;
                cout<<"           ----------"<<endl;
                cout<<"          -="<<gamDat.P1Name<<"'s turn!=-"<<endl;
                guess="0"; //Reset guess value
                cout<<endl;
                cout<<"Here is your Guess Board, "<<gamDat.P1Name<<"!"<<endl;
                cout<<endl;
                DisBrd(gamDat.BrdDat.B1G,Z9);
                cout<<"You have "<<gamDat.P1Pts<<" Points"<<endl;
                cout<<endl;
                cout<<gamDat.P1Name<<"; choose a Grid Square!"<<endl;
                cin>>ValBuff; //Receive player input into Buffer, do not declare guess until validated
                IPVal (ValBuff); //Validation Function to Loop Player Input until within [A1,I9]
                guess=ValBuff; //Release Validation buffer to guess 
                ValBuff="0";
                Shoot(guess,gamDat.BrdDat.B2S,Z9,gamDat.BrdDat.MB,gamDat.BrdDat.B1G,gamDat.P1Pts);
                cout<<endl;
                addDmg(gamDat.P2Ships,gamDat.ShpDZ,guess);
                if(gamDat.P1Pts>=17) //Are all Player 2 Ships off the board?
                {Win=gamDat.P1Name; gamDat.turn=gamDat.tMax;} //Set turns to max here to ensure game ends correctly, Declare Winner
                else //Endgame Check Fails, Run Player 2 Turn
                {
                        if (gamDat.P2Name!="AI")                    //Human player 2 turn
                        {  
                        cout<<"-----------------"<<endl;    
                        cout<<gamDat.P2Name<<"'s turn!"<<endl;
                        guess="0";       
                        cout<<endl;
                        cout<<"Here is your Guess Board, "<<gamDat.P2Name<<"!"<<endl;
                        cout<<endl;
                        DisBrd(gamDat.BrdDat.B2G,Z9);
                        cout<<"You have "<<gamDat.P2Pts<<" Points"<<endl;
                        cout<<endl;
                        cout<<gamDat.P2Name<<"; choose a Grid Square!"<<endl;
                        cin>>ValBuff; //Receive player input into Buffer, do not declare guess until validated
                        IPVal (ValBuff); //Validation Function to Loop Player Input until within [A1,I9]
                        } 
                        else                                        //AI Turn
                        { 
                            char *AIL = new char;
                            int *AIN = new int;
                            bool *regus = new bool;
                            *regus=true;
                            *AIL=0;*AIN=0; //Reset Buffers for next ship
                                while(*regus)
                                {
                                *AIL=(rand()%9+1+64); //set random Char for column guess A-I A=65?
                                *AIN=(rand()%9+1);   //set random Number for Row guess 1-9
                                for(int u=0;u<=*cnt;u++)
                                {
                                if(((Cnvt(*AIL))+to_string(*AIN))==noregus[u]){*regus=true;u=*cnt;} //Ensures the computer does not guess the same thing twice
                                else if(u==*cnt){*regus=false;}
                                }    
                                }
                            ValBuff=(*AIL)+to_string(*AIN); //concatenate string for guess
                            cout<<"---------------------------"<<endl;
                            cout<<"The Computer has guessed "<<ValBuff<<endl;
                            cout<<"---------------------------"<<endl;
                            noregus[*cnt]=guess;*cnt+=1;
                            delete AIL;delete AIN;delete regus;
                        } //End AI Turn
                        guess=ValBuff; //Transfer buffer to actual guess
                        ValBuff="0"; //Clear buffer
                        Shoot(guess,gamDat.BrdDat.B1S,Z9,gamDat.BrdDat.MB,gamDat.BrdDat.B2G,gamDat.P2Pts);
                        addDmg(gamDat.P1Ships,gamDat.ShpDZ,guess);
                        gamDat.turn++;                          //Increment turn counter after valid guess, before save initiated
                        if(gamDat.P2Pts>=17)                    //Are all Player 2 Ships off the board?
                        {Win=gamDat.P2Name; gamDat.turn=gamDat.tMax;}  //Set turns to max here to ensure game ends correctly, Declare Winner
                        else{MakSave(gamDat,file,Z9);}          //If game will continue, send data to save file
                }
                cout<<"---==Turn End==---"<<endl;
                cout<<gamDat.P1Name<<" Points: "<<gamDat.P1Pts<<endl;
                cout<<gamDat.P2Name<<" Points: "<<gamDat.P2Pts<<endl;
                cout<<"------------------"<<endl;
            }//End Turn Loop
    if (gamDat.P1Pts<gamDat.P2Pts){Win=gamDat.P2Name;}
    else if (gamDat.P1Pts==gamDat.P2Pts){Win="Nobody";}
    else {Win=gamDat.P1Name;} 
    }
    if(gamDat.P2Name=="AI"){delete[] noregus;delete cnt;}       //Cleans up memory for re-guess if player was AI at end of game
}
void EGScr (plyrSv &gamDat,string Win,vector<record> &Scrs,fstream &file)     //Performs Score Writing Tasks at End of Game
{
    short WinPts,LosePts;               //Placeholders to allow for single function to write scores
    bool *wrote = new bool;             //Did I write this score? flag
    *wrote=false;
    string *buff = new string;          //Buffer for instances where player name is not necessarily Win
    Scrs={};                            //Default Scores Vector
    txtRd(Scrs,file);                   //Acquire existing scores file
    if(Scrs.size()<1)                   //If no records exist, create new records
        {
            record *P1 = new record;  //create P1 record
            P1=newscre(gamDat.P1Name,Win,gamDat.P1Pts,gamDat.turn);
            Scrs.push_back(*P1);
            delete P1;    
            record *P2 = new record;  //create P2 record
            P2=newscre(gamDat.P2Name,Win,gamDat.P2Pts,gamDat.turn);   
            Scrs.push_back(*P2);
            delete P2;
        }   
    else if(Win!="Nobody")              //Records exist and it was not a tie
    {
        if(gamDat.P1Name==Win) //Set Winner/Loser points
        {WinPts=gamDat.P1Pts; LosePts=gamDat.P2Pts;}
        else{WinPts=gamDat.P2Pts;LosePts=gamDat.P1Pts;}
        
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==Win)
            {
                updscre(Win,Win,WinPts,gamDat.turn,e,Scrs);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=Win && *wrote!=true)
            {
            record *Vctr = new record;  //create winner record
            Vctr=newscre(Win,Win,WinPts,gamDat.turn);
            Scrs.push_back(*Vctr);
            delete Vctr;
            *wrote=true;
            }
            if(*wrote){e=Scrs.size();}
        }        
        *wrote=false;
        if(Win==gamDat.P1Name){*buff=gamDat.P2Name;}
        else {*buff=gamDat.P1Name;}         //Determine buffer identity for loser
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,LosePts,gamDat.turn,e,Scrs);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Lsr = new record;  //create loser record
                Lsr=newscre(*buff,Win,LosePts,gamDat.turn);   
                Scrs.push_back(*Lsr);
                *wrote=true;
                delete Lsr;
            }
            if(*wrote){e=Scrs.size();}
        }        
    }
    else if(Win=="Nobody")                  //Records exist and it IS a tie
    {
        *buff=gamDat.P1Name;
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,gamDat.P1Pts,gamDat.turn,e,Scrs);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Tie = new record;  
                Tie=newscre(*buff,Win,gamDat.P1Pts,gamDat.turn);   
                Scrs.push_back(*Tie);
                *wrote=true;
                delete Tie;
            }
        }
        *wrote=false;
        *buff=gamDat.P2Name;
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,gamDat.P2Pts,gamDat.turn,e,Scrs);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Tie = new record;  
                Tie=newscre(*buff,Win,gamDat.P2Pts,gamDat.turn);   
                Scrs.push_back(*Tie);
                *wrote=true;
                delete Tie;
            }
        }
        
    }
    txtWrt(Scrs,file);      //Replace scores in file
    Scrs={};                //Reset Vector       
    txtRd(Scrs,file);       //Re-read scores for display purposes
    DisScre(Scrs);          //display scores after game
    delete buff; 
    delete wrote;
}
plyrSv NewGam(int Z2,int Z3,int Z4,int Z5,int Z9,int &maxSpc)
{
            plyrSv gamDat;
            gamDat.ShpDZ = 5;                           //Number of ships per player determined here
            gamDat.P2Ships = new shipDat[gamDat.ShpDZ];
            gamDat.P1Ships = new shipDat[gamDat.ShpDZ];
            gamDat.P1Ships[0].size = Z2;
            gamDat.P1Ships[1].size = Z3;
            gamDat.P1Ships[2].size = Z3;
            gamDat.P1Ships[3].size = Z4;
            gamDat.P1Ships[4].size = Z5;
            for(int r=0;r<gamDat.ShpDZ;r++){maxSpc+=gamDat.P1Ships[r].size;}
            gamDat.P2Ships[0].size = Z2;
            gamDat.P2Ships[1].size = Z3;
            gamDat.P2Ships[2].size = Z3;
            gamDat.P2Ships[3].size = Z4;
            gamDat.P2Ships[4].size = Z5;

            for(int s=0;s<gamDat.ShpDZ;s++) //Initialize Ships Loop
            {
            gamDat.P1Ships[s].spcs = new string[gamDat.P1Ships[s].size];
            gamDat.P2Ships[s].spcs = new string[gamDat.P2Ships[s].size];
                for(int Q=0;Q<gamDat.P1Ships[s].size;Q++)   //Set all ships to XX as initial spaces
                {
                gamDat.P1Ships[s].spcs[Q] = "XX";
                gamDat.P2Ships[s].spcs[Q] = "XX";
                }
            gamDat.P2Ships[s].dmg = 0;
            gamDat.P1Ships[s].dmg = 0;
            }
            
            
    //Initialize Boards
    MBdFill(gamDat.BrdDat.MB,Z9);
    BBdFill(gamDat.BrdDat.B1S,Z9);
    BBdFill(gamDat.BrdDat.B2S,Z9);
    BBdFill(gamDat.BrdDat.B1G,Z9);
    BBdFill(gamDat.BrdDat.B2G,Z9);    
    
    return gamDat;                  //Send basically loaded game data back to main
}
void MenuOpt ()
{   
    cout<<"Please select from the following options:"<<endl;
    cout<<"     - - - - - - - - - - - - - - - -"<<endl;
    cout<<"    | N: Start New Game             |"<<endl;
    cout<<"    | L: Load Existing Game         |"<<endl;
    cout<<"    | S: Check Scores               |"<<endl;
    cout<<"    | R: Reset Scores               |"<<endl;
    cout<<"    | A: Sort Scores Alphabetically |"<<endl;
    cout<<"    | H: Sort Scores by High Score  |"<<endl;
    cout<<"    | F: Search Scores by Name      |"<<endl;
    cout<<"    | X: Exit                       |"<<endl;
    cout<<"    |                               |"<<endl;
    cout<<"    | ?:DebugMode+In/Out File Proof |"<<endl;
    cout<<"     - - - - - - - - - - - - - - - -"<<endl;
}
void SUtxt1 (string PName)
{
    cout<<"********************************************************"<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"*****Tell "<<PName<<" to look away!****"<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"********************************************************"<<endl;
}
void addDmg (shipDat *PShips,int ShpDZ,string guess)
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
short turnVal ()
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
void destroy (binXfer *mana,int Z9,char dType)
{
    int Zmod = 0;
    if(dType=='B'){Zmod=Z9*4;}  //Determine size of binXfer to create based on file name
    else if(dType=='S' || dType=='C'){Zmod=(Z9+6);}
    if(dType!='C')              //If array is generally sized for reading, or is perfectly sized like board xfers
    {
    for(int y=0;y<Zmod;y++)
    {
    delete[] mana[y].ltr;
    delete[] mana[y].num;
    }
    }  
    else                        //Particularly generated size for making save files; deletes elements exactly as created
    {
        for(int y=0;y<=Z9;y++)
        {
        delete[] mana[y].ltr;
        delete[] mana[y].num;
        }
        for(int y=(Z9+1);y<=Z9+4;y++)
        {
            delete[] mana[y].num;
        }
        for(int y=(Z9+5);y<=Z9+6;y++)
        {
            delete[] mana[y].ltr;
            delete[] mana[y].num;
        }
    }
}
void txtWrt (vector<record> &Scrs,fstream &file)
{
    file.open("Test1.txt",ios::in | ios::out);  
           for(int k=0;k<Scrs.size();k++)
           {
               file << Scrs[k].Name<<"\t"<<Scrs[k].Vs<<"\t"<<Scrs[k].Ps<<"\t"<<Scrs[k].Ts<<"\t"<<Scrs[k].Gs<<"\n"; //tab-delineated so it can be dropped in excel
            }

    file.close();
}
void txtRd (vector<record> &Scrs,fstream &file)
{
    file.open("Test1.txt", ios::in);  
                while(!file.eof())
                {
                    record Plyr;
                    if(file >> Plyr.Name >> Plyr.Vs >> Plyr.Ps >> Plyr.Ts >> Plyr.Gs)
                    {Scrs.push_back(Plyr);}
                    else{
                        file.clear();
                        file.ignore(100,'\n');
                    }
                }
            file.close();
}


//Binary File Operations
void Bin2Brd(BrdSet &BrdDat,int Z9,binXfer *mana)
{//Repeats process from Brd2Bin to decode the order of data
    int Xcnt=0;
    for(int p=0;p<Z9;p++)   
     {
        for(int q=0;q<Z9;q++)
        {
        Xcnt=p*4;           //Creates sequence 0/4/8/12/16....             
        char ltrB, numB;
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B1G[q][p]=(Cnvt(ltrB)+Cnvt(numB));
        Xcnt++;             //Creates sequence 1/5/9/13/17....
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B1S[q][p]=(Cnvt(ltrB)+Cnvt(numB));
        Xcnt++;             //Creates sequence 2/6/10/14/18...
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B2G[q][p]=(Cnvt(ltrB)+Cnvt(numB));
        Xcnt++;             //Creates sequence 3/7/11/15/19...
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B2S[q][p]=(Cnvt(ltrB)+Cnvt(numB));
        Xcnt++;
        }
     } 
}
void Bin2Shp(plyrSv &gamDat,int Z9,binXfer *shps)
{   //Retrieve key data points from binXfer structure
    gamDat.P1Pts=static_cast<short>(shps[(gamDat.ShpDZ*2)].num[0]);
    gamDat.P2Pts=static_cast<short>(shps[(gamDat.ShpDZ*2)+1].num[0]);
    gamDat.tMax=static_cast<short>(shps[(gamDat.ShpDZ*2)+2].num[0]);
    gamDat.turn=static_cast<short>(shps[(gamDat.ShpDZ*2)+3].num[0]);
    //Retrieve player names from binXfer structure
    for(int i=0;i<static_cast<short>(shps[(gamDat.ShpDZ*2)+4].num[0]);i++)
    {
        gamDat.P1Name+=shps[(gamDat.ShpDZ*2)+4].ltr[i];
    }
    for(int i=0;i<static_cast<short>(shps[(gamDat.ShpDZ*2)+5].num[0]);i++)
    {
        gamDat.P2Name+=shps[(gamDat.ShpDZ*2)+5].ltr[i];
    }
    //Retrieve ship spaces data from binXfer structure
    int Xcnt=0;
    for(int p=0;p<gamDat.ShpDZ;p++)
    {
        for(int q=0;q<gamDat.P1Ships[p].size;q++)
        {
            Xcnt=p;                 //Creates Sequence 0,1,2,3,4 for Player 1 Ships
            char ltrB, numB;            
            ltrB=shps[Xcnt].ltr[q];
            numB=shps[Xcnt].num[q];
            gamDat.P1Ships[p].spcs[q]=(Cnvt(ltrB)+Cnvt(numB));
            Xcnt+=gamDat.ShpDZ;      //Creates Sequence 5,6,7,8,9 for Player 2 Ships
            ltrB=shps[Xcnt].ltr[q];
            numB=shps[Xcnt].num[q];
            gamDat.P2Ships[p].spcs[q]=(Cnvt(ltrB)+Cnvt(numB));
        }
    }
}
binXfer *Shp2Bin (plyrSv gamDat)
{   //Create binXfer structure to hold Ship data
    binXfer *mana = new binXfer[(gamDat.ShpDZ*2)+6];
    //Holds Ships spaces
    for(int y=0;y<gamDat.ShpDZ;y++)
    {
    mana[y].ltr = new char[gamDat.P1Ships[y].size];
    mana[y].num = new char[gamDat.P1Ships[y].size];
    mana[y+gamDat.ShpDZ].ltr = new char[gamDat.P2Ships[y].size];
    mana[y+gamDat.ShpDZ].num = new char[gamDat.P2Ships[y].size];
    }
    //Holds Points, turns, player names, player name sizes
    for(int y=(gamDat.ShpDZ*2);y<(gamDat.ShpDZ*2)+4;y++)
    {
    mana[y].num = new char[1];
    }
    mana[(gamDat.ShpDZ*2)+4].ltr = new char[(gamDat.P1Name.length())];
    mana[(gamDat.ShpDZ*2)+5].ltr = new char[(gamDat.P2Name.length())];
    mana[(gamDat.ShpDZ*2)+4].num = new char[1];
    mana[(gamDat.ShpDZ*2)+5].num = new char[1];
    mana[(gamDat.ShpDZ*2)+4].num[0] = static_cast<char>(gamDat.P1Name.length());
    mana[(gamDat.ShpDZ*2)+5].num[0] = static_cast<char>(gamDat.P2Name.length());
    
    mana[(gamDat.ShpDZ*2)].num[0]=static_cast<char>(gamDat.P1Pts);
    mana[(gamDat.ShpDZ*2)+1].num[0]=static_cast<char>(gamDat.P2Pts);
    mana[(gamDat.ShpDZ*2)+2].num[0]=static_cast<char>(gamDat.tMax);
    mana[(gamDat.ShpDZ*2)+3].num[0]=static_cast<char>(gamDat.turn);
    
    //Set player name sizes
    for(int z=0;z<gamDat.P1Name.length();z++)
    {
    mana[14].ltr[z] = gamDat.P1Name[z];
    }
    for(int z=0;z<gamDat.P2Name.length();z++)
    {
    mana[15].ltr[z] = gamDat.P2Name[z];
    }
    //Set Ship Spaces
    int Xcnt=0;
    for(int p=0;p<gamDat.ShpDZ;p++)
    {
        for(int q=0;q<gamDat.P1Ships[p].size;q++)
        {
            Xcnt=p;                 //Creates Sequence 0,1,2,3,4 for Player 1 Ships
            char *buff = new char[1];
            strcpy(buff,gamDat.P1Ships[p].spcs[q].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,gamDat.P1Ships[p].spcs[q].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            Xcnt+=gamDat.ShpDZ;      //Creates Sequence 5,6,7,8,9 for Player 2 Ships
            strcpy(buff,gamDat.P2Ships[p].spcs[q].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,gamDat.P2Ships[p].spcs[q].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            delete buff;
        }
    }
    return mana;
}
binXfer *Brd2Bin (BrdSet BrdDat,int Z9)
{   //Create structure to convert all 4 boards to binXfer
    binXfer *mana = new binXfer[Z9*4];
    for(int y=0;y<(Z9*4);y++)
    {
    mana[y].ltr = new char[Z9];
    mana[y].num = new char[Z9];
    }
    int Xcnt=0;
    for(int p=0;p<Z9;p++)
    {
        for(int q=0;q<Z9;q++)
        {
            Xcnt=p*4;   //Creates sequence 0/4/8/12/16....
            char *buff = new char[1];
            strcpy(buff,BrdDat.B1G[q][p].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,BrdDat.B1G[q][p].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            Xcnt++;     //Creates sequence 1/5/9/13/17....
            strcpy(buff,BrdDat.B1S[q][p].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,BrdDat.B1S[q][p].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            Xcnt++;     //Creates sequence 2/6/10/14/18...
            strcpy(buff,BrdDat.B2G[q][p].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,BrdDat.B2G[q][p].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            Xcnt++;     //Creates sequence 3/7/11/15/19...
            strcpy(buff,BrdDat.B2S[q][p].substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,BrdDat.B2S[q][p].substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            delete[] buff;
        }
    }
    return mana;
}
binXfer *binRC(fstream &file,int Z9,string fName)
{   //Reads data based on file name into binXfer structure 
    file.open((fName+".bin"),ios::in|ios::binary);
    int Zmod = 0;
    if(fName=="brdSv"){Zmod=Z9*4;}  //Determine size of binXfer to create based on file name
    else(Zmod=Z9+6);
    binXfer *xfer = new binXfer[Zmod];
    
    for(int y=0;y<=Zmod;y++)        //Create large blank arrays for binXfer to receive universally
    {
    xfer[y].ltr = new char[Z9];
    xfer[y].num = new char[Z9];
    }
    
    int cur=0;
    if(fName=="brdSv")              //Read boards into a binXfer structure
    {
    for(int t=0;t<Zmod;t++)                            //Begin Extraction Loop
    {
        for(int v=0;v<Z9;v++)
        {
        file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
        file.read(&xfer[t].ltr[v], sizeof(char));       //Reads one character from a binary file                 
        cur+=sizeof(char);                               //Update Pointer/Cursor Position
        file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
        file.read(&xfer[t].num[v], sizeof(char));       //Reads one character from a binary file  
        cur+=sizeof(char);                               //Update Pointer/Cursor Position
        }
        }
    }
    else if(fName=="shpSv")         //Read ship data, turns, points, and names into binXfer structure
        {
         for(int r=0;r<=Z9+6;r++)                            
        {
            if(r<10)                //If accessing a ship strucutre
            {
                for(int d=0;d<Z9;d++)
                {
                file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
                file.read(&xfer[r].ltr[d], sizeof(char));       //Reads one character from a binary file                 
                cur+=sizeof(char);                               //Update Pointer/Cursor Position
                file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
                file.read(&xfer[r].num[d], sizeof(char));       //Reads one character from a binary file  
                cur+=sizeof(char);                               //Update Pointer/Cursor Position   
                }
            }
            else if(r>9 && r<14)    //If accessing a turn/points structure
            {
                for(int d=10;d<=Z9+4;d++)
                {
                file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
                file.read(&xfer[d].num[0], sizeof(char));       //Reads one character from a binary file  
                cur+=sizeof(char);
                }
            }
            else if(r>13 && r<16)   //If accessing a name strucutre
            {   //Gets size of string to return
                file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
                file.read(&xfer[r].num[0], sizeof(char));       //Reads one character from a binary file  
                cur+=sizeof(char);                               //Update Pointer/Cursor Position
                //Returns string based on size of string indicated
                for(int v=0;v<static_cast<short>(xfer[r].num[0]);v++)
                {
                file.seekg(cur,ios::beg);                                   //Places Pointer/Cursor at next target start
                file.read(&xfer[r].ltr[v], sizeof(char));       //Reads one character from a binary file                 
                cur+=sizeof(char);                               //Update Pointer/Cursor Position
                }
            }
         }
        }
    file.close();                                           //Got stuck here for over an hour, CLOSE YOUR FILE
    return xfer;
}
void binWrt (binXfer *data,fstream &file,int Z,string fName)
{
    file.open((fName+".bin"),ios::out|ios::binary);     //Open file for output
    if(fName=="brdSv")
    {
    for(int r=0;r<Z*4;r++)                              //Writes data to a binary file from binXfer sized for boards
    {
        for(int d=0;d<Z;d++)
        {
           file.write(&data[r].ltr[d],sizeof(char));
           file.write(&data[r].num[d],sizeof(char));
        }    
    }
    }
    else if(fName=="shpSv")
    {
        for(int r=0;r<=Z+6;r++)                            //Writes data to a binary file from binXfer sized for general data
        {
            if(r<10)                                        //Writes ship spaces
            {
                for(int d=0;d<Z;d++)
                {
                   file.write(&data[r].ltr[d],sizeof(char));
                   file.write(&data[r].num[d],sizeof(char));
                }
            }
            else if(r>=10 && r<=13)                         //Writes player points and turns
            {
                for(int d=10;d<=Z+4;d++)
                {
                file.write(&data[d].num[0],sizeof(char));
                }
            }
            else if(r>=14 && r<=15)                         //Writes player name sizes and then names based on sizes
            {
                file.write(&data[r].num[0],sizeof(char));   //Binary file can now read number of characters required for a string
                for(int d=0;d<static_cast<short>(data[r].num[0]);d++)
                {
                file.write(&data[r].ltr[d],sizeof(char));
                }
            }
        }
    }
    file.close();
}
void LdSave (plyrSv &gamDat,fstream &file,int Z9)
{
    binXfer *saves = new binXfer[Z9*4];                 //Create memory to receive board data from file
    for(int y=0;y<Z9*4;y++)
    {
    saves[y].ltr = new char[Z9];
    saves[y].num = new char[Z9];
    }
    
    saves=binRC(file,Z9,"brdSv");           //Read binary file "brdSv"
    MBdFill(gamDat.BrdDat.MB,Z9);           //Pre-fill Master Board since it's always the same
    Bin2Brd(gamDat.BrdDat,Z9,saves);        //Fill remaining ship/guess boards with file data (pass-by-reference)
    destroy(saves,Z9,'B');                  //Clean up nasty memory

    binXfer *shps = new binXfer[(gamDat.ShpDZ*2)+6];    //Create memory to receive ship/points/turn/name data from file
    for(int y=0;y<gamDat.ShpDZ;y++)
    {
    shps[y].ltr = new char[gamDat.P1Ships[y].size];
    shps[y].num = new char[gamDat.P1Ships[y].size];
    shps[y+gamDat.ShpDZ].ltr = new char[gamDat.P2Ships[y].size];
    shps[y+gamDat.ShpDZ].num = new char[gamDat.P2Ships[y].size];
    }
    for(int y=(gamDat.ShpDZ*2);y<(gamDat.ShpDZ*2)+4;y++)
    {
        shps[y].num = new char[1];
    }
    for(int y=(gamDat.ShpDZ*2)+4;y<(gamDat.ShpDZ*2)+6;y++)
    {
    shps[y].ltr = new char[Z9];
    shps[y].num = new char[Z9];
    }
    shps=binRC(file,Z9,"shpSv");            //Read binary file "ShpSv"
    Bin2Shp(gamDat,Z9,shps);                //Convert binXfer to data (uses pass-by-reference)
    destroy(shps,Z9,'S');                   //Clean up nasty memory
    
}
void MakSave (plyrSv gamDat,fstream &file, int Z9)
{
    binXfer *brds = new binXfer[Z9*4];      //Create memory to send board data to a file
    for(int y=0;y<Z9*4;y++)
    {
    brds[y].ltr = new char[Z9];
    brds[y].num = new char[Z9];
    }
    brds=Brd2Bin(gamDat.BrdDat,Z9);         //Converts game data to binXfer structure
    binWrt(brds,file,Z9,"brdSv");           //Sends binXfer structure to file
    destroy(brds,Z9,'B');                   //Clean up nasty memory

    
    binXfer *shps = new binXfer[(gamDat.ShpDZ*2)+6];    //Create memory to send ship/turn/points/name data to file
    for(int y=0;y<gamDat.ShpDZ;y++)
    {
    shps[y].ltr = new char[gamDat.P1Ships[y].size];
    shps[y].num = new char[gamDat.P1Ships[y].size];
    shps[y+gamDat.ShpDZ].ltr = new char[gamDat.P2Ships[y].size];
    shps[y+gamDat.ShpDZ].num = new char[gamDat.P2Ships[y].size];
    }
    for(int y=(gamDat.ShpDZ*2);y<=(gamDat.ShpDZ*2)+4;y++)
    {
        shps[y].num = new char[1];
    }
    shps[(gamDat.ShpDZ*2)+4].ltr = new char[(gamDat.P1Name.length())];
    shps[(gamDat.ShpDZ*2)+5].ltr = new char[(gamDat.P2Name.length())];
    shps[(gamDat.ShpDZ*2)+4].num = new char[1];
    shps[(gamDat.ShpDZ*2)+5].num = new char[1];
    
    shps=Shp2Bin(gamDat);                   //Convert dame data to binXfer structure
    binWrt(shps,file,Z9,"shpSv");           //Send binXfer structure to file
    destroy(shps,Z9,'C');                   //Clean up nasty memory
}
void IOProof(fstream &file)
{
    file.open("GradeMe.txt",ios::in | ios::out | ios::app); //Simultaneous output, opened at the end of file
    file<<"test"<<endl;                                     //Writes "test" into file in a new line
    file.seekg(0,ios::beg);                                 //Reset cursor to beginning to read
    string tests;                                           //Create output buffer
    file>>tests;                                            //Load first word of file "GOOD!" into variable
    cout<<tests<<endl;                                      //Display "GOOD!" when Skip is P1 name
    file.close();                                           //Close file that just did both Input and Output
}                                                           //simultaneously
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
