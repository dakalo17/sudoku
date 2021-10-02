#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <string.h>

static const int DEFAULT_ROWS=12 + 1;
static const int DEFAULT_COLS=24 + 1;

static const int NUMBERS_SIZE=9;
static const char obj[] = {'\0','+',(char)205,(char)186,'~','@',(char)200,(char)201,(char)202,(char)203,(char)204,(char)206,(char)185,(char)187,(char)188};
///static const char obj[] = {'\0','+','-','|','~','@'};
enum FEATURES
{
    SPACE=10,
    PLUS,
    MINUS,
    LINE,
    TILDA,
    PLAYER=50
};
struct Valcord
{
    int bi;
    int bj;

    int crow;
    int ccol;
};

class Sudoku
{
public:
    Sudoku();
    Sudoku(int,int);
    void Run();


    ///Holds the structure of the games and the numbers will be added from n_array
    int array[DEFAULT_ROWS][DEFAULT_COLS];

    ///Only holds the 9 by 9 array of sudoku numbers
    int n_array[NUMBERS_SIZE][NUMBERS_SIZE];
private:
    ///stores completed sudoku
    //int a_array[NUMBERS_SIZE][NUMBERS_SIZE];
    std::string _answer;
    ///Hold coords of empty spaces/0s in n_array
    Valcord _nEmp[NUMBERS_SIZE*NUMBERS_SIZE];

    int _hardMode;
    bool _won;
    bool _dontquit;

    int _rows;
    int _cols;

    int _prow;
    int _pcol;

    ///Puts the randomized number(s) into the n_array accordingly
    bool makeNumber();
    ///Puts zero's in n_array after n_array has valid sudoku puzzle
    void putZeros();
    ///Checks if there are zeros in n_array
    bool checkZero(int,int);
    void addNumber();
    ///Checks if a number is repeating in n_array
    bool checkNum(int&,int,int);

    ///USELESS
    bool checkIndex(int,int);
    void showLogo(void);
    ///Checks if a number violates the 'rules'of sudoku,i.e matching of rows
    bool checkNumPre(int random,int bi,int bj,int cr,int cc);
    ///Just generalizes numbers (1,9) into (1,3)
    int rangeCheck(int);
    ///Util method
    void LoadingGame();
    ///Makes var (array[][] and n_array) have zeros everywhere
    void makeItZero();
    ///Makes var array[][] have zeros everywhere
    void makeItZeroArray();
    ///main OUTPUT
    void Render();
    ///~~Test output
    void tempRender();

    ///Interface where input is managed,placing number,or exiting game
    bool MovePlayer();
    ///Useless for now
    bool checkPlayerPos(int,int);
    int Random(int,int);

    ///Plyer enteres numbers
    Valcord placeNum(int,int);

    ///Checks replacabilty
    bool checkReplacablity(int,int);

    bool checkAnother();
    //Util method
    int anotherRangecheck(int);

    ///Copies n_array into a_array
    std::string storeAnswer(std::string&);
    ///Displays answer
    void displayAnswer();

    ///Option UI
    void InitOption();
    bool movePlayerLoop();
    ///Places the char(s) to the grid
    void placeStuff(const int&,const int&);

    ///Checks if game is won
    bool gameWin();
    ///Usless for now
    bool findNums(int,int,int,int,int);
};
