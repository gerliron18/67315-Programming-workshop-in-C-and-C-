/**
 * @file Dense.h
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

#ifndef CPP_EX1_DENSE_H
#define CPP_EX1_DENSE_H

// ------------------------------ includes ------------------------------
#include "Matrix.h"
#include "Activation.h"


// -------------------------- class definitions -------------------------

/**
 * This class represent a layer of the MlpNetwork and it used to
 * set and activate layer operations at the net.
 */
class Dense
{
private:
    Matrix weightsLayer;
    Matrix biasLayer;
    Activation activationFunc;

public:

    /**
     * A constructor for the class. Inits a new layer with given parameters
     * @param w A matrix that represent the weights of the layer
     * @param bias A matrix that represent the biases of the layer
     * @param activationType An activation class object that can generate operations on matrix
     */
    Dense(const Matrix &w, const Matrix &bias, ActivationType activationType);


    /**
     * Getter function of the weights matrix as inline function
     * @return The weights matrix layer
     */
    const Matrix &getWeights() const { return weightsLayer; }


    /**
     * Getter function of the bias matrix as inline function
     * @return The bias matrix layer
     */
    const Matrix &getBias() const { return biasLayer; }


    /**
     * Getter function of the activation function as inline function
     * @return The activation type of the layer
     */
    ActivationType getActivation() { return activationFunc.getActivationType(); }


    /**
     * Applies the layer on input and returns output matrix.
     * @param other Given matrix to be applied by the layer
     * @return Output matrix after applying the layer
     */
    Matrix operator()(const Matrix& other) const;

};
#endif //CPP_EX1_DENSE_H
