#include <iostream>
#include "RubiksCube.h"

int *findPiece(Cube, char, char);

void leftTrigger(Cube, int);
void rightTrigger(Cube, int);

void whiteCross(Cube);
void FirstLayer(Cube);
void SecondLayer(Cube);


int *findPiece(Cube, char firstColor, char secondColor)
{
    int array[3];

    // Find the piece

    return array;
}

void whiteCross(Cube cube)
{
    
}

int main()
{
    Cube cube1;

    cube1.log = true;
    cube1.scramble(20);
    cube1.movefile << "-------------------" << std::endl;
    cube1.printCube();
    cube1.resetOrientation();
    
    cube1.printCube();
    
    return 0;
}