// CS360 Utilities for FFT Validation
// Spring 2024
// Mitchell Conrad

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <complex>

// Set Standard Namespace
using namespace::std;

// Define Complex Types
typedef complex<double> Complex;
typedef valarray<Complex> ComplexArray;

/* Utility function to create a random ComplexArray of length n */
void make_complex_array(int D[], int n, int range)
{
    int i;
    D[0] = n;
    for (i = 1; i <= n; i++)
    {
        D[i] = rand() % range + 1;
    }
}

/* Utility function to copy D[] -> A[] */
void copy_array(int A[], int D[], int n)
{
    int i;
    for (i = 0; i <= n; i++)
    {
        A[i] = D[i];
    }
}

/* Utility function to print A[] array */
void printArray(int A[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%i ", A[i]);
    }
    printf("\n");
}

// Utility Function to Print ComplexArray
void printComplexArray(ComplexArray &a, int n){
    for (int i = 0; i < n; i++){
        //cout << a[i] << endl; // Format: (a, b)
        printf("%f + i%f\n", real(a[i]), imag(a[i])); // Format: a + bi
    }
    printf("\n");
}