/**
 * @file MlpNetwork.cpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 25 Dec 2019
 *
 * @brief Define a class that represent a layer of the MlpNetwork.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will set and activate layer operations at the net.
 * Input  :
 * Process:
 * Output :
 */

// ------------------------------ includes ------------------------------
#include "MlpNetwork.h"
#include "Dense.h"


// ------------------------ class implementation ------------------------

/**
* A constructor of MlpNetwork. Accepts 2 arrays, size 4 each.
* one for weights and one for biases.
* @param weights The weights matrix layer of the network
* @param biases The bias matrix layer of the network
*/
MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases) : weightsLayer(weights),
biasLayer(biases) {}


/**
* Applies the entire network on input.
* @param other The input matrix represent a handwriting number
* @return The max probability digit struct
*/
Digit MlpNetwork::operator()(const Matrix &other)
{
    Dense stepOne(weightsLayer[0], biasLayer[0], Relu);
    Dense stepTwo(weightsLayer[1], biasLayer[1], Relu);
    Dense stepThree(weightsLayer[2], biasLayer[2], Relu);
    Dense stepFour(weightsLayer[3], biasLayer[3], Softmax);

    Matrix finalMatrix = stepFour(stepThree(stepTwo(stepOne(other))));
    unsigned int value = 0;
    float probability = 0;

    for(int i = 0 ; i < finalMatrix.getRows() ; i++)
    {
        if(finalMatrix[i] > probability)
        {
            probability = finalMatrix[i];
            value = i;
        }
    }

    Digit finalDigit{value, probability};

    return finalDigit;
}


