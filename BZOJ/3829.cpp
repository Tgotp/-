#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 1e6 + 50;
int c[N],n;
int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int sz[N];
int t[N];

inline bool cmp(pair<int,int> a,pair<int,int> b)
{
	return max(a.first + 1,a.second * 2 + 1 + b.first) < 
		max(b.first + 1,b.second * 2 + 1 + a.first);
}

void dfs(int x,int fa)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa)
			dfs(to[i],x);
	vector<pair<int,int> > v; v.clear(); sz[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa)
		{
			sz[x] += sz[to[i]];
			v.push_back(make_pair(t[to[i]],sz[to[i]]));
		}
	
	t[x] = c[x];
	if(v.empty()) return;
	sort(v.begin(),v.end(),cmp);

	int z = 0;

	rep(i,0,((int)v.size())-1)
	{
		chkmax(t[x],z + 1 + v[i].first);
		z += v[i].second * 2;
	}
}

int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n) read(c[i]);
	rep(i,2,n)
	{
		int u ,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	int k = c[1]; c[1] = 0;
	dfs(1,1);

	cout << max(t[1],n * 2 - 2 + k) << endl;

	return 0;
}
