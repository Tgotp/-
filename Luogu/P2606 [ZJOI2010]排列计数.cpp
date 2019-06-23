#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 60;
int n,mod,sz[N],fac[N],inv[N];
int ans = 1;
vector<int> g[N];

int C(int n,int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod ; }

void dfs(int x)
{
	for(auto&i : g[x])
	{
		dfs(i);
		sz[x] += sz[i];
		ans = 1ll * ans * C(sz[x],sz[i]) % mod;
	}
	++ sz[x];
}

int main()
{
	read(n); read(mod);
	fac[0] = inv[0] = inv[1] = 1;
	rep(i,1,n) fac[i] = 1ll * fac[i - 1] * i % mod;
	rep(i,2,n) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	rep(i,2,n) inv[i] = 1ll * inv[i] * inv[i - 1] % mod;
	rep(i,2,n) g[i/2].push_back(i);
	dfs(1);
	cout << ans << endl;
	return 0;
}
