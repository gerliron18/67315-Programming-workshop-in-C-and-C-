/**
 * @file Activation.h
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

#ifndef ACTIVATION_H
#define ACTIVATION_H

// ------------------------------ includes ------------------------------
#include "Matrix.h"


// -------------------------- class definitions -------------------------

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};


/**
 * Set the activation operation on matrix according to given type
 */
class Activation
{
private:
    ActivationType type;

    /**
     * Apply Relu activation type on given matrix
     * @param other The given matrix
     * @return The same matrix after activating Relu
     */
    static Matrix _reluFunc(const Matrix &other);

    /**
     * Apply SoftMax activation type on given matrix
     * @param other The given matrix
     * @return The same matrix after activating SoftMax
     */
    static Matrix _softmaxFunc(const Matrix &other);

public:

    /**
     * Constructor for the Activation class, Accepts activation type (Relu/Softmax)
     * and defines this instance’s activation accordingly
     * @param actType The activation type needed to apply on given matrix
     */
    explicit Activation(ActivationType actType);

    /**
     * Getter function of the activation type as inline function
     * @return This activation type (Relu/SoftMax)
     */
    const ActivationType &getActivationType(){ return type; }

    /**
     * Applies activation function on input matrix, does not change input
     * @param other The given matrix
     * @return The matrix after activating it according to the type
     */
    Matrix operator()(const Matrix &other) const;

};

#endif //ACTIVATION_H
