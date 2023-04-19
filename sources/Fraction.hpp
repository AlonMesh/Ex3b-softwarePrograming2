#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <string>
using namespace std;

namespace ariel {

    class Fraction {
        private:
            int numerator;
            int denominator;

        public:
            Fraction(int numerator, int denominator);
            Fraction(float flt);
            Fraction() : numerator(0), denominator(1) {};
            Fraction(const Fraction& other);

            /* The following functions declare arithmetic operators (+,-,*,/)
             and comparison operators (<,>,<=,>=,==) for the Fraction class.
             Each operator has three variations:
             fraction and fraction, fraction and float, and float and fraction. */

            friend Fraction operator+(const Fraction &fr1, const Fraction &fr2);
            friend Fraction operator+(const Fraction &fra, float num);
            friend Fraction operator+(float num, const Fraction &fra);

            friend Fraction operator-(const Fraction &fr1, const Fraction &fr2);
            friend Fraction operator-(const Fraction &fra, float num);
            friend Fraction operator-(float num, const Fraction &fra);

            friend Fraction operator*(const Fraction &fr1, const Fraction &fr2);
            friend Fraction operator*(const Fraction &fra, float num);
            friend Fraction operator*(float num, const Fraction &fra);

            friend Fraction operator/(const Fraction &fr1, const Fraction &fr2);
            friend Fraction operator/(const Fraction &fra, float num);
            friend Fraction operator/(float num, const Fraction &fra);

            friend bool operator==(const Fraction &fr1, const Fraction &fr2);
            friend bool operator==(const Fraction &fra, float num);
            friend bool operator==(float num, const Fraction &fra);

            friend bool operator<(const Fraction &fr1, const Fraction &fr2);
            friend bool operator<(const Fraction &fra, float num);
            friend bool operator<(float num, const Fraction &fra);

            friend bool operator>(const Fraction &fr1, const Fraction &fr2);
            friend bool operator>(const Fraction &fra, float num);
            friend bool operator>(float num, const Fraction &fra);

            friend bool operator<=(const Fraction &fr1, const Fraction &fr2);
            friend bool operator<=(const Fraction &fra, float num);
            friend bool operator<=(float num, const Fraction &fra);

            friend bool operator>=(const Fraction &fr1, const Fraction &fr2);
            friend bool operator>=(const Fraction &fra, float num);
            friend bool operator>=(float num, const Fraction &fra);

            Fraction operator++(); // Prefix, ++ is left
            Fraction operator++(int num); // Postfix, ++ is right
            Fraction operator--(); // Prefix, -- is left
            Fraction operator--(int num); // Postfix, -- is right

            // Printing a fraction by the next foramt: "numerator/denominator"
            friend ostream& operator<<(ostream& outs, const Fraction &fra);

            // Reading a given string to a fraction object
            friend istream& operator>>(istream& ins, const Fraction &fra);
            
            // Getters
            int getNumerator();
            int getDenominator();

            // Changing a fraction to its reduced form
            void reduceFraction();
    };
}
#endif