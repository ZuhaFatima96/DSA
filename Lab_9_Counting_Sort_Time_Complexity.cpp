#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

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
        val = rand() % 100 + 1;  // range [1, 100]
    }
    return arr;
}

int main() {
    srand(time(0));  // Seed RNG

    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

    cout << "==== Counting Sort Timing ====" << endl;
    for (int size : sizes) {
        vector<int> data = generateRandomArray(size);

        auto start = high_resolution_clock::now();
        CountingSort cs(data);
        cs.sort();
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Counting Sort on size " << size << " took " << duration.count() << " ms" << endl;
    }

    return 0;
}
