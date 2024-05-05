// CS360 FFT Implementation
// Spring 2024
// Mitchell Conrad

#include <stdio.h>
#include <complex>
#include <valarray>
#include <iostream>
#include "Utilities.h"

using namespace::std;

// Define Complex Types
typedef complex<double> Complex;
typedef valarray<Complex> ComplexArray;

// Define Constants
const float PI = 3.14159265;

// Recursive Fast-Fourier Transform (Based on CLRS)
void fft(ComplexArray& a, int n, ComplexArray& y){
    if(n == 1){
        y = a;
        return;
    }

    // Use Slice to Generate Evens/Odds
    ComplexArray a_even = a[slice(0, n / 2, 2)];
    ComplexArray a_odd = a[slice(1, n / 2, 2)];

    // Even Recursive Call
    ComplexArray y_even(n / 2);
    fft(a_even, n / 2, y_even);

    // Odd Recursive Call
    ComplexArray y_odd(n / 2);
    fft(a_odd, n / 2, y_odd);

    // Calculations
    for(int k = 0; k < n / 2; k++){
        Complex omega = polar(1.0, -2.0 * PI * k / n);
        y[k] = y_even[k] + omega * y_odd[k];
        y[k + (n / 2)] = y_even[k] - omega * y_odd[k];
    }

    // No Return Statement Since Output is Passed in
}

// Run Main & Test FFT
int main() {
    // TODO: Implement Averaging of FFT for Various Datasets
    // Init Complex Array With Data

    // note that this can just be a regular array
    const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    ComplexArray data(test, 8);

    // Init Output Array
    ComplexArray out(8);

    // Execute FFT
    fft(data, 8, out);

    // Print Results
    printComplexArray(out, 8);

    return 0;
}