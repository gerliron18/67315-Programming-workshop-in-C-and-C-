/**
 * @file SpamDetector.cpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 20 Jan 2020
 *
 * @brief The program is a spam detector for any kind of text file.
 *        The user provides file that include some suspicious phrases and score
 *        for each one of them, a text file represent a message and a threshold number.
 *        The program will search for the suspicious phrases in the message
 *        and calculate final score- If the final score of the message is higher then
 *        the threshold given, the message will consider as spam, if not, not-spam.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program uses implementation of hash-map to save the database of suspicious phrases.
 * Input  : 1. Database file of suspicious phrases
 *          2. Message text file
 *          3. Threshold limitation
 * Process: Save the database into hash-map, calculate final score of the given message
 * Output : "SPAM" if the final score is higher then the given threshold, else "NOT-SPAM"
 */

// ------------------------------ includes ------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.hpp"

// -------------------------- const definitions -------------------------

/*
 * @def VALID_ARGS_NUM 4
 * @brief The valid number of arguments the user need to give to the program
 */
#define VALID_ARGS_NUM 4

/*
 * @def USAGE_ERR_MSG "Usage: SpamDetector <database path> <message path> <threshold>"
 * @brief An error message if the user doesn't use the program properly
 */
#define USAGE_ERR_MSG "Usage: SpamDetector <database path> <message path> <threshold>"

/*
 * @def INVALID_INPUT_MSG "Invalid input"
 * @brief An error message if one of the inputs are invalid according to exercise instructions
 */
#define INVALID_INPUT_MSG "Invalid input"

/*
 * @def DATABASE_INDEX 1
 * @brief The index of the database file from the given arguments vector
 */
#define DATABASE_INDEX 1

/*
 * @def MESSAGE_INDEX 2
 * @brief The index of the message file from the given arguments vector
 */
#define MESSAGE_INDEX 2

/*
 * @def THRESHOLD_INDEX 3
 * @brief The index of the threshold limitation from the given arguments vector
 */
#define THRESHOLD_INDEX 3

/*
 * @def COMMA ','
 * @brief Representation of a comma
 */
#define COMMA ','

/*
 * @def NEWLINE '\n'
 * @brief Representation of a newline
 */
#define NEWLINE '\n'

/*
 * @def SPAM "SPAM"
 * @brief Representation of a SPAM message
 */
#define SPAM "SPAM"

/*
 * @def NOT_SPAM "NOT_SPAM"
 * @brief Representation of a NOT_SPAM message
 */
#define NOT_SPAM "NOT_SPAM"


// --------------------------- implementation ---------------------------


/**
 * A function that deal with usage error. Will print to the screen the proper error message
 * and exit the program with exit_failure status.
 */
void usageErrorExit()
{
    std::cerr << USAGE_ERR_MSG << std::endl;
}


/**
 * A function that deal with invalid input errors. Will print to the screen the proper error message
 * and exit the program with exit_failure status.
 */
void inputErrorExit()
{
    std::cerr << INVALID_INPUT_MSG << std::endl;
}


/**
 * A function that check if given path represents a valid text file that is readable.
 * @param fileName The path to the text file
 * @return true if the file is valid, false otherwise
 */
bool fileCheck(const char *fileName)
{
    std::ifstream infile;

    infile.open(fileName);
    if(infile.fail())
    {
        return false;
    }

    return infile.good();
}


/**
 * A function that checks if given string represents a number.
 * @param str The given string needed to be checked
 * @return true if the string represents a valid number, false otherwise
 */
bool isNumber(const std::string& str)
{
    for(char i : str)
    {
        if(!isdigit(i))
        {
            return false;
        }
    }
    return true;
}


/**
 * A function that checks the given arguments by the user, their count,
 * uses other functions to check for valid files and validation of the threshold limitation.
 * @param argNum The number of arguments given by the user
 * @param argv A vector that includes the given arguments
 */
bool checkArguments(const int argNum, char *argv[])
{
    if (argNum != VALID_ARGS_NUM)
    {
        usageErrorExit();
        return false;
    }

    for(int i = DATABASE_INDEX ; i <= MESSAGE_INDEX ; i++)
    {
        if(!fileCheck(argv[i]))
        {
            inputErrorExit();
            return false;
        }
    }

    if(!isNumber(argv[THRESHOLD_INDEX]))
    {
        inputErrorExit();
        return false;
    }

    int threshold = std::stoi(argv[THRESHOLD_INDEX]);
    if(threshold <= 0)
    {
        inputErrorExit();
        return false;
    }

    return true;
}


/**
 * A function that converts given string to a lower case version of itself.
 * @param string The given string to convert to lower case
 */
void lowerCaseGenerator(std::string &string)
{
    for(unsigned long i = 0 ; i < string.length() ; i++)
    {
        string[i] = tolower(string[i]);
    }
}


/**
 * A function that in charge of printing the final result to the screen.
 * Will check if the final score of the message is higher then
 * the given threshold and print accordingly.
 * @param finalScore The final score of the message
 * @param threshold The threshold limitation
 */
void printResult(const int finalScore, const int threshold)
{
    if(finalScore >= threshold)
    {
        std::cout << SPAM << std::endl;
    }
    else
    {
        std::cout << NOT_SPAM << std::endl;
    }
}


/**
 * A function that parse the given database file into hash-map so it can be easily reachable.
 * Will save any phrase and its score inside the hash-map as <key, value>.
 * @param fileName The path to the database text file
 * @param dataMap Pointer to an empty hash-map ready to be filled with suspicious phrases
 * @return A pointer to the given hash-map after it was filled with all given database
 */
bool dataToMap(const char *fileName, HashMap<std::string, int> *dataMap)
{
    std::ifstream database(fileName);
    std::string phrase;
    std::string strScore;
    int intScore;

    while(std::getline(database, phrase, COMMA))
    {
        std::getline(database, strScore, NEWLINE);

        if(phrase.empty() || strScore.empty() || phrase.find(NEWLINE) != std::string::npos ||
           !isNumber(strScore))
        {
            database.close();
            dataMap->clear();
            inputErrorExit();
            return false;
        }

        intScore = std::stoi(strScore);
        if(intScore < 0)
        {
            database.close();
            dataMap->clear();
            inputErrorExit();
            return false;
        }

        dataMap->insert(phrase, intScore);
    }

    database.close();
    return true;
}


/**
 * A function that calculate the final score of the given message.
 * Will parse and compare between the message and the database from the hash-map and every time
 * it will find matching phrase it will increase the final score according to the score of the
 * phrase from the hash-map. If the database hash-map is empty, the final score will be zero.
 * @param fileName The path to the message text file
 * @param dataMap Pointer to a hash-map full of suspicious phrases and their score
 * @return The final score of the message
 */
int calcFinalScore(const char *fileName, HashMap<std::string, int> *dataMap)
{
    int finalScore = 0;

    if(dataMap->empty())
    {
        return finalScore;
    }
    else
    {
        std::ifstream message(fileName);
        std::string line;

        while(getline(message, line))
        {
            lowerCaseGenerator(line);

            for(const std::pair<std::string, int> &phrase : *dataMap)
            {
                std::string key = phrase.first;
                lowerCaseGenerator(key);

                for(size_t loc = line.find(key) ; loc != std::string::npos ;
                    (loc = line.find(key, loc + 1)))
                {
                    finalScore += phrase.second;
                }
            }
        }

        message.close();
        return finalScore;
    }
}


/**
 * The main function of the program. Will call previous functions to manage the program flow.
 * If all went right, the program will exit with exit_success status.
 * @param argc The number of arguments given to the program
 * @param argv A vector with all given arguments
 * @return exit_success status if the program end its flow without failures
 */
int main(int argc, char *argv[])
{
    if(!checkArguments(argc, argv))
    {
        return EXIT_FAILURE;
    }

    HashMap<std::string, int> dataMap;

    if(!dataToMap(argv[DATABASE_INDEX], &dataMap))
    {
        return EXIT_FAILURE;
    }

    int finalScore = calcFinalScore(argv[MESSAGE_INDEX], &dataMap);

    int threshold = std::stoi(argv[THRESHOLD_INDEX]);

    printResult(finalScore, threshold);

    dataMap.clear();

    return EXIT_SUCCESS;
}
