
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

    cout << "\nA + B:\n" << (A + B);
    cout << "A - B:\n" << (A - B);
    cout << "-A:\n" << (-A);
    cout << "~A (transpose):\n" << (~A);

    cout << "\nA * 2.0 (scalar):\n" << (A * 2.0);
    cout << "A / 2.0 (scalar):\n" << (A / 2.0);
    cout << "A % 3 (modulo scalar):\n" << (A % 3);

    cout << "\nA * B (element-wise):\n" << (A * B);
    cout << "A % B (element-wise):\n" << (A % B);

    cout << "\nA ^ 2 (power):\n" << (A ^ 2);
    cout << "Determinant of A (!A): " << !A << "\n";

    cout << "\nUsing compound operators:\n";
    SquareMat C = A;
    C += B;
    cout << "A += B:\n" << C;
    C -= B;
    cout << "A -= B (back to original A):\n" << C;
    C *= 2;
    cout << "A *= 2:\n" << C;
    C %= 3;
    cout << "A %= 3:\n" << C;

    C = A;
    C *= B;
    cout << "A *= B (element-wise):\n" << C;
    C %= B;
    cout << "A %= B (element-wise):\n" << C;

    cout << "\nTesting comparison operators:\n";
    cout << "A == B: " << (A == B ? "true" : "false") << "\n";
    cout << "A != B: " << (A != B ? "true" : "false") << "\n";
    cout << "A < B: " << (A < B ? "true" : "false") << "\n";
    cout << "A > B: " << (A > B ? "true" : "false") << "\n";

    return 0;
}
