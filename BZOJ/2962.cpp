#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y, 1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int mod = 19940417,N = 1e5 + 50,inf = 1e9 + 7;
int n,q,a[N],C[N][21];

struct DATA
{
	int a[21];

	inline int&operator[](int x) { return a[x]; }
};

struct segment_tree
{
	DATA val[N << 2];
	int lzy1[N << 2],lzy2[N << 2];


	inline DATA merge(DATA a,DATA b)
	{
		DATA x;
		rep(i,0,20) x[i] = 0;
		x[0] = 1;
			
		rep(i,1,20)
			rep(j,0,i)
				x[i] = (x[i] + 1ll*a[j] * b[i-j] % mod)%mod;
		return x;
	}

	void build(int id,int l,int r)	
	{
		if(l == r)
		{
			rep(i,0,20) val[id][i] = 0;
			val[id][0] = 1;
			val[id][1] = a[l];
			return ;	
		}
		int mid = l + r >> 1;
		build(id<<1,l,mid); build(id<<1|1,mid+1,r);
		val[id] = merge(val[id<<1],val[id<<1|1]);
		//printf("%d %d %d %d\n",l,r,val[id][2],val[id][1]);
	}

	int w[21];
	inline void put_down(int id,int l,int r)
	{
		if(l == r)
		{
			lzy1[id] = lzy2[id] = 0;
			return ;
		}
		if(lzy1[id])
		{
			rep(i,1,20)
			{
				val[id<<1][i] = -val[id<<1][i],
				val[id<<1|1][i] = -val[id<<1|1][i];
				++ i;
			}
			lzy1[id] ^= 1;
			lzy2[id<<1] = -lzy2[id<<1];
			lzy2[id<<1|1] = -lzy2[id<<1|1];
			lzy1[id<<1] ^= 1;
			lzy1[id<<1|1] ^= 1;
		}
		if(lzy2[id])
		{
			int mid = l + r>> 1;
			w[0] = 1;
			rep(i,1,20) w[i] = 1ll * w[i-1] * lzy2[id] % mod;
			repd(i,20,1)
				rep(j,1,i)
				{
					val[id<<1][i] = (val[id<<1][i] + 1ll * w[j] * val[id<<1][i-j]%mod * C[mid-l+1-i+j][j]%mod) %mod;
					val[id<<1|1][i] = (val[id<<1|1][i] + 1ll * w[j] * val[id<<1|1][i-j]%mod * C[r-mid-i+j][j]%mod) %mod;
				}
	
			lzy2[id<<1|1] = (lzy2[id<<1|1] + lzy2[id]) % mod;
			lzy2[id<<1] = (lzy2[id<<1] + lzy2[id]) % mod;
			lzy2[id] = 0;
		}
	}

	void update(int id,int l,int r,int L,int R,int c)
	{
		put_down(id,l,r);
		if(l == L && r == R)
		{
			if(c == inf)
			{
				rep(i,1,20)
				{
					val[id][i] = -val[id][i];
					++ i;
				}
				lzy1[id] ^= 1;
			}
			else
			{
				w[0] = 1;
				rep(i,1,20) w[i] = 1ll * w[i-1] * c % mod;
				repd(i,20,1)
					rep(j,1,i)
						val[id][i] = (val[id][i] + 1ll * w[j] * val[id][i-j]%mod * C[r-l+1-i+j][j]%mod) %mod;
				lzy2[id] = c;
			}
			return ;
		}
		int mid = l + r >> 1;
		if(R <= mid) update(id<<1,l,mid,L,R,c);
		else if(L > mid) update(id<<1|1,mid+1,r,L,R,c);
		else update(id<<1,l,mid,L,mid,c),update(id<<1|1,mid+1,r,mid+1,R,c);
		val[id] = merge(val[id<<1],val[id<<1|1]);
	}

	DATA find(int id,int l,int r,int L,int R)
	{
		if(l == L && r == R) return val[id];
		put_down(id,l,r);
		int mid = l + r >> 1;
		if(R <= mid) return find(id<<1,l,mid,L,R);
		else if(L > mid) return find(id<<1|1,mid+1,r,L,R);
		else return merge(find(id<<1,l,mid,L,mid),find(id<<1|1,mid+1,r,mid+1,R));
	}
}seg;

char s[42];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
#endif
	read(n); read(q);
	rep(i,1,n) read(a[i]);
	C[0][0] = 1;
	rep(i,1,n) rep(j,0,min(20,i))
		if(j == 0) C[i][j] = C[i-1][j];
		else C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod;
	seg.build(1,1,n);
	while(q --)
	{
		scanf("%s",s + 1);
		if(s[1] == 'I')
		{
			int l,r,c;
			read(l); read(r); read(c);
			seg.update(1,1,n,l,r,c);
		}
		else if(s[1] == 'R')
		{
			int l,r;
			read(l); read(r);
			seg.update(1,1,n,l,r,inf);
		}
		else 
		{
			int l,r,c;
			read(l); read(r); read(c);
			DATA a = seg.find(1,1,n,l,r);
			printf("%d\n",(a[c]%mod + mod) % mod);
		}
	}
	return 0;
}
