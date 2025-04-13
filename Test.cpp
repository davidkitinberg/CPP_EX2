#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"

using namespace matlib;

////////////////// Rule of three //////////////////////
TEST_CASE("Constructor and element access") {
    SquareMat mat(2);
    mat[0][0] = 1.5;
    mat[0][1] = 2.5;
    mat[1][0] = 3.5;
    mat[1][1] = 4.5;

    CHECK(mat[0][0] == 1.5);
    CHECK(mat[1][1] == 4.5);
    CHECK(mat[1][0] == 3.5);
    CHECK(mat[0][1] == 2.5);

    mat[0][1] = 5;
    CHECK(mat[0][1] == 5);

}

TEST_CASE("Copy constructor") {
    SquareMat a(2);
    a[0][0] = 5;
    SquareMat b(a); // Deep copy
    CHECK(b[0][0] == 5);
    CHECK(&b != &a); // Validate deep copy (by address)
}

TEST_CASE("Assignment operator") {
    SquareMat a(2);
    a[0][0] = 7;
    a[1][0] = 3.2;
    SquareMat b(2);
    b = a; // Assignment operator
    CHECK(b[0][0] == 7);
    CHECK(b[1][0] == 3.2);
}

///////////////////////// All the other operators /////////////////////////

TEST_CASE("Addition and subtraction -> + , - ") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    SquareMat c = a + b;
    CHECK(c[0][0] == 6);
    CHECK(c[1][1] == 12);

    SquareMat d = b - a;
    CHECK(d[0][0] == 4);
    CHECK(d[1][1] == 4);
}

TEST_CASE("Unary minus") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = -3; a[1][1] = -4;
    
    SquareMat b = -a;
    CHECK(b[0][0] == -1);
    CHECK(b[0][1] == -2);
    CHECK(b[1][0] == 3);
    CHECK(b[1][1] == 4);
}

TEST_CASE("Matrix multiplication *") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;

    b[0][0] = 3; b[0][1] = 4;
    b[1][0] = 5; b[1][1] = 8;
    SquareMat c = a * b;
    CHECK(c[0][0] == 13); // 1*3 + 2*5
    CHECK(c[0][1] == 20); // 1*4 + 2*8
    CHECK(c[1][0] == 39); // 3*3 + 5*6
    CHECK(c[1][1] == 60); // 3*4 + 6*8
}

TEST_CASE("Scalar multiplication matrix * scalar") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;
    SquareMat c = a * 2;
    CHECK(c[0][0] == 2);
    CHECK(c[0][1] == 4);
    CHECK(c[1][0] == 6); 
    CHECK(c[1][1] == 12); 
}

TEST_CASE("Scalar multiplication scalar * matrix") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;
    SquareMat c = 3 * a;
    CHECK(c[0][0] == 3);
    CHECK(c[0][1] == 6);
    CHECK(c[1][0] == 9); 
    CHECK(c[1][1] == 18); 
}

TEST_CASE("Element-wise multiplication %") {
    SquareMat a(2), b(2);
    a[0][0] = 2; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;
    
    b[0][0] = 3; b[0][1] = 4;
    b[1][0] = 5; b[1][1] = 8;

    SquareMat c = a % b;
    CHECK(c[0][0] == 6);
    CHECK(c[0][1] == 8);
    CHECK(c[1][0] == 15); 
    CHECK(c[1][1] == 48); 
}

TEST_CASE("Modulo with scalar %") {
    SquareMat a(2);
    a[0][0] = 2; a[0][1] = 5;
    a[1][0] = 3; a[1][1] = 6;

    SquareMat b = a % 3;
    CHECK(b[0][0] == 2);
    CHECK(b[0][1] == 2);
    CHECK(b[1][0] == 0);
    CHECK(b[1][1] == 0);
}

TEST_CASE("Division with scalar /") {
    SquareMat a(2);
    a[0][0] = 2; a[0][1] = 5;
    a[1][0] = 18; a[1][1] = 6;

    SquareMat b = a / 2; // division
    CHECK(b[0][0] == 1);
    CHECK(b[0][1] == 2.5);
    CHECK(b[1][0] == 9);
    CHECK(b[1][1] == 3);
}

TEST_CASE("Power operator ^") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    SquareMat a2 = a ^ 2;
    CHECK(a2[0][0] == 7);   // 1*1 + 2*3
    CHECK(a2[0][1] == 10);  // 1*2 + 2*4
    CHECK(a2[1][0] == 15);  // 3*1 + 4*3
    CHECK(a2[1][1] == 22);  // 3*2 + 4*4
}

TEST_CASE("Pre-increment ++a") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 4;
    a[1][0] = 2; a[1][1] = -2;
    ++a; // Pre-increment
    CHECK(a[0][0] == 2);
    CHECK(a[0][1] == 5);
    CHECK(a[1][0] == 3);
    CHECK(a[1][1] == -1);
}

TEST_CASE("Post-increment a++") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 4;
    a[1][0] = 2; a[1][1] = -2;
    SquareMat b = a++; // Post-increment
    CHECK(b[0][0] == 1);
    CHECK(a[0][0] == 2);
    CHECK(b[0][1] == 4);
    CHECK(a[0][1] == 5);
    CHECK(b[1][0] == 2);
    CHECK(a[1][0] == 3);
    CHECK(b[1][1] == -2);
    CHECK(a[1][1] == -1);
}

TEST_CASE("Pre-decrement --a") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 4;
    a[1][0] = 2; a[1][1] = -2;
    --a; // Pre-decrement
    CHECK(a[0][0] == 0);
    CHECK(a[0][1] == 3);
    CHECK(a[1][0] == 1);
    CHECK(a[1][1] == -3);
}

TEST_CASE("Post-decrement a--") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 4;
    a[1][0] = 2; a[1][1] = -2;
    SquareMat b = a--; // Post-decrement
    CHECK(b[0][0] == 1);
    CHECK(a[0][0] == 0);
    CHECK(b[0][1] == 4);
    CHECK(a[0][1] == 3);
    CHECK(b[1][0] == 2);
    CHECK(a[1][0] == 1);
    CHECK(b[1][1] == -2);
    CHECK(a[1][1] == -3);
}

TEST_CASE("Transpose ~a") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 3;
    a[1][0] = 2; a[1][1] = -2;
    SquareMat t = ~a;
    CHECK(t[0][0] == 1);
    CHECK(t[0][1] == 2);
    CHECK(t[1][0] == 3);
    CHECK(t[1][1] == -2);

}

TEST_CASE("Equality == and Inequality !=") {
    SquareMat a(2), b(2);
    // a sum - 13
    a[0][0] = 2; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;
    
    // b sum - 13
    b[0][0] = 0; b[0][1] = 0;
    b[1][0] = 5; b[1][1] = 8;
    
    CHECK(a == b);

    b--; // thats means that b's sum is 9 now

    CHECK(a != b);

}

TEST_CASE("Less than < , less than equal <= , greater than > , greater than equal >= ") {
    SquareMat a(2), b(2);
    // a sum - 13
    a[0][0] = 2; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 6;
    
    // b sum - 14
    b[0][0] = 1; b[0][1] = 0;
    b[1][0] = 5; b[1][1] = 8;

    SquareMat c = b; // Deep copy

    CHECK(a < b);
    CHECK(a <= c);
    CHECK(b <= c);

    b--; // thats means that b's sum is 10 now
    SquareMat d = a;

    CHECK(a > b);
    CHECK(a >= b);
    CHECK(a >= d);

}

TEST_CASE("Determinant ! ") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;
    CHECK(!a == doctest::Approx(-2));

    SquareMat b(3);

    b[0][0] = 6;  b[0][1] = 1;  b[0][2] = 1;
    b[1][0] = 4;  b[1][1] = -2; b[1][2] = 5;
    b[2][0] = 2;  b[2][1] = 8;  b[2][2] = 7;

    CHECK(!b == doctest::Approx(-306.0));
}

TEST_CASE("Compound assignment operators (+=, -=, *=, %=)") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    a += b; // +=
    CHECK(a[0][0] == 6);
    CHECK(a[1][1] == 12);

    a -= b; // -=
    CHECK(a[0][0] == 1);
    CHECK(a[1][1] == 4);

    a *= 2; // operator *= scalar
    CHECK(a[0][0] == 2);

    a %= 3; // operator %= scalar
    CHECK(a[0][0] == 2);

    SquareMat x(2), y(2);
    x[0][0] = 2; x[0][1] = 4;
    x[1][0] = 6; x[1][1] = 8;

    y[0][0] = 2; y[0][1] = 2;
    y[1][0] = 2; y[1][1] = 2;

    x *= y; // operator *= matrix
    CHECK(x[0][0] == 12);
    CHECK(x[0][1] == 12);
    CHECK(x[1][0] == 28);
    CHECK(x[1][1] == 28);

    x %= y; // operator %= matrix
    CHECK(x[0][0] == 0);
    CHECK(x[1][0] == 0);
    CHECK(x[0][0] == 0);
    CHECK(x[1][0] == 0);
}
