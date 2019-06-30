#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c; int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 50;
int n,t,rt,now;
int fa[N],f[N],zz[N];
int vis[N];
vector<int> g[N];

void dfs1(int x) { for(auto&i:g[x]) if(i != fa[x]) { fa[i] = x; dfs1(i); } }

void dfs(int x)
{
	int mx = 0;
	for(auto&i:g[x]) if(i != fa[x])
	{
		dfs(i);
		if(vis[i]) continue;
		if(f[i] + 2 >= mx)
		{
			f[x] = mx;
			mx = f[i] + 2;
		} else if(f[i] + 2 > f[x])
			f[x] = f[i] + 2;
	}
	f[x] += max(0,(((int)g[x].size()) - 3));
	if(f[x] == 0 && mx) f[x] = 1;
}
void dfs2(int x,int t)
{
	if(x != rt) t += max(0,(((int)g[x].size()) - 2));
	if(vis[x] == 1 && x != rt) ++ t;
	for(auto&i: g[x]) if(i != fa[x])
	{
		if(vis[i]) dfs2(i,t);
		else f[i] += t;
	}
}

int a[N],cnt,ans;

int p[N];
int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }

const bool cmp(int a,int b) { return f[a] > f[b]; }

inline bool check(int w)
{
	int x = now,y = 1,k = 0;	
	while(x != rt)
	{
		//printf("%d\n",g[x].size());
		int z = 0;
		for(auto&i :g[x]) if(!vis[i] && f[i] + k > w)
			-- y, ++ z;
		k += z;
		if(y < 0 || k > w) return false;
		x = fa[x]; ++ y;
	}
	return true;
}

int main()
{
	read(n); read(rt); read(now);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs1(rt);
	int x = now;
	while(x != rt) { vis[x] = ++ cnt; x = fa[x]; }

	dfs(rt);
	dfs2(rt,0);

	int l = 0,r = n,mid,ans = INT_MAX;
	while(l <= r)
	{
		if(check(mid = l + r >> 1)) r = mid - 1,ans = mid;
		else l = mid + 1;
	}

	cout << ans << endl;

	return 0;
}
