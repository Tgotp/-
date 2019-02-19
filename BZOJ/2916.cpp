#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1010;
int n,m,ans;
int mp[N][N],vis[N],vised;
int in[N],x[N * N],y[N * N];
vector<int> g[N];

inline void solve(bool k)
{
	m = 0;
	memset(in,0,sizeof in);
	rep(i,1,n) rep(j,i + 1,n)
		if(mp[i][j] == k)
		{
			++ in[j]; ++ in[i];
			x[++ m] = i;y[m] = j;
		}
	
	#define mk(x,y) make_pair(x,y)
	rep(i,1,n) g[i].clear();
	rep(i,1,m)
	{
		if(in[x[i]] > in[y[i]]) swap(x[i],y[i]);
		g[x[i]].push_back(y[i]);
	}

	rep(i,1,m)
	{
		int sz = g[x[i]].size(); -- sz; ++ vised;
		rep(j,0,sz) vis[g[x[i]][j]] = vised;
		sz = g[y[i]].size(); -- sz;
		rep(j,0,sz) if(vis[g[y[i]][j]] == vised) ++ ans;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	read(n); read(m);

	rep(i,1,m)
	{
		int a,b;
		read(a); read(b);
		mp[a][b] = 1; mp[b][a] = 1;
	}

	solve(0);
	solve(1);

	cout << ans << endl;

	return 0;
}
