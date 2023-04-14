#include <iostream>
#include <vector>

void countingSort(std::vector<int>& arr);
bool isSorted(std::vector<int>& arr);

int main() {
    // best case: already sorted
    std::vector<int> arr1 = { 1, 2, 3, 4, 5 };
    countingSort(arr1);
    std::cout << "Best case: ";
    if (isSorted(arr1)) {
        std::cout << "Passed \n";
    }
    else {
        std::cout << "Failed \n";
    }

}

void countingSort(std::vector<int>& arr) {
    const int sizeArray = arr.size();
    if (sizeArray == 0) {
        return;
    }

    // find the range of values
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < sizeArray; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // initialize the counting array
    const int sizeCountArray = maxVal - minVal + 1;
    std::vector<int> countArray(sizeCountArray, 0);

    // count the occurrences of each value
    for (int i = 0; i < sizeArray; i++) {
        countArray[arr[i] - minVal]++;
    }

    // calculate the prefix sums
    for (int i = 1; i < sizeCountArray; i++) {
        countArray[i] += countArray[i - 1];
    }

    // create the sorted array
    std::vector<int> sortedArray(sizeArray);
    for (int i = sizeArray - 1; i >= 0; i--) {
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