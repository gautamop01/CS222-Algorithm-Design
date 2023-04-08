/*
*** Name - Gautam Kumar Mahar 
*** Roll Number - 2103114
*** Name - Kanwarraj Singh
*** Roll Number - 1903122
*/

#include <bits/stdc++.h> // include all standard C++ libraries
using namespace std;

class Node // define a Node class
{
public:
    int VALUE;   // integer value for frequency
    Node *left;  // pointer to left child node
    char CHAR;   // character value for the node
    Node *right; // pointer to right child node

    Node(int FREQUENCY, int ch) // constructor for a leaf node
    {
        left = NULL;
        right = left;
        CHAR = ch;
        VALUE = FREQUENCY;
    }

    Node(Node *l, Node *r) // constructor for an internal node
    {
        VALUE = l->VALUE + r->VALUE; // frequency of an internal node is the sum of its children's frequencies
        left = l;
        right = r;
        CHAR = '#';                  // internal nodes have '#' as their character value
        
    }

    Node(Node *l) // constructor for a copied node
    {
        CHAR = l->CHAR;
        VALUE = l->VALUE;
        left = l->left;
        right = l->right;
    }
};

class COMPARE_FUNC // define a comparison function for the priority queue
{
public:
    bool operator()(Node *a, Node *b) // this operator defines how to compare two nodes
    {
        return a->VALUE > b->VALUE; // priority queue will order nodes by increasing frequency
    }
};

// This function takes a string as input and returns a vector of pairs
// where each pair contains a character from the input string and its count
vector<pair<char, int>> count(string str)
{
    // create an empty vector to store the result
    vector<pair<char, int>> RESULT;

    // loop over each character in the input string
    for (int i = 0; i < str.size(); i++)
    {
        // create a boolean variable to keep track of whether the current character
        // has been seen before in the result vector
        bool VALUE = 0;

        // loop over each pair in the result vector
        for (auto &j : RESULT)
        {
            // if the current character has already been seen in the result vector,
            // increment its count and set the boolean variable to true
            if (j.first == str[i])
            {
                j.second++;
                VALUE = 1;
            }
        }

        // if the current character has not been seen before in the result vector,
        // add a new pair to the result vector with a count of 1
        if (VALUE == 0)
            RESULT.push_back({str[i], 1});
    }

    // sort the result vector based on the counts of the characters
    // using bubble sort algorithm
    for (int i = 1; i < RESULT.size(); i++)
    {
        for (int j = 0; j < RESULT.size() - i; j++)
        {
            if (RESULT[j + 1].second < RESULT[j].second)
            {
                pair<char, int> temp = RESULT[j];
                RESULT[j] = RESULT[j + 1];
                RESULT[j + 1] = temp;
            }
        }
    }

    // return the result vector
    return RESULT;
}

// Function to calculate the edit distance between two strings
string EDIT_DISTANCE_BETWEEN(string STRING1, string STRING2)
{
    // Create a 2D vector to store the edit distance values
    vector<vector<int>> ARRAY(STRING2.size() + 1, vector<int>(STRING1.size() + 1, 0));

    // Initialize the first row of the vector with deletion cost values
    for (int i = 1; i < ARRAY.size(); i++)
        ARRAY[i][0] = 3 + ARRAY[i - 1][0];

    // Initialize the first column of the vector with insertion cost values
    for (int i = 1; i < ARRAY[0].size(); i++)
        ARRAY[0][i] = 1 + ARRAY[0][i - 1];

    // Fill the remaining cells of the vector by comparing the characters of both strings
    for (int i = 1; i <= STRING2.size(); i++)
    {
        for (int j = 1; j <= STRING1.size(); j++)
        {
            // If the characters match, there is no cost incurred
            if (STRING2[i - 1] == STRING1[j - 1])
                ARRAY[i][j] = ARRAY[i - 1][j - 1];
            // If the characters don't match, calculate the cost of the minimum of three possible operations
            else
                ARRAY[i][j] = min({ARRAY[i - 1][j] + 3, ARRAY[i][j - 1] + 1, ARRAY[i - 1][j - 1] + 2});
        }
    }

    // Print the final edit distance value
    cout << "THE EDITING DISTANCE BETWEEN THE PROVIDED STRINGS IS --> " << ARRAY[STRING2.size()][STRING1.size()] << endl;
    cout << endl;

    // Initialize variables for backtracking
    int i = STRING2.size();
    int j = STRING1.size();
    string RESULT = STRING1;

    // Backtrack to find the edit operations performed
    cout << "TOTAL OPERATIONS -->" << endl;
    while (i > 0 && j > 0)
    {
        // If the characters match, move to the previous diagonal cell
        if (j - 1 >= 0 && i - 1 >= 0 && STRING1[j - 1] == STRING2[i - 1])
        {
            i--;
            j--;
        }
        // If there is a substitution, move to the previous diagonal cell and print the operation
        else if (ARRAY[i][j] == ARRAY[i - 1][j - 1] + 2)
        {
            cout << "SO, WE CHANGE " << j - 1 << " --> "
                 << " TO --> " << STRING2[i - 1] << endl;

            // Append the operation to the RESULT string
            RESULT += '2';              // 2 indicates substitution
            RESULT += STRING2[i - 1];      // the character that replaces the original one
            RESULT += to_string(j - 1); // the index of the original character

            i--;
            j--;
        }
        // If there is a deletion, move to the previous column and print the operation
        else if (ARRAY[i][j] == ARRAY[i][j - 1] + 1)
        {
            cout << "WE DELETE " << j - 1 << endl;

            // Append the operation to the RESULT string
            RESULT += '1'; // 1 indicates deletion
            RESULT += '@'; // a placeholder for the deleted
            RESULT += to_string(j - 1);

            j--;
        }
        else if (ARRAY[i][j] == ARRAY[i - 1][j] + 3)
        {
            // If the value in the current cell is obtained by adding a character from STRING2
            // then append the character and the index to the RESULT string
            cout << "WE INSERT " << STRING2[i - 1] << " AT " << j << endl;
            RESULT += '0';
            RESULT += STRING2[i - 1];
            RESULT += to_string(j);
            i--;
        }
    }

    // While there are still characters in STRING1 that haven't been matched with STRING2
    while (j != 0)
    {
        // Append a '1' to the RESULT string to indicate deletion
        cout << "DELETE  " << j - 1 << endl;
        RESULT += '1';
        // Append '@' and the index to the RESULT string to indicate which character is deleted
        RESULT += '@';
        RESULT += to_string(j - 1);
        j--;
    }

    // While there are still characters in STRING2 that haven't been matched with STRING1
    while (i != 0)
    {
        // Append a '0' to the RESULT string to indicate insertion
        cout << "INSERT " << STRING2[i - 1] << " AT " << j << endl;
        RESULT += '0';
        // Append the character and the index to the RESULT string to indicate where it is inserted
        RESULT += STRING2[i - 1];
        RESULT += to_string(j);
        i--;
    }

    // Return the RESULT string, which contains a sequence of operations that transforms STRING1 into STRING2
    cout << endl;
    return RESULT;
}

// This function takes the root node of a Huffman tree, a reference to an unordered map to store the Huffman codes, and a string encoding (which is initially an empty string)
void HUFFMAN_CODE(Node *root, unordered_map<char, string> &TABLE, string ENCODING)
{
    // If the root node is NULL (i.e., the tree is empty), then simply return from the function
    if (root == NULL)
        return;

    // If the root node is a leaf node (i.e., it has no children), then it represents a character in the input string, and its Huffman code is the encoding string that has been built up so far
    if (root->left == NULL && root->right == NULL)
    {
        // Store the Huffman code for this character in the unordered map
        TABLE[root->CHAR] = ENCODING;
    }
    // If the root node is not a leaf node (i.e., it has children), then recursively traverse the left and right subtrees, appending '0' to the encoding string when going left and '1' when going right
    else
    {
        HUFFMAN_CODE(root->left, TABLE, ENCODING + '0');
        HUFFMAN_CODE(root->right, TABLE, ENCODING + '1');
    }
}

// This function takes a priority queue of Node pointers, which represents a set of Huffman trees, and recursively combines the trees into a single Huffman tree
Node *HUFFMAN_TREE(priority_queue<Node *, vector<Node *>, COMPARE_FUNC> &PRIORITY_QUEUE)
{
    // If there is only one tree left in the priority queue, return that tree (which is the root of the Huffman tree)
    if (PRIORITY_QUEUE.size() == 1)
        return PRIORITY_QUEUE.top();

    // Otherwise, remove the two smallest trees from the priority queue and combine them into a new tree, which is then added back to the priority queue
    Node *l = new Node(PRIORITY_QUEUE.top()); // Create a new node and copy the contents of the top element in the priority queue into it (i.e., the smallest tree)
    PRIORITY_QUEUE.pop();                     // Remove the top element from the priority queue
    Node *r = new Node(PRIORITY_QUEUE.top()); // Create another new node and copy the contents of the new top element in the priority queue into it (i.e., the second smallest tree)
    PRIORITY_QUEUE.pop();                     // Remove the second smallest element from the priority queue
    PRIORITY_QUEUE.push(new Node(l, r));      // Create a new node that has l and r as its left and right children, respectively, and add it back to the priority queue

    // Recursively call the HUFFMAN_TREE function with the updated priority queue
    return HUFFMAN_TREE(PRIORITY_QUEUE);
}

// This function takes two input strings and performs Huffman encoding on their edit distance string
void HUFFMAN_ENCODING(string STRING1, string STRING2)
{
    // Compute the edit distance between the two input strings and store it in a new string
    string str = EDIT_DISTANCE_BETWEEN(STRING1, STRING2);
    cout << "BEFORE ENCODING, THE MESSAGE :" << str << endl;
    cout << endl;

    // Count the frequency of each character in the edit distance string and store the counts in a vector of pairs
    vector<pair<char, int>> temp = count(str);
    cout << " HERE IS FREQUENCY TABLE --> " << endl;
    cout << " CHARACTER "
         << " FREQUENCY  " << endl;
    for (auto k : temp)
    {
        cout << k.first << "              " << k.second << endl;
    }

    // Create a priority queue of Node pointers, where each Node represents a tree with a single character and its frequency
    priority_queue<Node *, vector<Node *>, COMPARE_FUNC> PRIORITY_QUEUE;
    for (auto i : temp)
    {
        PRIORITY_QUEUE.push(new Node(i.second, i.first));
    }

    // Construct the Huffman tree by repeatedly combining the two smallest trees in the priority queue
    Node *root = HUFFMAN_TREE(PRIORITY_QUEUE);

    // Generate a table of Huffman codes for each character in the edit distance string using the Huffman tree
    unordered_map<char, string> TABLE;
    string sl = "";
    HUFFMAN_CODE(root, TABLE, sl);

    // Print the Huffman code table
    cout << endl;
    cout << "THIS IS HUFFMAN_CODE TABLE --> " << endl;
    cout << "CHAR "
         << "  ENCODING " << endl;
    for (auto i : TABLE)
    {
        cout << i.first << "     " << i.second << endl;
    }

    // Encode the edit distance string using the Huffman code table
    string MESSAGE = "";
    for (auto i : str)
    {
        MESSAGE += TABLE[i];
    }

    // Print the original and encoded messages
    cout << endl;
    cout << "MESSAGE BEFORE ENCODING --> " << str << endl;
    cout << "MESSAGE AFTER ENCODING  --> " << MESSAGE << endl;
}

// This is the main function of the program
int main()
{
    // Prompt the user to enter the two input strings
    string STRING1, STRING2;
    cout << "PLEASE ENTER THE FIRST STRING --> ";
    cin >> STRING1;
    cout << "PLEASE ENTER THE SECOND STRING --> ";
    cin >> STRING2;
    cout << endl;

    // Perform Huffman encoding on the edit distance string between the two input strings
    HUFFMAN_ENCODING(STRING1, STRING2);
}
