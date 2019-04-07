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
	do { x = x * 10 + c - '0';c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e5 + 50;
int head[N],nxt[N << 1],to[N << 1],tot;
int n,rt,num,sz[N],mx[N],c[N]; bool vis[N];

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

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
	chkmax(mx[x],num - sz[x]);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa && !vis[to[i]]) 
			dfs2(to[i],x);
	if(mx[x] < mx[rt]) rt = x;
}

void get_rt(int x)
{
	rt = 0; num = 0;
	dfs1(x,x); dfs2(x,x);
}

ll ans[N];
int vised[N],cnt[N],col[2][N],sum[2][N],size[2];
int flag,t;
void dfs(int x,int fa,bool k)
{
	sz[x] = 1;
	++ cnt[c[x]];
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]] && to[i] != fa)
		{
			dfs(to[i],x,k);
			sz[x] += sz[to[i]];
		}
	if(cnt[c[x]] == 1)
	{
		col[k][++size[k]] = c[x];
		sum[k][size[k]] = sz[x];
	}
	-- cnt[c[x]];
}

ll tnum[N];
void dfs3(int x,int fa,ll w)
{
	++ cnt[c[x]];
	if(cnt[c[x]] == 1) w += t - tnum[c[x]];
	ans[x] += w;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa && !vis[to[i]])
			dfs3(to[i],x,w);
	-- cnt[c[x]];
}

void solve(int x)
{
	size[1] = 0; dfs(x,x,1);
	rep(i,1,size[1]) ans[x] += sum[1][i]; 
	vis[x] = 1;cnt[c[x]] = 1; ll Mres = 0;
	rep(i,1,size[1]) tnum[col[1][i]] += sum[1][i],Mres += sum[1][i];
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]]) 
		{
			size[0] = 0;
			t = num - sz[to[i]];
			dfs(to[i],to[i],0); 
			ll res = Mres;
			rep(j,1,size[0]) res -= sum[0][j],tnum[col[0][j]] -= sum[0][j]; 
			dfs3(to[i],to[i],res - sz[to[i]]);
			rep(j,1,size[0]) tnum[col[0][j]] += sum[0][j]; 
		}
	cnt[c[x]] = 0;
	rep(i,1,size[1]) tnum[col[1][i]] = 0;
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]])
		{
			get_rt(to[i]);
			solve(rt);
		}
}

int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n) read(c[i]);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(v,u); add(u,v);
	}
	mx[0] = n + 1;
	get_rt(1);
	solve(rt);
	rep(i,1,n) printf("%lld\n",ans[i]);
	return 0;
}
