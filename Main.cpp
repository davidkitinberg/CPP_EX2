
#include <iostream>
#include "SquareMat.hpp"

using namespace std;
using namespace matlib;

int main() {
    cout << "Creating 2x2 matrices A and B:\n";
    SquareMat A(2), B(2);

    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

    cout << "Matrix A:\n" << A;
    cout << "Matrix B:\n" << B;

    cout << "\n========= addition & subtraction =========\n";

    cout << "\n=== A + B ===\n" << (A + B);
    cout << "=== A - B ===\n" << (A - B);

    cout << "\n========= minus unary & transpose =========\n";

    cout << "=== -A === \n" << (-A);
    cout << "=== ~A (transpose) ===\n" << (~A);

    cout << "\n========= matrix multiplication/division/modulo with scalar =========\n";

    cout << "\n=== A * 2.0 (scalar)=== \n" << (A * 2.0);
    cout << "=== A / 2.0 (scalar) ===\n" << (A / 2.0);
    cout << "=== A % 3 (modulo scalar) ===\n" << (A % 3);

    cout << "\n========= matrix multiplication =========\n";

    cout << "\n=== A * B ===\n" << (A * B);
    cout << "=== A % B (element-wise multiplication) ===\n" << (A % B);

    cout << "\n========= matrix exponentiation & determinant calculation =========\n";

    cout << "\n=== A ^ 2 (power) ===\n" << (A ^ 2);
    cout << "=== Determinant of A & B (!A , !B) === \nThe determinant value of A is: " << !A << "\nThe determinant value of B is: " << !B ;

    cout << "\n========= Using compound operators (+=,-=,*=,%=) =========\n";

    SquareMat C = A; // Temp matrix for the compound operators

    C += B;
    cout << "=== A += B ===\n" << C;

    C -= B;
    cout << "=== A -= B (back to original A) ===\n" << C;

    C *= 2;
    cout << "=== A *= 2 (scalar) ===\n" << C;

    C = A; // Return to the original values of A for easy tracking of the values

    C %= 3;
    cout << "=== A %= 3 (modulo between matrix and scalar) ===\n" << C;

    C = A; // Return to the original values of A for easy tracking of the values

    C *= B;
    cout << "=== A *= B (matrix multiplication compound) ===\n" << C;

    C = A; // Return to the original values of A for easy tracking of the values

    C %= B;
    cout << "=== A %= B (element-wise multiplication compound) ===\n" << C;

    cout << "\n=== Comparison operators===\n";
    cout << "A == B: " << (A == B ? "true" : "false") << "\n";
    cout << "A != B: " << (A != B ? "true" : "false") << "\n";
    cout << "A < B: " << (A < B ? "true" : "false") << "\n";
    cout << "A > B: " << (A > B ? "true" : "false") << "\n";

    return 0;
}
