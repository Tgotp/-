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
int head[N],to[N << 1],nxt[N << 1],w[N << 1],tot;
inline void add(int x,int y,int val)
{
	to[tot] = y;
	w[tot] = val;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int p[N];
int find_p(int x) { return p[x] == x ? x : p[x] = find_p(p[x]); }

bool is_t[N << 1];
int id[N],deep[N],h[N << 1][21],t[N << 1][21],sz;

void dfs(int x,int fa)
{
	id[x] = ++ sz; h[sz][0] = deep[x]; t[sz][0] = x;
	for(register int i = head[x];~i;i=nxt[i])
		if(is_t[i] && to[i] != fa)
		{
			deep[to[i]] = deep[x] + 1;
			dfs(to[i],x);
			h[++sz][0] = deep[x]; t[sz][0] = x;
		}
}

int lg[N << 1];
int find_lca(int x,int y)
{
	x = id[x],y = id[y];
	if(x > y) swap(x,y);
	int k = lg[y - x + 1];
	return h[x][k] < h[y - (1 << k) + 1][k] ? t[x][k]: t[y-(1<<k)+1][k];
}

int cnt[N << 1],k[N],res;
int n,m;
void dfs2(int x,int fa)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(!is_t[i])
		{
			int z = find_lca(to[i],x),q = 1;
			if((deep[x] + deep[to[i]] - 2 * deep[z]) & 1) q = -1;
			else { ++ res; ++ cnt[w[i]]; }
			k[to[i]] += q; k[x] += q; k[z] -= 2 * q;
		} else if(to[i] != fa && is_t[i]) dfs2(to[i],x);
}

int dfs3(int x,int fa)
{
	int z = k[x];	
	for(register int i = head[x];~i;i=nxt[i])
		if(is_t[i] && to[i] != fa)
		{
			int zz = dfs3(to[i],x);
			cnt[w[i]] += zz;
			z += zz;
		}
	return z;
}


bool vis[N];
inline void bfs(int x)
{
	queue<int>q;
	q.push(x); vis[x] = 1;
	while(!q.empty())
	{
		x = q.front();q.pop();
		for(register int i = head[x];~i;i=nxt[i])
			if(!vis[to[i]])
			{
				vis[to[i]] = 1;
				q.push(to[i]);
			}
	}
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m);
	rep(i,1,n) p[i] = i;
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		add(u,v,i); add(v,u,i);
		int a = find_p(u),b = find_p(v); 
		if(a != b)
		{
			p[a] = b;
			is_t[tot-1] = 1;
			is_t[tot-2] = 1;
		}
	}
	rep(i,1,n) if(!vis[i]) { bfs(i);add(0,i,0);is_t[tot-1] = 1;}
	dfs(0,0);

	rep(i,2,sz) lg[i] = lg[i>>1] + 1;
	rep(j,1,20) rep(i,1,sz) 
	{
		if(i + (1 << j-1) > sz) continue;
		if(h[i][j-1] < h[i+(1<<j-1)][j-1])
			h[i][j] = h[i][j-1],
			t[i][j] = t[i][j-1];
		else 
			h[i][j] = h[i+(1<<j-1)][j-1],
			t[i][j] = t[i+(1<<j-1)][j-1];
	}

	dfs2(0,0);
	if(res == 0)
	{
		printf("%d\n",m);
		rep(i,1,m) printf("%d ",i);
		return 0;
	}
	dfs3(0,0);

	int ans = 0;
	rep(i,1,m) if(cnt[i] == res) ++ ans;
	printf("%d\n",ans);
	rep(i,1,m) if(cnt[i] == res) printf("%d ",i);
	return 0;
}
