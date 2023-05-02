# Fraction Class / Ex3-SoftWarePrograming2

The Fraction class is a C++ class that represents a fraction. It can be used to perform basic arithmetic operations on fractions, such as addition, subtraction, multiplication, and division, as well as comparison operations, such as less than, greater than, and equal to.

## Installation
To use the Fraction class, simply include the Fraction.hpp header file in your C++ code.

## Usage
To create a Fraction object, you can either provide the numerator and denominator as integers, or provide a floating point number, which will be automatically converted to a fraction. For example:

    #include "Fraction.hpp"
    using namespace ariel;

    // Creating a fraction with numerator 3 and denominator 4
    Fraction f1(3, 4);

    // Creating a fraction from a floating point number
    Fraction f2(0.5);

Once you have a Fraction object, you can perform arithmetic and comparison operations on it using the overloaded operators. For example:

    // Adding two fractions
    Fraction f3 = f1 + f2;

    // Multiplying a fraction by a floating point number
    Fraction f4 = f1 * 2.5;

    // Comparing two fractions
    bool result = f1 < f2;

You can also modify a Fraction object by incrementing or decrementing it, or by updating its value directly. For example:

    // Incrementing a fraction
    Fraction f5 = ++f1;

    // Decrementing a fraction
    Fraction f6 = f1--;

    // Updating a fraction's value
    f1.updateValue(5);

To print the value of a Fraction object, you can use the << operator. For example:

    // Printing the value of a fraction
    std::cout << f1 << std::endl;

To input a value for a Fraction object, you can use the >> operator. For example:

    // Inputting a value for a fraction
    std::cin >> f1;

## Limitations
The Fraction class has a few limitations:

* Fractions with denominators of 0 are not allowed and will result in an exception being thrown.
* Fractions are not simplified automatically during arithmetic operations. You must call the *reduceFraction()* method to reduce a fraction to its simplest form.

## Authors
The Fraction class was developed by Alon Meshualm as a project for Sofware Programing 2.
