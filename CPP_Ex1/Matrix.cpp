/**
 * @file Matrix.cpp
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

// ------------------------------ includes ------------------------------
#include "Matrix.h"


// ------------------------ class implementation ------------------------

/**
* Constructor for matrix of rows*cols dimensions. Init all elements to zero.
* @param rows The number of rows
* @param cols The number of columns
*/
Matrix::Matrix(int rows, int cols) : dimensions({rows, cols})
{
    if(rows <= 0 || cols <= 0)
    {
        std::cerr << INVALID_MATRIX_INIT_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    dimensions.rows = rows;
    dimensions.cols = cols;
    pMatrix = new float[rows * cols];
    if(pMatrix == nullptr)
    {
        std::cerr << ALLOCATION_FAILED_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    for(int i = 0 ; i < rows * cols ; i++)
    {
        pMatrix[i] = INITIALIZE_VALUE;
    }
}


/**
* Copy constructor that construct matrix from given matrix.
* @param m The given matrix needed to be copied
*/
Matrix::Matrix(const Matrix &m) : Matrix(m.dimensions.rows, m.dimensions.cols)
{
    for(int i = 0 ; i < dimensions.rows * dimensions.cols ; i++)
    {
        pMatrix[i] = m.pMatrix[i];
    }
}


/**
* A destructor of matrix. Will delete all allocated memory.
*/
Matrix::~Matrix()
{
    if(pMatrix != nullptr)
    {
        delete [] pMatrix;
    }

    pMatrix = nullptr;
}


/**
* Transforms a matrix into a column vector i.e nX1 matrix.
* Supports function calling concatenation.
* @return A new matrix object of size nX1 with the information of the original matrix
*/
Matrix &Matrix::vectorize()
{
    dimensions.rows = dimensions.rows * dimensions.cols;
    dimensions.cols = 1;
    return *this;
}


/**
* Prints matrix elements, no return value. Prints space after each element (incl. last
* element in the row), prints newline after each row (incl. last row)
*/
void Matrix::plainPrint() const
{
    for(int i = 0 ; i < dimensions.rows ; i++)
    {
        for(int j = 0 ; j < dimensions.cols ; j++)
        {
            std::cout << pMatrix[i * dimensions.cols + j] << " ";
        }

        std::cout << std::endl;
    }
}


/**
* Assignment operator overriding of one matrix to another
* @param other The matrix we want to assign to *this
* @return The matrix after assign it with other matrix
*/
Matrix &Matrix::operator=(const Matrix &other)
{
    if(this == &other)
    {
        return *this;
    }

    delete [] pMatrix;
    dimensions.rows = other.dimensions.rows;
    dimensions.cols = other.dimensions.cols;
    pMatrix = new float[other.dimensions.rows * other.dimensions.cols];
    if(pMatrix == nullptr)
    {
        std::cerr << ALLOCATION_FAILED_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    for(int i = 0 ; i < dimensions.rows * dimensions.cols ; i++)
    {
        pMatrix[i] = other.pMatrix[i];
    }

    return *this;
}


/**
* Matrix multiplication operator overriding between two matrix
* @param other A matrix we want to multiply ours with
* @return Our matrix after multiplication with the given one
*/
Matrix Matrix::operator*(Matrix const &other) const
{
    if(dimensions.cols != other.dimensions.rows)
    {
        std::cerr << INVALID_MATRIX_MULTIPLICATION_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    Matrix newMatrix(dimensions.rows, other.dimensions.cols);

    for(int i = 0 ; i < dimensions.rows ; i++)
    {
        for(int j = 0 ; j < other.dimensions.cols ; j++)
        {
            float result = 0;
            for(int k = 0 ; k < dimensions.cols ; k++)
            {
                result = result + pMatrix[i * dimensions.cols + k] *
                         other.pMatrix[k * other.dimensions.cols + j];
            }
            newMatrix.pMatrix[i * other.dimensions.cols + j] = result;
        }
    }

    return newMatrix;
}


/**
* Scalar multiplication on the right operator overriding
* @param scalar The given scalar we want to multiply our matrix with
* @return Our matrix after multiply it with the given scalar from the right
*/
Matrix Matrix::operator*(const float &scalar) const
{
    Matrix newMatrix(dimensions.rows, dimensions.cols);

    for(int i = 0 ; i < dimensions.rows * dimensions.cols ; i++)
    {
        newMatrix.pMatrix[i] = pMatrix[i] * scalar;
    }

    return newMatrix;
}


/**
* Scalar multiplication on the left operator overriding
* @param scalar The given scalar we want to multiply given matrix with
* @param other The given matrix to multiply it from the left
* @return A new matrix represents the given matrix multiply be the scalar from the left
*/
Matrix operator*(const float &scalar, const Matrix &other)
{
    Matrix newMatrix(other.dimensions.rows , other.dimensions.cols);

    for( int i = 0 ; i < other.dimensions.rows * other.dimensions.cols ; i++)
    {
        newMatrix.pMatrix[i] = other.pMatrix[i] * scalar;
    }

    return newMatrix;
}


/**
* Matrix addition operator overriding between two matrix
* @param other The second matrix we want to add to ours
* @return A new matrix represents the addition of our matrix with the given one
*/
Matrix Matrix::operator+(const Matrix &other) const
{
    if(dimensions.rows != other.dimensions.rows || dimensions.cols != other.dimensions.cols)
    {
        std::cerr << INVALID_MATRIX_ADDITION_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    Matrix newMatrix(dimensions.rows, dimensions.cols);

    for(int i = 0 ; i < dimensions.rows * dimensions.cols ; i++)
    {
        newMatrix.pMatrix[i] = pMatrix[i] + other.pMatrix[i];
    }

    return newMatrix;
}


/**
* Matrix addition accumulation operator overriding of given matrix to ours
* @param other The second matrix we want to add to ours
* @return Our matrix after addition of the given one
*/
Matrix &Matrix::operator+=(const Matrix &other)
{
    if(dimensions.rows != other.dimensions.rows || dimensions.cols != other.dimensions.cols)
    {
        std::cerr << INVALID_MATRIX_ADDITION_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    for(int i = 0 ; i < dimensions.rows * dimensions.cols ; i++)
    {
        pMatrix[i] += other.pMatrix[i];
    }

    return *this;
}


/**
* The non-const implementation of parenthesis indexing operator
* to get the m(i,j) element in the matrix
* @param i The index of the row
* @param j The index of the column
* @return The i,j element in the matrix
*/
float &Matrix::operator()(const int i, const int j)
{
    if(i < 0 || i >= dimensions.rows || j < 0 || j >= dimensions.cols)
    {
        std::cerr << INVALID_INPUT_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    return pMatrix[i * dimensions.cols + j];
}


/**
* The const implementation of parenthesis indexing operator
* to get the m(i,j) element in the matrix
* @param i The index of the row
* @param j The index of the column
* @return The i,j element in the matrix
*/
const float &Matrix::operator()(const int i, const int j) const
{
    if(i < 0 || i >= dimensions.rows || j < 0 || j >= dimensions.cols)
    {
        std::cerr << INVALID_INPUT_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    return pMatrix[i * dimensions.cols + j];
}


/**
* The non-const implementation of brackets indexing operator
* give an excess to the m[i] element in the matrix
* @param i The index we want to get excess to
* @return The i'th element in the matrix
*/
float &Matrix::operator[](const int i)
{
    if(i < 0 || i >= dimensions.rows * dimensions.cols)
    {
        std::cerr << INVALID_INPUT_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    return pMatrix[i];
}


/**
* The const implementation of brackets indexing operator
* give an excess to the m[i] element in the matrix
* @param i The index we want to get excess to
* @return The i'th element in the matrix
*/
const float &Matrix::operator[](const int i) const
{
    if(i < 0 || i >= dimensions.rows * dimensions.cols)
    {
        std::cerr << INVALID_INPUT_DIMENSIONS_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    return pMatrix[i];
}


/**
* Input stream operator that fills matrix elements through reading input stream fully
* @param is The input stream
* @param other The matrix we need to fill with values given in the input stream
* @return The input stream itself
*/
std::istream &operator>>(std::istream &is, Matrix &other)
{
    is.seekg(0, std::istream::end);
    int length = is.tellg();
    is.seekg(0, std::istream::beg);

    unsigned int matrixSize = other.dimensions.rows * other.dimensions.cols * sizeof(float);
    if((unsigned int) length != matrixSize)
    {
        std::cerr << FILE_DIMENSIONS_DOESNT_MATCH_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    for(int i = 0 ; i < other.dimensions.rows * other.dimensions.cols ; i++)
    {
        is.read((char *) &other[i], sizeof(float));
    }

    if(is.eof() || !is.good())
    {
        std::cerr << INVALID_INPUT_FILE_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    return is;
}


/**
* Output stream operator that pretty export the matrix
* according to section 3.4 at the instructions
* @param os The output stream
* @param other The matrix we want to export
* @return The output stream itself
*/
std::ostream &operator<<(std::ostream &os, const Matrix &other)
{
    if(!os.good())
    {
        std::cerr << INVALID_OUTPUT_STREAM_MSG << std::endl;
        exit(EXIT_STATUS);
    }

    for(int i = 0 ; i < other.dimensions.rows ; i++)
    {
        for(int j = 0 ; j < other.dimensions.cols ; j++)
        {
            if(other(i, j) <= 0.1f)
            {
                os << "  ";
            }
            else
            {
                os << "**";
            }
        }

        os << std::endl;
    }

    return os;
}

