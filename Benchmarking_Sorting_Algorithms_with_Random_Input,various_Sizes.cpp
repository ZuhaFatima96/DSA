#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

// Sorting Algorithms
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; ++i)
        for(int j = 0; j < n - i - 1; ++j)
            if(arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for(int j = i + 1; j < n; ++j)
            if(arr[j] < arr[minIdx])
                minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; ++i) {
        int key = arr[i], j = i - 1;
        while(j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1], *R = new int[n2];
    for(int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for(int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Timer and Tester
void testSorts(int size) {
    cout << "\nArray size: " << size << "\n";

    int* original = new int[size];
    for(int i = 0; i < size; ++i)
        original[i] = rand() % 100 + 1;

    auto test = [&](void (*sortFunc)(int[], int), const string& name, bool show = true) {
        int* arr = new int[size];
        copy(original, original + size, arr);
        auto start = high_resolution_clock::now();
        sortFunc(arr, size);
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;
        if (show)
            cout << name << " Time: " << duration.count() << " seconds\n";
        else
            cout << name << " skipped (too slow)\n";
        delete[] arr;
    };

    auto testMergeSort = [&]() {
        int* arr = new int[size];
        copy(original, original + size, arr);
        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, size - 1);
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;
        cout << "Merge Sort Time: " << duration.count() << " seconds\n";
        delete[] arr;
    };

    if (size <= 10000) {
        test(bubbleSort, "Bubble Sort");
        test(selectionSort, "Selection Sort");
        test(insertionSort, "Insertion Sort");
    } else {
        test(bubbleSort, "Bubble Sort", false);
        test(selectionSort, "Selection Sort", false);
        test(insertionSort, "Insertion Sort", false);
    }

    testMergeSort();
    delete[] original;
}

int main() {
    srand(time(0));
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    for(int size : sizes)
        testSorts(size);
    return 0;
}
