# Square Matrix Operator Overloading Project in C++

In this project we are asked to implement a class representing square matrices and support a wide set of operator overloads, including arithmetic operations, comparison, scalar operations, increment/decrement, matrix exponentiation, and more.

The project is run fully in C++ and in Linux environment.

---

## Project Structure

```
├── SquareMat.hpp
├── SquareMat.cpp
├── Main.cpp
├── Test.cpp
├── doctest.h
├── Makefile
└── README.md
```

All functionality is implemented in one class: `SquareMat`.

---

## Features

-  **Rule of Three**:
  - Constructor
  - Copy constructor
  - Copy assignment operator
  - Destructor

-  **Operator Overloads**:
  - Arithmetic: `+`, `-`, `*`, `/`, `%`, `^`
  - Unary: `-`
  - Transpose: `~`
  - Determinant: `!`
  - Scalar multiplication from left and right (`matrix * scalar`, `scalar * matrix`)
  - Element-wise multiplication and scalar modulo
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=` (based on matrix sum)
  - Pre/post increment & decrement: `++`, `--`
  - Compound assignment: `+=`, `-=`, `*=`, `/=`, `%=`
  - Custom printing `operator<<` prints matrix object


-  **Memory Safe**
  - All operations use deep copying
  - Destructor frees memory
  - `valgrind` reports zero memory leaks

---

## Build Instructions

You can build and run the project using the included `makefile`.

### 1. Build and run demo (`Main.cpp`)
```
make Main
```

### 2. Run unit tests
```
make Test
```

### 3. Run demo with Valgrind (memory leak check)
```
make valgrind
```

### 4. Clean up build artifacts
```
make clean
```

---

## Testing

- All test cases live in `Test.cpp`
- Tests include:
  - Matrix construction and access
  - All operator behaviors (`+`, `-`, `*`, `/`, `^`, etc.)
  - Comparison correctness
  - Determinant for multiple matrix sizes
  - Memory leakage testing (using valgrind)

---

## Notes

- STL library is **not used**
- Project is based on manual memory management
- Follows the assignment instructions strictly
- Output is clean and readable for easy validation
- The project uses the `matlib` namespace to encapsulate the SquareMat class and its custom operators

---

## Author

**David Kitinberg**  
- For any questions about this project you are welcome to contact me through my email: davidkitinberg@gmail.com
