/*
... Kanwarraj Singh(1903122) & Gautam Kumar Mahar(2103114)
... C++ code to find n fibonacci number using repeating square algorithm
*/
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>
#include <cstdio>
#include <cstring>
using namespace std;
using namespace std::chrono;


#define MOD 10000000008

/*
Function to find fibonacci number using repeating square method
*/
void Repeat_Sq(int n, int result[])
{
	// Base Condition
	int p, q, r, s;
	if (n == 0) {
		result[0] = 0;
		result[1] = 1;
		return;
	}
	Repeat_Sq((n / 2), result);

	p = result[0];

	// Here b = F(n+1)
	q = result[1];

	r = 2 * q - p;

	if (r < 0)
		r += MOD;

	// As F(2n) = F(n)[2F(n+1) – F(n)]
	// Here c = F(2n)
	r = (p * r) % MOD;

	// As F(2n + 1) = F(n)^2 + F(n+1)^2
	// Here d = F(2n + 1)
	s = (p * p + q * q) % MOD;

	// Check if N is odd OR odd
	if (n % 2 == 0) {
		result[0] = r;
		result[1] = s;
	}
	else {
		result[0] = s;
		result[1] = r + s;
	}
}

int main()
{
	int N; 
	cout<<"How many Fib Series Number you want : "<<endl;
	cin>>N;
	FILE* ptr = fopen("fibonacci_repeated_squaring.txt","w");
	int result[2] = { 0 };
	
	int t = 0;
	for (int  i = 1; i <= N; i++)
	{
		auto start = high_resolution_clock::now(); // start counting time here, 
		Repeat_Sq(i, result);
		t = result[0];			 // storing value in variable t, it takes neglagible time 
		auto stop = high_resolution_clock::now();		// stop counting time here, 
    	auto duration = duration_cast<nanoseconds>(stop - start);		// this is time taken by program to execute. 
    	double t2i = duration.count();		//t2i is time taken in execution
		fprintf(ptr,"%d->%d->%lf\n",i,t,t2i); 
		/*
		output will come in following format and store in file reapsq.txt
		number -> fibonacci number -> time taken to compute that Fib number
		*/
		cout << i <<","<< t <<","<< t2i<< endl;
	}
	fclose(ptr);
}
