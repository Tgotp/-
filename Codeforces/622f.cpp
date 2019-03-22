#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
const int N = 1e6 + 60,mod = 1e9 + 7;
int n,k;
int a[N];

inline int ksm(int x,int y)
{
	int ans = 1;
	while(y)
	{
		if(y&1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod; y >>= 1;
	}
	return ans;
}

int s1[N],s2[N],inv[N];
inline int lagrange(int*a,int n,int pos)
{
	if(pos <= n) return a[pos];
	s1[0] = s2[n + 1] = 1;
	rep(i,1,n) s1[i] = 1ll * ((pos - i) % mod + mod) % mod * s1[i-1] % mod;
	repd(i,n,1) s2[i] = 1ll * ((pos - i) % mod + mod) % mod * s2[i+1] % mod;
	int ans = 0;
	rep(i,1,n)
		ans = (ans + 1ll * a[i] * s1[i-1] % mod *s2[i+1] % mod
			* inv[i-1] % mod * inv[n-i] % mod * ((n-i)&1?mod-1:1))%mod;
	ans = (ans % mod + mod) % mod;
	return ans;
}

int main()
{
	cin >> n >> k;
	rep(i,1,k + 2) a[i] = ksm(i,k);
	rep(i,1,k + 2) a[i] = (a[i-1] + a[i]) % mod;

	inv[0] = 1; inv[1] = 1;
	rep(i,2,k + 2) inv[i] = 1ll * (mod - mod/i) * inv[mod%i] % mod;
	rep(i,2,k + 2) inv[i] = 1ll * inv[i] * inv[i-1] % mod;

	cout << lagrange(a,k+2,n) << endl;

	return 0;
}
