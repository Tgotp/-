#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i) 
using namespace std; 
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') c = getchar(); }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 4e6 + 50;
int f[N];
int n ,mod;

inline int add(int x,int y)
{
	return x + y > mod ? x + y - mod : x + y;
}

int main()
{
//	freopen("1.txt","w",stdout);
	read(n); read(mod);
	
	f[1] = 1;

//	get();
	rep(i,1,n)
	{
		
		if(i != 1) f[i] = add (2*f[i - 1] % mod ,f[i]);
		if(i == 2) f[i] -- ;
		int t = add(f[i] - f[i - 1],mod);
		for(int j = i * 2;j <= n;j += i)
		{
			f[j] = add(f[j],t);
		}
	}
	
	cout << (f[n] % mod + mod) % mod<< endl;
	
	return 0;	
}

/*

5 998244353
2 2 3
3 5 8
4 12 20
5 25 45

*/
