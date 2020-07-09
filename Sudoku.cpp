#include "Sudoku.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <algorithm>
#include <time.h>
#include <sstream>

Sudoku::Sudoku() : Sudoku(DEFAULT_ROWS,DEFAULT_COLS){}
Sudoku::Sudoku(int _rows,int _cols)
{
    this->_rows = _rows;
    this->_cols = _cols;
    _hardMode=8;
    _dontquit=true;
    for(int r=0;r<this->_rows;r++)
    {
        for(int c=0;c<this->_cols;c++)
        {
            ///Places the +-\s| in the game
            placeStuff(r,c);
        }
    }
    for(int i=0;i<9*9;i++)
        _nEmp[i] = {-1,-1,-1,-1};

    ///Initial Input------
    InitOption();
}

void Sudoku::InitOption(){
    ///Initial Input------
   system("color 81");

/*
                    _                 _       _
  ___ _ __ ___   __| |  ___ _   _  __| | ___ | | ___   _
 / __| '_ ` _ \ / _` | / __| | | |/ _` |/ _ \| |/ | | | |
| (__| | | | | | (_| | \__ | |_| | (_| | (_) |   <| |_| |
 \___|_| |_| |_|\__,_| |___/\__,_|\__,_|\___/|_|\_\\__,_|


    */
    std::cout.width(90);
    std::cout << "#################################################################\n";
    std::cout.width(90);
    std::cout << "#################################################################\n";
    std::cout.width(90);
    std::cout << "#       # SODOKU       SODOKU         SODOKU     SODOKU #       #\n";
    std::cout.width(90);
    std::cout << "#       #  SODOKU         SODOKU            SODOKU      #       #\n";
    std::cout.width(90);
    std::cout << "#################################################################\n";
    for(int i=0;i<2;i++)
    {
        std::cout.width(90);
        std::cout << "#################################################################\n";
    }

    std::cout.width(90);
    std::cout << "############## Easy Mode:e<===========>Hard Mode:h ##############\n";
    std::cout.width(90);
    std::cout << "#################################################################\n";
    bool tempBool =true;
    do{
        char choice = '\0';
        std::cin >>choice;

        if(tolower(choice) == 'x')
        {
            _dontquit = false;
            return;
        }
        tempBool  =  !('e' == tolower(choice) || 'h' == tolower(choice)) ;
        if(tempBool)
            std::cout << "Try again please\n" ;
        if(tolower(choice) == 'e')
            _hardMode = 15;
        else
            _hardMode = 4;

    }while(tempBool);

    system("pause");
}

void Sudoku::placeStuff(const int& r,const int& c)
{
    /**
    * There is SPACE in array positions 1,3...
    * so (c+1) mod 2 is to make sure that SPACE is in the *ODD* number[s] position of the array
    **/
    if((c+1)%2 == 0)
        array[r][c] = SPACE;///IF (c+1) is odd
    else if(((r%4) == 0) && ((c%8) == 0))
        array[r][c] = PLUS;///IF row is a multiple of 4 and if Column is a multiple of 8
    else if(((r%4) == 0))
        array[r][c] = MINUS;///IF row is a multiple of 4
    else if((c%8) == 0)
        array[r][c] = LINE;///IF column is a multiple of 8
}
int Sudoku::Random(int min,int max){return rand()%(max-min+1)+min;}
void Sudoku::Render()
{   ///Outputs the array
    int count=0;
    std::cout << " ";

    for(int i=0;i<_cols;i++){
        if(i%2 == 0 && i%8 != 0)
        {
            std::cout<<count++;
        }
        else{
            std::cout << ' ';
        }

    }
    std::cout << std::endl;
    count =0;
    for(int r=0;r<_rows;r++)
    {
        /**/
        if(r%4 != 0)
            std::cout << count++;
        else
            std::cout << ' ';
        /**/

        for(int c=0;c<_cols;c++)
        {
            ///Displays Space,Plus,line,player,minus, and NUMBERs respectively
            if(array[r][c] == SPACE && !(r%4 == 0) && !(r == _rows - 1 || r == 0))
                std::cout << obj[0] ;
            else if(array[r][c] == PLUS)
            {
                if(r == 0 && c == 0)
                {
                    std::cout << obj[7];
                }
                else if(r == 0 && c == _cols-1)
                {
                    std::cout << obj[13];
                }
                else if(r == _rows-1 && c == 0)
                {
                    std::cout << obj[6];
                }
                else if(r == _rows-1 && c == _cols-1)
                {
                    std::cout << obj[14];
                }
                //Sides
                else if(!(r ==0 || r ==_rows-1) && c == 0)
                {
                    std::cout << obj[10];
                }
                else if(!(r ==0 || r ==_rows-1) && c == _cols-1)
                {
                    std::cout << obj[12];
                }

                else if(!(c ==0 || c ==_cols-1) && r==0)
                {
                    std::cout << obj[9];
                }
                else if(!(c ==0 || c ==_cols-1) && r==_rows-1)
                {
                    std::cout << obj[8];
                }

                //Middle
                else if(!(r ==0 || r ==_rows-1) && !(c ==0 || c ==_cols-1))
                {
                    std::cout << obj[11];
                }
            }
            else if(array[r][c] == LINE )
                std::cout << obj[3] ;
            else if(array[r][c] == MINUS || r%4 == 0)
                std::cout << obj[2] ;
            else
            {
            if(array[r][c]>=0 && array[r][c]<=9)
            {
                if(array[r][c] == 0)
                    std::cout << '-';
                else
                    std::cout << (array[r][c]);
            }
            else
                std::cout <<obj[5];
            }
        }
        std::cout<< std::endl;
    }
}

bool Sudoku::movePlayerLoop()
{
    do
    {
        system("cls");
        system("color 07");
        ///Shows the game
        Render();
       // tempRender();
    }while(MovePlayer());

    return 1;
}

void Sudoku::LoadingGame()
{
    ///Starts by making the (n_array and array) have only zeros
    makeItZero();
    //Erase grid
  //  system("cls")
    ///Puts numbers in (n_array)
    while(makeNumber());
     ///This mean that the sudoku is solvable therefore we will put zero's in random locations
    putZeros();
    ///Adds numbers in n_array into array
    addNumber();
}
void Sudoku::Run()
{
    while(_dontquit)
    {
        system("cls");
        system("color 07");
        ///Reloads the game
        LoadingGame();
        ///Loops while player is moving
        movePlayerLoop();
    }
}

bool Sudoku::MovePlayer()
{
    ///Menu
    std::cout <<"X:EXIT\nR:Change puzzle\nP:Place\nA:***#Reveal Answer#***\nW:Check if you won\n--ANY OTHER KEY TO RESET--\n\nEnter : ";

    switch(tolower(getch()))
    {
        case'x':
        {
            _dontquit =false;
            return false;
        }
        ///Placing a number
        case'p':
        {
                std::cout << "\n\nEnter Coords to change" << std::endl;

                int crow = 0;
                std::cout << "Row: ";
                std::cin >>crow;

                int ccol= 0;
                std::cout << "Col: ";
                std::cin >>ccol;

                int value=0;
                std::cout << "Value: ";
                std::cin >>value;

                std::cin.clear();
                std::cin.ignore();



                if( crow >NUMBERS_SIZE || crow < 0 ||
                    ccol >NUMBERS_SIZE || ccol < 0 ||
                    value>NUMBERS_SIZE || value< 0  )
                {
                    system("color 0c");
                    std::cout << "\n********** Wrong input **********\n";
                    system("pause");
                    return true;
                }

                if((n_array[crow][ccol]) != 0 && checkReplacablity(crow,ccol) || !checkReplacablity(crow,ccol) )
                {
                    system("color 0c");
                    std::cout << "\n********** Not allowed **********\n";
                    system("pause");
                    return true;
                }

                Valcord valcords = placeNum(crow,ccol);

                if(checkNum(value,valcords.bi*3,valcords.bj*3)&& checkNumPre(value,valcords.bi*3,valcords.bj*3,anotherRangecheck(crow),anotherRangecheck(ccol)))
                {
                    ///adding to n_array
                    n_array[crow][ccol] = value;
                    ///Clearing main array
                    makeItZeroArray();
                    ///Adding to array main
                    addNumber();
                }else{
                    std::cout << "\n**********!!! Number already exists !!!**********" << std::endl;
                    system("color 0c");
                    system("pause");
                }
                return true;
        }

        case'c':{
            ///Check if Won or not

            for(int i=0;i<NUMBERS_SIZE;i+=3){
                for(int j=0;j<NUMBERS_SIZE;j+=3){
                    if(checkZero(i,j)){
                        _won = false;
                        system("color 04");
                        std::cout << "!!!!!!!! Nop !!!!!!\n";
                        system("pause");
                        return true;
                    }
                }
            }
        }

        case'r':
        {
            ///Reset game / new Game?
            std::cout << "Are ya restarting son?\ny-Yes\n";
            char option ='\0';
            std::cin >> option;
            if('y' == tolower(option))
                return false;

        };

        case 'a':
        {
            system("cls");
            system("color 02");

            displayAnswer();

            system("pause");
            return true;
        }

        case 'w':
        {
            if(gameWin())
            {
                _dontquit =false;

                system("color 02");

                std::cout << "\n\n\n__________________________________________________________________\n";
                std::cout << "-----------SUDOKU-----------SUDOKU-----------SUDOKU---------------\n";
                std::cout << "-----------SUDOKU-----------SUDOKU-----------SUDOKU---------------\n";
                std::cout << "------------------------------------------------------------------\n";

                std::cout << "************************************************WINNER************\n";
                std::cout << "******************************************************WINNER******\n";
                std::cout << "*****WINNER******                WINNER         ******************\n";
                std::cout << "***************** WINNER                        ******************\n";
                std::cout << "*****************       WINNER         WINNER   ******************\n";
                std::cout << "*****WINNER*******************************************WINNER******\n";
                std::cout << "******************************WINNER******************************\n";

                std::cout << "------------------------------------------------------------------\n";
                std::cout << "------------------------------------------------------------------\n";
                std::cout << "__________________________________________________________________\n";


                system("pause");
                return false;
            }

            system("cls");
            system("color 40");
            std::cout << "\n\n\n!!!!!! No keep going !!!!!!\n\n";
            system("pause");
            return true;

        };

    }

    ///Still in the current game
    return 1;
}


 void Sudoku::makeItZero()
 {
    for(int r=1;r<_rows-1 ;r++)
    {
        if((r%4 == 0))continue;
        for(int c=1;c<_cols-1;c++)
        {
            if( ((c%8 == 0)||((c+1)%2 == 0)))continue;
                array[r][c] = 0;
        }
    }

    ///Make n_array have zeros
    for (int i = 0; i < NUMBERS_SIZE; i+=3)
     {
        for (int j = 0; j < NUMBERS_SIZE; j+=3)
        {
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    n_array[r+i][c+j] = 0;
                }
            }
        }
     }
}

bool Sudoku::checkNum(int& random,int i,int j)
{
    ///i -- big square column. j-- big square row
    for(int r=0;r < NUMBERS_SIZE/3; r++)
        for(int c=0;c < NUMBERS_SIZE/3; c++)
            if(n_array[r+i][c+j] == random)
                return 0;
    return 1;
}

void Sudoku::addNumber()
{
    int i=-1;
    int j=0;

    for(int r=0;r < _rows; r++)
    {
        if(((r%4) != 0))i++;
        for(int c=0;c < _cols; c++)
        {
            if(array[r][c] == 0)
                array[r][c] = n_array[i][j++];
        }
        if(j == NUMBERS_SIZE) j=0;
        if(i == NUMBERS_SIZE) i=0;
    }
}

bool Sudoku::checkNumPre(int random,int bi,int bj,int cr,int cc)
{
    if(rangeCheck(cr+bi) == 1 && rangeCheck(cc+bj) == 1)
        return true;
     for (int i = 0; i <= bi; i+=3)
     {
        for (int j = 0; j <= bj; j+=3)
        {
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    //Check if in same column
                    if((bj == j && (bj+cc)%3 == (j+c)%3) || (bi+cr) == (i+r) )
                        if(n_array[i+r][j+c] == random)
                            return false;

                    //For checking if numbers are the same in a num's row
                    if((cr+bi)==r+i && bi==i && (bj+cc) != (j+c))
                    {
                        if(n_array[i+r][j+c] == random){
                            return false;
                        }
                    }
                }

            }
        }
    }

    return true;
}

/*
bool Sudoku::findNums(int random,int bi,int bj,int cr,int cc)
{

   // if((bi) != 6  && bj != 0)return false;
    std::vector<int> vNums;
    system("cls");


    for (int i = 0; i <=bi; i+=3)
     {
        for (int j = 0; j <=bj; j+=3)
        {
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    //if((i) == 0 && (bi) == 0 && (j) == 0 && (bj) == 0)continue;
                    //Check if in same column
                    if(bj == j && (bj+cc)%3 == (j+c)%3 || (bi+cr) == (i+r) )
                    {
                       std::cout << n_array[bi+cr][bj+cc] << "\t" << n_array[i+r][j+c] << std::endl;
                       vNums.push_back(n_array[i+r][j+c]);
                    }

                    //For checking if numbers are the same in a num's row
                    else if((cr+bi)==r+i && bi==i && (bj+cc) != (j+c))
                    {
                        std::cout << n_array[bi+cr][bj+cc] << "\t" << n_array[i+r][j+c] << std::endl;
                        vNums.push_back(n_array[i+r][j+c]);
                    }
                }

            }
        }
    }

        std::cout << n_array[bi+cr][bj+cc] <<"=rand Coord(" << bj+cc<<','<<bi+cr<<')'<<std::endl << std::endl;
system("pause");
    system("cls");
    //std::sort(vNums.begin(),vNums.end());
    for(int i=0;i<vNums.size();i++)
    {
        std::cout <<  i << "is :"<< vNums[i] << std::endl<< std::endl;

    }
    std::cout << "---SIZE()---:" << vNums.size() << std::endl<< std::endl;
    std::cout << n_array[bi+cr][bj+cc] <<"rand Coord(" << bi+cr<<','<<bj+cc<<')'<<std::endl << std::endl;
    system("pause");
    return false;

}*/


int Sudoku::anotherRangecheck(int value)
{
    if(value == 0 ||  value == 3 || value == 6)
        return 0;
    else if(value == 1 || value == 4 || value == 7)
        return 1;
    else if(value == 2 || value == 5 || value == 8)
        return 2;

    return -2;
}


int Sudoku::rangeCheck(int value)
{
    if(value == 0 ||  value == 1 || value == 2)
        return 1;
    else if(value == 3 || value == 4 || value == 5)
        return 2;
    else if(value == 6 || value == 7 || value == 8)
        return 3;

    return -2;
}

bool Sudoku::makeNumber()
{

    ///Adds zeros array[][] & n_array[][]
    makeItZero();

    auto checkVector =[&](Valcord newStr)->bool{
        for(int i=0;i<9*9;i++)
        {
            if(_nEmp[i].crow == newStr.crow
            && _nEmp[i].ccol == newStr.ccol)
            {
                return false;
            }
        }
        return true;
    };

    int RandNofNum= 0;
    int countRand = 0;
    int index =0;
    int loops=0;

    ///This is where the numbers are put into the array accordingly
    for(int i=0;i < NUMBERS_SIZE; i+=3)
    {
        for(int j=0;j < NUMBERS_SIZE; j+=3)
        {
            RandNofNum = Random(1,7);

            RandNofNum = RandNofNum -_hardMode < 0? 0: RandNofNum;
            countRand =0;
            while(checkZero(i,j))
            {
                for(int r=0;r < NUMBERS_SIZE/3; r++)
                {
                    for(int c=0;c < NUMBERS_SIZE/3; c++)
                    {
                        int random = Random(1, 9);
                        if((checkNum(random,i,j) && checkNumPre(random,i,j,r,c) )){
                            n_array[r+i][c+j] = random;
                            countRand++;
                        }
                        else if(checkVector({i,j,r+i,c+j}) )
                        {
                            _nEmp[index++]={i,j,r+i,c+j};
                            random =-1;
                        }
                        else
                            random =-1;
                        ///If itirations reach 10 000 that means the sudoku is unsolvable
                        if(++loops >= (10000))
                            return true;
                    }
                }
            }

        }
    }
    //checkAnother();
    ///Store the correct solutin before putting zeros
    addNumber();
    storeAnswer(_answer);
    ///Removes from array
    makeItZeroArray();

    ///Done
    return false;
}

void Sudoku::displayAnswer()
{
    std::cout << _answer;
}

///Stores answer to sudoku!!
void Sudoku::storeAnswer(std::string& _answer)
{
    _answer ="";
   for(int r=0;r<_rows;r++)
    {
        for(int c=0;c<_cols;c++)
        {
            ///Displays Space,Plus,line,player,minus, and NUMBERs respectively
            if(array[r][c] == SPACE && !(r%4 == 0) && !(r == _rows - 1 || r == 0))
                _answer += obj[0] ;
            else if(array[r][c] == PLUS)
            {
                if(r == 0 && c == 0)
                {
                    _answer += obj[7];
                }
                else if(r == 0 && c == _cols-1)
                {
                    _answer += obj[13];
                }
                else if(r == _rows-1 && c == 0)
                {
                    _answer += obj[6];
                }
                else if(r == _rows-1 && c == _cols-1)
                {
                    _answer += obj[14];
                }
                //Sides
                else if(!(r ==0 || r ==_rows-1) && c == 0)
                {
                    _answer += obj[10];
                }
                else if(!(r ==0 || r ==_rows-1) && c == _cols-1)
                {
                    _answer += obj[12];
                }

                else if(!(c ==0 || c ==_cols-1) && r==0)
                {
                    _answer += obj[9];
                }
                else if(!(c ==0 || c ==_cols-1) && r==_rows-1)
                {
                    _answer += obj[8];
                }

                //Middle
                else if(!(r ==0 || r ==_rows-1) && !(c ==0 || c ==_cols-1))
                {
                    _answer += obj[11];
                }
            }
            else if(array[r][c] == LINE )
                _answer += obj[3] ;
            else if(array[r][c] == MINUS || r%4 == 0)
                _answer += obj[2] ;
            else
            {
            if(array[r][c]>=0 && array[r][c]<=9)
            {
                if(array[r][c] == 0)
                    _answer += '-';
                else
                {
                    std::stringstream ss;
                    ss << array[r][c];

                    _answer += ss.str();
                }
            }
            else
                _answer +=obj[5];
            }
        }
        _answer+='\n';
    }
}


void Sudoku::putZeros()
{
    int RandNofNum = 0;
    int countRand =0;
    for(int i=0;i < NUMBERS_SIZE; i+=3)
    {
        for(int j=0;j < NUMBERS_SIZE; j+=3)
        {
            RandNofNum = Random(1,8);
            ///Testing for difficulty level
            RandNofNum = RandNofNum -_hardMode < 0? 0: RandNofNum;
            countRand =0;
            while(countRand <= RandNofNum)
            {
                for(int r=0;r < NUMBERS_SIZE/3; r++)
                {
                    for(int c=0;c < NUMBERS_SIZE/3; c++)
                    {
                        if(Random(1,(_hardMode/4)) == 1) n_array[i+r][(3*Random(0,2)) + Random(0,2)] = 0;
                        ++countRand;
                    }
                }
            }
        }
    }
}

bool Sudoku::checkAnother()
{
    for(int i=0;i<9*9;i++)
    {
        if(!(_nEmp[i].bi != -1 || _nEmp[i].bj != -1 || _nEmp[i].ccol != -1 || _nEmp[i].crow != -1 ))continue;
        if(n_array[_nEmp[i].crow][_nEmp[i].ccol] == 0)continue;

        _nEmp[i] = {-1,-1,-1,-1};
    }
    return true;
}

void Sudoku::tempRender()
{
    std::cout << "~~~~ Complex loop ~~~~\n";
    for(int i=0;i < NUMBERS_SIZE; i+=3)
    {
        for(int j=0;j < NUMBERS_SIZE; j+=3)
        {
            for(int r=0;r < NUMBERS_SIZE/3; r++)
            {
                for(int c=0;c < NUMBERS_SIZE/3; c++)
                {
                    std::cout << n_array[r+i][c+j] << ' ';
                }std::cout << '\t' ;
            }std::cout << std::endl;
        }std::cout << std::endl;
    }
}

bool Sudoku::checkZero(int bi,int bj)
{
    ///TODO -- Make sure it doesnt do for the 'whole' array blocks at once
    for (int i = 0; i < NUMBERS_SIZE/3; i++)
        for (int j = 0; j < NUMBERS_SIZE/3; j++)
            if (n_array[i+bi][j+bj]==0)
                return 1;
    return 0;
}


Valcord Sudoku::placeNum(int row,int col)
{
    Valcord numData;
    numData.bi =rangeCheck(row)-1;
    numData.bj =rangeCheck(col)-1;

    numData.crow=-1;
    numData.ccol=-1;
    return numData;

}

void Sudoku::makeItZeroArray()
{
    for(int r=1;r<_rows-1 ;r++)
    {
        if((r%4 == 0))continue;
        for(int c=1;c<_cols-1;c++)
        {
            if( ((c%8 == 0)||((c+1)%2 == 0)))continue;
                array[r][c] = 0;
        }
    }
}

bool Sudoku::checkReplacablity(int crow,int ccol)
{
    for(int i=0;i<9*9;i++)
        if( crow == _nEmp[i].crow &&
            ccol == _nEmp[i].ccol)
            return false;

    return true;
}
bool Sudoku::gameWin()
{
    std::string playeranswer="";
    storeAnswer(playeranswer);
    ///Won!!!
    if(_answer == playeranswer)
        return true;
    ///Have not won
    return false;
}
Sudoku::~Sudoku(){}
