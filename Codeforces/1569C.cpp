#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	x = 0; char c; int sign = 1;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
 
/*
1
6
3 4 2 1 3 3
*/
 
const int mod = 998244353,N = 2e5 + 50;
 
int n,a[N],f[N],inv[N];
 
inline int C(int n,int m) { return 1ll * f[n] * inv[m] % mod * inv[n - m] % mod; }
 
inline void solve()
{	
	read(n); 
	rep(i,1,n) read(a[i]);
	sort(a + 1,a + 1 + n);
	if(a[n] - a[n - 1] == 0) printf("%d\n",f[n]);
	else if(a[n] - a[n - 1] == 1) 
	{
		if(n == 2) return void (puts("1"));
		int x = 1,now = n - 1;
		while(now > 1 && a[now - 1] == a[now]) -- now,++ x;
		
		printf("%d\n",1ll * C(n,n - 1 - x) * f[n - 1 - x] % mod * f[x] % mod * x % mod);
	}
	else puts("0");
}
 
int main()
{
	int t,z = 200000;
	read(t);
	
	f[0] = 1; inv[0] = inv[1] = 1;
	rep(i,1,z) f[i] = 1ll * f[i-1] * i % mod;
	rep(i,2,z) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	rep(i,2,z) inv[i] = 1ll * inv[i] * inv[i - 1] % mod;
	
	while(t --) solve();
	return 0;
}
