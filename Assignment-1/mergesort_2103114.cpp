/* Name - Gautam Kumar Mahar
   Roll.n. 2103114
   Branch - CSE
   Assignment - 1
*/
// Header files
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// This function merges two sorted subarrays (leftArray and rightArray)
// into the given array in a sorted fashion
void MergeArray(vector<int> &array, int const left, int const mid, int const right)
{
    // Calculate the sizes of the left and right subarrays
    auto const lengthOfLeftArray = mid - left + 1;
    auto const lengthOfRightArray = right - mid;

    // Declare the left and right subarrays
    auto *leftArray = new int[lengthOfLeftArray],
         *rightArray = new int[lengthOfRightArray];

    // Fill the left and right subarrays
    for (auto i = 0; i < lengthOfLeftArray; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < lengthOfRightArray; j++)
        rightArray[j] = array[mid + 1 + j];

    auto leftIndex = 0;
    auto rightIndex = 0;
    int mergedArrayIndex = left;

    // Merge the subarrays and store the result in the original array
    while (leftIndex < lengthOfLeftArray && rightIndex < lengthOfRightArray)
    {
        if (leftArray[leftIndex] <= rightArray[rightIndex])
        {
            array[mergedArrayIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else
        {
            array[mergedArrayIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedArrayIndex++;
    }
    // Copy the remaining elements of the left subarray, if any
    while (leftIndex < lengthOfLeftArray)
    {
        array[mergedArrayIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedArrayIndex++;
    }
    // Copy the remaining elements of the right subarray, if any
    while (rightIndex < lengthOfRightArray)
    {
        array[mergedArrayIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedArrayIndex++;
    }
    // Free memory
    delete[] leftArray;
    delete[] rightArray;
}

// This function performs merge sort on the given array between
// the indices left and right (inclusive)
void mergeSort(vector<int> &array, int const begin, int const end)
{
    if (begin >= end)
        return; // Recursive base case
    // Calculate the midpoint of the array
    auto mid = begin + (end - begin) / 2;
    // Recursively sort the left and right subarrays
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    // Merge the sorted subarrays
    MergeArray(array, begin, mid, end);
}

int main()
{
    vector<double> ciValues;

    int k;
    cout << "What is k ? ";
    cin >> k;
    cout << "Here is Tuple (i,2**i,T(2**i),i*2**i,c_i) for each iteration:" << endl;
    for (int i = 1; i <= k; i++)
    {
        // Calculate the size of the array
        auto arraySize = pow(2, i);
        // Declare and fill the array with random values
        vector<int> arr(arraySize);
        auto randomValueGenerator = []() -> int
        { return rand() % 100000; };
        generate(arr.begin(), arr.end(), randomValueGenerator);

        // Record the start time
        auto start = high_resolution_clock::now();
        // Sort the array
        mergeSort(arr, 0, arraySize - 1);
        // Record the stop time
        auto stop = high_resolution_clock::now();
        // Calculate the duration of the sorting operation in microseconds
        auto duration = duration_cast<microseconds>(stop - start);
        // Calculate the c_i value for this iteration

        double ci = duration.count() / (arraySize * i);
        // Store the c_i value in the array
        ciValues.push_back(ci);
        // Print the tuple for this iteration
        cout << i << " " << arraySize << " " << duration.count() << " " << i * arraySize << " " << ci << endl;
    }

    // Calculate the Mean and Variance of the c_i values
    double Mean = 0, Variance = 0, Mean_square = 0;

    for (int i = 0; i < ciValues.size(); i++)
    {
        // Calculate the Mean of the c_i values
        Mean += ciValues[i] / ciValues.size();
        // Calculate the Mean of the squares of the c_i values
        Mean_square += pow(ciValues[i], 2) / ciValues.size();
    }
    // Calculate the Variance
    Variance = Mean_square - pow(Mean, 2);
    cout << "Expectation is : " << Mean << " ms\n" << "Variance is : " << Variance << " square_ms";
    return 0;
}
/* Thank You */