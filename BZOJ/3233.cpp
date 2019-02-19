#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 51,M = 1e5 + 50;
int n,mx;
int a[N],f[M];
int prime[M],cnt; bool vis[M];

void pre(int n)
{
	rep(i,2,n)	
	{
		if(!vis[i]) prime[++ cnt] = i;
		for(register int j = 1;prime[j] * i <= n; ++ j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
}

int main()
{
	read(n);
	rep(i,1,n) read(a[i]),mx = max(mx,a[i]);
	pre(mx);
	repd(i,mx,1)
	{
		rep(j,1,n) f[i] += a[j] / i;
		rep(j,1,cnt)
			if(i * prime[j] <= mx)
			{
				int t = f[i * prime[j]];
				rep(k,1,n) t += (a[k] % (i * prime[j])) / i;
				f[i] = min(f[i],t);
			}else break;
	}
	cout << f[1] << endl;
	return 0;
}
