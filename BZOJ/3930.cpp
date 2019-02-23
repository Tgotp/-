#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;

const int N = 1e5 + 50,mod = 1e9 + 7;
int n,k,l,h,f[N];

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

int main()
{
	cin >> n >> k >> l >> h;
	int z = l <= k && k <= h ? 1 : 0;
	-- l; l /= k; h /= k;int len = h - l;
	repd(i,len,1)
	{
		int x = l/i,y = h/i;
		f[i] = (ksm(y-x,n) - (y-x)+mod)%mod;
		for(register int j = i * 2;j <= len; j += i)
			f[i] = (f[i] - f[j] + mod) % mod;
	}
	cout << (f[1] + z) % mod << endl;
	return 0;
}
