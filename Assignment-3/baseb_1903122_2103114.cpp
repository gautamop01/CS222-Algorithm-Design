#include <bits/stdc++.h>
#include <chrono>
#include <math.h>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace std::chrono;
#include <vector>

class Solution
{
public:
    vector<string> getNumber(int B, int N)
    {
        vector<string> v;
        int a, t;
        while (N > 0)
        {
            a = N / B;
            t = N % B;

            if (t < 10)
            {
                v.push_back(to_string(t));
            }
            if (t == 10)
            {
                v.push_back("A");
            }
            if (t == 11)
            {
                v.push_back("B");
            }
            if (t == 12)
            {
                v.push_back("C");
            }
            if (t == 13)
            {
                v.push_back("D");
            }
            if (t == 14)
            {
                v.push_back("E");
            }
            if (t == 15)
            {
                v.push_back("F");
            }

            N = a;
        }
        reverse(v.begin(), v.end());
        return v;
    }
vector<string> addnumber(int B, int a , int b){
    int sum = a + b;
    return getNumber(B,sum);
}

};

int main()
{
    Solution ob;
    int B, N, X;
    cout<<"Enter the Integer :"<<endl;
    cin >> N;
    cout<<"Enter the Base : "<<endl;
    cin>> B;
    cout<<"Integer "<<N<< " In base "<<B<<" will be : "<<endl;
    vector<string> ans1 = ob.getNumber(B, N);
    for (int i = 0; i < ans1.size(); i++)
    {
        cout << ans1[i];
    }
    cout << endl;
    int x , y,z;
    cout<<"Enter the first Number : "<<endl;
    cin>>x;
    cout<<"Enter the second Number : "<<endl;
    cin>>y;
    cout<<"Enter the Base : "<<endl;
    cin>>z;
    cout<<"Sum of "<<x<<" & "<<y<<" in base "<<z<<" is : "<<endl;
    vector<string> sum = ob.addnumber(z, x, y);
    for (int i = 0; i < sum.size(); i++)
    {
        cout << sum[i];
    }
    cout << endl;
}