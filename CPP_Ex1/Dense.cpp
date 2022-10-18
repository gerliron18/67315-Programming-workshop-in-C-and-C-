/**
 * @file Dense.cpp
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
#include "Dense.h"


// ------------------------ class implementation ------------------------

/**
* A constructor for the class. Inits a new layer with given parameters
* @param w A matrix that represent the weights of the layer
* @param bias A matrix that represent the biases of the layer
* @param activationType An activation class object that can generate operations on matrix
*/
Dense::Dense(const Matrix &w, const Matrix &bias, ActivationType activationType) : weightsLayer(w),
biasLayer(bias), activationFunc(activationType) {}

/**
* Applies the layer on input and returns output matrix.
* @param other Given matrix to be applied by the layer
* @return Output matrix after applying the layer
*/
Matrix Dense::operator()(const Matrix &other) const
{
    Matrix newMatrix = other;

    newMatrix = weightsLayer * other;
    newMatrix += biasLayer;
    newMatrix = activationFunc(newMatrix);

    return newMatrix;
}

