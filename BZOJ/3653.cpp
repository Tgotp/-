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
const int N = 3e5 + 50;
int n,q;
int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}
int Head[N],To[N << 1],Nxt[N << 1],w[N << 1],Tot;
inline void Add(int x,int y,int val)
{
	w[Tot] = val;
	To[Tot] = y;
	Nxt[Tot] = Head[x];
	Head[x] = Tot ++;
}

int deep[N],dep[N],hs[N],sz[N],fa[N];
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
			if(dep[hs[x]] < dep[to[i]])
				hs[x] = to[i];
		}
	dep[x] = dep[hs[x]] + 1;
}

int M,now;
#define lowbit(x) (-x & x)
struct BIT_TREE
{
	ll t[N << 1];
	inline void insert(int x,ll y) { for(register int i = x;i <= M;i += lowbit(i)) t[i] += y; }
	inline ll find(int x) { ll ans = 0; for(register int i = x;i;i -= lowbit(i)) ans += t[i];return ans; }
}t;
ll ans[N]; 
inline int newpos(int x) { int w = now; now += dep[x] + 1; return w; }
void dfs2(int x,int pos)
{
	if(hs[x])	
		dfs2(hs[x],pos+1);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x] && to[i] != hs[x])
		{
			int trt = newpos(to[i]);
			dfs2(to[i],trt);
			rep(j,0,dep[to[i]])
				t.insert(pos+j+1,t.find(trt+j)-t.find(trt+j-1));
		}
	
	for(register int i = Head[x];~i;i=Nxt[i])
	{
		int id = To[i];
		ans[id] = 1ll * min(deep[x],w[i]) * (sz[x] - 1);
		ans[id] += t.find(pos + min(w[i],dep[x])) - t.find(pos);
	}	
	t.insert(pos,sz[x] - 1);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("2.out","w",stdout);
#endif
	memset(head,-1,sizeof head);
	memset(Head,-1,sizeof Head);
	read(n); read(q);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}
	
	dfs1(1);

	rep(i,1,q)
	{
		int p,k;
		read(p); read(k);
		Add(p,i,k);
	}
	now = M = 1;
	rep(x,1,n) if(hs[fa[x]] != x) M += dep[x] + 1;
	dfs2(1,newpos(1));

	rep(i,1,q) printf("%lld\n",ans[i]);
	return 0;
}
