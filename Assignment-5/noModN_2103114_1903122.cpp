/*
... Kanwarraj Singh(1903122) & Gautam Kumar Mahar(2103114)
... C++ code for operator overloading for base b number using template
*/

#include <iostream>
using namespace std;


// Template class "noModN" with a single integer template parameter N
template <int N>
class noModN
{
private:
    int m_data; // member variable "m_data" to store the integer value

public:
    // Default constructor that initializes m_data to 0
    noModN()
    {
        m_data = 0;
    }

    // Parameterized constructor that takes in an integer and stores its remainder when divided by N
    noModN(int x)
    {
        pair<int, int> result = divide(x, N);
        m_data = result.second;
    }

    // Utility function to calculate the quotient and remainder of a division operation
    pair<int, int> divide(int a, int b) const
    {
        int quotient = a / b;
        int remainder = a - quotient * b;
        return {quotient, remainder};
    }

    // Overloading the + operator to add two noModN objects and return the result in another noModN object
    noModN operator+(const noModN &value) const
    {
        int sum = m_data + value.m_data;
        auto result = divide(sum, N).second;
        if (result < 0)
            result += N;
        return noModN(result);
    }

    // Overloading the - operator to subtract two noModN objects and return the result in another noModN object
    noModN operator-(const noModN &value) const
    {
        int difference = m_data - value.m_data;
        auto result = divide(difference, N).second;
        if (result < 0)
            result += N;
        return noModN(result);
    }

    // Overloading the unary - operator to find the negative of a noModN object
    noModN operator-() const.
    {
        return noModN(N - m_data);
    }

    // Overloading the * operator to multiply two noModN objects and return the result in another noModN object
    noModN operator*(const noModN &value) const
    {
        int result = divide((divide(m_data, N).second * divide(value.m_data, N).second), N).second;
        auto mod_result = divide(result, N).second;
        if (result < 0)
            result += N;
        return noModN(mod_result);
    }

    // Overloading the prefix ++ operator to increment a noModN object by 1
    noModN operator++()
    {
        int plus_1 = m_data + 1;
        auto result = divide(plus_1, N).second;
        if (result < 0)
            result += N;
        return noModN(result);
    }

    // Overloading the postfix ++ operator to increment a noModN object by 1
    noModN operator++(int)
    {
        noModN temp = *this;
        int temp_value = m_data;
        int plus_1 = m_data + 1;
        auto result = divide(plus_1, N).second;
        m_data = result;
        // if the result is negative, add N to it to ensure it is within the valid range [0, N-1]
        if (result < 0)
        {
            return temp_value + N;
        }
        // return the original value of the object before incrementing
        return temp;
    }
    // Overloading the stream insertion operator << to output the value of a noModN object
    friend ostream &operator<<(ostream &cout, const noModN &modN)
    {
        cout << modN.m_data;
        return cout;
    }
};

int main()
{
   int i, j, k;
    cout << "Enter the value x:";
    cin >> i;
    cout << "Enter the value y:";
    cin >> j;
    cout << "Enter the value z:";
    cin >> k;

    noModN<70> a(i), b(j), c(k);

    cout << "(a + b) * c = " << (a + b) * c << endl;
    cout << "-a = " << -a << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a++ = " << a++ << endl;
    cout << "++a = " << ++a << endl;

    return 0;
}
