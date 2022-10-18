/**
 * @file Fractal.cpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 08 Jan 2020
 *
 * @brief Definition of a Fractal base class and three different types of fractals classes
 * that inherit from it.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program can construct a Fractal from any of the three types and can preform operations
 * on each type in any valid dimension.
 * Input  :
 * Process:
 * Output :
 */


// ------------------------------ includes ------------------------------
#include <iostream>
#include <cmath>
#include "Fractal.h"


// -------------------------- const definitions -------------------------

/*
 * @def SPACE ' '
 * @brief A space char representation
 */
#define SPACE ' '

/*
 * @def POUND '#'
 * @brief A pound char representation
 */
#define POUND '#'

/*
 * @def CARPET_INIT_SIZE 3
 * @brief The initialize grid size (nXn) of carpet type fractal
 */
#define CARPET_INIT_SIZE 3

/*
 * @def CARPET_INIT_GRID {{POUND, POUND, POUND}, {POUND, SPACE, POUND}, {POUND, POUND, POUND}}
 * @brief The initialize grid from size 3X3 of carpet type fractal
 */
#define CARPET_INIT_GRID {{POUND, POUND, POUND}, {POUND, SPACE, POUND}, {POUND, POUND, POUND}}

/*
 * @def TRIANGLE_INIT_SIZE 2
 * @brief The initialize grid size (nXn) of triangle type fractal
 */
#define TRIANGLE_INIT_SIZE 2

/*
 * @def TRIANGLE_INIT_GRID {{POUND, POUND}, {POUND, SPACE}}
 * @brief The initialize grid from size 2X2 of triangle type fractal
 */
#define TRIANGLE_INIT_GRID {{POUND, POUND}, {POUND, SPACE}}

/*
 * @def VICSEK_INIT_SIZE 3
 * @brief The initialize grid size (nXn) of vicsek type fractal
 */
#define VICSEK_INIT_SIZE 3

/*
 * @def VICSEK_INIT_GRID {{POUND, SPACE, POUND}, {SPACE, POUND, SPACE}, {POUND, SPACE, POUND}}
 * @brief The initialize grid from size 3X3 of vicsek type fractal
 */
#define VICSEK_INIT_GRID {{POUND, SPACE, POUND}, {SPACE, POUND, SPACE}, {POUND, SPACE, POUND}}


// ------------------------ class implementation ------------------------

/**
 * Explicit constructor of Fractal object that gets the fractal dimension.
 * @param dim The dimension of the fractal we would like to construct
*/
Fractal::Fractal(int &dim)
{
    dimension = dim;

    std::vector<char> oneDimGrid(1 , SPACE);
    std::vector<std::vector<char>> oneDimGridVec(1 , oneDimGrid);
    initFractal = oneDimGridVec;

    std::vector<char> grid(dimension, SPACE);
    std::vector<std::vector<char>> gridVec(dimension, grid);
    finalFractal = gridVec;
}

/**
 * Printer function of a fractal object, will print to the screen the current fractal
 * according to the exercise instructions.
*/
void Fractal::fractalPrinter()
{
    for(int i = 0 ; i < finalGridSize ; i++)
    {
        for(int j = 0 ; j < finalGridSize ; j++)
        {
            if(finalFractal[i][j] == POUND)
            {
                std::cout << POUND;
            }
            else if(finalFractal[i][j] == SPACE)
            {
                std::cout << SPACE;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * A recursive function that helps the generator function to generate the fractal vectors with
 * the appropriate char at any index according to the initialize grid of each fractal type.
 * @param rowNum The current fractal row
 * @param colNum The current fractal column
 * @param dim The current dimension of the fractal the function generates
*/
void Fractal::generateFractalHelper(const int &rowNum, const int &colNum, int dim)
{
    int row = rowNum;
    int column = colNum;

    if(dim == 0)
    {
        finalFractal[row][column] = POUND;
        return;
    }

    int index = (int) pow(initGridSize, dim - 1);

    for(int i = 0 ; i < initGridSize ; i++)
    {
        column = colNum;
        for(int j = 0 ; j < initGridSize ; j++)
        {
            if(initFractal[i][j] == POUND)
            {
                generateFractalHelper(row, column, dim - 1);
            }

            column += index;
        }
        row += index;
    }
}


/**
 * A generator for fractal vectors according to fractal type and dimension.
 * Uses helper recursive function.
 * @param dim The current dimension of the fractal the function generates
*/
void Fractal::generateFractal(int dim)
{
    generateFractalHelper(0 , 0 , dim);
}


/**
 * Explicit constructor of carpet type Fractal object that gets the fractal dimension.
 * @param dimension The dimension of the carpet fractal we would like to construct
*/
Carpet::Carpet(int &dimension) : Fractal(dimension)
{
    initGridSize = CARPET_INIT_SIZE;
    finalGridSize = (int) pow(initGridSize, dimension);

    initFractal = CARPET_INIT_GRID;

    std::vector<char> grid(finalGridSize, SPACE);
    std::vector<std::vector<char>> gridVec(finalGridSize, grid);
    finalFractal = gridVec;

    generateFractal(dimension);
}


/**
 * Explicit constructor of triangle type Fractal object that gets the fractal dimension.
 * @param dimension The dimension of the triangle fractal we would like to construct
*/
Triangle::Triangle(int &dimension) : Fractal(dimension)
{
    initGridSize = TRIANGLE_INIT_SIZE;
    finalGridSize = (int) pow(initGridSize, dimension);

    initFractal = TRIANGLE_INIT_GRID;

    std::vector<char> grid(finalGridSize, SPACE);
    std::vector<std::vector<char>> gridVec(finalGridSize, grid);
    finalFractal = gridVec;

    generateFractal(dimension);
}


/**
 * Explicit constructor of vicsek type Fractal object that gets the fractal dimension.
 * @param dimension The dimension of the vicsek fractal we would like to construct
*/
Vicsek::Vicsek(int &dimension) : Fractal(dimension)
{
    initGridSize = VICSEK_INIT_SIZE;
    finalGridSize = (int) pow(initGridSize, dimension);

    initFractal = VICSEK_INIT_GRID;

    std::vector<char> grid(finalGridSize, SPACE);
    std::vector<std::vector<char>> gridVec(finalGridSize, grid);
    finalFractal = gridVec;

    generateFractal(dimension);
}
