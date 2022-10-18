/**
 * @file Activation.cpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 25 Dec 2019
 *
 * @brief Define a class that set the activation function on matrix.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will set activation class and can apply the activation function on given matrix
 * Input  :
 * Process:
 * Output :
 */

// ------------------------------ includes ------------------------------
#include "Activation.h"
#include <math.h>


// ------------------------ class implementation ------------------------

/**
* Constructor for the Activation class, Accepts activation type (Relu/Softmax)
* and defines this instance’s activation accordingly
* @param actType The activation type needed to apply on given matrix
*/
Activation::Activation(ActivationType actType) : type(actType){}


/**
* Applies activation function on input matrix, does not change input
* @param other The given matrix
* @return The matrix after activating it according to the type
*/
Matrix Activation::operator()(const Matrix &other) const
{
    if(type == Relu)
    {
        return _reluFunc(other);
    }

    return _softmaxFunc(other);
}


/**
* Apply Relu activation type on given matrix
* @param other The given matrix
* @return The same matrix after activating Relu
*/
Matrix Activation::_reluFunc(const Matrix &other)
{
    Matrix newMatrix(other.getRows(), other.getCols());

    for(int i = 0 ; i < other.getRows() * other.getCols() ; i++)
    {
        if(other[i] >= 0)
        {
            newMatrix[i] = other[i];
        }

        else
        {
            newMatrix[i] = INITIALIZE_VALUE;
        }
    }

    return newMatrix;
}


/**
* Apply SoftMax activation type on given matrix
* @param other The given matrix
* @return The same matrix after activating SoftMax
*/
Matrix Activation::_softmaxFunc(const Matrix &other)
{
    Matrix newMatrix(other.getRows(), other.getCols());

    for(int i = 0 ; i < other.getCols() ; i++)
    {
        float sum = 0;

        for(int j = 0 ; j < other.getRows() ; j++)
        {
            sum += std::exp(other(j, i));
        }

        sum = 1 / sum;

        for(int k = 0 ; k < other.getRows() ; k++)
        {
            newMatrix(k, i) = sum * std::exp(other(k, i));
        }
    }

    return newMatrix;
}

