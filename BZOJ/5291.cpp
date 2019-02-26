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

const int N = 2e5 + 50,mod = 1e9 + 7,inv2 = 500000004;
int n,m,w[N];

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

struct Segment_tree
{
	int lzy[3][N << 2],val[N << 2],f1[N << 2],f2[N << 2];
	void build(int id,int l,int r)
	{
		if(l == r)			
		{
			val[id] = w[l];
			f1[id] = l; f2[id] = 1ll * l * l % mod;

			return;
		}
		int mid = l + r >> 1;
		build(id<<1,l,mid); build(id<<1|1,mid+1,r);
		val[id] = (val[id << 1] + val[id << 1|1]) % mod;
		f1[id] = (f1[id << 1] + f1[id << 1|1]) % mod;
		f2[id] = (f2[id << 1] + f2[id << 1|1]) % mod;
	}

	inline void put_down(int id,int l,int r)
	{
		if(lzy[0][id])
		{
			val[id<<1] = (val[id<<1] + 1ll * lzy[0][id] * f2[id<<1]) % mod;
			lzy[0][id<<1] = (lzy[0][id<<1] + lzy[0][id]) % mod; 

			val[id<<1|1] = (val[id<<1|1] + 1ll * lzy[0][id] * f2[id<<1|1]) % mod;
			lzy[0][id<<1|1] = (lzy[0][id<<1|1] + lzy[0][id]) % mod;

			lzy[0][id] = 0; 
		}
		if(lzy[1][id])
		{
			val[id<<1] = (val[id<<1] + 1ll * lzy[1][id] * f1[id<<1]) % mod;
			lzy[1][id<<1] = (lzy[1][id<<1] + lzy[1][id]) % mod; 

			val[id<<1|1] = (val[id<<1|1] + 1ll * lzy[1][id] * f1[id<<1|1]) % mod;
			lzy[1][id<<1|1] = (lzy[1][id<<1|1] + lzy[1][id]) % mod;
			
			lzy[1][id] = 0;
		}
		if(lzy[2][id])
		{
			int mid = l + r >> 1;
			val[id<<1] = (val[id<<1] + 1ll * lzy[2][id] * (mid - l + 1)) % mod;
			lzy[2][id<<1] = (lzy[2][id<<1] + lzy[2][id]) % mod; 

			val[id<<1|1] = (val[id<<1|1] + 1ll * lzy[2][id] * (r - mid)) % mod;
			lzy[2][id<<1|1] = (lzy[2][id<<1|1] + lzy[2][id]) % mod;
			
			lzy[2][id] = 0;
		}
	}

	void update(int id,int l,int r,int L,int R,int a,int b,int c)
	{
		if(l == L && r == R)
		{
			lzy[0][id] = (lzy[0][id] + a) % mod; 
			lzy[1][id] = (lzy[1][id] + b) % mod; 
			lzy[2][id] = (lzy[2][id] + c) % mod;
			val[id] = (val[id] + 1ll * a * f2[id]) % mod;
			val[id] = (val[id] + 1ll * b * f1[id]) % mod;
			val[id] = (val[id] + 1ll * c * (r - l + 1)) % mod;
			return ;
		}

		//put_down(id,l,r);
		int mid = l + r >> 1;
		if(R <= mid) update(id<<1,l,mid,L,R,a,b,c);
		else if(L > mid) update(id<<1|1,mid+1,r,L,R,a,b,c);
		else update(id<<1,l,mid,L,mid,a,b,c),update(id<<1|1,mid+1,r,mid+1,R,a,b,c);

		val[id] = (val[id << 1] + val[id << 1|1] + (1ll * f2[id] * lzy[0][id] % mod) + 
			(1ll * f1[id] * lzy[1][id] % mod) + (1ll * lzy[2][id] * (r - l + 1)%mod)) % mod;
	}

	int find(int id,int l,int r,int L,int R,int a,int b,int c)
	{
		a %= mod; b %= mod;c %= mod;
		if(l == L && r == R)
		{
			ll ans = val[id] + (1ll * f2[id] * a % mod) + (1ll * f1[id] * b % mod) + (1ll * c * (r - l + 1)%mod);
			return ans % mod;
		}

		a = (a + lzy[0][id]) % mod; b = (b + lzy[1][id]) % mod; c = (c + lzy[2][id]) % mod;

		//put_down(id,l,r);
		int mid = l + r >> 1;
		if(R <= mid) return find(id<<1,l,mid,L,R,a,b,c);
		else if(L > mid) return find(id<<1|1,mid+1,r,L,R,a,b,c);
		else return (find(id<<1,l,mid,L,mid,a,b,c)+find(id<<1|1,mid+1,r,mid+1,R,a,b,c))%mod;
	}
}seg;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	read(n); read(m);
	rep(i,1,n) read(w[i]);
	rep(i,1,n) w[i] = (w[i-1] + w[i]) % mod;
	rep(i,1,n) w[i] = (w[i-1] + w[i]) % mod;
	seg.build(1,1,n);
	while(m -- )
	{
		int op,l,r,d;
		read(op); read(l); read(r);
		if(l > r) swap(l,r);
		if(op == 1)
		{
			read(d);
			int a = 1ll*d*inv2%mod,b = 1ll*d*(2*l-3)%mod*inv2%mod,c = 1ll*d*(l-1)%mod*(l-2)%mod*inv2%mod;
			seg.update(1,1,n,l,r,a,-b,c);
			if(r == n) continue;
			a = 1ll * (r-l+1)*(r-l+2)%mod*inv2%mod,b = r-l+1;
			seg.update(1,1,n,r+1,n,0,1ll * b * d % mod,(a - 1ll * b * r) % mod * d % mod);
		}
		else
		{
			int ans = 1ll * seg.find(1,1,n,n,n,0,0,0) * (r - l + 1) % mod;
			if(r > 1) ans = (ans - seg.find(1,1,n,max(l-1,1),r-1,0,0,0)) % mod;
			if(n - l) ans = (ans - seg.find(1,1,n,max(n-r,1),n-l,0,0,0)) % mod;
			printf("%d\n",(ans%mod + mod) % mod);
		}
	}
	return 0;
}
