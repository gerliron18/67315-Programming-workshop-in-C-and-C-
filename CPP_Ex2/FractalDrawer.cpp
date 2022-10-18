/**
 * @file FractalDrawer.cpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 08 Jan 2020
 *
 * @brief A program that can print to the screen fractals from three different types and six
 * different dimensions according to 'csv' file given by the user with int instructions.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will read instructions from the given file, generates fractals according to it
 * and print them to the screen in opposite order according to the exercise instructions.
 * Input  : 'csv' file with int instructions of what fractal type and in which dimension
 *          to generate and print back.
 * Process: Generating all needed fractals and keep them as objects that hold their representations
 *          in vector containers.
 * Output : Print to the screen all needed fractals as it writen in the exercise instructions.
 */

// ------------------------------ includes ------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include "Fractal.h"
#include <boost/tokenizer.hpp>

// -------------------------- const definitions -------------------------

/*
 * @def VALID_ARG_NUM 2
 * @brief The valid number of arguments needed to be transfered to the program when called.
 */
#define VALID_ARG_NUM 2


/*
 * @def CSV "csv"
 * @brief A string representation of 'csv' file suffix.
 */
#define CSV "csv"

/*
 * @def MAX_NUM_OF_DIMENSION 6
 * @brief The max number of valid dimensions of a fractal
 */
#define MAX_NUM_OF_DIMENSION 6

/*
 * @def USAGE_ERR_MSG "Usage: FractalDrawer <file path>"
 * @brief An usage error message that will be printed if user not using the program correctly
 */
#define USAGE_ERR_MSG "Usage: FractalDrawer <file path>"

/*
 * @def INVALID_INPUT_MSG "Invalid input"
 * @brief An error message if one of the input instructions or the file itself is invalid
 */
#define INVALID_INPUT_MSG "Invalid input"

/*
 * @def CARPET_TYPE 1
 * @brief A carpet fractal type int representations at the input file
 */
#define CARPET_TYPE 1

/*
 * @def TRIANGLE_TYPE 2
 * @brief A triangle fractal type int representations at the input file
 */
#define TRIANGLE_TYPE 2

/*
 * @def VICSEK_TYPE 3
 * @brief A vicsek fractal type int representations at the input file
 */
#define VICSEK_TYPE 3



// --------------------------- implementation ---------------------------


/**
 * A function that called if there is an invalid input in any step of the program running,
 * will print an error msg to the screen and exit the program.
 */
void inputErrorExit()
{
    std::cerr << INVALID_INPUT_MSG << std::endl;
    exit(EXIT_FAILURE);
}


/**
 * A function that called if there is an invalid usage of the program when initiate,
 * will print an error msg to the screen and exit the program.
 */
void usageErrorExit()
{
    std::cerr << USAGE_ERR_MSG << std::endl;
    exit(EXIT_FAILURE);
}


/**
 * A function that check the given path of the input file. Check if it is a 'csv' suffix file
 * and if it exist and readable.
 * @param fileName The given path to an input file.
 * @return True if the given file is valid, False otherwise
 */
bool fileChecks(const char *fileName)
{
    std::string fileNameStr = fileName;

    if(fileNameStr.substr(fileNameStr.find_last_of('.') + 1) == CSV)
    {
        std::ifstream infile(fileName);
        return infile.good();
    }
    return false;
}


/**
 * A function that check if given string represents a valid number.
 * @param string The given string that as to be checked
 * @return 1 if the string represent a valid number, 0 otherwise
 */
int numCheck(const std::string& string)
{
    int flag = 0;
    int count = 0;

    for(auto c : string)
    {
        if(!isdigit(c))
        {
            if (isspace(c) && flag && count == 0)
            {
                count++;
                continue;
            }
            return 0;
        }

        flag++;
        if(flag > 1 || count > 1)
        {
            return 0;
        }
    }

    return 1;
}


/**
 * A function that check if the given arguments to the program are valid to its function.
 * Will use other function to validate it.
 * @param argNum The number of arguments given by the user
 * @param filePath A path to a 'csv' file
 */
void checkArguments(const int argNum, const char *filePath)
{
    if (argNum != VALID_ARG_NUM)
    {
        usageErrorExit();
    }

    if(!fileChecks(filePath))
    {
        inputErrorExit();
    }
}


/**
 * A function the generates new fractal according to given type and dimension
 * @param type The type of the fractal
 * @param dimension The dimension of the fractal
 * @return A pointer to a Fractal type object with the given properties
 */
Fractal* findFractal(int type, int dimension)
{
    if(type == CARPET_TYPE)
    {
        return new Carpet(dimension);
    }

    if(type == TRIANGLE_TYPE)
    {
        return new Triangle(dimension);
    }

    if(type == VICSEK_TYPE)
    {
        return new Vicsek(dimension);
    }

    return nullptr;
}


/**
 * A function that check given instruction from the input file.
 * Will check if the type of the fractal is valid and if the dimension is valid.
 * @param type The fractal type needed to be construct
 * @param dimension The dimension of the fractal needed to be construct
 */
void checkData(int type, int dimension)
{
    if(type != CARPET_TYPE && type != TRIANGLE_TYPE && type != VICSEK_TYPE)
    {
        inputErrorExit();
    }

    if(dimension < 1 || dimension > MAX_NUM_OF_DIMENSION)
    {
        inputErrorExit();
    }
}


/**
 * A printer function of all needed fractals from the file in opposite order.
 * Will also delete all allocated memory after printing each fractal.
 * @param fractalVec A vector that hold pointers to fractals needed to be print to the screen
 */
void printAndDelete(std::vector<Fractal*> fractalVec)
{
    for(int i = (int) fractalVec.size() - 1 ; i >= 0 ; i--)
    {
        fractalVec[i]->fractalPrinter();
        delete fractalVec[i];
    }
}


/**
 * A parsing function of the given 'csv' file, will use other function to read and parse the
 * data from the given file, generate the appropriate fractals and save them in a vector container.
 * @param fractalVec A vector container for the fractals
 * @param filePath The path to the 'csv' file
 * @return The vector container that include all the fractal needed to be print
 */
std::vector<Fractal*> parseFile(std::vector<Fractal*>& fractalVec, const char *filePath)
{
    std::ifstream infile(filePath);
    std::vector<std::string> inputData;
    std::string line;

    infile.seekg(0, std::ios::end);
    line.reserve(infile.tellg());
    infile.seekg(0, std::ios::beg);

    int errorFlag = 0;

    while(std::getline(infile, line))
    {
        if(errorFlag)
        {
            inputErrorExit();
        }
        if(line == "," || line.empty())
        {
            errorFlag++;
            continue;
        }

        boost::char_separator<char> comma{","};
        boost::tokenizer<boost::char_separator<char>> tok{line, comma};
        inputData.assign(tok.begin(), tok.end());

        if(inputData.size() != 2)
        {
            inputErrorExit();
        }

        if(!numCheck(inputData[0]) || !numCheck(inputData[1]))
        {
            inputErrorExit();
        }

        int type = std::stoi(inputData[0]);
        int dimension = std::stoi(inputData[1]);
        checkData(type, dimension);

        fractalVec.push_back(findFractal(type, dimension));
    }

    infile.close();
    return fractalVec;
}


/**
 * The main function of the program, will parse the instructions from the given file and use other
 * functions and classes to generate the needed fractals and than finally print them to the
 * screen in opposite order according to the exercise instructions.
 * @param argc The number of arguments given to the program
 * @param argv A vector of the arguments given to the program
 * @return EXIT_SUCCESS if the program run properly, will raise an error msg and exit the program
 *         otherwise
 */
int main(int argc, char *argv[])
{
    checkArguments(argc, argv[1]);

    std::vector<Fractal*> fractalVec;

    fractalVec = parseFile(fractalVec, argv[1]);

    printAndDelete(fractalVec);

    fractalVec.clear();

    return EXIT_SUCCESS;
}
