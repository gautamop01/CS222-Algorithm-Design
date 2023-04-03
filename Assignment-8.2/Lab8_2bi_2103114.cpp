/*
*** Name - Gautam Kumar Mahar 
*** Roll Number - 2103114

*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Function to compute the frequency of each character in a string
vector<pair<char, int>> computeFrequency(string s) {
    // Initialize an empty vector to store the frequency of each character
    vector<pair<char, int>> freq;

    // Iterate over each character in the string
    for (char c : s) {
        // Check if the character has already been counted
        bool found = false;
        for (int i = 0; i < freq.size(); i++) {
            if (freq[i].first == c) {  // f freq[i].first is == c, it means that the character has already been counted and its frequency needs to be incremented.
                freq[i].second++;// Here we freq[i].second is used to access the second element 
                found = true;  // found is a boolean variable that is used to keep track of whether the character c has been found in the freq vector or not. 
                break;
            }
        }
        // If the character has not been counted, add it to the vector
        if (!found) {
            freq.push_back(make_pair(c, 1));
        }
    }

    // Sort the vector in increasing order of frequency
    sort(freq.begin(), freq.end(), [](const pair<char, int>& a, const pair<char, int>& b) {  //  takes two pairs of characters and their frequencies (a and b)
        return a.second < b.second; // if the frequency of a is less than the frequency of b, indicating that a should come before b in the sorted sequence.
    });

    // Return the vector
    return freq;
}

int main() {
    // Test the function
    string s = "gghgtyujghj";
    vector<pair<char, int>> freq = computeFrequency(s);
    for (auto p : freq) {
        cout << p.first << ": " << p.second << endl;
    }
    return 0;
}
