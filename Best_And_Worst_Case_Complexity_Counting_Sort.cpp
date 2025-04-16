#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

// CountingSort OOP
class CountingSort {
private:
    vector<int>& arr;

public:
    CountingSort(vector<int>& input) : arr(input) {}

    void sort() {
        if (arr.empty()) return;

        int maxVal = *max_element(arr.begin(), arr.end());
        int minVal = *min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;

        vector<int> count(range, 0);
        vector<int> output(arr.size());

        for (int num : arr)
            count[num - minVal]++;

        for (int i = 1; i < range; i++)
            count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }

        arr = output;
    }
};

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int& val : arr) {
        val = rand() % 100 + 1;
    }
    return arr;
}

void testCountingSortWithSortedInputs() {
    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    cout << "\n==== Counting Sort ====\n";
    for (int size : sizes) {
        vector<int> base = generateRandomArray(size);

        // Ascending sorted input
        vector<int> asc = base;
        sort(asc.begin(), asc.end());

        auto start1 = high_resolution_clock::now();
        CountingSort cs1(asc);
        cs1.sort();
        auto end1 = high_resolution_clock::now();

        // Descending sorted input
        vector<int> desc = base;
        sort(desc.begin(), desc.end(), greater<int>());

        auto start2 = high_resolution_clock::now();
        CountingSort cs2(desc);
        cs2.sort();
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
    testCountingSortWithSortedInputs();
    return 0;
}
