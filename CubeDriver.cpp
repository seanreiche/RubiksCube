#include <iostream>
#include "RubiksCube.h"


void enterMove(Cube *cube)
{
    char move;
    std::cout << "\nPlease enter move. Type letter of move, uppercase for normal, lowercase for prime.\nExample:\nF -- front\nf -- front prime\n" << std::endl;

    std::cin >> move;

    //std::cout << move << std::endl;

    
    switch (move)
    {
        case 'U':
            cube->U();
            break;

        case 'u':
            cube->U_prime();
            break;

        case 'D':
            cube->D();
            break;

        case 'd':
            cube->D_prime();
            break;

        case 'F':
            cube->F();
            break;

        case 'f':
            cube->F_prime();
            break;

        case 'L':
            cube->L();
            break;

        case 'l':
            cube->L_prime();
            break;

        case 'R':
            cube->R();
            break;

        case 'r':
            cube->R_prime();
            break;

        case 'B':
            cube->B();
            break;

        case 'b':
            cube->B_prime();
            break;
        
        case 'X':
            cube->x();
            break;

        case 'x':
            cube->x_prime();
            break;

        case 'Y':
            cube->y();
            break;

        case 'y':
            cube->y_prime();
            break;

        case 'Z':
            cube->z();
            break;

        case 'z':
            cube->z_prime();
            break;

        default:
            std::cout << "Please enter a valid move\n" << std::endl;
            break;
    }
}

int menu(Cube *cube)
{
    std::string opt;
    int option = -1;

    while (true)
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Enter Move" << std::endl;
        std::cout << "2. Print Cude" << std::endl;
        std::cout << "3. Exit" << std::endl;

        std::cin >> opt;
        
        try
        {
            option = std::stoi(opt);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "please enter a valid input" << std::endl;
            continue;
        }
        
        //std::cout << option << std::endl;

        switch (option)
        {
        case 1:
            enterMove(cube);
            break;

        case 2:
            cube->printCube();
            break;

        case 3:
            return 0;
            
        default:
            return 1;
        }
    }

}

int main()
{
    Cube cube;
    menu(&cube);
    return 0;
}