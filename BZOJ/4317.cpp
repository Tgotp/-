#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e4 + 50;
int n,k;
int head[N],to[N << 1],nxt[N << 1],w[N << 1],tot;

inline void add(int x,int y,int val)
{
	to[tot] = y;
	nxt[tot] = head[x];
	w[tot] = val;
	head[x] = tot ++;
}

int sz[N],mx[N],num,rt; bool vis[N];

void dfs1(int x,int fa)
{
	++ num; sz[x] = mx[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa && !vis[to[i]]){
			dfs1(to[i],x);
			sz[x] += sz[to[i]];
			chkmax(mx[x],sz[to[i]]);
	}
}
void dfs2(int x,int fa)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa && !vis[to[i]])
			dfs2(to[i],x);
	chkmax(mx[x],num - sz[x] - 1);
	if(mx[x] < mx[rt]) rt = x;
}
void get_rt(int x)
{
	num = 0; rt = 0;
	dfs1(x,x); dfs2(x,x);
}

int t; vector<int>v[N],f[N];
int fa[N];
void dfs(int x,int fa,int dis,bool p)
{
	if(p) v[t].push_back(dis);
	else f[t].push_back(dis); 
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa && !vis[to[i]])
			dfs(to[i],x,dis + w[i],p);
}

void solve(int x)
{
	t = x;dfs(x,x,0,1); vis[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]])
		{
			get_rt(to[i]); fa[rt] = x;
			t = rt; dfs(to[i],x,w[i],0);
			solve(rt);
		}
	sort(v[x].begin(),v[x].end());
	sort(f[x].begin(),f[x].end());
}

int deep[N],dep[N],p[N][21];
void dfs3(int x)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != p[x][0]){
		p[to[i]][0] = x;
		dep[to[i]] = dep[x] + w[i];
		deep[to[i]] = deep[x] + 1;
		dfs3(to[i]);
	}
}

inline int lca(int x,int y)
{
	if(deep[x] < deep[y]) swap(x,y);
	repd(i,20,0) if(deep[x] - (1 << i) >= deep[y]) x = p[x][i];
	if(x == y) return x;
	repd(i,20,0) if(p[x][i] != p[y][i]) x = p[x][i],y = p[y][i];
	return p[x][0];
}

inline int dis(int x,int y)
{
	int c = lca(x,y);
	return dep[x] + dep[y] - 2 * dep[c];
}

inline bool check(int x,int val)
{
	int a = x,ans = 0;
	while(a) { ans += upper_bound(v[a].begin(),v[a].end(),val-dis(x,a)) - v[a].begin(); a = fa[a]; }
	a = x;
	while(fa[a]) {ans -= upper_bound(f[a].begin(),f[a].end(),val-dis(x,fa[a])) - f[a].begin(); a = fa[a];}
	return k <= ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
	freopen("2.out","w",stdout);
#endif
	memset(head,-1,sizeof head);
	read(n); read(k); ++ k;
	rep(i,2,n)
	{
		int u,v,w;
		read(u); read(v); read(w);
		add(u,v,w); add(v,u,w);
	}

	dfs3(1);
	rep(j,1,20) rep(i,1,n) p[i][j] = p[p[i][j-1]][j-1];
	
	mx[0] = 1e8;
	get_rt(1);
	solve(rt);
	/*
	puts("");
	rep(i,1,n) 
	{
		printf("fa:%d=%d\n",i,fa[i]);
		printf("%d:",i);
		rep(j,0,((int)v[i].size())-1)
			printf("%d ",v[i][j]);puts("");
		printf("%d:",i);rep(j,0,((int)f[i].size())-1)
			printf("%d ",f[i][j]);puts("");	
	}
	puts("");
	*/
	
	rep(i,1,n)
	{
		int l = 0,r = 1e8,mid,ans;
		while(l <= r)
		{
			if(check(i,mid=l+r>>1)) r = mid - 1,ans = mid;
			else l = mid + 1;
		}
		printf("%d\n",ans);
	}

	return 0;
}
