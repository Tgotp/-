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

const int N = 1e5 + 50;

int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int top[N],hson[N],size[N],fa[N],deep[N];
void dfs1(int x)
{
	size[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
	{
		if(to[i] == fa[x]) continue;
		deep[to[i]] = deep[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		size[x] += size[to[i]];
		if(size[to[i]] > size[hson[x]])
			hson[x] = to[i];
	}
}

void dfs2(int x,int t)
{
	top[x] = t;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
	{
		if(to[i] == fa[x] || to[i] == hson[x]) continue;
		dfs2(to[i],to[i]);
	}
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

int n,m,sz;

int ans[N];

const int M = 6e6 + 50;
int rt[N],ls[M],rs[M],val[M],num[M];

void insert(int&x,int l,int r,int pos,int w)
{
	if(!x) x = ++ sz;
	if(l == r)	
	{
		num[x] += w;
		val[x] = l;
		return;
	}
	int mid = l + r >> 1;
	if(pos <= mid) insert(ls[x],l,mid,pos,w);
	else insert(rs[x],mid+1,r,pos,w);

	num[x] = max(num[ls[x]],num[rs[x]]);
	if(num[ls[x]] >= num[rs[x]])
		val[x] = val[ls[x]];
	else val[x] = val[rs[x]];
}

int merge(int x,int y,int l,int r)
{
	if(!x || !y) return x | y;
	if(l == r)
	{
		num[x] += num[y];
		return x;
	}

	int mid = l + r >> 1;
	ls[x] = merge(ls[x],ls[y],l,mid);
	rs[x] = merge(rs[x],rs[y],mid+1,r);

	num[x] = max(num[ls[x]],num[rs[x]]);
	if(num[ls[x]] >= num[rs[x]])
		val[x] = val[ls[x]];
	else val[x] = val[rs[x]];

	return x;
}

void dfs3(int x)
{
	for(register int i = head[x];~i;i=nxt[i])
	{
		if(to[i] == fa[x]) continue;
		dfs3(to[i]);

		rt[x] = merge(rt[x],rt[to[i]],1,m);
	}
	
	ans[x] = val[rt[x]];
}

int a[N],b[N],c[N],z[N],id[N];

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m);

	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs1(1);
	dfs2(1,1);
	
	rep(i,1,m) { read(a[i]); read(b[i]); read(c[i]); z[i] = c[i]; }

	sort(z + 1,z + 1 + m);
	
	rep(i,1,m)
	{
		int t = lower_bound(z + 1,z + 1 + m,c[i]) - z;
		id[t] = c[i];
		c[i] = t;

		insert(rt[a[i]],1,m,c[i],1);
		insert(rt[b[i]],1,m,c[i],1);
		int lc = get_lca(a[i],b[i]);
		insert(rt[lc],1,m,c[i],-1);
		insert(rt[fa[lc]],1,m,c[i],-1);
	}

	dfs3(1);

	rep(i,1,n) printf("%d\n",id[ans[i]]);

	return 0;
}
