// davidkitinberg@gmail.com


#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <iostream>
#include <stdexcept>

namespace matlib {

class SquareMat {
private:
    int size;
    double** data;

    void allocate();
    void copyFrom(const SquareMat& other);
    void deallocate();

public:

    // Rule of three:
    // 1. Normal constructor
    SquareMat(int n);
    // 2. Deep copy constructor
    SquareMat(const SquareMat& other);
    // 3. Copy assignment operator
    SquareMat& operator=(const SquareMat& other);

    // Destructor
    ~SquareMat();

    // Operator [][] for easy access (write and read) to the elements in the matrix
    double* operator[](int i);
    const double* operator[](int i) const;

    // Arithmetic operators
    SquareMat operator+(const SquareMat& other) const; // Addition
    SquareMat operator-(const SquareMat& other) const; // Subtraction
    SquareMat operator-() const; // Unary minus
    SquareMat operator*(const SquareMat& other) const; // Multiplication between 2 matrixes
    SquareMat operator*(double scalar) const; // Multiplication between matrix and scalar
    friend SquareMat operator*(double scalar, const SquareMat& mat); // Multiplication between matrix and scalar (but in the opposite order)
    SquareMat operator%(const SquareMat& other) const; // Element-wise multiplication
    SquareMat operator%(int scalar) const; // Modulo matrix on scalar
    SquareMat operator/(double scalar) const; // Divition matrix by scalar
    SquareMat operator^(int power) const; // Matrix power

    // Increment/Decrement
    SquareMat& operator++(); // Pre-increment (updates the values first and then return the incremented mat)
    SquareMat operator++(int); // Post-increment (stores a copy of the original mat first and then increments the original mat and return the copy that wasn't incremented)
    SquareMat& operator--(); // Pre-decrement (updates the values first and then return the decremented mat)
    SquareMat operator--(int); // Post-decrement (stores a copy of the original mat first and then decrements the original mat and return the copy that wasn't decremented)


    // Transpose
    SquareMat operator~() const;

    // Compound assignment
    SquareMat& operator+=(const SquareMat& other);
    SquareMat& operator-=(const SquareMat& other);
    SquareMat& operator*=(double scalar);
    SquareMat& operator/=(double scalar);
    SquareMat& operator%=(const SquareMat& other);
    SquareMat& operator%=(int scalar);

    // Comparison
    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    // Determinant
    double operator!() const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
};

}

#endif
