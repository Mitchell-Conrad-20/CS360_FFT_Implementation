// CS360 Utilities for FFT Validation
// Spring 2024
// Mitchell Conrad

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <complex>

// Define Complex Types
typedef std::complex<double> Complex;
typedef std::valarray<Complex> ComplexArray;

// Utility Function to Create a Random ComplexArray of Length n
void makeComplexArray(ComplexArray &a, int n, int range){
    int i;
    Complex data[n];
    for (i = 0; i < n; i++){
        data[i] = rand() % range + 1;
    }

    a = ComplexArray(data, n);
}

// Utility Function to Print ComplexArray
void printComplexArray(ComplexArray &a, int n){
    for (int i = 0; i < n; i++){
        //std::cout << a[i] << std::endl; // Format: (a, b)
        printf("%f + %fi\n", real(a[i]), imag(a[i])); // Format: a + bi
    }
    printf("\n");
}

// Utility Function to Print Real Part ComplexArray
void printRealPartOfComplexArray(ComplexArray &a, int n){
    for (int i = 0; i < n; i++){
        printf("%f\n", real(a[i]));
    }
    printf("\n");
}

void printSolution(double a[8][2]){
    for (int i = 0; i < 8; i++){
        printf("%f + %fi\n", a[i][0], a[i][1]); // Format: a + bi
    }
    printf("\n");
}