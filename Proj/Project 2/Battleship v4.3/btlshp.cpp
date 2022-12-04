/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "btlshp.h"

using namespace std;

btlshp::btlshp()
{
    gamDat = plyrSv();
    maxSpc=17;
    Win="null";
}
void btlshp::setShps()
{
    cout<<"Type a name for Player 1"<<endl;
    gamDat.setN1();
    if(gamDat.getN(1)!="a")
    {
    cout<<"Type a name for Player 2"<<endl;
    cout<<"To play against the computer, type AI"<<endl;
    gamDat.setN2();
    cout<<endl;
    
    cout<<"Player 1 Setup"<<endl;
    gamDat.P1Shps(maxSpc);

    cout<<"Your Ship Locations"<<endl;
    gamDat.shwBS1();
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"Shrink the Window to below this line to hide your ships!"<<endl;
    }else{gamDat.frcN2();}
    //AI setup if statement
    if(gamDat.getN(2)!="AI")
    {
    cout<<"Player 2 Setup"<<endl;
    gamDat.P2Shps(maxSpc);
    
    cout<<"Your Ship Locations"<<endl;
    gamDat.shwBS2();
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"Shrink the Window to below this line to hide your ships!"<<endl;
    }else{gamDat.AIShpSU(maxSpc);}
    
    cout<<"All ships were set up correctly!"<<endl;
    //Players ships are set up, boards are set up
        //run save game
    
    //Prompt for number of turns to play
    
    //Run play game
    
    //Run end game scoring


    }
void btlshp::chkTrns()
{
    siffy *sif = new siffy();
    cout<<"Set number of turns to play for: ";
    gamDat.setTrn(sif->turnVal());
    delete sif;
}

//run all functions to initialize boards


//potentially run all user set up of ships



void btlshp::txtWrt()
{
    file.open("Test1.txt",ios::in | ios::out);  
           for(int k=0;k<Scrs.size();k++)
           {
               file << Scrs[k].Name<<"\t"<<Scrs[k].Vs<<"\t"<<Scrs[k].Ps<<"\t"<<Scrs[k].Ts<<"\t"<<Scrs[k].Gs<<"\n"; //tab-delineated so it can be dropped in excel
            }

    file.close();
}
void btlshp::txtRd ()
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

void btlshp::DisScre()  //Displays Vector contents
{   cout<<"--------Player Scores---------------------------------------------"<<endl;
    cout<<"Name"<<"\t"<<"\t"<<"W/L"<<"\t"<<"Pts"<<"\t"<<"Turns"<<"\t"<<"Games"<<endl;
            for(int h=0;h<(Scrs.size());h++)
            {
                cout<<Scrs[h].Name<<"\t";
                if(Scrs[h].Name.length()<8){cout<<"\t";}
                cout<<Scrs[h].Vs<<"\t"<<Scrs[h].Ps<<"\t"<<Scrs[h].Ts<<"\t"<<Scrs[h].Gs<<endl;
            }cout<<"------------------------------------------------------------------"<<endl;
}
record* btlshp::newscre (string name,string S,int Pts,int Len)
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
void btlshp::updscre (string name,string Win,int Pts,int Len,int e)
{
    if(name==Win)
    {   
          //update winner record
            Scrs[e].Vs++;
            Scrs[e].Ps+=Pts;
            Scrs[e].Ts+=Len;
            Scrs[e].Gs++;
    }
    else 
    {
          //update loser or tie record
            Scrs[e].Ps+=Pts;
            Scrs[e].Ts+=Len;
            Scrs[e].Gs++;
    }
}
void btlshp::swtch (char Menu,bool &ld)
{
    switch (Menu)
    { //Start Switch (Menu) Box
case 'N':   {ld=false;break;} //Passes through
case 'L':   {ld=true;gamDat.LdSave(gamDat,file);break;} //Loads a new game from a binary file based on a string
case 'S':   {//High Score Display
            txtRd();
            DisScre();
            cout<<endl;
            Scrs={};
break;}
case 'R':   {//Reset Score
            Scrs={};
            txtWrt();
break;}
case 'X': {cout<<"Goodbye!"<<endl;exit(0); break;}
case 'A':   { //Sort Scores Alphabetically (Selection Sort)
            Scrs={};
            txtRd();
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
            txtWrt();
            Scrs={};       
            delete BF;
break;}
case 'H':   {//Sort Scores by High Score (Bubble Sort)
            Scrs={};
            txtRd();
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
            txtWrt();
            Scrs={};  
            delete BF;
break;}       
case 'F':   {//Search Scores using Linear Search
            string *Srch = new string;
            cout<<"Please type the desired name"<<endl;
            cin>>*Srch;
            Scrs={};
            txtRd();
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
            txtWrt();
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

void btlshp::EGScr ()     //Performs Score Writing Tasks at End of Game
{
    short WinPts,LosePts;               //Placeholders to allow for single function to write scores
    bool *wrote = new bool;             //Did I write this score? flag
    *wrote=false;
    string *buff = new string;          //Buffer for instances where player name is not necessarily Win
    Scrs={};                            //Default Scores Vector
    txtRd();                   //Acquire existing scores file
    if(Scrs.size()<1)                   //If no records exist, create new records
        {
            record *P1 = new record;  //create P1 record
            P1=newscre(gamDat.getN(1),Win,gamDat.getPts(1),gamDat.getTMAX());
            Scrs.push_back(*P1);
            delete P1;    
            record *P2 = new record;  //create P2 record
            P2=newscre(gamDat.getN(2),Win,gamDat.getPts(2),gamDat.getTMAX());   
            Scrs.push_back(*P2);
            delete P2;
        }   
    else if(Win!="Nobody")              //Records exist and it was not a tie
    {
        if(gamDat.getN(1)==Win) //Set Winner/Loser points
        {WinPts=gamDat.getPts(1); LosePts=gamDat.getPts(2);}
        else{WinPts=gamDat.getPts(2);LosePts=gamDat.getPts(1);}
        
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==Win)
            {
                updscre(Win,Win,WinPts,gamDat.getTMAX(),e);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=Win && *wrote!=true)
            {
            record *Vctr = new record;  //create winner record
            Vctr=newscre(Win,Win,WinPts,gamDat.getTMAX());
            Scrs.push_back(*Vctr);
            delete Vctr;
            *wrote=true;
            }
            if(*wrote){e=Scrs.size();}
        }        
        *wrote=false;
        if(Win==gamDat.getN(1)){*buff=gamDat.getPts(2);}
        else {*buff=gamDat.getN(1);}         //Determine buffer identity for loser
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,LosePts,gamDat.getTMAX(),e);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Lsr = new record;  //create loser record
                Lsr=newscre(*buff,Win,LosePts,gamDat.getTMAX());   
                Scrs.push_back(*Lsr);
                *wrote=true;
                delete Lsr;
            }
            if(*wrote){e=Scrs.size();}
        }        
    }
    else if(Win=="Nobody")                  //Records exist and it IS a tie
    {
        *buff=gamDat.getN(1);
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,gamDat.getPts(1),gamDat.getTMAX(),e);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Tie = new record;  
                Tie=newscre(*buff,Win,gamDat.getPts(1),gamDat.getTMAX());   
                Scrs.push_back(*Tie);
                *wrote=true;
                delete Tie;
            }
        }
        *wrote=false;
        *buff=gamDat.getN(2);
        for(int e=0;e<Scrs.size();e++)
        {
            if(Scrs[e].Name==*buff)
            {
                updscre(*buff,Win,gamDat.getPts(1),gamDat.getTMAX(),e);
                *wrote=true;
            }
            else if(e==(Scrs.size()-1) && Scrs[e].Name!=*buff && *wrote!=true)
            {
                record *Tie = new record;  
                Tie=newscre(*buff,Win,gamDat.getPts(1),gamDat.getTMAX());   
                Scrs.push_back(*Tie);
                *wrote=true;
                delete Tie;
            }
        }
        
    }
    txtWrt();      //Replace scores in file
    Scrs={};                //Reset Vector       
    txtRd();       //Re-read scores for display purposes
    DisScre();          //display scores after game
    delete buff; 
    delete wrote;
}

void btlshp::MenuOpt ()
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
void btlshp::SUtxt1 (string PName)
{
    cout<<"********************************************************"<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"*****Tell "<<PName<<" to look away!****"<<endl;
    cout<<"********************************************************"<<endl;
    cout<<"********************************************************"<<endl;
}
