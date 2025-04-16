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

// Time tester for each algorithm
void timeSort(void (*sortFunc)(int[], int), const string& name, int arr[], int size) {
    int* copyArr = new int[size];
    copy(arr, arr + size, copyArr);

    auto start = high_resolution_clock::now();
    sortFunc(copyArr, size);
    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;
    cout << name << ": " << duration.count() << " seconds\n";
    delete[] copyArr;
}

void timeMergeSort(const string& name, int arr[], int size) {
    int* copyArr = new int[size];
    copy(arr, arr + size, copyArr);

    auto start = high_resolution_clock::now();
    mergeSort(copyArr, 0, size - 1);
    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;
    cout << name << ": " << duration.count() << " seconds\n";
    delete[] copyArr;
}

void runTests(int size) {
    cout << "\n====== Testing for size: " << size << " ======\n";
    int* base = new int[size];
    for(int i = 0; i < size; ++i)
        base[i] = rand() % 100 + 1;

    // Sort using STL (ascending and descending)
    int* asc = new int[size];
    int* desc = new int[size];
    copy(base, base + size, asc);
    copy(base, base + size, desc);

    sort(asc, asc + size); // ascending
    sort(desc, desc + size, greater<int>()); // descending

    cout << "\n-- On Ascending Sorted Input --\n";
    if (size <= 10000) {
        timeSort(bubbleSort, "Bubble Sort", asc, size);
        timeSort(selectionSort, "Selection Sort", asc, size);
        timeSort(insertionSort, "Insertion Sort", asc, size);
    } else {
        cout << "Bubble/Selection/Insertion skipped (too large)\n";
    }
    timeMergeSort("Merge Sort", asc, size);

    cout << "\n-- On Descending Sorted Input --\n";
    if (size <= 10000) {
        timeSort(bubbleSort, "Bubble Sort", desc, size);
        timeSort(selectionSort, "Selection Sort", desc, size);
        timeSort(insertionSort, "Insertion Sort", desc, size);
    } else {
        cout << "Bubble/Selection/Insertion skipped (too large)\n";
    }
    timeMergeSort("Merge Sort", desc, size);

    delete[] base;
    delete[] asc;
    delete[] desc;
}

int main() {
    srand(time(0));
    int sizes[] = {100, 1000, 10000};
    for(int size : sizes)
        runTests(size);
    return 0;
}
