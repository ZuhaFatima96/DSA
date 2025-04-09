#include <iostream>
#include <chrono>      // High precision timing
#include <iomanip>     // For fixed precision
#include <fstream>     // For file handling

using namespace std;
using namespace chrono;

// Recursive factorial function
long long factorialRecursive(long long n) {
    if (n == 0) return 1;
    return n * factorialRecursive(n - 1);
}

// Iterative factorial function
long long factorialIterative(long long n) {
    long long result = 1;
    for (long long i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    // Five different values of n
    long long testValues[] = {5, 10, 15, 20, 25};
    int numTests = sizeof(testValues) / sizeof(testValues[0]);

    // Open CSV file for writing
    ofstream file("factorial_results.csv");
    
    // Write CSV header
    file << "n,Factorial,Recursive Time (sec),Iterative Time (sec)\n";
    cout << "n,Factorial,Recursive Time (sec),Iterative Time (sec)\n";

    // Set precision for better readability
    cout << fixed << setprecision(10);
    file << fixed << setprecision(10);

    for (int i = 0; i < numTests; i++) {
        long long n = testValues[i];

        // Measure time for recursive approach
        auto startTime = high_resolution_clock::now();
        long long factRec = factorialRecursive(n);
        auto endTime = high_resolution_clock::now();
        double timeRec = duration<double>(endTime - startTime).count();

        // Measure time for iterative approach
        startTime = high_resolution_clock::now();
        long long factIter = factorialIterative(n);
        endTime = high_resolution_clock::now();
        double timeIter = duration<double>(endTime - startTime).count();

        // Print results to console
        cout << n << "," << factIter << "," << timeRec << "," << timeIter << "\n";

        // Write results to CSV file
        file << n << "," << factIter << "," << timeRec << "," << timeIter << "\n";
    }

    // Close the CSV file
    file.close();
    
    cout << "\nCSV file 'factorial_results.csv' has been saved.\n";

    return 0;
}
