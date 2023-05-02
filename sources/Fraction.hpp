#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <string>
#include <limits>
using namespace std;

namespace ariel {

    class Fraction {
        private:
            int numerator;
            int denominator;

        public:
            // 2 ints constructor
            Fraction(int numerator, int denominator);

            // float constructor
            Fraction(float flt);

            // defultive constructor
            Fraction() : numerator(0), denominator(1) {};

            // copy constructor
            Fraction(const Fraction& other);

            ~Fraction() = default; // destructor, tidy requirment

            // copy assignment operator, tidy requirment
            Fraction& operator=(const Fraction& other) {
                if (this != &other) {
                    numerator = other.numerator;
                    denominator = other.denominator;
                }
                return *this;
            }

            // move constructor, tidy requirment
            Fraction(Fraction&& other) noexcept : numerator(other.numerator), denominator(other.denominator) {
                other.numerator = 0;
                other.denominator = 1;
            }

            // move assignment operator, tidy requirment
            Fraction& operator=(Fraction&& other) noexcept {
                if (this != &other) {
                    numerator = other.numerator;
                    denominator = other.denominator;
                    other.numerator = 0;
                    other.denominator = 1;
                }
                return *this;
            }

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

            // Helpful function to increase or decrease by 1 the values of a fraction
            void updateValue(int num);

            // Printing a fraction by the next foramt: "numerator/denominator"
            friend ostream& operator<<(ostream& outs, const Fraction &fra);

            // Reading a given string to a fraction object
            friend istream& operator>>(istream& ins, Fraction &fra);
            
            // Getters
            int getNumerator();
            int getDenominator();

            // Changing a fraction to its reduced form
            void reduceFraction();

            static bool overflowCheck_addition(int num1, int num2) {
                int max_int{std::numeric_limits<int>::max()};
                int min_int{std::numeric_limits<int>::min()};

                if (num2 > 0) {
                    if (num1 > max_int - num2) {
                        throw overflow_error("Addition overflow");
                    }
                }
                else { //num2 < 0
                    if (num2 < min_int - num2) {
                        throw overflow_error("Addition overflow");
                    }
                }
                return true;
            }

            static bool overflowCheck_multiplication(int num1, int num2) {
                int max_int{std::numeric_limits<int>::max()};
                int min_int{std::numeric_limits<int>::min()};

                if (num1 > 0) {
                    if (num2 > 0 && num1 > max_int / num2) {
                        throw overflow_error("Multiplication overflow");
                    }
                    if (num2 < 0 && num2 < min_int / num1) {
                        throw overflow_error("Multiplication overflow");
                    }
                }
                else { // num1 < 0
                    if (num2 > 0 && num1 < min_int / num2) {
                        throw overflow_error("Multiplication overflow");
                    }
                    if (num2 < 0 && num1 < max_int / num2) {
                        throw overflow_error("Multiplication overflow");
                    }
            }
        return true;
    }
    
    };
}
#endif