// CS360 FFT Implementation
// Spring 2024
// Mitchell Conrad

#include <stdio.h>
#include <complex>
#include <valarray>
#include <iostream>
#include "Utilities.h"

// Definitions
#define NUM_AVG 10              // Number of sorting runs to average
#define MAX_ELEMENTS 65537      // Maximum number of elements in input array
#define HIGH_RANGE 32768        // Maximum value for large input range
#define LOW_RANGE 1024			// Maximum value for small input range
#define MAX_RUNS 13             // Maximum number of 2^i input sizes to run

//using namespace::std;

// Define Complex Types
typedef std::complex<double> Complex;
typedef std::valarray<Complex> ComplexArray;

// Define Constants
const float PI = 3.14159265;

// Define Count Variable
int count;

// Define Function Prototypes
void fft(ComplexArray& a, int n, ComplexArray& y);
int fftCount(ComplexArray& a, int n, ComplexArray& y);

// Generate Counts for Asymptotic Analysis of FFT at
// For Various Datasets with Averaging
int main() {
    // TODO: Implement Averaging of FFT Counts for Various Datasets

    // Set the Seed for Random Numbers
    srand(0);

    // Initialize the Count
    count = 0;

    // Set the Size of the Complex Array
    int n = 8;

    // Create Complex Array to Store Data
    ComplexArray data;

    // Make the Complex Array with Random Data
    makeComplexArray(data, n, LOW_RANGE);

    // Print Input
    printRealPartOfComplexArray(data, n);

    // Init Output Array
    ComplexArray out(n);

    // Execute FFT
    fftCount(data, n, out);

    // Print Results
    printComplexArray(out, n);

    // Print the Count
    printf("Count: %d", count);

    return 0;
}

// Recursive Fast-Fourier Transform (Based on CLRS)
void fft(ComplexArray& a, int n, ComplexArray& y){
    if(n == 1){
        y = a;
        return;
    }

    // Use Slice to Generate Evens/Odds
    ComplexArray a_even = a[std::slice(0, n / 2, 2)];
    ComplexArray a_odd = a[std::slice(1, n / 2, 2)];

    // Even Recursive Call
    ComplexArray y_even(n / 2);
    fft(a_even, n / 2, y_even);

    // Odd Recursive Call
    ComplexArray y_odd(n / 2);
    fft(a_odd, n / 2, y_odd);

    // Calculations
    for(int k = 0; k < n / 2; k++){
        Complex omega = std::polar(1.0, -2.0 * PI * k / n);
        y[k] = y_even[k] + omega * y_odd[k];
        y[k + (n / 2)] = y_even[k] - omega * y_odd[k];
    }

    // No Return Statement Since Output is Passed in
}

// Recursive Fast-Fourier Transform
// Incrementing Count for Each Line of Pseudocode in CLRS
// Returns the Count
int fftCount(ComplexArray& a, int n, ComplexArray& y){
    if(n == 1){
        count++;

        y = a;

        // Return the Count
        return count;
    }
    count++;

    // Add Counts for the two Omega Calculations That I Moved
    count++;
    count++;

    // Use Slice to Generate Evens
    ComplexArray a_even = a[std::slice(0, n / 2, 2)];
    count++;

    // Use Slice to Generate Odds
    ComplexArray a_odd = a[std::slice(1, n / 2, 2)];
    count++;

    // Even Recursive Call
    ComplexArray y_even(n / 2);
    fft(a_even, n / 2, y_even);
    count++;

    // Odd Recursive Call
    ComplexArray y_odd(n / 2);
    fft(a_odd, n / 2, y_odd);
    count++;

    // Calculations
    for(int k = 0; k < n / 2; k++){
        Complex omega = std::polar(1.0, -2.0 * PI * k / n);

        y[k] = y_even[k] + omega * y_odd[k];
        count++;

        y[k + (n / 2)] = y_even[k] - omega * y_odd[k];
        count++;

        // Count for Omega Calculation That is Moved
        count++;
    }
    count++;

    // Return the Count
    return count;
}