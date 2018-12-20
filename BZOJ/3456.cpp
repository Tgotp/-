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

const int N = 6e5 + 50,mod = 1004535809,G = 3;
int n,inv[N],fac[N];
inline void pre(int n)
{
	inv[0] = inv[1] = fac[0] = fac[1] = 1;
	rep(i,2,n) inv[i] = 1ll * (mod - mod/i) * inv[mod%i] % mod;
	rep(i,2,n) inv[i] = 1ll * inv[i] * inv[i-1] % mod;
	rep(i,2,n) fac[i] = 1ll * fac[i-1] * i % mod;
}

inline ll ksm(ll x,ll y)
{
	ll ans = 1; x %= mod; y %= mod-1;
	while(y)
	{
		if(y&1) ans = ans * x % mod;
		y >>= 1;x = x * x % mod;
	}
	return ans;
}

inline ll C(int n,int m)
{
	if(n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n-m] % mod;
}

int g[N],a[N],b[N],c[N],k[N];
int r[N];

void ntt(int*a,int f)
{
	rep(i,0,n-1) if(r[i] < i) swap(a[r[i]],a[i]);
	for(register int i = 1;i < n; i <<= 1)
	{
		ll wn = ksm(G,(mod-1)/(i<<1));
		if(f==-1) wn = ksm(wn,mod-2);
		for(register int j = 0;j < n ; j += i << 1)
		{
			ll w = 1;
			for(register int k = 0;k < i; ++ k,w = w * wn % mod)
			{
				ll x = a[j + k],y = a[i + j + k] * w%mod;
				a[j + k] = (x + y)% mod;
				a[i + j + k] = (x - y + mod) % mod;
			}
		}
	}
	if(f==-1)
	{
		ll inv = ksm(n,mod-2);
		rep(i,0,n-1) a[i] = a[i] * inv % mod;
	}
}

void solve(int now)
{
	if(now == 0)
	{
		b[0] = ksm(g[0],mod - 2);
		return;
	}
	solve(now/2);
	int L = 0,m = now << 1;
	for(n = 1;n <= m;n <<= 1,++ L);
	rep(i,0,n-1) r[i] = (r[i>>1]>>1)|((i&1)<<(L-1));
	rep(i,0,now) k[i] = g[i];
	ntt(k,1); ntt(b,1);
	rep(i,0,n-1) b[i] = b[i]*(2-1ll*b[i]%mod*k[i]%mod+mod)%mod;
	ntt(b,-1);
	rep(i,0,n-1) k[i] = 0;
	rep(i,now+1,n-1) b[i] = 0;
}

int main()
{
	int n;
	read(n);
	pre(n<<2);
	rep(i,0,n) g[i] = ksm(2,1ll*i*(i-1)/2) * inv[i] % mod;
	rep(i,0,n) c[i] = ksm(2,1ll*i*(i-1)/2) * inv[i-1]%mod;
	solve(n);
	int m = n << 1,L = 0,z = n;	
	for(n = 1;n <= m; n <<= 1,++ L);
	rep(i,0,n-1) r[i] = (r[i>>1]>>1)|((i&1)<<(L-1));
	ntt(c,1); ntt(b,1);
	rep(i,0,n-1) c[i] = 1ll*b[i] * c[i] % mod;
	ntt(c,-1);
	printf("%lld\n",1ll*c[z]*fac[z-1] %mod);
	return 0;
}
