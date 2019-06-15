#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
#define mk(x,y) make_pair(x,y)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 102,M = 1e4 + 50;
int a[N][M],b[N][M],id[N][M],vis[N * M];
int n,m,q;
unsigned int SA, SB, SC;int lim;
int getweight() 
{
	SA ^= SA << 16; SA ^= SA >> 5; SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB; SB = SC; SC ^= t ^ SA;
	return SC % lim + 1;
}

void gen() 
{
	read(n); read(m); read(SA); read(SB); read(SC); read(lim);
	rep(i,1,n) rep(j,1,m) a[i][j] = getweight();
	rep(i,1,n-1) rep(j,1,m)	b[i][j] = getweight();
}

struct Edge
{
	int s,t,w;
	Edge(){}
	Edge(int _s,int _t,int _w) { s = _s; t = _t; w = _w; }
}e[M]; int tot;

const bool cmp(Edge a,Edge b) { return a.w < b.w; }
struct MST
{
	ll w; vector<Edge> p;
	inline void clear() { w = 0;tot = 0; p.clear(); }
	inline ll query() { for(auto&i:p) w += i.w; return w; }
}M1[M],M2[M],z;

int p[N * M];

int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }

vector<pair<int,int> > g[N * M];
vector<Edge> v[M];
int sz[N * M],h[N * M];

void dfs(int x,int fa)
{
	h[x] = 0;
	for(auto&i:g[x]) if(fa != i.first)
		dfs(i.first,x),h[x] += h[i.first] >= 1;

	if(!fa || vis[x] || h[x] > 1) sz[x] = 1;
	h[x] = (h[x] + sz[x]) >= 1; 
}

void dfs2(int x,int fa,int lst,int w)
{
	if(sz[x] && x != lst) z.p.push_back(Edge(lst,x,w)),lst = x,z.w -= w,w = 0;
	for(auto&i:g[x]) if(fa != i.first)
		dfs2(i.first,x,lst,max(w,i.second));
}

MST doit(int j)
{
	z.clear();
	rep(i,1,n-1) z.p.push_back(Edge(id[i][j],id[i+1][j],b[i][j]));
	sort(z.p.begin(),z.p.end(),cmp);
	return z;
}

MST merge(MST x,MST y,int j,int j2)
{
	z.clear();
	tot = 0; z.w = x.w + y.w;

	/*
	sort(x.p.begin(),x.p.end(),cmp);
	sort(y.p.begin(),y.p.end(),cmp);
	sort(v[j].begin(),v[j].end(),cmp);
	*/

	vector<Edge> :: iterator it1,it2,it3;
	it1 = x.p.begin(); it2 = y.p.begin(); it3 = v[j].begin();
	while(it1 != x.p.end())
	{
		while((it2 != y.p.end() && (*it1).w > (*it2).w) || 
			((it3 != v[j].end() && (*it1).w > (*it3).w)))
			{
				if(it2 == y.p.end() ) { e[++ tot] = *(it3 ++); continue; }
				if(it3 == v[j].end()) { e[++ tot] = *(it2 ++); continue; }
				if((*it2).w < (*it3).w) e[++ tot] = *(it2 ++);
				else e[++ tot] = *(it3 ++);
			}

		e[++ tot] = *(it1 ++);
	}
	while(it2 != y.p.end())
	{
		while(it3 != v[j].end() && (*it3).w < (*it2).w) e[++ tot] = *(it3 ++);
		e[++ tot] = *(it2 ++);
	}
	while(it3 != v[j].end()) e[++ tot] = *(it3 ++);

/*
	for(auto&i:x.p) e[++ tot] = i;
	for(auto&i:y.p) e[++ tot] = i;
	for(auto&i:v[j])e[++ tot] = i;
	sort(e + 1,e + 1 + tot,cmp);
*/

	rep(i,1,n) ++ vis[id[i][j2]];

	rep(i,1,tot) 
		p[e[i].s] = e[i].s,p[e[i].t] = e[i].t,
		g[e[i].s].clear() ,g[e[i].t].clear() ,
		sz[e[i].s] = 0,sz[e[i].t] = 0;

	int cnt = 0;
	rep(i,1,tot) if(get_fa(e[i].s) != get_fa(e[i].t))
		p[get_fa(e[i].s)] = get_fa(e[i].t),e[++cnt] = e[i],z.w += e[i].w;
	
	rep(i,1,cnt) 
		g[e[i].s].push_back(mk(e[i].t,e[i].w)),
		g[e[i].t].push_back(mk(e[i].s,e[i].w));
	
	dfs(e[1].s,0);
	dfs2(e[1].s,0,e[1].s,0);

	rep(i,1,n) -- vis[id[i][j2]];

	if(j != m) sort(z.p.begin(),z.p.end(),cmp);
	return z;
}

int main()
{
	//freopen("2.out","w",stdout);
	gen();

	//rep(i,1,n) rep(j,1,m) printf("%d%c",a[i][j],j==m?'\n':' ');
	//rep(i,1,n) rep(j,1,m) printf("%d%c",b[i][j],j==m?'\n':' ');

	rep(i,1,n) rep(j,1,m) id[i][j] = (i - 1) * m + j;
	rep(i,1,n) id[i][m + 1] = id[i][1];
	rep(i,1,n) rep(j,1,m) v[j].push_back(Edge(id[i][j],id[i][j+1],a[i][j]));
	rep(i,1,m) sort(v[i].begin(),v[i].end(),cmp);

	M1[1] = doit(1); M2[m] = doit(m);
	rep(i,1,n) ++ vis[id[i][1]],++ vis[id[i][m]];

	rep(i,2,m - 1) M1[i] = merge(M1[i-1],doit(i),i-1,i);
	repd(i,m - 1,2) M2[i] = merge(M2[i+1],doit(i),i,i);

	read(q);

	while(q --)
	{
		int l,r; read(l); read(r);
		printf("%lld\n",merge(M1[l-1],M2[r+1],m,m).query());
	}

	return 0;
}
