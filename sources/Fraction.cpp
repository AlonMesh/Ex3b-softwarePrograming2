#include "Fraction.hpp"
using namespace std;
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm> // For __gcd

namespace ariel {
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        // Cannot creating a fraction with denominator equal to 0 
        if (this->denominator == 0) {
            throw invalid_argument("Denominator cannot be zero (0)");
        }
    }

    Fraction::Fraction(float flt) {
        this->numerator = static_cast<int>(round(flt * 1000));
        this->denominator = 1000;

        // Always simplify fractions (from floats) immediately after construction to ensure
        // they are in their simplest form for accurate comparisons
        this->reduceFraction();
    }

    Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}


    Fraction operator+(const Fraction &a, const Fraction &b) {

        Fraction::overflowCheck_multiplication(a.numerator, b.denominator);
        Fraction::overflowCheck_multiplication(b.numerator, a.denominator);
        Fraction::overflowCheck_multiplication(a.denominator, b.denominator);
        Fraction::overflowCheck_addition(a.numerator * b.denominator, b.numerator * a.denominator);

        // Multiplying each numerator by the other denominator, multiplying denominators
        Fraction fraction(a.numerator * b.denominator + b.numerator * a.denominator, a.denominator * b.denominator);

        fraction.reduceFraction();

        return fraction;
    }

    Fraction operator+(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to Fraction + Fraction
        return (a + b);
    }

    Fraction operator+(float a, const Fraction &b) {
        // Sending to Fraction + float
        return (b + a);
    }

    Fraction operator-(const Fraction &a, const Fraction &b) {
        // Modify b to -b, then (a + (-b) == a - b)
        return Fraction(a + (-1 * b));
    }

    Fraction operator-(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to Fraction - Fraction
        return (a - b);
    }

    Fraction operator-(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        // Sending to Fraction - Fraction
        return (a - b);
    }

    Fraction operator*(const Fraction &orig_a, const Fraction &orig_b) {  
        Fraction a = Fraction(orig_a);
        Fraction b = Fraction(orig_b);

        a.reduceFraction();
        b.reduceFraction();  

        Fraction::overflowCheck_multiplication(a.numerator, b.numerator);
        Fraction::overflowCheck_multiplication(a.denominator, b.denominator);

        Fraction fraction(a.numerator * b.numerator, a.denominator * b.denominator);
        fraction.reduceFraction();
        return fraction;
    }

    Fraction operator*(const Fraction &a, float flt_b) {
        // Converting b to a fraction
        Fraction b(flt_b);

        // Sending to (Fraction * Fraction)
        return Fraction(a*b);
    }

    Fraction operator*(float a, const Fraction &b) {
        // Sending to (Fraction * float)
        return (b * a);
    }

    Fraction operator/(const Fraction &a, const Fraction &b) {

        // Throw error if trying to divide by zero
        if (b.numerator == 0) {
            throw runtime_error("Can't divide by zero (0)");
        }

        // Creating the inverse fraction of b and multiplying a with it
        Fraction inversed_b(b.denominator, b.numerator);
        Fraction fraction = a * inversed_b; // Sending to (fraction * fraction)
        
        fraction.reduceFraction();

        return fraction;
    }

    Fraction operator/(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to (Fraction / Fraction)
        return (a / b);
    }

    Fraction operator/(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        // Sending to Fraction * Fraction
        return (a / b);
    }

    bool operator==(const Fraction &a, const Fraction &b) {
        // Creating 2 new fraction objects that represent the reducded forms of the given fractions
        Fraction reducded_a(a); // i must verify this
        Fraction reducded_b(b);

        reducded_a.reduceFraction();
        reducded_b.reduceFraction();

        // Check if both numerator and denominator of the reduced fractions are the same
        if ((reducded_a.getNumerator() == reducded_b.getNumerator()) &&
         (reducded_a.getDenominator() == reducded_b.getDenominator())) {
            return true;
         }
         
         else {
            float flt_a = static_cast<float>(reducded_a.numerator) / reducded_a.denominator;
            flt_a = round(flt_a * 1000.0) / 1000.0;

            float flt_b = static_cast<float>(reducded_b.numerator) / reducded_b.denominator;
            flt_b = round(flt_b * 1000.0) / 1000.0;

            return (flt_a == flt_b);
         }
    }

    bool operator==(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to (Fraction == Fraction)
        return (a == b);
    }

    bool operator==(float a, const Fraction &b) {
        // Sending to (Fraction == float)
        return (b == a); 
    }

    bool operator<(const Fraction &a, const Fraction &b) {
        // Given 1/3 and 333/1000 ---> (1*1000)/(3*1000) and (333*3)/(3*1000). Otherwise it'll be equal!
        // Therefore I will check what's bigger: (a.num*b.den) or (b.num*a.den)
        // Calculating common denominator is usless

        Fraction new_a = Fraction(a);
        Fraction new_b = Fraction(b);
        new_a.reduceFraction();
        new_b.reduceFraction();

        return ((new_a.numerator * new_b.denominator) < (new_b.numerator * new_a.denominator));
    }

    bool operator<(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending it to Fraction < Fraction
        return (a < b);
    }

    bool operator<(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        // Sending it to Fraction < Fraction
        return (a < b);
    }

    bool operator>(const Fraction &a, const Fraction &b) {
        // a > b === b < a
        return (b < a);
    }

    bool operator>(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        return (a > b);
    }

    bool operator>(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        return (a > b);
    }

    bool operator<=(const Fraction &a, const Fraction &b) {
        return ((a < b) || (a == b));
    }

    bool operator<=(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to Fraction <= Fraction
        return (a <= b);
    }

    bool operator<=(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        // Sending to Fraction <= Fraction
        return (a <= b);
    }

    bool operator>=(const Fraction &a, const Fraction &b) {
        // (a >= b) == (b <= a)
        // Sending to Fraction <= Fraction
        return (b <= a);
    }

    bool operator>=(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending to Fraction >= Fraction
        return (a >= b);
    }

    bool operator>=(float flt_a, const Fraction &b) {
        Fraction a(flt_a);

        // Sending to Fraction >= Fraction
        return (a >= b);
    }

    Fraction Fraction::operator++() {
        this->updateValue(1);

        Fraction toReturn = *this;
        return toReturn;
    }

    Fraction Fraction::operator++(int a) {
        Fraction toReturn = *this;

        this->updateValue(1);
        
        return toReturn;
    }

    Fraction Fraction::operator--() {
        this->updateValue(-1);
        
        Fraction toReturn = *this;
        return toReturn;    
    }

    Fraction Fraction::operator--(int a) {
        Fraction toReturn = *this;

        this->updateValue(-1);
        
        return toReturn;
    }

    void Fraction::updateValue(int num) {
        if ((num != 1) && (num != -1)) {
            throw invalid_argument("updateValue(int num) can get only 1 or -1");
        }

        this->numerator = this->numerator + (num * this->denominator); 
    }

    ostream& operator<<(ostream& os, const Fraction &original_a) {
        Fraction a = Fraction(original_a);
        a.reduceFraction();
        return os << a.numerator << "/" << a.denominator;
    }

    istream& operator>>(istream& is, Fraction &a) {
        int numerator, denominator;
        is >> numerator >> denominator;

        if (denominator == 0) {
            throw runtime_error("Denominator cannot be zero (0)");
        }

        if (is.fail()) {
            throw std::runtime_error("Input is not valid");
        }

        a = Fraction(numerator, denominator);
        return is;
    }

    int Fraction::getNumerator() {
        return this->numerator;
    }

    int Fraction::getDenominator() {
        return this->denominator;
    }

    void Fraction::reduceFraction() {
        // To reduce a fraction to its reduced form: finding the minimal divider (gcd)
        // and divide the numerator and denominator by it

        int gcd = __gcd(this->numerator, this->denominator);

        this->numerator = this->numerator / gcd;
        this->denominator = this->denominator / gcd;

        // If both numerator and denominator are negatives, make then both positives
        if ((this->numerator < 0) && (this->denominator < 0)) {
            this->numerator *= -1;
            this->denominator *= -1;
        }

        // To avoid situations like (-1/2) =! (1/-2) then using a solid foramt: numerator will be negative
        if ((this->numerator > 0) && (this->denominator < 0)) {
            this->numerator *= -1;
            this->denominator *= -1;
        }

        // To avoid situations like (0/1) =! (0/2) then using a solid foramt: 0 is 0/1
        if (this->numerator == 0) {
            this->denominator = 1;
        }
    }
}