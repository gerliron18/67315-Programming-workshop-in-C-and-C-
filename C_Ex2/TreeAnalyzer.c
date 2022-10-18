/**
 * @file TreeAnalyzer.c
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 27 Nov 2019
 *
 * @brief This program gets a text file representing an undirected m-ary tree
 *        and will create a data structure to store it and finally will calculate
 *        some information about the given tree and print it to the screen.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will create a data structure to store the given tree and calculate
 * some information about that tree.
 * Input  : A path to text file representing a tree and 2 vertexes to find shortest path between
 * Process: Creating a data structure to store the tree and calculate information about it
 * Output : Print to the screen all calculations
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

// -------------------------- const definitions -------------------------

/*
 * @def MAX_LINE_LEN 1025
 * @brief The maximum length of line in the text file,
 * also represent the maximum vertexes of the tree
 */
#define MAX_LINE_LEN 1025

/*
 * @def INITIALIZE_VALUE -1
 * @brief Initialize value of the parent of the tree root
 *        or other information of vertexes that should be initialize first
 */
#define INITIALIZE_VALUE -1

/*
 * @def VALID_NUM_OF_ARGS 4
 * @brief The valid number of arguments the user have to send to the program
 */
#define VALID_NUM_OF_ARGS 4

/*
 * @def FILE_INDEX 1
 * @brief The index of the text file at the given arguments
 */
#define FILE_INDEX 1

/*
 * @def FIRST_VERTEX_INDEX 2
 * @brief The index of the first vertex needed to be calculate the shortest path from
 */
#define FIRST_VERTEX_INDEX 2

/*
 * @def SECOND_VERTEX_INDEX 3
 * @brief The index of the second vertex needed to be calculate the shortest path to
 */
#define SECOND_VERTEX_INDEX 3

/*
 * @def SPACE " "
 * @brief A space char representation
 */
#define SPACE " "

/*
 * @def DASH "-"
 * @brief A dash char representation
 */
#define DASH "-"

/*
 * @def IMPROPER_USAGE_MSG "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n"
 * @brief An usage error message that will be printed to the screen
 *        if the user was wrong with his given arguments
 */
#define IMPROPER_USAGE_MSG "Usage: TreeAnalyzer <Graph File Path> <First Vertex> <Second Vertex>\n"

/*
 * @def INVALID_INPUT_MSG "Invalid input\n"
 * @brief An error message represent that some of the input information
 *        in the text file or with the given vertexes are invalid
 */
#define INVALID_INPUT_MSG "Invalid input\n"

// ------------------------------ functions -----------------------------

/**
 * A struct representing a tree node, will save information about himself
 */
typedef struct
{
    int key;
    int parent;
    int * children;
    int numOfChildren;
    int height;
    int prev;
    int depth;
} Node;

/**
 * This function called if there is any invalid input at the text file,
 * will print to stderr an error message and exit the program.
 */
void invalidInput()
{
    fprintf(stderr, INVALID_INPUT_MSG);
    exit(EXIT_FAILURE);
}

/**
 * A function that free every node children and the tree itself. Will be called only if the
 * program runs correctly.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 */
void freeOfCharge(Node ** tree, int numOfNodes)
{
    for(int i = 0 ; i < numOfNodes ; i++)
    {
        if ((*tree + i)->children != NULL)
        {
            free((*tree + i)->children);
            (*tree + i)->children = NULL;
        }
    }
    free(*tree);
    *tree = NULL;
}

/**
 * A function that gets a string and check if it representing a valid number.
 * @param string The given string as a pointer to array of chars
 * @return 1 if the given string is a valid number, 0 otherwise
 */
int checkIfNum(const char* string)
{
    if(*string == '\0')
    {
        return 0;
    }
    else
    {
        const int length = (const int) strlen(string);
        if(length == 0)
        {
            return 0;
        }
        for (int i = 0 ; i < length ; ++i)
        {
            if(!(isdigit(string[i])))
            {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * A function that calculate the number of lines writen in text file
 * @param file A pointer to file type
 * @return The number of lines writen in the given file
 */
int howManyLines(FILE * file)
{
    int linesNum = 0;
    char c;

    for (c = getc(file) ; c != EOF ; c = getc(file))
    {
        if (c == '\n')
        {
            linesNum = linesNum + 1;
        }
    }
    return linesNum;
}

/**
 * A function that check the given arguments to the program according to the instructions
 * of the excercise.
 * @param argc The number of given arguments
 * @param argv An array of the given arguments
 * @return 0 if the arguments are valid according to the excercise instructions
 */
int checkArguments(int argc, char *argv[])
{
    if (argc != VALID_NUM_OF_ARGS)
    {
        fprintf(stderr, IMPROPER_USAGE_MSG);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    fp = fopen((const char *) argv[FILE_INDEX], "r");
    if(fp == NULL)
    {
        invalidInput();
    }

    char string_nodeNum[MAX_LINE_LEN];

    fscanf(fp , "%[^\r\n]" , string_nodeNum);
    if(!(checkIfNum(string_nodeNum)))
    {
        fclose(fp);
        invalidInput();
    }
    if(checkIfNum(argv[FIRST_VERTEX_INDEX]) && checkIfNum(argv[SECOND_VERTEX_INDEX]))
    {
        int nodeNum = (int) strtod(string_nodeNum , NULL);
        int fVertex = (int) strtod(argv[FIRST_VERTEX_INDEX] , NULL);
        int sVertex = (int) strtod(argv[SECOND_VERTEX_INDEX] , NULL);

        int linesNum = howManyLines(fp);

        if(!((fVertex < nodeNum) && (sVertex < nodeNum)) || (nodeNum == 0) || (linesNum > nodeNum + 1))
        {
            fclose(fp);
            invalidInput();
        }
    }
    else
    {
        fclose(fp);
        invalidInput();
    }

    fclose(fp);
    fp = NULL;
    return 0;
}

/**
 * A function that remove trailing of newline and '\r' from the end of given string,
 * replacing it with end of line representation.
 * @param string The given string as a pointer to char
 */
void removeStringTrailing(char *string)
{
    int length = (int) strlen(string);
    if (string[length - 2] == '\r')
    {
        string[length - 1]  = '\0';
        string[length - 2]  = '\0';
    }

    if (string[length - 1] == '\n')
    {
        string[length - 1]  = '\0';
    }
}

/**
 * A function that take a line writen in the text file representing a tree node and the node itself
 * and find information about the current node children. If it has children, the number of children
 * field will be change and an array of pointer to integers will be initialize according to the
 * representation of the node children indexes.
 * @param string The line from the text file representing the current checked node as a pointer to
 *               char
 * @param currNode The current node needed to be updated according to given information from
 *                 the line
 */
void manageChildren(FILE * fp, char* string, Node * currNode, int numOfNodes, Node * tree)
{
    int childrenArr[MAX_LINE_LEN];
    int childCount = 0;
    int dash_flag = 0;

    const char s[2] = SPACE;
    char *token;

    token = strtok(string, s);

    while( token != NULL )
    {
        if((!(checkIfNum(token))) && (strcmp(token, DASH) != 0))
        {
            fclose(fp);
            freeOfCharge(&tree, numOfNodes);
            invalidInput();
        }
        if(checkIfNum(token))
        {
            if(dash_flag)
            {
                fclose(fp);
                freeOfCharge(&tree, numOfNodes);
                invalidInput();
            }
            int child = (int) strtod(token, NULL);
            if(child > numOfNodes)
            {
                fclose(fp);
                freeOfCharge(&tree, numOfNodes);
                invalidInput();
            }
            for(int i = 0 ; i < childCount ; i++)
            {
                if(childrenArr[i] == child)
                {
                    fclose(fp);
                    freeOfCharge(&tree, numOfNodes);
                    invalidInput();
                }
            }
            childrenArr[childCount] = child;
            childCount++;
        }

        if(strcmp(token, DASH) == 0)
        {
            dash_flag = 1;
            if(childCount != 0)
            {
                fclose(fp);
                freeOfCharge(&tree, numOfNodes);
                invalidInput();
            }
        }

        token = strtok(NULL, s);
    }

    currNode->children = (int *) malloc(sizeof(int) * childCount);
    if(currNode->children == NULL)
    {
        invalidInput();
    }

    for(int i = 0 ; i < childCount ; i++)
    {
        currNode->children[i] = childrenArr[i];
    }
    currNode->numOfChildren = childCount;
}

/**
 * A function that updating the parent field of every node in the tree.
 * @param numOfNodes The number of nodes in the tree
 * @param tree A pointer to the tree
 */
void manageParent(int numOfNodes , Node * tree)
{
    for(int i = 0 ; i < numOfNodes ; i++)
    {
        for(int j = 0 ; j < tree[i].numOfChildren ; j++)
        {
            int index = tree[i].children[j];
            tree[index].parent = i;
        }
    }
}

/**
 * A function that finds the key of the tree root.
 * @param numOfNodes The number of nodes in the tree
 * @param tree A pointer to the tree
 * @return The key of the given root
 */
int findRoot(int numOfNodes , Node * tree)
{
    int root = INITIALIZE_VALUE;
    int index = 0;

    while(index < numOfNodes)
    {
        if(tree[index].parent == INITIALIZE_VALUE)
        {
            root = index;
            break;
        }
        index++;
    }
    return root;
}

/**
 * A function that run BFS algorithm on the given tree, using queue data structure that been given
 * to us by the school.
 * @param tree A pointer to the tree
 * @param root The key of the tree root
 * @param numOfNodes The number of nodes in the tree
 */
void BFS(Node* tree, int root, int numOfNodes)
{
    for(int i = 0 ; i < numOfNodes ; i++)
    {
        tree[i].height = MAX_LINE_LEN;
    }

    tree[root].height = 0;
    tree[root].prev = INITIALIZE_VALUE;

    Queue * queue = allocQueue();
    enqueue(queue , root);

    while(!queueIsEmpty(queue))
    {
        unsigned int nodeU = dequeue(queue);
        for(int w = 0 ; w < tree[nodeU].numOfChildren ; w++)
        {
            if(tree[tree[nodeU].children[w]].height == MAX_LINE_LEN)
            {
                tree[tree[nodeU].children[w]].prev = nodeU;
                enqueue(queue, tree[nodeU].children[w]);
                tree[tree[nodeU].children[w]].height = tree[nodeU].height + 1;
            }
        }
        if(tree[nodeU].parent != INITIALIZE_VALUE)
        {
            int parentIndex = tree[nodeU].parent;
            if(tree[parentIndex].height == MAX_LINE_LEN)
            {
                enqueue(queue, tree[nodeU].parent);
                tree[parentIndex].prev = nodeU;
                tree[parentIndex].height = tree[nodeU].height + 1;
            }
        }
    }
    freeQueue(&queue);
}

/**
 * A function that find the key of the node that has the minimal height at the tree.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 * @return The key of the node that has the minimal height at the tree
 */
int findMinBranch(Node * tree, int numOfNodes)
{
    int minNodeKey = 0;
    int minNodeDist = MAX_LINE_LEN;

    for(int i = 0 ; i < numOfNodes ; i++)
    {
        if(tree[i].height < minNodeDist)
        {
            if(tree[i].numOfChildren == 0)
            {
                minNodeKey = tree[i].key;
                minNodeDist = tree[i].height;
            }
        }

    }
    return minNodeKey;
}

/**
 * A function that find the key of the node that has the maximal height at the tree.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 * @return The key of the node that has the maximal height at the tree
 */
int findMaxBranch(Node * tree, int numOfNodes)
{
    int maxNodeKey = 0;
    for(int i = 0 ; i < numOfNodes ; i++)
    {
        if(tree[i].height > tree[maxNodeKey].height)
        {
            maxNodeKey = tree[i].key;
        }
    }
    return maxNodeKey;
}

/**
 * A recursive function that calculate the depths of every node in the tree and update
 * the depth field of every node.
 * @param tree A pointer to the tree
 * @param root The key of the tree root
 */
void depthCalc(Node* tree, int root)
{
    int maxDepthKey = 0;
    Node* currNode = tree + root;

    if (currNode->numOfChildren == 0)
    {
        currNode->depth = 0;
        return;
    }

    if (currNode->numOfChildren == 1)
    {
        int currChildKey = currNode->children[0];
        depthCalc(tree, currChildKey);
        currNode->depth = tree[currChildKey].depth + 1;
        return;
    }

    for (int i = 0 ; i < currNode->numOfChildren ; ++i)
    {
        int currChildKey = currNode->children[i];
        depthCalc(tree, currChildKey);
        if (tree[currChildKey].depth > tree[maxDepthKey].depth)
        {
            maxDepthKey = tree[currChildKey].key;
        }
    }
    currNode->depth = tree[maxDepthKey].depth + 1;
}

/**
 * A function that calculate the diameter of given tree.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 * @return The diameter of the tree
 */
int findDiameter(Node * tree, int numOfNodes)
{
    int maxDiameter = 0;

    for(int i = 0 ; i < numOfNodes ; i++)
    {
        int max1 = 0, max2 = 0;

        for(int j = 0 ; j < tree[i].numOfChildren ; j++)
        {
            int currChildIndex = tree[i].children[j];
            if(tree[currChildIndex].depth > max1)
            {
                if(tree[currChildIndex].depth > max2)
                {
                    max2 = max1;
                    max1 = tree[currChildIndex].depth;
                }
                else
                {
                    max2 = tree[currChildIndex].depth;
                }
            }
        }
        int tempDiameter = max1 + max2 + 1;
        if (tempDiameter > maxDiameter)
        {
            maxDiameter = tempDiameter;
        }
    }
    return maxDiameter + 1;
}

/**
 * A function that prints the shortest path between two given vertexes.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 * @param startIndex The index of the first vertex needed to be calculate the shortest path from
 * @param endIndex The index of the second vertex needed to be calculate the shortest path from
 */
void printShortPath(Node * tree, int numOfNodes, int startIndex, int endIndex)
{
    BFS(tree, endIndex, numOfNodes);

    int currNode = startIndex;

    printf("%d ", tree[currNode].key);
    while(currNode != endIndex)
    {
        printf("%d ", tree[currNode].prev);
        currNode = tree[currNode].prev;
    }
    printf("\n");
}

/**
 * A managing function that uses other functions to calculate what needed to be print to the
 * screen and then prints it with the proper message according to school instructions.
 * @param tree A pointer to the tree
 * @param numOfNodes The number of nodes in the tree
 * @param fVertex The index of the first vertex needed to be calculate the shortest path from
 * @param sVertex The index of the second vertex needed to be calculate the shortest path from
 */
void managePrints(Node * tree, int numOfNodes, char * fVertex, char * sVertex)
{
    manageParent(numOfNodes , tree);
    int root = findRoot(numOfNodes , tree);
    BFS(tree , root , numOfNodes);
    int minBranch = findMinBranch(tree , numOfNodes);
    int maxBranch = findMaxBranch(tree , numOfNodes);
    depthCalc(tree, root);
    int diameter = findDiameter(tree , numOfNodes);
    int startIndex = (int) strtod(fVertex , NULL);
    int endIndex = (int) strtod(sVertex , NULL);

    // Final prints:
    printf("Root Vertex: %d\n" , root);
    printf("Vertices Count: %d\n" , numOfNodes);
    printf("Edges Count: %d\n" , numOfNodes - 1);
    printf("Length of Minimal Branch: %d\n" , tree[minBranch].height);
    printf("Length of Maximal Branch: %d\n" , tree[maxBranch].height);
    printf("Diameter Length: %d\n" , diameter);
    printf("Shortest Path Between %d and %d: " , startIndex , endIndex);
    printShortPath(tree, numOfNodes, startIndex, endIndex);
}

/**
 * A function that manage the reading from text file. Will iterate line by line, generate the tree
 * and call the prints function to do all the calculations.
 * @param file A pointer to char that represent the text file given by the user
 * @param fVertex The index of the first vertex needed to be calculate the shortest path from
 * @param sVertex The index of the second vertex needed to be calculate the shortest path from
 */
void readLines(char * file, char * fVertex, char * sVertex)
{
    FILE *fp;
    fp = fopen(file, "r");
    if(fp == NULL)
    {
        invalidInput();
    }

    char line[MAX_LINE_LEN];

    if(!(fgets(line, MAX_LINE_LEN, fp)))
    {
        fclose(fp);
        invalidInput();
    }
    else if (*line == '\n')
    {
        fclose(fp);
        invalidInput();
    }
    else
    {
        int numOfNodes = (int) strtod(line, NULL);

        Node *tree = (Node *) malloc(sizeof(Node) * numOfNodes);
        if (tree == NULL)
        {
            invalidInput();
        }

        int lineCount = 0;
        while (fgets(line, MAX_LINE_LEN, fp) != NULL)
        {
            if(strcmp(line, "\n") == 0)
            {
                fclose(fp);
                free(tree);
                invalidInput();
            }
            removeStringTrailing(line);
            tree[lineCount].key = lineCount;
            tree[lineCount].parent = INITIALIZE_VALUE; //Any node start as a root
            manageChildren(fp, line, tree + lineCount, numOfNodes, tree);
            lineCount++;
        }
        if(lineCount < numOfNodes)
        {
            fclose(fp);
            free(tree);
            invalidInput();
        }
        else
        {
            managePrints(tree, numOfNodes, fVertex, sVertex);
        }
        freeOfCharge(&tree, numOfNodes);
    }
}

/**
 * The main function of the program. Uses other functions to manage the flow of the program.
 * @param argc The number of arguments given by the user
 * @param argv An array of the given arguments by the user
 * @return 0 if all OK
 */
int main(int argc, char *argv[])
{
    if (checkArguments(argc, argv) == 0)
    {
        readLines(argv[FILE_INDEX], argv[FIRST_VERTEX_INDEX],
                argv[SECOND_VERTEX_INDEX]);
    }
    return 0;
}
