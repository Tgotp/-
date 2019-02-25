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

int n,m,fac[4001001];
const int mod = 20100403;

inline int ksm(int x,int y)
{
	int ans = 1;
	while(y)
	{
		if(y&1) ans = 1ll * ans * x % mod;
		x = 1ll *x * x % mod; y >>= 1;
	}
	return ans;
}

inline ll c(int n,int m)
{
	return 1ll *fac[n] * ksm(fac[m],mod-2) % mod * ksm(fac[n-m],mod-2) % mod;
}

int main()
{
	fac[0] = 1;
	read(n); read(m);
	rep(i,1,n+m) fac[i] = 1ll * fac[i-1] * i % mod;
	if(n < m) return puts("0"),0;
	printf("%lld\n",(c(n + m,m)-c(n+m,m-1) + mod) % mod);

	return 0;
}
