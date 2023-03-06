/* 
Gautam Kumar Mahar ( 2103114 )
Kanwarraj Singh (1903122)
Assignment - 6 - Modular division
*/

#include <iostream>
using namespace std;

class noModN {
private:
    int val;
    int N = 60; // Set N = 60

    
    // Private function for Extended Euclid's algorithm
    void extendedEuclid(int a, int b, int& x, int& y, int& gcd) {
        if (b == 0) {
            x = 1;
            y = 0;
            gcd = a;
            return;
        }
        int x1, y1;
        extendedEuclid(b, a % b, x1, y1, gcd);
        x = y1;
        y = x1 - (a / b) * y1;
    }
    
public:
    pair<int, int> divide(int a, int b) const {  // To function for get the remainder and quotient 
        int quotient = a/b;
        int remainder= a-quotient*b;
        return {quotient,remainder};
    }
    // Constructor to set the value of noModN object
    noModN(int v) {
        val = v % N; // // Ensure that the value is between 0 and N-1
    }
    
    // Public function to find the inverse of a number modulo N
    int findInverse() {
        int x, y, gcd;
        extendedEuclid(val, N, x, y, gcd); // Use the extended Euclid's algorithm to find the inverse
        if (gcd != 1) {
            throw runtime_error("Inverse does not exist");  // If the inverse does not exist, throw an error
        }
        return (x+N) % N; // Return the inverse modulo N
    }
    
    // Overloading the division operator
    noModN operator/(noModN y) {
        int inverse = y.findInverse(); // Find the inverse of y
        return noModN((val * inverse) % N); // Return a new noModN object with the result of division
    }
    
    // Getter function to get the value of noModN object
    int getValue() {
        return val;  // Return the value 
    }
};

// Main Function 
int main() {
    noModN x1(6);
    noModN y1(31);
    noModN z1 = x1 / y1; // Divide x1 by y1 
    cout << "Result : "<< x1.getValue() << " / " << y1.getValue() << " = " << z1.getValue() << endl;
    
    // noModN x2(6);
    // noModN y2(10);
    // noModN z2 = x2 / y2; // Divide x2 by y2 
    // cout << x2.getValue() << " / " << y2.getValue() << " = " << z2.getValue() << endl;
    
    return 0;
}
