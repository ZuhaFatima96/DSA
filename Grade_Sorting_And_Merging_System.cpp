#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class GradeManager {
private:
    std::map<std::string, std::vector<int>> courseGrades;

    // Merge two sorted vectors
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
        std::vector<int> result;
        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i++]);
            } else {
                result.push_back(right[j++]);
            }
        }
        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);
        return result;
    }

    // Recursive merge sort
    std::vector<int> mergeSort(std::vector<int>& arr) {
        if (arr.size() <= 1) return arr;
        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());
        left = mergeSort(left);
        right = mergeSort(right);
        return merge(left, right);
    }

public:
    void addCourseGrades(const std::string& courseName, const std::vector<int>& grades) {
        courseGrades[courseName] = grades;
    }

    void sortGrades() {
        for (auto& entry : courseGrades) {
            entry.second = mergeSort(entry.second);
        }
    }

    std::vector<int> mergeAllSortedGrades() {
        std::vector<int> allGrades;
        for (const auto& entry : courseGrades) {
            allGrades = merge(allGrades, entry.second);
        }
        return allGrades;
    }

    void displaySortedGrades() {
        for (const auto& entry : courseGrades) {
            std::cout << entry.first << " Sorted Grades: ";
            for (int grade : entry.second) {
                std::cout << grade << " ";
            }
            std::cout << std::endl;
        }
    }

    void displayMergedGrades(const std::vector<int>& allGrades) {
        std::cout << "All Merged Sorted Grades: ";
        for (int grade : allGrades) {
            std::cout << grade << " ";
        }
        std::cout << std::endl <<std::endl;
    }
};

// Utility to generate random grades
std::vector<int> generateRandomGrades(int count) {
    std::vector<int> grades;
    for (int i = 0; i < count; ++i) {
        grades.push_back(rand() % 101); // 0 to 100
    }
    return grades;
}

int main() {
    srand(time(0)); // Seed for randomness
    GradeManager gm;

    gm.addCourseGrades("PDP", generateRandomGrades(20));
    gm.addCourseGrades("Engineering Economics", generateRandomGrades(20));
    gm.addCourseGrades("Electrical Machine", generateRandomGrades(20));
    gm.addCourseGrades("DSA", generateRandomGrades(20));

    gm.sortGrades();
    gm.displaySortedGrades();

    std::vector<int> mergedGrades = gm.mergeAllSortedGrades();
    gm.displayMergedGrades(mergedGrades);

    return 0;
}
