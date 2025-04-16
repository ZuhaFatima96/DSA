#include <iostream>
#include <vector>
using namespace std;

class QuickSort {
private:
    vector<int> arr;

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
    QuickSort(const vector<int>& input) : arr(input) {}

    void sort() {
        quickSort(0, arr.size() - 1);
    }

    void display() {
        for (int num : arr)
            cout << num << " ";
        cout << endl;
    }
};
int main() {
    vector<int> data = {10, 7, 8, 9, 1, 5};

    cout << "Quick Sort:" << endl;
    QuickSort qs(data);
    qs.sort();
    qs.display();

    return 0;
}


