#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y;-- i)
typedef long long ll;
using namespace std;
template<typename T> inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T> inline bool chkmin(T&x,T y) { return x > y ? x = y, 1 : 0; }
template<typename T> inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int w[N],sz[N],mx[N],num,cnt,rt,n;
vector<pair<int,int> > g[N];
#define mk(x,y) make_pair(x,y)
bool vis[N];

struct EDGE
{
	int u,v;ll w;
	EDGE(){}
	EDGE(int _u,int _v,ll _w) { u = _u; v = _v,w = _w; }
}e[N * 31];

void get_rt(int x,int fa)
{
	sz[x] = 1; mx[x] = 0;
	for(auto&i:g[x])
		if(!vis[i.first] && i.first != fa)
		{
			get_rt(i.first,x);
			sz[x] += sz[i.first];
			if(sz[i.first] > mx[x])
				mx[x] = sz[i.first];
		}
	chkmax(mx[x],num - sz[x]);
	if(mx[rt] > mx[x]) rt = x;
}

int P;ll W;

void get_p(int x,int fa,ll dep)
{
	if(W > dep + w[x]) P = x,W = dep + w[x];
	for(auto&i:g[x]) if(i.first != fa && !vis[i.first])
		get_p(i.first,x,dep + i.second);
}

void get_e(int x,int fa,ll dep)
{
	e[++cnt] = EDGE(P,x,1ll *W + dep + w[x]);
	for(auto&i:g[x]) if(i.first != fa && !vis[i.first])
		get_e(i.first,x,dep + i.second);
}

void dfs(int x)
{
	vis[x] = 1;W = 1e18;get_p(x,x,0); 
	get_e(x,x,0);
	for(auto&i:g[x])
		if(!vis[i.first])
		{
			num = sz[i.first];
			rt = 0; get_rt(i.first,i.first);
			dfs(rt);		
		}
}

inline bool cmp(EDGE a,EDGE b) { return a.w < b.w; }

int p[N];

int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }

int main()
{
	read(n);
	rep(i,1,n) read(w[i]);
	rep(i,2,n)
	{
		int u,v,w;
		read(u); read(v); read(w);
		g[u].push_back(mk(v,w));
		g[v].push_back(mk(u,w));
	}
	
	mx[0] = n;
	num = n; get_rt(1,1);

	dfs(rt);

	sort(e + 1,e + 1 + cnt,cmp);

	rep(i,1,n) p[i] = i;

	ll ans = 0;
	rep(i,1,cnt)
	{
		int u = get_fa(e[i].u),v = get_fa(e[i].v);

		if(u != v)
		{
			ans += e[i].w;
			p[u] = v;
		}
	}

	cout << ans << endl;

	return 0;
}
