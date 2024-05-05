#include <stdlib.h>
#include <stdio.h>
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

/* Utility function to print ComplexArray */
void printComplexArray(Complex A[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%i ", A[i]);
    }
    printf("\n");
}

/* Utility function to check if A[] array is increasing */
bool checkSorted(int A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] > A[i+1]) {
            return false;
        }
    }
    return true;
}