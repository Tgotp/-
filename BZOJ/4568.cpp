#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y ;++ i)
#define repd(i,x,y) for(register int i = x;i >= y ;-- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e4 + 50;
int n,q; ll g[N];
int head[N],nxt[N << 1],to[N << 1],tot;

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

int fa[N],sz[N],top[N],hson[N],deep[N];
void dfs1(int x)
{
	sz[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x])
		{
			deep[to[i]] = deep[x] + 1;
			fa[to[i]] = x;
			dfs1(to[i]);
			sz[x] += sz[to[i]];
			if(sz[hson[x]] < sz[to[i]])
				hson[x] = to[i];
		}
}

int id[N],idx[N],cnt;

void dfs2(int x,int t)
{
	id[x] = ++ cnt;idx[cnt] = x; top[x] = t;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x] && to[i] != hson[x])
			dfs2(to[i],to[i]);

}

struct DATA { int p[61];int mx;  };

ll t[150],ans;int rel[150];

inline DATA merge(DATA a,DATA b)
{
	ans = 0;
	int cnt = 0,z=1;
	rep(i,0,a.mx) if(a.p[i]) t[++cnt] = g[a.p[i]],rel[cnt] = a.p[i];
	rep(i,0,b.mx) if(b.p[i]) t[++cnt] = g[b.p[i]],rel[cnt] = b.p[i];
	DATA c; c.mx = max(a.mx,b.mx); rep(i,0,c.mx) c.p[i] = 0;
	repd(i,c.mx,0)
		rep(j,z,cnt) if(t[j] & (1LL<<i))
		{
			if(!(ans&(1LL<<i))) ans ^= t[j];
			c.p[i] = rel[j];  
			swap(t[j],t[z]); swap(rel[j],rel[z]); ++ z;
			rep(k,z,cnt) if(t[k] & (1LL<<i))
				t[k] ^= t[z-1];
		}
	return c;
}

DATA a[N][15];
int lg[N];

inline void build()
{
	rep(i,2,n) lg[i] = lg[i>>1] + 1;
	rep(i,1,n) 
	{
		rep(j,0,60) a[i][0].p[j]=0;
		repd(j,60,0) if(g[idx[i]]&(1LL<<j))
			{a[i][0].mx = j;a[i][0].p[j]=idx[i];break;}
	}
	rep(j,1,14) rep(i,1,n) if(i + (1 << j) - 1 <= n)
		a[i][j] = merge(a[i][j-1],a[i+(1<<j-1)][j-1]);
}

inline DATA query(int l,int r)
{
	int k = lg[r - l + 1];
	return merge(a[l][k],a[r-(1<<k)+1][k]);
}

inline ll find(int x,int y)
{
	DATA c; c.mx = -1;
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		c = merge(c,query(id[top[x]],id[x]));
		x = fa[top[x]];
	}

	if(deep[x] > deep[y]) swap(x,y);
	c = merge(c,query(id[x],id[y]));

	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("9.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	
	memset(head,-1,sizeof head);
	read(n); read(q);
	rep(i,1,n) read(g[i]);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs1(1);
	dfs2(1,1);

	build();

	//printf("%.3lf\n",clock()/(double)CLOCKS_PER_SEC);

	while(q --)
	{
		int x,y;
		read(x); read(y);
		printf("%lld\n",find(x,y));
	}

	//printf("%.3lf\n",clock()/(double)CLOCKS_PER_SEC);
	return 0;
}
