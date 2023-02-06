/*
... Kanwarraj Singh(1903122) & Gautam Kumar Mahar(2103114)
... C++ code for operator overloading for base b number using template
*/
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>
#include <cstdio>
#include <cstring>
using namespace std::chrono;
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

template <int b> // template that will create a new class for every new base b

class base_b
{
private:
    vector<int> data; // private vector data
public:
    // Default constructor
    base_b(){}; 

    // construtor that converts (+ve) int to base b
    //  it will give output as [idx1 : idx2]
    base_b(int base)
    {
        if (base == 0)
        {
            data.push_back(0);
        }
        for (int i = base; i > 0; i /= b)
        {
            int index = 0;
            data.insert(data.begin() + index++, i % b);
        }
    }

    // Overload the `<<` operator for the `base_b` class
    friend ostream &operator<<(ostream &write, const base_b<b> &obj)
    {
        write << "[";
        for (int i = 0; i < obj.data.size(); i++)
        {
            write << obj.data[i];
            if (obj.data.size() - i - 1)
                write << ":";
        }
        write << "]";
        return write;
    }

    // Overloading the plus operator
    base_b operator+(const base_b &sum)
    {
        base_b result;
        int carry = 0;
        int s1 = data.size(), s2 = sum.data.size();
        for (int i = 0; i < max(data.size(), sum.data.size()); i++)
        {
            int x = (0 < s1) ? data[--s1] : 0;          // select the value from end to begin in first object member data
            int y = (0 < s2) ? sum.data[--s2] : 0;      // select the value from end to begin in second object member data
            result.data.push_back((x + y + carry) % b); // storing the value after addition
            carry = (x + y + carry) / b;                // updated carry
        }
        // To store Non-Zero Carry 
        if (carry != 0)
        {
            result.data.push_back(carry);
        }
        // reversing the vector                                   
        reverse(result.data.begin(), result.data.end());
        return result;
    }

    // Overloading the * operator
    base_b operator*(const base_b &other)
    {
        base_b result, null(0);
        result.data.resize(data.size() + other.data.size());
        for (int i = data.size() - 1; i >= 0; i--)
        {
            for (int j = other.data.size() - 1; j >= 0; j--)
            {
                result.data[i + j + 1] += data[i] * other.data[j]; // After multipliing, add it to the same index which is already a value store
            }                                                     // The last index will decrease
        }
        null.data.resize(data.size() + other.data.size());
        result = null + result; // it'll reconvert in same base after adding same size null object

        // To remove 0 in starting
        while (result.data.size() > 1 && result.data.front() == 0)
        {
            result.data.erase(result.data.begin());
        }

        return result;
    }

    // Overloading the < operator
    int operator<(const base_b &less)
    {
        int index = 0;
        if (data.size() != less.data.size())
        { // checking acording to size
            return (data.size() < less.data.size()) ? 1 : 0;
        } // in case equal size
        for (int i = 0; data[i] == less.data[i]; i++)
        {
            index++;
        } // Searching the index on which the value is changed, from the beginning
        if (index > data.size())
        {
            index--;
        } // Incase are equal both vector
        if (data[index] < less.data[index])
        {
            return 1;
        } // checkin the value at that index
        else
        {
            return 0;
        }
    }

    // Overloading the - operator
    base_b operator-(const base_b &sub)
    {
        base_b result, tempData = *this, tempSub = sub; // using = operator
        int index = 0;
        vector<int> base1(b);
        int s1 = data.size(), s2 = sub.data.size();
        for (int i = 0; i < max(data.size(), sub.data.size()); i++)
        {
            int x = (0 < s1) ? tempData.data[--s1] : 0;
            int y = (0 < s2) ? tempSub.data[--s2] : 0;
            int a = (x >= y) ? x - y : ((x + b) - y);
            if (x < y)
                tempData.data[s1 - 1] = tempData.data[s1 - 1] - 1; // subtract
            result.data.push_back(a);
        }
        while (result.data.size() > 1)
        {
            if (result.data.back() == 0)
            {
                result.data.pop_back();
            }
            else
            {
                break;
            }
        }

        reverse(result.data.begin(), result.data.end());
        return result;
    }

    /*
    *** Overloading the <= operator
    *** it's similar to < operator overloading
    *** but it will return true in case equal object
     */
    int operator<=(const base_b &lessOReq)
    {
        int index = 0;
        if (data.size() != lessOReq.data.size())
        {
            return (data.size() < lessOReq.data.size()) ? 1 : 0;
        }
        for (int i = 0; data[i] == lessOReq.data[i]; i++)
        {
            index++;
        }
        if (index > data.size())
        {
            index--;
        }
        if (data[index] <= lessOReq.data[index])
        {
            return 1;
        } 
        else
        {
            return 0;
        }
    }

    // Overloading the / operator
    base_b operator/(const base_b &divisor)
    {
        if (divisor.data.empty())
        {
            throw runtime_error("Division by zero"); // In case divisoin from zeroes
        }
        int quotient = 0;
        base_b tempData = *this, tempDiv = divisor; // u sing = operator
        base_b null(0);
        tempData.data.resize(data.size());
        tempDiv.data.resize(divisor.data.size());
        if (tempData < divisor)
        {
            return null;
        } // incase a<b and compute a/b return zero quotient (< o)
        while (tempDiv <= tempData)
        {
            tempData = tempData - tempDiv; // repeated subtraction
            quotient++;                    // compute quotient
        }
        base_b<b> result(quotient); // convert quotient in same base
        return result;
    }

    // Overloading the ++ operator (prefix)
    base_b &operator++()
    {
        int carry = 1;
        for (int i = data.size() - 1; i >= 0 && carry > 0;)
        {
            int current = data[i] + carry; // addition of 1 in vector
            data[i] = current % b;         // convert in same base
            carry = current / b;
            i--;
        }
        if (carry)
        {
            reverse(data.begin(), data.end());
            data.push_back(carry);
            reverse(data.begin(), data.end());
        }
        // return the object after derefernce
        return *this;
    }
    // Overloading the ++ operator (postfix)
    base_b operator++(int)
    { // non-void because it will be similer to prefix
        base_b result(*this);
        ++(*this); // using prefix it will be updated
        return result;
    }

    // Overloading the = operator
    void operator = (const base_b &equal)
    { // assighned the value of first object to another
        data.resize(equal.data.size());
        for (int i = 0; i < equal.data.size(); i++)
        {
            this->data[i] = equal.data[i];
        }
    }
};
int main()
{
    int x, y, z;
    cout << "Please Enter x -->  " ;  cin >> x; 
    cout << "Please Enter y -->  ";  cin >> y;
    cout << "Please Enter z -->  ";   cin >> z;
    base_b<37> X(x), Y(y), Z(z); // Call the Converter
    cout << " x in base 37 is --> " << X << endl;
    cout << " y in base 37 is --> " << Y << endl;
    cout << " z in base 37 is --> " << Z<< endl;
    cout << "(x+y)*z is --> " << ((X + Y) * Z) << endl; 
    cout << "(x/y*y) is --> " << (X / (Y)*(Y)) << endl; 
    cout << "(x++) is -->  " << (X++) << endl;
    cout << "(++x) is --> " << (++X) << endl;
    cout << "(x - y ) is --> " << ( X - Y ) << endl;
}