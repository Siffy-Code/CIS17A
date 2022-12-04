/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */
#include "plyrSv.h"

using namespace std;


void plyrSv::MBdFill ()
{//Fills Master Board with Grid Locations
    string Ltr="A";     //grid starts with this letter
    char act;
    char *Buff = new char;
    int Num=1;
    for(int q=0 ; q<BrdDat.Z9; q++)
    {    
        for(int w=0 ; w<BrdDat.Z9; w++)
        {
            BrdDat.MB[w][q]=(Ltr+to_string(Num));
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
void plyrSv::DisBrd (string b[][9])
{//Displays any board with nice formatting
    cout<<"    A  B  C  D  E  F  G  H  I"<<endl;
    cout<<"    -------------------------"<<endl;
    for(int q=0 ; q<BrdDat.Z9; q++)
    {
        cout<<q+1<<" | ";
        for(int w=0 ; w<BrdDat.Z9; w++)
        {cout<<b[w][q]<<" ";}
        cout<<endl;
    }
    cout<<"    -------------------------"<<endl;
}
void plyrSv::BBdFill (string b[][9])
{//Fills a player board with waves - it's the ocean!
    for(int q=0 ; q<BrdDat.Z9; q++)
    {
        for(int w=0 ; w<BrdDat.Z9; w++)
        {
          b[w][q]="~~"; //Ride on those waves!
        }
    }
}
void plyrSv::UpdGBrd (string user,string b[][9],bool hit) //updates guess boards
{
    for(int i=0 ; i<BrdDat.Z9 ; i++)
    {
        for(int q=0 ; q<BrdDat.Z9; q++)
        {
            if(BrdDat.MB[i][q]==user)
            {
                if(hit==true)
                {b[i][q]="XX";}
                else if(b[i][q]!="XX")
                { b[i][q]="OO";}
            }
        }
    }
}
void plyrSv::UpdBS (shipDat a,string b[][9]) //updates ship boards
{
    for(int i=0 ; i<a.getSZ() ; i++)
    {
    for(int q=0 ; q<BrdDat.Z9; q++)
    {
        for(int w=0 ; w<BrdDat.Z9; w++)
        {
            if(a.getSpc(i)==BrdDat.MB[w][q])
            {
                b[w][q]="||";
            }
        }
    }
    }
}
void plyrSv::PSetUp (int maxSpc,string PName,string b[][9],shipDat *PShips)
{
    cout<<"Let's set up your ships, "<<PName<<"!"<<endl;
    string *valLst = new string[maxSpc];            //Buffer to hold all spaces occupied by players' ships while setting up
    
    
    siffy *sif = new siffy();                       //New utility class (should run basic zero-ing constructor)
    for(int a=0;a<ShpDZ;a++)                        //Loop for size of total number of ships per player
    {    

        cout<<endl;
        cout<<endl;
        DisBrd(b);  
        cout<<"-=Ship "<<(a+1)<<" of "<<ShpDZ<<"=-"<<endl;
        cout<<"Input a Grid Square to initialize Ship Placement"<<endl;
        PShips->shptxt(a);
        cout<<"Use one Capital Letter from A-I followed by one Number 1-9"<<endl;
        cout<<"(Examples: A1, B6, I8, G9)"<<endl;
        sif->sifREC();                         //Receive input and run through validation process
        for(int c=0;c<maxSpc;c++)               //Validate player selection against existing ships placed
        {
            if(sif->useS()==valLst[c]){
                cout<<"##################### ERROR ######################"<<endl;
                cout<<"Selection Overlaps Existing Ship, Please try again"<<endl;
                cout<<"##################### ERROR ######################"<<endl;
                c=maxSpc;sif->flipB();}             //Error Text, loop quit, flag notification
        }

        if(!sif->useB()){PShips[a].setSpc(sif->useS());}   //Set initial value of Array to Player Input
        
        sif->sifSClr();
        if(!sif->useB())
        {
            cout<<"Set up direction starting at: "<<PShips[a].getSpc(0)<<endl;
            PShips->shptxt(a);
            cout<<"Type |L| for Left, |R| for Right, |U| for Up, and |D| for down"<<endl;
            sif->charREC();                                       //Receive player input for direction
            cout<<"test"<<endl;
            PShips[a].FillShp(sif->useS());
            for(int h=0;h<PShips[a].getSZ();h++)                  //Loop to load space buffer with proposed ship spaces
                {            

                    valLst[sif->useI()]=PShips[a].getSpc(h);

                    sif->ovride();                               //overloaded operator??
                                
                }
            for(int w=0;w<sif->useI();w++)                           //Loop to check if Fill Ship was valid or if it needs to be re-run
                {
                for(int c=0;c<sif->useI();c++)                       //Inner loop of search procedures
                    {
                    if(w!=c){                                   //As long as it is not counting itself,
                    if(valLst[c]==valLst[w]){                   //check if space already exists
                        cout<<"##################### ERROR ######################"<<endl;
                        cout<<"Ships Overlap - Please select again"<<endl;
                        cout<<"##################### ERROR ######################"<<endl;
                        c=sif->useI();w=sif->useI();sif->flipB();sif->sifI2I(sif->useI()-PShips[a].getSZ());}//Error Text, loop quit, flag notification, reset counter for buffer array
                        }
                    }
                }
            if(!sif->useB()){
            cout<<"Your Ship's Coordinates Are:"<<endl;
            PShips[a].ICoord();            //Outputs individual ship coordinates
            UpdBS(PShips[a],b);  //Updates Ship Board for validation
                    }
        }cout<<sif->useB()<<endl;
        if(sif->useB()){a--;}                                           //Repeat loop if flag is hit
        sif->flipF(); 
        sif->sifSClr();//Reset flag for next loop
    }
    delete[] valLst;  
    delete sif;//Clean up nasty memory
}
void plyrSv::AIShpSU (int maxSpc)
{
    siffy *sif = new siffy();
    
    string *valLst = new string[maxSpc];                        //Buffer for AI ship selection values to verify against
        int lstCnt = 0;
        
        for(int f=0;f<ShpDZ;f++)                                //Similar loop logic for players but separated so it can be adjusted for
        {                                                       //better functionality and precision
        sif->sifC2C((rand()%9+1+64));    //set random Char for column guess A-I A=65?
        sif->sifI2I((rand()%9+1));       //set random Number for Row guess 1-9 
            for(int c=0;c<maxSpc;c++)                                           //Run for number of ship sizes
            {
            if(((sif->Cnvt(sif->useC()))+to_string(sif->useI()))==valLst[c]){c=maxSpc;sif->flipB();}                     //Ships overlap during AI setup, run again
            }
            P2Ships[f].setSpc((sif->Cnvt(sif->useC()))+to_string(sif->useI())); //combine Column/Row for input
            sif->sifS2S(P2Ships->AIShpDr(sif->useC(),sif->useI(),P2Ships[f].getSZ()));
            P2Ships[f].FillShp(sif->useS());
            for(int h=0;h<P2Ships[f].getSZ();h++)
                {
                valLst[lstCnt]=P2Ships[f].getSpc(h);                                                  
                lstCnt++;
                }
            for(int w=0;w<lstCnt;w++)
            {
                for(int c=0;c<lstCnt;c++)
                {
                    if(w!=c){
                    if(valLst[c]==valLst[w]){c=lstCnt;w=lstCnt;sif->flipB();lstCnt-=P2Ships[f].getSZ();}   //Ships overlap during AI setup, run again
                    }
                }
            }
            if(!sif->useB()){UpdBS(P2Ships[f],BrdDat.B2S);} //If valid, update ship board
            sif->sifIClr();
            sif->sifCClr();                      //Reset Buffers for next ship
            if(sif->useB()){f--;}                       //If bad, retract counter and collect data again
            sif->flipF();                          //Reset flag
        }
        delete[] valLst;
        
        cout<<"AI Ship Setup Has Run"<<endl;                                //DEBUG LINES
        
        if(P1Name=="a")
        {
        DisBrd(BrdDat.B2S);                                              //Shows AI Ship board to player after set up during debug mode
        for(int q=0;q<ShpDZ;q++){P2Ships[q].ICoord();}  //DEBUG LINES
        }
}
void plyrSv::plyGam (string &Win,fstream &file)               //Plays a game of Battleship with a loaded plyrSv
{
    siffy *sif = new siffy();                       //siffy takes the place of cnt
    string *noregus = new string[tMax];              //Creates an array to ensure AI doesn't re-guess (NO RE-GUESS, sounds like "no Regus", kinda funny)
    if(P2Name!="AI"){delete[] noregus;}   //Cleans up memory immediately if non-AI player.
    //string guess;                                   //siffy takes the place of guess
    
    while (Win=="null") //Run forced while loop until winner is declared
    {    
            for (; turn<=tMax; )  //Due to save/load features, now relies on minimal data.  Counter increments at bottom before game saves
            {
                //Begin New Turn Transition Text
                cout<<"           ----------"<<endl;
                cout<<"          | Turn #"<<turn<<"/"<<tMax<<" |"<<endl;
                cout<<"           ----------"<<endl;
                cout<<"          -="<<P1Name<<"'s turn!=-"<<endl;
                cout<<endl;
                cout<<"Here is your Guess Board, "<<P1Name<<"!"<<endl;
                cout<<endl;
                DisBrd(BrdDat.B1G);
                cout<<"You have "<<P1Pts<<" Points"<<endl;
                cout<<endl;
                cout<<P1Name<<"; choose a Grid Square!"<<endl;
                
                sif->sifREC(); //data validation for grid square
                
                Shoot(sif->useS(),BrdDat.B2S,BrdDat.B1G,P1Pts);
                cout<<endl;
                P2Ships->addDmg(P2Ships,ShpDZ,sif->useS());
                if(P1Pts>=17) //Are all Player 2 Ships off the board?
                {Win=P1Name; turn=tMax;} //Set turns to max here to ensure game ends correctly, Declare Winner
                else //Endgame Check Fails, Run Player 2 Turn
                {
                        if (P2Name!="AI")                    //Human player 2 turn
                        {  
                        cout<<"-----------------"<<endl;    
                        cout<<P2Name<<"'s turn!"<<endl;
                        cout<<endl;
                        cout<<"Here is your Guess Board, "<<P2Name<<"!"<<endl;
                        cout<<endl;
                        DisBrd(BrdDat.B2G);
                        cout<<"You have "<<P2Pts<<" Points"<<endl;
                        cout<<endl;
                        cout<<P2Name<<"; choose a Grid Square!"<<endl;
                        sif->sifREC(); //data validation for grid square
                        } 
                        else                                        //AI Turn
                        { 
                            siffy *sophie = new siffy();
                            sophie->flipB();
                                while(sophie->useB())
                                {
                                sophie->sifC2C(rand()%9+1+64); //set random Char for column guess A-I A=65?
                                sophie->sifI2I(rand()%9+1);   //set random Number for Row guess 1-9
                                for(int u=0;u<=sif->useI();u++)
                                {
                                if((sophie->sndC2S()+sophie->sndI2S())==noregus[u]){sophie->flipB();u=sif->useI();} //Ensures the computer does not guess the same thing twice
                                else if(u==sif->useI()){sophie->flipF();}
                                }    
                                }
                            sif->sifS2S(sophie->sndC2S()+sophie->sndI2S()); //concatenate string for guess
                            cout<<"---------------------------"<<endl;
                            cout<<"The Computer has guessed "<<sif->useS()<<endl;
                            cout<<"---------------------------"<<endl;
                            noregus[sif->useI()]=sif->useS();sif->operator++();
                        //destructor for sophie
                        } //End AI Turn
                        Shoot(sif->useS(),BrdDat.B1S,BrdDat.B2G,P2Pts);
                        P1Ships->addDmg(P1Ships,ShpDZ,sif->useS());
                        turn++;                          //Increment turn counter after valid guess, before save initiated
                        if(P2Pts>=17)                    //Are all Player 2 Ships off the board?
                        {Win=P2Name; turn=tMax;}  //Set turns to max here to ensure game ends correctly, Declare Winner
                        else{MakSave(file);cout<<"|Autosaved|"<<endl;}          //If game will continue, send data to save file
                }
                cout<<"---==Turn End==---"<<endl;
                cout<<P1Name<<" Points: "<<P1Pts<<endl;
                cout<<P2Name<<" Points: "<<P2Pts<<endl;
                cout<<"------------------"<<endl;
            }//End Turn Loop
    if (P1Pts<P2Pts){Win=P2Name;}
    else if (P1Pts==P2Pts){Win="Nobody";}
    else {Win=P1Name;} 
    }
    if(P2Name=="AI"){delete[] noregus;}       //Cleans up memory for re-guess if player was AI at end of game
}
void plyrSv::Shoot (string user,string b[][9],string g[][9],short &pts)
{
    bool hit; //input for updating guess boards with X's or O's
    for(int i=0 ; i<BrdDat.Z9 ; i++)
    {
    for(int q=0 ; q<BrdDat.Z9; q++)
    {
        if(BrdDat.MB[i][q]==user)
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
    UpdGBrd(user,g,hit); //update guess board for player
}

plyrSv::plyrSv()
{
            P1Ships[0].shipD(P1Ships->gZ2()); 
            P1Ships[1].shipD(P1Ships->gZ3()); 
            P1Ships[2].shipD(P1Ships->gZ3()); 
            P1Ships[3].shipD(P1Ships->gZ4()); 
            P1Ships[4].shipD(P1Ships->gZ5()); 
            P2Ships[0].shipD(P1Ships->gZ2()); 
            P2Ships[1].shipD(P1Ships->gZ3()); 
            P2Ships[2].shipD(P1Ships->gZ3()); 
            P2Ships[3].shipD(P1Ships->gZ4()); 
            P2Ships[4].shipD(P1Ships->gZ5()); 
            
            turn = 1;
    //Initialize Boards
    MBdFill();
    BBdFill(BrdDat.B1S);
    BBdFill(BrdDat.B2S);
    BBdFill(BrdDat.B1G);
    BBdFill(BrdDat.B2G);    
}
void plyrSv::destroy (binXfer *mana,int Z9,char dType)
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



//Binary File Operations
void plyrSv::Bin2Brd(binXfer *mana)
{//Repeats process from Brd2Bin to decode the order of data
    siffy *sif = new siffy();
    int Xcnt=0;
    for(int p=0;p<BrdDat.Z9;p++)   
     {
        for(int q=0;q<BrdDat.Z9;q++)
        {
        Xcnt=p*4;           //Creates sequence 0/4/8/12/16....             
        char ltrB, numB;
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B1G[q][p]=(sif->Cnvt(ltrB)+sif->Cnvt(numB));
        Xcnt++;             //Creates sequence 1/5/9/13/17....
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B1S[q][p]=(sif->Cnvt(ltrB)+sif->Cnvt(numB));
        Xcnt++;             //Creates sequence 2/6/10/14/18...
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B2G[q][p]=(sif->Cnvt(ltrB)+sif->Cnvt(numB));
        Xcnt++;             //Creates sequence 3/7/11/15/19...
        ltrB=mana[Xcnt].ltr[q];
        numB=mana[Xcnt].num[q];
        BrdDat.B2S[q][p]=(sif->Cnvt(ltrB)+sif->Cnvt(numB));
        Xcnt++;
        }
     } 
    delete sif;
}
void plyrSv::Bin2Dat(binXfer *shps)
{   //Retrieve key data points from binXfer structure
    siffy *sif = new siffy();
    P1Pts=static_cast<short>(shps[(ShpDZ*2)].num[0]);
    P2Pts=static_cast<short>(shps[(ShpDZ*2)+1].num[0]);
    tMax=static_cast<short>(shps[(ShpDZ*2)+2].num[0]);
    turn=static_cast<short>(shps[(ShpDZ*2)+3].num[0]);
    //Retrieve player names from binXfer structure
    for(int i=0;i<static_cast<short>(shps[(ShpDZ*2)+4].num[0]);i++)
    {
        P1Name+=shps[(ShpDZ*2)+4].ltr[i];
    }
    for(int i=0;i<static_cast<short>(shps[(ShpDZ*2)+5].num[0]);i++)
    {
        P2Name+=shps[(ShpDZ*2)+5].ltr[i];
    }
    //Retrieve ship spaces data from binXfer structure
    int Xcnt=0;
    for(int p=0;p<ShpDZ;p++)
    {
        for(int q=0;q<P1Ships[p].getSZ();q++)
        {
            Xcnt=p;                 //Creates Sequence 0,1,2,3,4 for Player 1 Ships
            char ltrB, numB;            
            ltrB=shps[Xcnt].ltr[q];
            numB=shps[Xcnt].num[q];
            P1Ships[p].frcSpc(q,(sif->Cnvt(ltrB)+sif->Cnvt(numB)));
            Xcnt+=ShpDZ;      //Creates Sequence 5,6,7,8,9 for Player 2 Ships
            ltrB=shps[Xcnt].ltr[q];
            numB=shps[Xcnt].num[q];
            P2Ships[p].frcSpc(q,(sif->Cnvt(ltrB)+sif->Cnvt(numB)));
        }
    }
}
binXfer* plyrSv::Dat2Bin ()
{   //Create binXfer structure to hold Ship data
    binXfer *mana = new binXfer[(ShpDZ*2)+6];
    //Holds Ships spaces
    for(int y=0;y<ShpDZ;y++)
    {
    mana[y].ltr = new char[P1Ships[y].getSZ()];
    mana[y].num = new char[P1Ships[y].getSZ()];
    mana[y+ShpDZ].ltr = new char[P2Ships[y].getSZ()];
    mana[y+ShpDZ].num = new char[P2Ships[y].getSZ()];
    }
    //Holds Points, turns, player names, player name sizes
    for(int y=(ShpDZ*2);y<(ShpDZ*2)+4;y++)
    {
    mana[y].num = new char[1];
    }
    mana[(ShpDZ*2)+4].ltr = new char[(P1Name.length())];
    mana[(ShpDZ*2)+5].ltr = new char[(P2Name.length())];
    mana[(ShpDZ*2)+4].num = new char[1];
    mana[(ShpDZ*2)+5].num = new char[1];
    mana[(ShpDZ*2)+4].num[0] = static_cast<char>(P1Name.length());
    mana[(ShpDZ*2)+5].num[0] = static_cast<char>(P2Name.length());
    
    mana[(ShpDZ*2)].num[0]=static_cast<char>(P1Pts);
    mana[(ShpDZ*2)+1].num[0]=static_cast<char>(P2Pts);
    mana[(ShpDZ*2)+2].num[0]=static_cast<char>(tMax);
    mana[(ShpDZ*2)+3].num[0]=static_cast<char>(turn);
    
    //Set player name sizes
    for(int z=0;z<P1Name.length();z++)
    {
    mana[14].ltr[z] = P1Name[z];
    }
    for(int z=0;z<P2Name.length();z++)
    {
    mana[15].ltr[z] = P2Name[z];
    }
    //Set Ship Spaces
    int Xcnt=0;
    for(int p=0;p<ShpDZ;p++)
    {
        for(int q=0;q<P1Ships[p].getSZ();q++)
        {
            Xcnt=p;                 //Creates Sequence 0,1,2,3,4 for Player 1 Ships
            char *buff = new char[1];
            strcpy(buff,P1Ships[p].getSpc(q).substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,P1Ships[p].getSpc(q).substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            Xcnt+=ShpDZ;      //Creates Sequence 5,6,7,8,9 for Player 2 Ships
            strcpy(buff,P2Ships[p].getSpc(q).substr(0,1).c_str());
            mana[Xcnt].ltr[q]=*buff;
            strcpy(buff,P2Ships[p].getSpc(q).substr(1,1).c_str());
            mana[Xcnt].num[q]=*buff;
            delete buff;
        }
    }
    return mana;
}
binXfer* plyrSv::Brd2Bin (BrdSet BrdDat)
{   //Create structure to convert all 4 boards to binXfer
    binXfer *mana = new binXfer[BrdDat.Z9*4];
    for(int y=0;y<(BrdDat.Z9*4);y++)
    {
    mana[y].ltr = new char[BrdDat.Z9];
    mana[y].num = new char[BrdDat.Z9];
    }
    int Xcnt=0;
    for(int p=0;p<BrdDat.Z9;p++)
    {
        for(int q=0;q<BrdDat.Z9;q++)
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
binXfer* plyrSv::binRC(fstream &file,int Z9,string fName)
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
void plyrSv::binWrt (binXfer *data,fstream &file,int Z,string fName)
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
void plyrSv::LdSave (plyrSv &gamDat,fstream &file)
{
    binXfer *saves = new binXfer[BrdDat.Z9*4];                 //Create memory to receive board data from file
    for(int y=0;y<BrdDat.Z9*4;y++)
    {
    saves[y].ltr = new char[BrdDat.Z9];
    saves[y].num = new char[BrdDat.Z9];
    }
    
    saves=binRC(file,BrdDat.Z9,"brdSv");           //Read binary file "brdSv"
    gamDat.MBdFill();           //Pre-fill Master Board since it's always the same
    Bin2Brd(saves);        //Fill remaining ship/guess boards with file data (pass-by-reference)
    destroy(saves,BrdDat.Z9,'B');                  //Clean up nasty memory

    binXfer *lore = new binXfer[(gamDat.ShpDZ*2)+6];    //Create memory to receive ship/points/turn/name data from file
    for(int y=0;y<gamDat.ShpDZ;y++)
    {
    lore[y].ltr = new char[gamDat.P1Ships[y].getSZ()];
    lore[y].num = new char[gamDat.P1Ships[y].getSZ()];
    lore[y+gamDat.ShpDZ].ltr = new char[gamDat.P2Ships[y].getSZ()];
    lore[y+gamDat.ShpDZ].num = new char[gamDat.P2Ships[y].getSZ()];
    }
    for(int y=(gamDat.ShpDZ*2);y<(gamDat.ShpDZ*2)+4;y++)
    {
        lore[y].num = new char[1];
    }
    for(int y=(gamDat.ShpDZ*2)+4;y<(gamDat.ShpDZ*2)+6;y++)
    {
    lore[y].ltr = new char[BrdDat.Z9];
    lore[y].num = new char[BrdDat.Z9];
    }
    lore=binRC(file,BrdDat.Z9,"shpSv");            //Read binary file "ShpSv"
    Bin2Dat(lore);                //Convert binXfer to data (uses pass-by-reference)
    destroy(lore,BrdDat.Z9,'S');                   //Clean up nasty memory
    cout<<"Loaded Summary"<<endl;
    gamDat.Summary();
}
void plyrSv::MakSave (fstream &file)
{
    binXfer *brds = new binXfer[BrdDat.Z9*4];      //Create memory to send board data to a file
    for(int y=0;y<BrdDat.Z9*4;y++)
    {
    brds[y].ltr = new char[BrdDat.Z9];
    brds[y].num = new char[BrdDat.Z9];
    }
    brds=Brd2Bin(BrdDat);         //Converts game data to binXfer structure
    binWrt(brds,file,BrdDat.Z9,"brdSv");           //Sends binXfer structure to file
    destroy(brds,BrdDat.Z9,'B');                   //Clean up nasty memory

    binXfer *shps = new binXfer[(ShpDZ*2)+6];    //Create memory to send ship/turn/points/name data to file
    for(int y=0;y<ShpDZ;y++)
    {
    shps[y].ltr = new char[P1Ships[y].getSZ()];
    shps[y].num = new char[P1Ships[y].getSZ()];
    shps[y+ShpDZ].ltr = new char[P2Ships[y].getSZ()];
    shps[y+ShpDZ].num = new char[P2Ships[y].getSZ()];
    }
    for(int y=(ShpDZ*2);y<=(ShpDZ*2)+4;y++)
    {
        shps[y].num = new char[1];
    }
    shps[(ShpDZ*2)+4].ltr = new char[(P1Name.length())];
    shps[(ShpDZ*2)+5].ltr = new char[(P2Name.length())];
    shps[(ShpDZ*2)+4].num = new char[1];
    shps[(ShpDZ*2)+5].num = new char[1];
    shps=Dat2Bin();                   //Convert dame data to binXfer structure
    binWrt(shps,file,BrdDat.Z9,"shpSv");           //Send binXfer structure to file
    destroy(shps,BrdDat.Z9,'C');                   //Clean up nasty memory
}
void plyrSv::Summary()
{
    DisBrd(BrdDat.B1G);
    DisBrd(BrdDat.B2G);
    DisBrd(BrdDat.B1S);
    DisBrd(BrdDat.B2S);
    DisBrd(BrdDat.MB);
    
    for(int i = 0;i<ShpDZ;i++)
    {
        P1Ships[i].ICoord();
    }
    for(int i = 0;i<ShpDZ;i++)
    {
        P2Ships[i].ICoord();
    }
    cout<<P1Name<<"|"<<P1Pts<<endl;
    cout<<P2Name<<"|"<<P2Pts<<endl;
    cout<<turn<<" turn|tmax= "<<tMax<<endl;
    
    
}
