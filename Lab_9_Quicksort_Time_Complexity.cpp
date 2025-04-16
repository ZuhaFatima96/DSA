#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

class QuickSort {
private:
    vector<int>& arr;

    int partition(int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

public:
    QuickSort(vector<int>& input) : arr(input) {}

    void sort() {
        quickSort(0, arr.size() - 1);
    }
};

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int& val : arr) {
        val = rand() % 100 + 1;  // range [1, 100]
    }
    return arr;
}

int main() {
    srand(time(0));  // Seed RNG

    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

    cout << "==== Quick Sort Timing ====" << endl;
    for (int size : sizes) {
        vector<int> data = generateRandomArray(size);

        auto start = high_resolution_clock::now();
        QuickSort qs(data);
        qs.sort();
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Quick Sort on size " << size << " took " << duration.count() << " ms" << endl;
    }

    return 0;
}
