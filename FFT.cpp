// CS360 FFT Implementation
// Spring 2024
// Mitchell Conrad

#include <cstdio>
#include <complex>
#include <valarray>
#include "Utilities.h"

// Definitions
#define NUM_AVG 10              // Number of sorting runs to average
#define MAX_ELEMENTS 65537      // Maximum number of elements in input array
#define HIGH_RANGE 32768        // Maximum value for large input range
#define LOW_RANGE 1024			// Maximum value for small input range
#define MAX_RUNS 13             // Maximum number of 2^i input sizes to run

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
    // Test FFT
    Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    ComplexArray test_data(test, 8), test_out(8);

    // Run FFT - The Two Implementations Should Be Identical
    // Only Difference Should be Calculating a Count
    fftCount(test_data, 8, test_out);
    //fft(test_data, 8, test_out);

    // Set the Solution to Test
    double solution[8][2] = { {4,0}, {1,-2.41421}, {0,0}, {1,-0.414214}, {0,0}, {1,0.414214}, {0,0}, {1,2.41421} };

    // Check the Output Against the Solution
    for(int m = 0; m < 8; m++){
        // Get the Absolute Value of Difference Between Output and Solution
        double delta_real = abs(real(test_out[m]) - solution[m][0]);
        double delta_imag = abs(imag(test_out[m]) - solution[m][1]);

        // Check if Solution Matches (Small Error is Allowed Since Using Floating-Point Math)
        if(delta_real > 0.01 || delta_imag > 0.01){
            printf("Test Failed!\n");

            // Print Input
            printf("FFT Input\n");
            printRealPartOfComplexArray(test_data, 8);

            // Print Output
            printf("FFT Output\n");
            printComplexArray(test_out, 8);

            // Print Solution
            printf("FFT Solution\n");
            printSolution(solution);

            // Return Exit Code 1
            return 1;
        }
    }

    // Set the Seed for Random Numbers
    srand(0);

    // Define Vars
    int n, i, j;

    // Define Counter to Store Average Counts for Each Run
    double counter[MAX_RUNS][2];

    // Initialize Counters
    for(i=0; i<MAX_RUNS; i++){
        counter[i][0] = 0.0;
        counter[i][1] = 0.0;
    }

    // Set Starting Number of Elements
    n = 16;

    // Initial Iteration Count
    i = 0;

    while((n <= MAX_ELEMENTS) && (i < MAX_RUNS)){
        // Loop with random input arrays of fixed size to average results
        for(j = 0; j < NUM_AVG; j++){
            // Define Complex Arrays
            ComplexArray data(n), data_large(n), out(n), out_large(n);

            // Generate Random ComplexArray of Size n for Small Element Range
            makeComplexArray(data, n, LOW_RANGE);

            // Reset Count
            count = 0;
            counter[i][0] += (fftCount(data, n, out) / ((double)NUM_AVG));

            // Generate Random ComplexArray of Size n for Large Element Range
            makeComplexArray(data_large, n, HIGH_RANGE);

            // Reset Count
            count = 0;
            counter[i][1] += (fftCount(data_large, n, out_large) / ((double)NUM_AVG));
        }

        // Double Number of Input Elements for Next Run
        n *= 2;

        // Increment the Iteration Count
        i++;
    }

    // Reset n to Starting Value
    n = 16;

    // Print the Counts to CSV and Terminal
    FILE *fp = fopen("fftOutput.csv","w");
    if(fp != NULL){
        // Print Header
        printf("%-20s %-20s %-20s\n", "n", "FFT-1024", "FFT-32768");
        fprintf(fp,"%-20s %-20s %-20s\n", "n", "FFT-1024", "FFT-32768");
        printf("-------------------- -------------------- --------------------\n");

        // Print out Averaged Counts
        for(j = 0; j < i; j++){
            printf("%-20d,%-20d,%-20d\n", n, (int) counter[j][0], (int) counter[j][1]);
            fprintf(fp, "%-20d,%-20d,%-20d\n", n, (int) counter[j][0], (int) counter[j][1]);

            // Double the n Value
            n *= 2;
        }
    }
    else{
        printf("Unable to open output file! Make sure it is not open in another application.\n");
        return 1;
    }

    return 0;
}

// Recursive Fast-Fourier Transform (Based on CLRS)
// Note That Input Array, a, Only Has Real Dimension
void fft(ComplexArray &a, int n, ComplexArray &y){
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
int fftCount(ComplexArray &a, int n, ComplexArray &y){
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
        // Count for For-Loop Check
        count++;

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