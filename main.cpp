#include "Sudoku.h"
#include <time.h>
#include <random>
#include <iostream>

void ra();

int main()
{
    srand(time(nullptr));
	///Space
    Sudoku sudoku;

    sudoku.Run();

//ra();
    return 0;
}

void ra(){
int i=-1;
    int j=0;

Sudoku s;
system("cls");
    for(int r=0;r < 13; r++)
    {
        if(((r%4) != 0))i++;
        for(int c=0;c < 25; c++)
        {
            if(s.array[r][c] == 0)
                std::cout<<j++<<std::endl;
        }
        if(j == 9) j=0;
        if(i == 9) i=0;
    }}
