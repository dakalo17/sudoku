#include "Sudoku.h"
#include <time.h>
#include <random>
#include <iostream>

int main()
{
    srand(time(nullptr));
	///Space
    Sudoku sudoku;

    sudoku.Run();

    return 0;
}
