#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>


void countingSort(std::vector<int>& arr);
bool isSorted(std::vector<int>& arr);

int main() {
    const int SIZE_ARRAY = 100000;
    int temp = -100;

    // best case
    std::cout << "Best case: ";
    std::vector<int> arr1(SIZE_ARRAY, 0);
    for (int i = 0; i < SIZE_ARRAY; i++) {
        arr1[i] = temp;
        temp++;
    }

    auto start = std::chrono::steady_clock::now();
    countingSort(arr1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time: " << std::fixed << std::setw(9) << diff.count() << " s\n";

    std::cout << "Result: ";
    if (isSorted(arr1)) {
        std::cout << "YES \n";
    }
    else {
        std::cout << "NO \n";
    }

    // avarage case
    std::cout << "Avarage case: ";
    std::vector<int> arr2(SIZE_ARRAY, 0);
    for (int i = 0; i < SIZE_ARRAY; i++) {
        arr2[i] = rand() % SIZE_ARRAY;
    }
    
    start = std::chrono::steady_clock::now();
    countingSort(arr2);
    end = std::chrono::steady_clock::now();
    diff = end - start;
    std::cout << "Time: " << std::fixed << std::setw(9) << diff.count() << " s\n";

    std::cout << "Result: ";
    if (isSorted(arr2)) {
        std::cout << "YES \n";
    }
    else {
        std::cout << "NO \n";
    }

    // worst case
    std::cout << "Worst case: ";
    temp = SIZE_ARRAY;
    std::vector<int> arr3(SIZE_ARRAY, 0);
    for (int i = 0; i < SIZE_ARRAY; i++) {
        arr3[i] = temp;
        temp--;
    }

    start = std::chrono::steady_clock::now();
    countingSort(arr3);
    end = std::chrono::steady_clock::now();
    diff = end - start;
    std::cout << "Time: " << std::fixed << std::setw(9) << diff.count() << " s\n";

    std::cout << "Result: ";
    if (isSorted(arr3)) {
        std::cout << "YES \n";
    }
    else {
        std::cout << "NO \n";
    }
}

void countingSort(std::vector<int>& arr) {
    const int SIZE_ARRAY = arr.size();
    if (SIZE_ARRAY == 0) {
        return;
    }

    // find the range of values
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < SIZE_ARRAY; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // initialize the counting array
    const int SIZE_COUNT_ARRAY = maxVal - minVal + 1;
    std::vector<int> countArray(SIZE_COUNT_ARRAY, 0);

    // count the occurrences of each value
    for (int i = 0; i < SIZE_ARRAY; i++) {
        countArray[arr[i] - minVal]++;
    }

    // calculate the prefix sums
    for (int i = 1; i < SIZE_COUNT_ARRAY; i++) {
        countArray[i] += countArray[i - 1];
    }

    // create the sorted array
    std::vector<int> sortedArray(SIZE_ARRAY);
    for (int i = SIZE_ARRAY - 1; i >= 0; i--) {
        int index = countArray[arr[i] - minVal] - 1;
        sortedArray[index] = arr[i];
        countArray[arr[i] - minVal]--;
    }

    // copy the sorted array back to the original array
    std::copy(sortedArray.begin(), sortedArray.end(), arr.begin());
}

bool isSorted(std::vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
