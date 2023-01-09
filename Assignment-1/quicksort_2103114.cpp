/* Name - Gautam Kumar Mahar
   Roll.n. 2103114
   Branch - CSE
   Assignment - 1
*/
// Header files
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// This function partitions the given array into two subarrays around the pivot element
int PartationOfArr(vector<int> &arr, int low, int high)
{
    // The pivot element is the element at the high index
    int pivot = arr[high];
    // The partition index is the index of the first element that is greater than the pivot
    int partitionIndex = low - 1;
    // Iterate through the array and partition it around the pivot element
    for (int j = low; j <= high - 1; j++)
    {
        // If the current element is smaller than the pivot element,
        // swap it with the element at the partition index and increment the partition index
        if (arr[j] < pivot)
        {
            partitionIndex++;
            swap(arr[partitionIndex], arr[j]);
        }
    }
    // Swap the pivot element with the element at the partition index
    swap(arr[high], arr[partitionIndex + 1]);
    return partitionIndex + 1;
}

// This function sorts the given array using quicksort
void quicksort(vector<int> &arr, int low, int high)
{
    // Recursive base case: the array is already sorted if it has 0 or 1 elements
    if (high <= low)
        return;
    // Partition the array around the pivot element
    int part = PartationOfArr(arr, low, high);
    // Recursively sort the left and right subarrays
    quicksort(arr, low, part - 1);
    quicksort(arr, part + 1, high);
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
        vector<int> arr(arraySize);
        // Declare and fill the array with random values
        auto randomValueGenerator = []() -> int
        { return rand() % 100000; };
        generate(arr.begin(), arr.end(), randomValueGenerator);

        // Record the start time
        auto start = high_resolution_clock::now();
        // Sort the array
        quicksort(arr, 0, arraySize - 1);
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
    // calculating Mean and variance
    double Mean = 0, variance = 0, Mean_square = 0;

    for (int i = 0; i < ciValues.size(); i++)
    {
        Mean += ciValues[i] / ciValues.size();
        Mean_square += pow(ciValues[i], 2) / ciValues.size();
    }
    variance = Mean_square - pow(Mean, 2);
    cout << "Expectation Value is : " << Mean << " ms\n" << "Variance Value is : " << variance << " square_ms";
    return 0;
}
/* Thank You */