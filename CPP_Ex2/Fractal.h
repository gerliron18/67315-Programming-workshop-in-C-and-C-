/**
 * @file Fractal.h
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 08 Jan 2020
 *
 * @brief Definition of a Fractal base class and three different types of fractals classes
 * that inherit from it.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program can construct a Fractal from any of the three types and can preform operations
 * on each type in any valid dimension.
 * Input  :
 * Process:
 * Output :
 */


#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

// ------------------------------ includes ------------------------------
#include <vector>

// -------------------------- class definitions -------------------------

/**
 * A base class of Fractal. Protects the sizes and grids of each  object and define generators
 * for >1 dimension fractals. Also define printer function.
 */
class Fractal
{
protected:
    int dimension;
    int initGridSize = 0;
    int finalGridSize = 0;

    std::vector<std::vector<char>> initFractal;
    std::vector<std::vector<char>> finalFractal;

    /**
     * A recursive function that helps the generator function to generate the fractal vectors with
     * the appropriate char at any index according to the initialize grid of each fractal type.
     * @param rowNum The current fractal row
     * @param colNum The current fractal column
     * @param dim The current dimension of the fractal the function generates
     */
    void generateFractalHelper(const int& rowNum, const int& colNum, int dim);

    /**
     * A generator for fractal vectors according to fractal type and dimension.
     * Uses helper recursive function.
     * @param dim The current dimension of the fractal the function generates
     */
    void generateFractal(int dim);

public:

    /**
     * Explicit constructor of Fractal object that gets the fractal dimension.
     * @param dim The dimension of the fractal we would like to construct
     */
    explicit Fractal(int &dim);

    /**
     * Printer function of a fractal object, will print to the screen the current fractal
     * according to the exercise instructions.
     */
    void fractalPrinter();
};


/**
 * A carpet type fractal class inherits from Fractal class.
 */
class Carpet : public Fractal
{
public:

    /**
     * Explicit constructor of carpet type Fractal object that gets the fractal dimension.
     * @param dimension The dimension of the carpet fractal we would like to construct
     */
    explicit Carpet(int& dimension);

    /**
     * Default copy constructor for the carpet type fractal.
     * @param other The carpet fractal object we would like to copy
     */
    Carpet(const Carpet &other) = default;

    /**
     * Default '=' operator of the carpet type fractal.
     * @param other The carpet fractal object we would like to set as this
     * @return *this
     */
    Carpet &operator=(const Carpet &other) = default;

    /**
     * Default destructor of carpet type fractal.
     */
    ~Carpet() = default;
};


/**
 * A triangle type fractal class inherits from Fractal class.
 */
class Triangle : public Fractal
{
public:

    /**
     * Explicit constructor of triangle type Fractal object that gets the fractal dimension.
     * @param dimension The dimension of the triangle fractal we would like to construct
     */
    explicit Triangle(int& dimension);

    /**
     * Default copy constructor for the triangle type fractal.
     * @param other The triangle fractal object we would like to copy
     */
    Triangle(const Triangle &other) = default;

    /**
     * Default '=' operator of the triangle type fractal.
     * @param other The triangle fractal object we would like to set as this
     * @return *this
     */
    Triangle &operator=(const Triangle &other) = default;

    /**
     * Default destructor of triangle type fractal.
     */
    ~Triangle() = default;
};


/**
 * A vicsek type fractal class inherits from Fractal class.
 */
class Vicsek : public Fractal
{
public:

    /**
     * Explicit constructor of vicsek type Fractal object that gets the fractal dimension.
     * @param dimension The dimension of the vicsek fractal we would like to construct
     */
    explicit Vicsek(int& dimension);

    /**
     * Default copy constructor for the vicsek type fractal.
     * @param other The vicsek fractal object we would like to copy
     */
    Vicsek(const Vicsek &other) = default;

    /**
     * Default '=' operator of the vicsek type fractal.
     * @param other The vicsek fractal object we would like to set as this
     * @return *this
     */
    Vicsek &operator=(const Vicsek &other) = default;

    /**
     * Default destructor of triangle type fractal.
     */
    ~Vicsek() = default;
};

#endif //CPP_EX2_FRACTAL_H
