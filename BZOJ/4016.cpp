#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar();if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 3e4 + 40;
int n,m,k;

vector<pair<int,int> > G[N];
vector<int>g[N];

int d[N],from[N],vl[N]; bool vis[N];
#define mk(x,y) make_pair(x,y)
#define to i.second 
#define w i.first
		
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > >q;
void dij()
{
	memset(d,0x3f,sizeof d);
	d[1] = 0;q.push(mk(0,1));
	rep(i,1,n) sort(G[i].begin(),G[i].end());
	rep(i,1,n)
	{
		while(vis[q.top().second]) q.pop();
		int x = q.top().second; vis[x] = 1;
		for(auto&i:G[x]) if(!vis[to] && chkmin(d[to],d[x]+w))
			q.push(mk(d[to],to));
	}
	memset(vis,0,sizeof vis);
}

void rebuild(int x)
{
	vis[x] = 1;
	for(auto&i:G[x])
	{
		if(d[to] != d[x] + w || vis[to]) continue;
		g[to].push_back(x);
		g[x].push_back(to);
		vl[to] = w;
		rebuild(to);
	}
}

int t[N << 2],MAXN = 1;
#define lowbit(x) (x & -x)
inline void update(int x,int val)
{
	for(register int i = x;i <= MAXN;i += lowbit(i))
		t[i] += val;
}

inline int find(int x)
{
	int ans = 0;
	for(register int i = x; i ; i -= lowbit(i))
		ans += t[i];
	return ans;
}

int fa[N],dep[N],hson[N];

#undef to
void dfs1(int x)
{
	for(auto&to:g[x]) if(to != fa[x])
	{
		fa[to] = x;
		dfs1(to);
		if(dep[to] > dep[hson[x]])
			hson[x] = to;
	}
	dep[x] = dep[hson[x]] + 1;
}

int now = 1;
inline int newnode(int x) { int pos = now;now += dep[x] + 2; return pos; }

int f[N << 2];
int res,ans;
void dfs2(int x,int pos)
{
	f[pos + 1] = 1;
	if(hson[x]) dfs2(hson[x],pos + 1); else return;
	update(pos + 2,vl[hson[x]]); update(pos + dep[x] + 1,-vl[hson[x]]);
	for(auto&to:g[x]) if(to != fa[x] && to != hson[x])
	{
		int t; dfs2(to,t = newnode(to));	
		int r = min(k - 2,dep[to]),l = max(1,k - dep[x]);
		rep(j,l,r)
		{
			int val = find(t + j) + find(pos + k - j) + vl[to];
			if(val == res) ans += f[t + j] * f[pos + k - j];
			else if(chkmax(res,val)) ans = f[t + j] * f[pos + k - j];
		}
		rep(j,1,dep[to])
		{
			int v1 = find(t + j) + vl[to],v2 = find(pos + j + 1);
			if(v1 == v2) f[pos + j + 1] += f[t + j];
			else if(v1 > v2)
			{
				f[pos + j + 1] = f[t + j];
				update(pos + j + 1,v1-v2);
				update(pos + j + 2,-(v1-v2));
			}
		}
	}
	if(dep[x] >= k)
	{
		int val = find(pos + k);
		if(res == val) ans += f[pos + k];
		else if(chkmax(res,val)) ans = f[pos + k];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4.in","r",stdin);
	freopen("4.out","w",stdout);
#endif
	read(n); read(m); read(k);
	rep(i,1,m)
	{
		int u,v,val;
		read(u); read(v); read(val);
		G[u].push_back(mk(val,v));
		G[v].push_back(mk(val,u));
	}

	dij();
	rebuild(1);
	dfs1(1); 
	rep(i,1,n) if(hson[fa[i]] != i) MAXN += dep[i] + 2;
	dfs2(1,newnode(1));

	printf("%d %d\n",res,ans);

	return 0;
}
