// CS360 Utilities for FFT Validation
// Spring 2024
// Mitchell Conrad

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>

// Set Standard Namespace
//using namespace::std;

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
        //cout << a[i] << endl; // Format: (a, b)
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