/**
 * @file Matrix.h
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 25 Dec 2019
 *
 * @brief Define a class that through it we will generate matrix and vectors
 *        needed to the program flow.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will define a class of matrix, getters and overload operators
 * so the program could work properly.
 * Input  :
 * Process:
 * Output :
 */

#ifndef MATRIX_H
#define MATRIX_H


// ------------------------------ includes ------------------------------
#include <iostream>


// -------------------------- const definitions -------------------------

/*
 * @def INITIALIZE_VALUE 0
 * @brief The initialize value of matrix cell
 */
#define INITIALIZE_VALUE 0

/*
 * @def EXIT_STATUS 1
 * @brief The exit status when we get an error
 */
#define EXIT_STATUS 1

/*
 * @def INVALID_MATRIX_INIT_DIMENSIONS_MSG "Error: Invalid matrix initialization dimensions"
 * @brief Error msg when trying to initiate matrix with invalid dimensions
 */
#define INVALID_MATRIX_INIT_DIMENSIONS_MSG "Error: Invalid matrix initialization dimensions"

/*
 * @def ALLOCATION_FAILED_MSG "Error: Failed allocate memory"
 * @brief Error msg when allocation memory failed
 */
#define ALLOCATION_FAILED_MSG "Error: Failed allocate memory"

/*
 * @def INVALID_MATRIX_MULTIPLICATION_DIMENSIONS_MSG "Error: Can't preform matrix multiplication
 *      if ones number of columns not equal to others number of rows"
 * @brief Error msg when trying to multiply between matrix not from the valid dimensions
 */
#define INVALID_MATRIX_MULTIPLICATION_DIMENSIONS_MSG "Error: Can't preform matrix multiplication if ones number of columns not equal to others number of rows"

/*
 * @def INVALID_MATRIX_ADDITION_DIMENSIONS_MSG "Error: Can't preform matrix addition if ones
 *      dimensions not equal to others dimensions"
 * @brief Error msg when trying to preform addition of matrix not from the same dimensions
 */
#define INVALID_MATRIX_ADDITION_DIMENSIONS_MSG "Error: Can't preform matrix addition if ones dimensions not equal to others dimensions"

/*
 * @def INVALID_INPUT_DIMENSIONS_MSG "Error: Given dimension/s are
 *      invalid according to matrix dimensions"
 * @brief Error msg when trying to reach an invalid cell of the matrix
 */
#define INVALID_INPUT_DIMENSIONS_MSG "Error: Given dimension/s are invalid according to matrix dimensions"

/*
 * @def FILE_DIMENSIONS_DOESNT_MATCH_MSG "Error: Given file doesn't match the generated
 *      matrix dimensions"
 * @brief Error msg when the matrix information from the input file
 *        doesn't match the constructed one
 */
#define FILE_DIMENSIONS_DOESNT_MATCH_MSG "Error: Given file doesn't match the generated matrix dimensions"

/*
 * @def INVALID_INPUT_FILE_MSG "Error: Invalid input file or cell value"
 * @brief Error msg when something wrong with the input file or the current value writen in it
 */
#define INVALID_INPUT_FILE_MSG "Error: Invalid input file or cell value"

/*
 * @def INVALID_OUTPUT_STREAM_MSG "Error: Invalid output stream"
 * @brief Error msg when something wrong with the given output stream
 */
#define INVALID_OUTPUT_STREAM_MSG "Error: Invalid output stream"


// -------------------------- class definitions -------------------------

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;


/**
 * Set a matrix object including dimensions and values. Override operators and define methods
 * that can be preformed on matrix and will help the program flow.
 */
class Matrix
{
private:
    MatrixDims dimensions;
    float *pMatrix;

public:

    /**
     * Constructor for matrix of rows*cols dimensions. Init all elements to zero.
     * @param rows The number of rows
     * @param cols The number of columns
     */
    Matrix(int rows, int cols);


    /**
     * default constructor for 1X1 matrix that inits the single element to zero.
     * Writen as an inline.
     */
    Matrix() : Matrix(1, 1){ pMatrix[0] = INITIALIZE_VALUE; }


    /**
     * Copy constructor that construct matrix from given matrix.
     * @param m The given matrix needed to be copied
     */
    Matrix(const Matrix &m);


    /**
     * A destructor of matrix. Will delete all allocated memory.
     */
    ~Matrix();


    /**
     * Getter of the matrix number of rows.
     * @return The number of the matrix rows
     */
    int getRows() const { return dimensions.rows; }


    /**
     * Getter of the matrix number of columns.
     * @return The number of the matrix columns
     */
    int getCols() const { return dimensions.cols; }


    /**
     * Transforms a matrix into a column vector i.e nX1 matrix.
     * Supports function calling concatenation.
     * @return A new matrix object of size nX1 with the information of the original matrix
     */
    Matrix &vectorize();


    /**
     * Prints matrix elements, no return value. Prints space after each element (incl. last
     * element in the row), prints newline after each row (incl. last row)
     */
    void plainPrint() const;


    /**
     * Assignment operator overriding of one matrix to another
     * @param other The matrix we want to assign to *this
     * @return The matrix after assign it with other matrix
     */
    Matrix &operator=(const Matrix &other);


    /**
     * Matrix multiplication operator overriding between two matrix
     * @param other A matrix we want to multiply ours with
     * @return Our matrix after multiplication with the given one
     */
    Matrix operator*(const Matrix &other) const;


    /**
     * Scalar multiplication on the right operator overriding
     * @param scalar The given scalar we want to multiply our matrix with
     * @return Our matrix after multiply it with the given scalar from the right
     */
    Matrix operator*(const float &scalar) const;


    /**
     * Scalar multiplication on the left operator overriding
     * @param scalar The given scalar we want to multiply given matrix with
     * @param other The given matrix to multiply it from the left
     * @return A new matrix represents the given matrix multiply be the scalar from the left
     */
    friend Matrix operator*(const float &scalar, const Matrix &other);


    /**
     * Matrix addition operator overriding between two matrix
     * @param other The second matrix we want to add to ours
     * @return A new matrix represents the addition of our matrix with the given one
     */
    Matrix operator+(const Matrix &other) const;


    /**
     * Matrix addition accumulation operator overriding of given matrix to ours
     * @param other The second matrix we want to add to ours
     * @return Our matrix after addition of the given one
     */
    Matrix &operator+=(const Matrix &other);


    /**
     * The non-const implementation of parenthesis indexing operator
     * to get the m(i,j) element in the matrix
     * @param i The index of the row
     * @param j The index of the column
     * @return The i,j element in the matrix
     */
    float &operator()(int i, int j);


    /**
     * The const implementation of parenthesis indexing operator
     * to get the m(i,j) element in the matrix
     * @param i The index of the row
     * @param j The index of the column
     * @return The i,j element in the matrix
     */
    const float &operator()(int i, int j) const;


    /**
     * The non-const implementation of brackets indexing operator
     * give an excess to the m[i] element in the matrix
     * @param i The index we want to get excess to
     * @return The i'th element in the matrix
     */
    float &operator[](int i);


    /**
     * The const implementation of brackets indexing operator
     * give an excess to the m[i] element in the matrix
     * @param i The index we want to get excess to
     * @return The i'th element in the matrix
     */
    const float &operator[](int i) const;


    /**
     * Input stream operator that fills matrix elements through reading input stream fully
     * @param is The input stream
     * @param other The matrix we need to fill with values given in the input stream
     * @return The input stream itself
     */
    friend std::istream &operator>>(std::istream &is, Matrix &other);


    /**
     * Output stream operator that pretty export the matrix
     * according to section 3.4 at the instructions
     * @param os The output stream
     * @param other The matrix we want to export
     * @return The output stream itself
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &other);

};

#endif //MATRIX_H
