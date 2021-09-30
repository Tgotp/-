#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	x = 0;char c;int sign = 1;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
 
const int N = 2e5 + 50,M = 5e6 + 50;
 
int n,a[N],sum[M],x[M],y[M];
int main()
{
//	freopen("1.in","r",stdin);
	read(n);
	rep(i,1,n) read(a[i]);
	
	rep(i,1,n) 
	{
		rep(j,i + 1,n)
		{
			int sum = a[i] + a[j];
			if(x[sum] && x[sum] != j && x[sum] != i && y[sum] != i && y[sum] != j)
			{
				puts("YES");
				printf("%d %d %d %d\n",i,j,x[sum],y[sum]);
				return 0;
			}
			x[sum] = i;y[sum] = j;
		}
	}
	
	puts("NO");
	
	return 0;
}

