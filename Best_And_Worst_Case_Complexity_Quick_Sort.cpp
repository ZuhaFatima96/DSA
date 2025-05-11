#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

// QuickSort OOP
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
        if (!arr.empty())
            quickSort(0, arr.size() - 1);
    }
};

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int& val : arr) {
        val = rand() % 100 + 1;
    }
    return arr;
}

void testQuickSortWithSortedInputs() {
    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    cout << "\n==== Quick Sort ====\n";
    for (int size : sizes) {
        vector<int> base = generateRandomArray(size);

        // Ascending sorted input
        vector<int> asc = base;
        sort(asc.begin(), asc.end());

        auto start1 = high_resolution_clock::now();
        QuickSort qs1(asc);
        qs1.sort();
        auto end1 = high_resolution_clock::now();

        // Descending sorted input
        vector<int> desc = base;
        sort(desc.begin(), desc.end(), greater<int>());

        auto start2 = high_resolution_clock::now();
        QuickSort qs2(desc);
        qs2.sort();
        auto end2 = high_resolution_clock::now();

        auto timeAsc = duration_cast<milliseconds>(end1 - start1).count();
        auto timeDesc = duration_cast<milliseconds>(end2 - start2).count();

        cout << "Size " << size
             << " | Asc Time: " << timeAsc << " ms"
             << " | Desc Time: " << timeDesc << " ms" << endl;
    }
}

int main() {
    srand(time(0));
    testQuickSortWithSortedInputs();
    return 0;
    
}
