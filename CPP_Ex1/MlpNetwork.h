/**
 * @file MlpNetwork.h
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

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

// ------------------------------ includes ------------------------------
#include "Matrix.h"
#include "Digit.h"

// -------------------------- const definitions -------------------------

/*
 * @def MLP_SIZE 4
 * @brief The size of the MlpNetwork that the program work with
 */
#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128},
                                  {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},
                                  {10, 1}};


// -------------------------- class definitions -------------------------

/**
 * This class will help to arrange all the layers to network structure.
 * Will allow implement of input to the net and generate the output.
 */
class MlpNetwork
{
private:
    Matrix *weightsLayer;
    Matrix *biasLayer;

public:

    /**
     * A constructor of MlpNetwork. Accepts 2 arrays, size 4 each.
     * one for weights and one for biases.
     * @param weights The weights matrix layer of the network
     * @param biases The bias matrix layer of the network
     */
    MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);


    /**
     * Applies the entire network on input.
     * @param other The input matrix represent a handwriting number
     * @return The max probability digit struct
     */
    Digit operator()(const Matrix &other);

};

#endif // MLPNETWORK_H
