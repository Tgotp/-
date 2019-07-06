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

const int mod = 1e9 + 7,N = 1e6 + 50;
int f[N],fac[N],m,n,h,d;

inline int ksm(int x,int y)
{
	int ans = 1;
	while(y)
	{
		if(y&1) ans = 1ll * ans * x % mod;
		y >>= 1; x = 1ll * x * x % mod;
	}
	return ans;
}
int main()
{
	read(n); read(h); read(d);
	f[0] = 1; fac[0] = 1;
	rep(i,1,n) fac[i] = 1ll * fac[i-1] * i % mod;
	rep(i,1,n) m = (m + fac[i]) % mod;

	rep(i,1,h)
	{
		f[i] = 1ll * (f[i - 1] - (i - d - 1 >= 0 ? f[i - d - 1] : 0)) * m % mod;
		if(f[i] < 0) f[i] = f[i] + mod;

		f[i] = (f[i-1] + f[i]) % mod;
	}
	
	cout << 1ll * (f[h] - f[h-1] + mod) % mod * fac[n] % mod * ksm(m,mod-2) % mod << endl;
	
	return 0;
}
