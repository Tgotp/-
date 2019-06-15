#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y, 1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e3 + 50;
int n,m,p,cnt,id[N];
vector<pair<int,int> > g[N];
vector<int> K[11];
#define mk(x,y) make_pair(x,y)
#define fi first
#define se second

int G[1 << 11],f[N][1 << 11];

int s;

struct DATA
{
	int x,sta,w;
	DATA(){}
	DATA(int _x,int _sta,int _w)
	{
		x = _x; sta = _sta; w = _w;
	}
	inline bool operator < (const DATA b) const { return w > b.w; }
};
priority_queue<pair<int,int> > q;

inline bool check(int x)
{
	rep(i,1,p) for(auto&j:K[i]) if(x & id[j])
	{
		for(auto&z:K[i]) if(!(x&id[z])) return false;
		break;
	}

	return true;
}

bool vis[N];

inline void SPFA(int j)
{
	while(!q.empty())	
	{
		int x = q.top().se; q.pop(); vis[x] = 0;

		for(auto&i:g[x])
			if(chkmin(f[i.fi][j],f[x][j] + i.se) && !vis[i.fi])
				vis[i.fi] = 1,q.push(mk(-f[i.fi][j],i.fi));
	}
}

int main()
{
	read(n); read(m); read(p);
	while(m -- )
	{
		int u,v,w;
		read(u); read(v); read(w);
		g[u].push_back(mk(v,w));
		g[v].push_back(mk(u,w));
	}

	memset(f,0x3f,sizeof f);
	memset(G,0x3f,sizeof G);
	rep(i,1,n) f[i][0] = 0; G[0] = 0;
	rep(i,1,p) 
	{
		int c,d;
		read(c),read(d),
		id[d] = 1 << (cnt ++);
		f[d][id[d]] = 0;
		K[c].push_back(d);
	}

	s = (1 << cnt) - 1;

	rep(i,1,s) 
	{
		rep(x,1,n) for(int j = (i - 1) & i;j; j = (j - 1) & i)
			if(chkmin(f[x][i],f[x][i^j] + f[x][j])) ;

		rep(j,1,n) if(f[j][i] < 0x3f3f3f3f) q.push(mk(-f[j][i],j));
		SPFA(i);
	}

	rep(j,1,s) if(check(j)) rep(i,1,n)
		G[j] = min(G[j],f[i][j]);
	rep(i,1,s) for(int j = (i - 1) & i;j;j = (j - 1) & i) 
		chkmin(G[i],G[j] + G[i ^ j]);

	if(G[s] > 2e7) puts("-1");
	else printf("%d\n",G[s]);

	return 0;
}
