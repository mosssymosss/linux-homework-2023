#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <iostream>

class ComplexNumber
{
private:
    long long real_part;
    long long im_part;
    double modulus;
public:
    ComplexNumber();
    ComplexNumber(long long x, long long y);
    ComplexNumber(const ComplexNumber& other);
    ComplexNumber& operator=(const ComplexNumber& other);
    ~ComplexNumber() = default;
    ComplexNumber operator+(const ComplexNumber& other);
    ComplexNumber operator-(const ComplexNumber& other);
    ComplexNumber operator*(long long num);
    double get_modulus() const;
private:
    double calculate_modulus() const;
    friend ComplexNumber operator+(const ComplexNumber& first, const ComplexNumber& second);
    friend ComplexNumber operator-(const ComplexNumber& first, const ComplexNumber& second);
    friend std::ostream& operator<<(std::ostream& out, const ComplexNumber& other);
};

//ComplexNumber operator+(const ComplexNumber& first, const ComplexNumber& second);
//std::ostream& operator<<(std::ostream& out, const ComplexNumber& other);


#endif //COMPLEX_NUMBER_H
