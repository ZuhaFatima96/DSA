#include <iostream>
#include <vector>
#include <algorithm> // For max_element and min_element
using namespace std;

class CountingSort {
private:
    vector<int> arr;

public:
    CountingSort(const vector<int>& input) : arr(input) {}

    void sort() {
        if (arr.empty()) return;

        int maxVal = *max_element(arr.begin(), arr.end());
        int minVal = *min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;

        vector<int> count(range, 0);
        vector<int> output(arr.size());

        for (int num : arr)
            count[num - minVal]++;

        for (int i = 1; i < count.size(); i++)
            count[i] += count[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }

        arr = output;
    }

    void display() {
        for (int num : arr)
            cout << num << " ";
        cout << endl;
    }
};

int main() {
    vector<int> data = {4, 2, -1, 5, 3, 2, 1, 0};

    cout << "Before Sorting:" << endl;
    for (int val : data)
        cout << val << " ";
    cout << endl;

    CountingSort cs(data);
    cs.sort();

    cout << "After Counting Sort:" << endl;
    cs.display();

    return 0;
}
