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
int head[N],nxt[N << 1],to[N << 1],tot;
int ans[N],a[N],n;

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int top[N],hson[N],deep[N],sz[N],fa[N];

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

void dfs2(int x,int t)
{
	top[x] = t;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x] && to[i] != hson[x])
			dfs2(to[i],to[i]);
}

inline int get_lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	return deep[x] > deep[y] ? y : x;
}

int t[N];
void dfs3(int x)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x])
		{
			dfs3(to[i]);
			t[x] += t[to[i]];
		}

	ans[x] += t[x];	
}

int main()
{
	memset(head,-1,sizeof head);
	read(n);

	rep(i,1,n) read(a[i]);

	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs1(1);
	dfs2(1,1);

	ans[a[n]] = -1;
	ans[a[1]] = 1;
	rep(i,2,n)
	{
		++ t[a[i]];
		++ t[a[i-1]];
		-- ans[a[i-1]];
		int lc = get_lca(a[i],a[i-1]);
		-- t[lc];
		-- t[fa[lc]];
	}

	dfs3(1);

	rep(i,1,n) printf("%d\n",ans[i]);

	return 0;
}
