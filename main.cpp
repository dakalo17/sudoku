#include "Sudoku.h"
#include <time.h>
#include <random>
#include <iostream>
using namespace std;

int main()
{
    srand(time(nullptr));
    Sudoku sudoku;

    sudoku.Run();

    return 0;
}
