#include "Fraction.hpp"
using namespace std;
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm> // For __gcd

// Any function is returning a defultive known value, only for compiling. Will be edited.
namespace ariel {
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

    Fraction::Fraction(float flt) {
        this->numerator = static_cast<int>(round(flt * 1000));
        this->denominator = 1000;
    }

    Fraction::Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}


    Fraction operator+(const Fraction &a, const Fraction &b) {
        // Multiplying each numerator by the other denominator, multiplying denominators
        Fraction fraction(a.numerator * b.denominator + b.numerator*a.numerator, a.denominator * b.denominator);

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

    Fraction operator*(const Fraction &a, const Fraction &b) {
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

        // throw error if dividing by 0*********************

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
        return ((reducded_a.getNumerator() == reducded_b.getNumerator()) &&
         (reducded_a.getDenominator() == reducded_b.getDenominator()));
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

        return ((a.numerator * b.denominator) < (b.numerator * a.denominator));
    }

    bool operator<(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        // Sending it to Fraction < Fraction
        return (a < b);
    }

    bool operator<(float a, const Fraction &b) {
        // Sending it to Fraction < float
        return (b < a);
    }

    bool operator>(const Fraction &a, const Fraction &b) {
        // a > b === b < a
        return (b < a);
    }

    bool operator>(const Fraction &a, float flt_b) {
        Fraction b(flt_b);

        return (a > b);
    }

    bool operator>(float a, const Fraction &b) {
        return (b < a);
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
        return Fraction(1,1);
    }

    Fraction Fraction::operator++(int a) {
        return Fraction(1,1);
    }

    Fraction Fraction::operator--() {
        return Fraction(1,1);
    }

    Fraction Fraction::operator--(int a) {
        return Fraction(1,1);
    }

    ostream& operator<<(ostream& os, const Fraction &a) {
        return os << a.numerator << "/" << a.denominator;
    }

    istream& operator>>(istream& is, const Fraction &a) {
        int numerator, denominator;
        is >> numerator >> denominator;
        //a = Fraction(numerator, denominator);
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
    }
}