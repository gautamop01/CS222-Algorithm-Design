/*
... Kanwarraj Singh(1903122) & Gautam Kumar Mahar(2103114)
... C++ code to find n fibonacci number using recursisve algorithm
*/
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace std::chrono;

int FIB(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else if (n == 2)
    {
        return 1;
    }

    else
    {
        return FIB(n - 1) + FIB(n - 2);
    }
}

int main()
{
    int x;
    cout << "Enter the Number" << endl;
    cin >> x;
    FILE *ptr = fopen("Fibonacci_Recursive.txt", "w");  // created a file name check0.txt to take output value there which will helpful in graph 
    int t = 0;
    for (int i = 1; i <= x; i++)
    {
        auto start = high_resolution_clock::now(); // start counting time here, 
        t = FIB(i);         // storing value in variable t, it takes neglagible time 
        auto stop = high_resolution_clock::now();  // stop counting time here, 
        auto duration = duration_cast<nanoseconds>(stop - start); // this is time taken by program to execute. 
        double t2i = duration.count();      //t2i is time taken in execution
        fprintf(ptr, "%d,%d,%lf\n", i, t, t2i);
        cout << i << t << t2i << endl;
    }
    fclose(ptr);
}