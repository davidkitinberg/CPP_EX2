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

    // Helper method to return the difference between 2 matrix's sum
    // If returned val > 0 -> left has a bigger sum, if val < 0 -> right has a bigger sum, if val = 0 -> the sums are equal
    static double sumDifference(const SquareMat& left, const SquareMat& right);
    
    // Helper function that returns a minor matrix
    // by excluding one row and one column from the original
    SquareMat getMinor(int excludeRow, int excludeCol) const;

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


    
    SquareMat operator~() const;// Transpose

    // Comparison
    bool operator==(const SquareMat& other) const;// Equal matrix-sum comperison operator
    bool operator!=(const SquareMat& other) const;// Not equal matrix-sum comperison operator
    bool operator<(const SquareMat& other) const;// Less then matrix-sum comperison operator
    bool operator>(const SquareMat& other) const;// Greater then matrix-sum comperison operator
    bool operator<=(const SquareMat& other) const;// Less then equal matrix-sum comperison operator
    bool operator>=(const SquareMat& other) const;// Greater then equal matrix-sum comperison operator

    double operator!() const;// Determinant calculation of the square matrix using Laplace expansion
    
    // Compound assignment
    SquareMat& operator+=(const SquareMat& other);// Instant addition of matrix to this matrix
    SquareMat& operator-=(const SquareMat& other);// Instant subtraction of matrix to this matrix
    SquareMat& operator*=(double scalar);// Instant Scalar multiplication to this matrix
    SquareMat& operator*=(const SquareMat& other);// Instant multiplication between this matrix and another matrix
    SquareMat& operator/=(double scalar);// Instant division of this matrix with scalar
    SquareMat& operator%=(int scalar);// Instant Scalar modulo on this matrix with scalar
    SquareMat& operator%=(const SquareMat& other);// Instant Element-wise modulo between this matrix and another matrix

    
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);// Custom output stream 
};

}

#endif
