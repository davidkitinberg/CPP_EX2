// davidkitinberg@gmail.com


#include <iostream>
#include <stdexcept>
#include "SquareMat.hpp"



namespace matlib {

    // Constractor
    SquareMat::SquareMat(int n) : size(n) {

        if (n <= 0) {
            throw std::invalid_argument("Matrix size must be positive");
        }
    
        data = new double*[size]; // Allocate array of pointers (rows)
        for (int i = 0; i < size; ++i) 
        {
            data[i] = new double[size]; // Allocate array of pointers to each row (cols)
            for (int j = 0; j < size; ++j) 
            {
                data[i][j] = 0.0; // assign 0 to defult values
            }
        }
    }

    // Deep copy constractor
    SquareMat::SquareMat(const SquareMat& other) : size(other.size) {

        data = new double*[size]; // Allocate array of pointers (rows)
        for (int i = 0; i <size ; i++)
        {
            data[i] = new double[size]; // Allocate array of pointers to each row (cols)
            for (int j = 0; j < size ; j++)
            {
                data[i][j] = other.data[i][j]; // Copy the values (deep copy) from other mat to the new one
            }
        }
    }

    // Copy assignment operator
    SquareMat& SquareMat::operator=(const SquareMat& other) {
        if (this == &other) return *this; // Prevent self-assignment

        // Free the current memory before we allocate new memory
        for (int i = 0; i < size; ++i) delete[] data[i];
        delete[] data;

        // Allocate new memory and copy
        size = other.size;
        data = new double*[size];
        for (int i = 0; i < size; ++i) 
        {
            data[i] = new double[size];
            for (int j = 0; j < size; ++j) 
            {
                data[i][j] = other.data[i][j];
            }
        }

        return *this;
    }

    // Destructor
    SquareMat::~SquareMat() {
        
        for(int i = 0; i < this->size ; ++i)
        {
            delete[] this->data[i];
        }
        delete[] data;
    }

    // Operator [][] for easy access (write and read) to the elements in the matrix (instead of get and set)
    // Non-const version for writing only
    double* SquareMat::operator[](int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Row index out of bounds"); // Validate access bounds
        }
        return data[i];
    }

    // Const version for reading only
    const double* SquareMat::operator[](int i) const {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Row index out of bounds"); // Validate access bounds
        }
        return data[i];
    }

    // Addition
    SquareMat SquareMat::operator+(const SquareMat& other) const {

        // Operator `+` works only with same size matrix
        if (size != other.size) {
            throw std::invalid_argument(
                "Matrix sizes do not match for operator+: this mat is " + std::to_string(size) + "x" + std::to_string(size) +
                ", while the other mat is " + std::to_string(other.size) + "x" + std::to_string(other.size)
            );
        }
        SquareMat M(size); // New mat after addition operator

        for(int i = 0 ; i < size ; ++i)
        {
            for(int j = 0 ; j < size ; ++j)
                {
                    M.data[i][j] = data[i][j] + other.data[i][j];
                }
        }

        return M;
    }

    // Subtraction
    SquareMat SquareMat::operator-(const SquareMat& other) const {
        // Operator `-` works only with same size matrix
        if (size != other.size) {
            throw std::invalid_argument(
                "Matrix sizes do not match for operator-: this mat is " + std::to_string(size) + "x" + std::to_string(size) +
                ", while the other mat is " + std::to_string(other.size) + "x" + std::to_string(other.size)
            );
        }
        SquareMat M(size); // New mat after subtraction operator

        for(int i = 0 ; i < size ; ++i)
        {
            for(int j = 0 ; j < size ; ++j)
                {
                    M.data[i][j] = data[i][j] - other.data[i][j];
                }
        }

        return M;
    }
    // Unary minus
    SquareMat SquareMat::operator-() const {
        SquareMat M(size);

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] = -data[i][j];
            }
        }

    return M;
    }

    // Multiplication
    SquareMat SquareMat::operator*(const SquareMat& other) const {
        // Operator `*` works only with same size matrix
        if (size != other.size) {
            throw std::invalid_argument(
                "Matrix sizes do not match for operator*: this mat is " + std::to_string(size) + "x" + std::to_string(size) +
                ", while the other mat is " + std::to_string(other.size) + "x" + std::to_string(other.size)
            );
        }

        SquareMat M(size); // New mat after multiplication operator

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                for (int k = 0; k < size; ++k) 
                {
                    M[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
    
        return M;
    }

    // Multiplication between matrix and scalar
    SquareMat SquareMat::operator*(double scalar) const {
        if (this->size == 0) {
            throw std::invalid_argument("Mat size is 0 therefore nothing to be done");
        }

        SquareMat M(size); // New mat after multiplication with scalar operator

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] += data[i][j] * scalar;
            }
        }

        return M;
    }

    // Multiplication between matrix scalar and matrix (when written the other way)
    SquareMat operator*(double scalar, const SquareMat& mat) {
        return mat * scalar;
    }

    // Element-wise multiplication
    SquareMat SquareMat::operator%(const SquareMat& other) const {
        // Operator `%` works only with same size matrix
        if (size != other.size) {
            throw std::invalid_argument(
                "Matrix sizes do not match for operator%: this mat is " + std::to_string(size) + "x" + std::to_string(size) +
                ", while the other mat is " + std::to_string(other.size) + "x" + std::to_string(other.size)
            );
        }

        SquareMat M(size); // New mat after Element-wise multiplication

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] = data[i][j] * other.data[i][j];
            }
        }

        return M;
    }

    // Modulo matrix on scalar
    SquareMat SquareMat::operator%(int scalar) const {
        if(scalar == 0) {
            return *this;
        }

        SquareMat M(size); // New mat after Element-wise multiplication

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] = static_cast<int>(data[i][j]) % scalar;
            }
        }
        return M;
    }

    // Divition matrix by scalar
    SquareMat SquareMat::operator/(double scalar) const {
        if (this->size == 0) {
            throw std::invalid_argument("Mat size is 0 therefore nothing to be done");
        }
        if (scalar == 0) {
            throw std::invalid_argument("We cannot divide by zero");
        }

        SquareMat M(size); // New mat after Divition with scalar operator

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] = data[i][j] / scalar;
            }
        }

        return M;
    }

    // Matrix power
    SquareMat SquareMat::operator^(int power) const {
        if (power < 0) {
            throw std::invalid_argument("Not every matrix has inverse version and therefore negative power not supported");
        }
    
        SquareMat result = *this;// New mat after power operator

        if (power == 0) { // Handle edge case when we are using power of 0
            for (int i = 0; i < size; ++i)
            result[i][i] = 1.0;
            return result;
        }
    
        for (int p = 1; p < power; ++p) {
            result = result * (*this);
        }
    
        return result;
    }

    // Pre-increment (updates the values first and then return the incremented mat)
    SquareMat& SquareMat::operator++() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            data[i][j] += 1;

        return *this;
    }

    // Post-increment (stores a copy of the original mat first and then increments the original mat and return the copy that wasn't incremented)
    SquareMat SquareMat::operator++(int) {
        SquareMat copy = *this;  // Save the mat before increment

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                data[i][j] += 1;

        return copy; // Return the copy before the increment
    }

    // Pre-decrement (updates the values first and then return the decremented mat)
    SquareMat& SquareMat::operator--() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
            data[i][j] -= 1;

        return *this;

    }

    // Post-decrement (stores a copy of the original mat first and then decrements the original mat and return the copy that wasn't decremented)
    SquareMat SquareMat::operator--(int) {
        SquareMat copy = *this;  // Save the mat before decrement

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                data[i][j] -= 1;

        return copy; // Return the copy before the decrement
    }

    

}

