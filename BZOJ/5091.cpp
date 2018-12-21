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
const int mod = 1e9 + 7,N = 2e5 + 50;
int n,m,k;

inline ll ksm(int x,int y)
{
	ll ans = 1;
	while(y)
	{
		if(y&1) ans = ans * x % mod;
		x = 1ll * x * x % mod; y >>= 1;
	}
	return ans;
}

int a[N],in[N];
int main()
{
	read(n); read(m); read(k);
	rep(i,1,n) read(a[i]);
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		++ in[u]; ++ in[v];
	}
	int ans = 0;
	int inv = ksm(2*m,mod-2);
	rep(i,1,n) ans = (ans + 1ll*a[i]*k%mod*in[i]%mod*inv)%mod;
	cout << ans << endl;
	return 0;
}
