#include "complex_number.h"
#include <iostream>
#include <cmath>
#include <string>

ComplexNumber::ComplexNumber()
    :real_part(0)
    ,im_part(0)
    ,modulus(calculate_modulus())
{
}
ComplexNumber::ComplexNumber(long long x, long long y)
        :real_part(x)
        ,im_part(y)
        ,modulus(calculate_modulus())
{
}
ComplexNumber::ComplexNumber(const ComplexNumber& other)
        :real_part(other.real_part)
        ,im_part(other.im_part)
        ,modulus(calculate_modulus())
{
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& other)
{
    real_part = other.real_part;
    im_part = other.im_part;
    modulus = other.modulus;
    return *this;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& other)
{
    return ComplexNumber(this->real_part + other.real_part, other.im_part + this->im_part);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other)
{
    return ComplexNumber(this->real_part + other.real_part, this->im_part + other.im_part);
}

ComplexNumber operator+(const ComplexNumber& first, const ComplexNumber& second)
{
    return ComplexNumber(first.real_part + second.real_part, first.im_part + second.im_part);
}

ComplexNumber operator-(const ComplexNumber& first, const ComplexNumber& second)
{
    return ComplexNumber(first.real_part - second.real_part, first.im_part - second.im_part);
}

ComplexNumber ComplexNumber::operator*(long long num)
{
    return ComplexNumber(this->real_part * num, this->im_part * num);
}

double ComplexNumber::get_modulus() const
{
    return modulus;
}
double ComplexNumber::calculate_modulus() const
{
    return sqrt(real_part * real_part + im_part * im_part);
}

std::ostream& operator<<(std::ostream& out, const ComplexNumber& other)
{
    if(other.im_part == 0 )
        return out << other.real_part;
    else if(other.real_part == 0 && other.im_part != 0)
        return out << other.im_part << "i";
    else if(other.real_part != 0 && other.im_part != 0)
    {
        if(other.im_part < 0)
            return out << other.real_part << other.im_part << "i";
        return out << other.real_part << "+" << other.im_part << "i";
    }
    return out;
}