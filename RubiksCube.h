#pragma once

#include <iostream>
#include <random>
#include <fstream>

class Cube
{
public:
    bool log = false;
    std::ofstream movefile;

    char cube[6][3][3] = 
    {
        {
            {'Y','Y','Y'}, // Top    0
            {'Y','Y','Y'},
            {'Y','Y','Y'}
        },
        {
            {'B','B','B'}, // Front  1
            {'B','B','B'},
            {'B','B','B'}
        },
        {
            {'O','O','O'}, //        2
            {'O','O','O'},
            {'O','O','O'},
        },
        {
            {'G','G','G'}, // Back   3  Its upright with the side faces (1 2 3 4)
            {'G','G','G'},
            {'G','G','G'}
        },
        {
            {'R','R','R'}, //        4
            {'R','R','R'},
            {'R','R','R'}
        },
        {
            {'W','W','W'}, // Bottom 5
            {'W','W','W'},
            {'W','W','W'}   
        }
    };

    ~Cube()
    {
        if (movefile.is_open())
        {
            movefile.close();
        }
    }

    // Used for temporary storage
    char tmp[3][3] = 
    {
        {'a','a','a'},
        {'a','a','a'},
        {'a','a','a'}
    };

    void resetCube()
    {
        char letters[6] = {'Y', 'B', 'O', 'G', 'R', 'W'};

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cube[i][j][k] = letters[i];
                }
            }
        }
    }

    void printCube()
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    std::cout << cube[i][j][k] << " ";
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;
        }
    }

    void copyFace(int face)
    {   
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tmp[i][j] = cube[face][i][j];
            }
        }
    }

    void U()
    {
        int face = 0;
        int tmpFace = 4;

        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate top face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 4; i > 1; i--) // Move the top rows of each face
        {
            for (int j = 0; j < 3; j++)
            {
                cube[i][0][j] = cube[i - 1][0][j];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            cube[1][0][i] = tmp[0][i];
        }

        logMove('U');    

    }

    void U_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            U();
        }
    }

    void D()
    {
        int face = 5;
        int tmpFace = 1;
        
        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate bottom face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 1; i < 4; i++) // Move the bottom rows of each face 
        {
            for (int j = 0; j < 3; j++)
            {
                cube[i][2][j] = cube[i + 1][2][j];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            cube[4][2][i] = tmp[2][i];
        }

        logMove('D');       
    }

    void D_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            D();
        }
    }

    void F()
    {
        int face = 1;
        int tmpFace = 2;
        
        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate front face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 0; i < 3; i++) // move pieces from face 5 to 2 (bottom to left)
        {
            cube[2][i][2] = cube[5][0][i];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 4 to 5 (right to bottom)
        {
            cube[5][0][i] = cube[4][2 - i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 0 to 4 (top to right)
        {
            cube[4][i][0] = cube[0][2][i];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 2 to 0 (tmp left to top)
        {
            cube[0][2][i] = tmp[2 - i][2];
        }

        logMove('F');
    }

    void F_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            F();
        }
    }

    void B()
    {
        int face = 3;
        int tmpFace = 4;
        
        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate back face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 0; i < 3; i++) // move pieces from face 5 to 4 (bottom to right)
        {
            cube[4][2 - i][2] = cube[5][2][i];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 2 to 5 (left to bottom)
        {
            cube[5][2][i] = cube[2][i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 0 to 2 (top to left)
        {
            cube[2][i][0] = cube[0][0][2 - i];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 4 to 0 (tmp right to top)
        {
            cube[0][0][i] = tmp[i][2]; 
        }
            
        logMove('B');
    }

    void B_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            B();
        }
    }

    void L()
    {
        int face = 2;
        int tmpFace = 3;
        
        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate left face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 0; i < 3; i++) // move pieces from face 5 to 3 (bottom to back)
        {
            cube[3][2 - i][2] = cube[5][i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 1 to 5 (front to bottom)
        {
            cube[5][i][0] = cube[1][i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 0 to 1 (top to front)
        {
            cube[1][i][0] = cube[0][i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 3 to 0 (back to top)
        {
            cube[0][i][0] = tmp[2 - i][2];
        }
            
        logMove('L');
    }

    void L_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            L();
        }
    }

    void R()
    {
        int face = 4;
        int tmpFace = 1;
        
        copyFace(face);

        for (int i = 0; i < 3; i++) // Rotate right face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[face][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(tmpFace);

        for (int i = 0; i < 3; i++) // move pieces from face 5 to 1 (bottom to front)
        {
            cube[1][i][2] = cube[5][i][2];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 3 to 5 (back to bottom)
        {
            cube[5][i][2] = cube[3][2 - i][0];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 0 to 3 (top to back)
        {
            cube[3][2 - i][0] = cube[0][i][2];
        }

        for (int i = 0; i < 3; i++) // move pieces from face 1 to 0 (front to top)
        {
            cube[0][i][2] = tmp[i][2];
        }
            
        logMove('R');       
    }

    void R_prime()
    {
        for(int i = 0; i < 3; i++)
        {
            R();
        }
    }

    void x()
    {        
        copyFace(3);

        for (int i = 0; i < 3; i++) // face 0 to 3 (top to back)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[3][i][j] = cube[0][2 - i][2 - j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 1 to 0 (front to top)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[0][i][j] = cube[1][i][j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 5 to 1 (bottom to front)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[1][i][j] = cube[5][i][j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 3 to 5 (tmp back to bottom)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[5][2 - i][2 - j] = tmp[i][j];
            }    
        }

        copyFace(2);

        for (int i = 0; i < 3; i++) // rotate left face counter clockwise 
        {
            for (int j = 0; j < 3; j++)
            {
                cube[2][i][j] = tmp[j][2 - i];
            }
        }
        
        copyFace(4);

        for (int i = 0; i < 3; i++)  // rotate right face clockwise 
        {
            for (int j = 0; j < 3; j++)
            {
                cube[4][i][j] = tmp[2 - j][i];
            }
        }

        logMove('x');
    }

    void y()
    {
        copyFace(1);

        for (int i = 0; i < 3; i++) // face 4 to 1 (right to front)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[1][i][j] = cube[4][i][j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 3 to 4 (back to right)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[4][i][j] = cube[3][i][j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 2 to 3 (left to back)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[3][i][j] = cube[2][i][j];
            }    
        }

        for (int i = 0; i < 3; i++) // face 1 to 2 (tmp front to left)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[2][i][j] = tmp[i][j];
            }    
        }

        copyFace(0);

        for (int i = 0; i < 3; i++) // rotate top face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[0][i][j] = tmp[2 - j][i];
            }
        }

        copyFace(5);

        for (int i = 0; i < 3; i++) // rotate bottom face counter clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[5][i][j] = tmp[j][2 - i];
            }
        }

        logMove('y');
    }

    void z()
    {
        copyFace(0);

        for (int i = 0; i < 3; i++) // face 2 to 0 (left to top)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[0][i][j] = cube[2][2 - j][i];
            }    
        }

        for (int i = 0; i < 3; i++) // face 5 to 2 (bottom to left)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[2][i][j] = cube[5][2 - j][i];
            }    
        }

        for (int i = 0; i < 3; i++) // face 4 to 5 (right to bottom)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[5][i][j] = cube[4][2 - j][i];
            }    
        }

        for (int i = 0; i < 3; i++) // face 0 to 4 (tmp top to right)
        {   
            for (int j = 0; j < 3; j++)
            {
                cube[4][i][j] = tmp[2 - j][i];
            }    
        }

        copyFace(1);

        for (int i = 0; i < 3; i++) // rotate front face clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[1][i][j] = tmp[2 - j][i];
            }
        }
        
        copyFace(3);

        for (int i = 0; i < 3; i++) // rotate back face counter clockwise
        {
            for (int j = 0; j < 3; j++)
            {
                cube[3][i][j] = tmp[j][2 - i];
            }
        }

        logMove('z');
    }

    void x_prime()
    {
        for (int i = 0; i < 3; i++)
        {
            x();
        }
    }

    void y_prime()
    {
        for (int i = 0; i < 3; i++)
        {
            y();
        }
    }

    void z_prime()
    {
        for (int i = 0; i < 3; i++)
        {
            z();
        }
    }

    void resetOrientation() // Yellow on top, blue in front
    {
        for (int i = 0; i < 4; i++) // See if blue is along the side
        {
            if (cube[1][1][1] == 'B')
            {
                break;
            }

            y();
        }

        if (cube[1][1][1] != 'B') // Checks if blue is on top or bottom
        {
            if (cube[0][1][1] == 'B') 
            {
                x_prime();
            }

            else if (cube[5][1][1] == 'B')
            {
                x();
            }
        }
        
        while (cube[0][1][1] != 'Y') // rotate it until yellow is in top
        {
            z();
        }
    }

    void logMove(char move) // Logs letter of move to file
    {
        if (log)
        {
            if (!movefile.is_open())
            {
                movefile.open("moves.txt", std::ofstream::out);
            }   
            
            movefile << move << std::endl;
        }
    }

    void scramble(int moves = 10)
    {
        int min = 0;
        int max = 11;

        std::srand(time(NULL));

        for (int i = 0; i < moves; i++)
        {
            int X = (rand() % 17);

            switch (X)
            {
                case 0:
                    U();
                    break;

                case 1:
                    D();
                    break;

                case 2:
                    F();
                    break;

                case 3:
                    B();
                    break;

                case 4:
                    L();
                    break;

                case 5:
                    R();
                    break;

                case 6:
                    U_prime();
                    break;

                case 7:
                    D_prime();
                    break;

                case 8:
                    F_prime();
                    break;

                case 9:
                    B_prime();
                    break;

                case 10:
                    L_prime();
                    break;

                case 11:
                    R_prime();
                    break;
                
                case 12:
                    x();
                    break;
                
                case 13:
                    y();
                    break;

                case 14:
                    z();
                    break;

                case 15:
                    x_prime();
                    break;
                
                case 16:
                    y_prime();
                    break;
                
                case 17:
                    z_prime();
                    break;

                default:
                    break;
            }
        }
    }
};

/*
Rotation Guide

           Y    
           |   Z
           |  /
           | /
           |/ 
-----------/----------- X  
          /|
         / |     
        /  | 
       /   |   
    Front  |
    
*/ // 764 lines