#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n = 45; // Example value, try different values

    // Measure Recursive Time
    auto start = high_resolution_clock::now();
    fibonacci_recursive(n);
    auto stop = high_resolution_clock::now();
    auto duration_recursive = duration_cast<nanoseconds>(stop - start).count(); // Now in ns
    double time_recursive_ms = duration_recursive / 1e6; // Convert ns to ms

    // Measure Iterative Time
    start = high_resolution_clock::now();
    fibonacci_iterative(n);
    stop = high_resolution_clock::now();
    auto duration_iterative = duration_cast<nanoseconds>(stop - start).count(); // Now in ns
    double time_iterative_ms = duration_iterative / 1e6; // Convert ns to ms

    cout << "n=" << n << " | Recursive: " << time_recursive_ms << " ms | Iterative: " << duration_iterative << " ns\n";

    return 0;
}
