#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;	
}

const int N = 1e6 + 50;
int head[N],to[N << 1],nxt[N << 1],tot;

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

int n,m,k;
int fa[N],sz[N],deep[N],hson[N];
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

int top[N],pos[N],posx[N],cnt;
void dfs2(int x,int t)
{
	top[x] = t;pos[x] = ++ cnt; posx[cnt] = x;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x] && to[i] != hson[x])
			dfs2(to[i],to[i]);
}

inline int find(int x,int y)
{
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) y = fa[top[y]];
		else x = fa[top[x]];
	}

	return deep[x] < deep[y] ? x : y;
}

inline int up(int x,int y)
{
	while(y > deep[x] - deep[top[x]]) y -= deep[x] - deep[top[x]] + 1,x = fa[top[x]];

	return posx[pos[x] - y];
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m); read(k);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs1(1);
	dfs2(1,1);

	int d,t;
	while(k --)
	{
		read(d); read(t);
		int lc = find(d,m);
		if(deep[d] + deep[m] - 2 * deep[lc] <= t) m = d;
		else
		{
			if(deep[m] - deep[lc] == t) m = lc;
			else if(deep[m] - deep[lc] < t)
				m = up(d,deep[d] - deep[lc] - (t - deep[m] + deep[lc]));
			else m = up(m,t);
		}
		printf("%d ",m);
	}

	return 0;
}
