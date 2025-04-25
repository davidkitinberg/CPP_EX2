// davidkitinberg@gmail.com


#include <iostream>
#include <stdexcept>
#include "SquareMat.hpp"
#include <cmath>


namespace matlib {

    // Constructor
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

    // Deep copy constructor
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
            throw std::invalid_argument("Cannot perform modulo with zero.");
        }

        SquareMat M(size); // New mat after modulo with scalar

        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                M[i][j] = std::fmod(data[i][j], scalar);
            }
        }
        return M;
    }

    // Division matrix by scalar
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

    // Transpose
    SquareMat SquareMat::operator~() const {
        SquareMat transposed(size); // New mat after transpose
    
        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                transposed[j][i] = data[i][j];
            }
        }
    
        return transposed;
    }

    // Helper method to return the difference between 2 matrix's sum
    double SquareMat::sumDifference(const SquareMat& left, const SquareMat& right) {
        double sumLeft = 0.0, sumRight = 0.0; // Sum of 2 matrixes

        // Sum up left matrix
        for (int i = 0; i < left.size; ++i) 
        {
            for (int j = 0; j < left.size; ++j) 
            {
                sumLeft += left.data[i][j];
            }
        }

        // Sum up right matrix
        for (int i = 0; i < right.size; ++i) 
        {
            for (int j = 0; j < right.size; ++j) 
            {
                sumRight += right.data[i][j];
            }
        }
        
        return sumLeft - sumRight; // return difference
    }

    // Equal matrix-sum comperison operator
    bool SquareMat::operator==(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result == 0) return true;
        return false;
    }

    // Not equal matrix-sum comperison operator
    bool SquareMat::operator!=(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result != 0) return true;
        return false;
    }

    // Less then matrix-sum comperison operator
    bool SquareMat::operator<(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result < 0) return true;
        return false;
    }
    
    // Greater then matrix-sum comperison operator
    bool SquareMat::operator>(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result > 0) return true;
        return false;
    }

    // Less then equal matrix-sum comperison operator
    bool SquareMat::operator<=(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result <= 0) return true;
        return false;
    }

    // Greater then equal matrix-sum comperison operator
    bool SquareMat::operator>=(const SquareMat& other) const {
        double result = sumDifference(*this,other);
        if(result >= 0) return true;
        return false;
    }

    // Helper function that returns a minor matrix
    // by excluding one row and one column from the original
    SquareMat SquareMat::getMinor(int excludeRow, int excludeCol) const {
        SquareMat minor(size - 1); // The resulting (n-1)x(n-1) matrix
        int newRow = 0;

        for (int i = 0; i < size; ++i) {
            if (i == excludeRow) continue; // Skip the excluded row

            int newCol = 0;
            for (int j = 0; j < size; ++j) {
                if (j == excludeCol) continue; // Skip the excluded column

                // Copy the value into the minor matrix
                minor[newRow][newCol] = data[i][j];
                ++newCol; // index of col increment
            }

            ++newRow; // index of row increment
        }

        return minor; // return the matrix minor
    }

    // Calculates the determinant of the square matrix using Laplace expansion
    double SquareMat::operator!() const {
        // Edge case
        if (size == 0) {
            throw std::invalid_argument("Matrix size is zero - no deretminant");
        }
        // Base cases:
        // Size == 1 
        if (size == 1) {
            return data[0][0];
        }

        // Size == 2
        if (size == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }


        // Recursive case: because we are handling only square matrixes we can use Laplace expansion

        double determinant = 0.0; // Starting value for our determinant calculation

        for (int col = 0; col < size; ++col) // We are doing the determinant calculation over the first row
        {
            // Calculate cofactor sign of the first row (row No.0 and col)
            int sign = (col % 2 == 0) ? 1 : -1;

            // Get the minor matrix by excluding row 0 and column `col`
            SquareMat minor = getMinor(0, col);

            // Recursive step: det += sign * value * determinant(minor)
            determinant += sign * data[0][col] * !minor;
        }

        return determinant;
    }

    // Instant addition of matrix to this matrix
    SquareMat& SquareMat::operator+=(const SquareMat& other) {
        if (size != other.size) {
            throw std::invalid_argument("Matrixes size is not the same");
        }
        *this = *this + other;

        return *this;
    }

    // Instant subtraction of matrix to this matrix
    SquareMat& SquareMat::operator-=(const SquareMat& other) {
        if (size != other.size) {
            throw std::invalid_argument("Matrixes size is not the same");
        }
        *this = *this - other;

        return *this;
    }

    // Instant Scalar multiplication to this matrix
    SquareMat& SquareMat::operator*=(double scalar) {
        *this = *this * scalar;
        return *this;
    }

    // Instant multiplication between this matrix and another matrix
    SquareMat& SquareMat::operator*=(const SquareMat& other) {
        *this = *this * other;
        return *this;
    }

    // Instant division of this matrix with scalar
    SquareMat& SquareMat::operator/=(double scalar) {
        *this = *this / scalar;
        return *this;
    }
    
    // Instant Scalar modulo on this matrix with scalar
    SquareMat& SquareMat::operator%=(int scalar) {
        *this = *this % scalar;
        return *this;
    }

    // Instant Element-wise modulo between this matrix and another matrix
    SquareMat& SquareMat::operator%=(const SquareMat& other) {
        if (size != other.size) {
            throw std::invalid_argument("Matrix sizes must match for element-wise modulo");
        }
    
        for (int i = 0; i < size; ++i) 
        {
            for (int j = 0; j < size; ++j) 
            {
                int leftMatrixValue = static_cast<int>(data[i][j]);
                int rightMatrixValue = static_cast<int>(other.data[i][j]);
    
                if (rightMatrixValue == 0) {
                    throw std::invalid_argument("Modulo by zero in matrix element");
                }
    
                data[i][j] = leftMatrixValue % rightMatrixValue;
            }
        }
    
        return *this;
    }

    // Custom output stream 
    std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
        for (int i = 0; i < mat.size; ++i) 
        {
            for (int j = 0; j < mat.size; ++j) 
            {
                os << mat.data[i][j];
                if (j < mat.size - 1)
                    os << " ";
            }
            os << '\n';
        }
        return os;
    }







}

