#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-')  sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e5 + 50;
int dfn[N],low[N],belong[N],sz,cnt;
int s[N],top; bool inq[N];

const int M = 3e5 + 50;
int head[N],nxt[M],to[M],tot;
int Head[N],Nxt[M],To[M],Tot;

inline void Add(int x,int y)
{
	To[Tot] = y;
	Nxt[Tot] = Head[x];
	Head[x] = Tot ++ ;
}

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

vector<int> v[N];

void tarjan(int x)
{
	dfn[x] = low[x] = ++ sz;
	s[++ top] = x; inq[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(!dfn[to[i]])
		{
			tarjan(to[i]);
			low[x] = min(low[x],low[to[i]]);
		}else if(inq[to[i]]) low[x] = min(low[x],dfn[to[i]]);
	
	if(low[x] == dfn[x])
	{
		belong[x] = ++ cnt; inq[x] = 0;
		v[cnt].push_back(x);
		while(s[top] != x)
		{
			v[cnt].push_back(s[top]);
			belong[s[top]] = cnt;
			inq[s[top--]] = 0;
		}
		-- top;
	}
}

int n,m;
bool k[N],t[N];

int in[N],vis[N],vised;

int main()
{
	memset(head,-1,sizeof head);
	memset(Head,-1,sizeof Head);
	read(n); read(m);
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		add(u,v); 
	}

	rep(i,1,n) if(!dfn[i]) tarjan(i);

	rep(h,1,cnt)
	{
		int sz = v[h].size(); -- sz;
		++ vised;
		rep(j,0,sz)
		{
			int x = v[h][j];
			for(register int i = head[x];~i;i=nxt[i])
				if(belong[to[i]] != belong[x] && vis[belong[to[i]]] != vised)
				{
					vis[belong[to[i]]] = vised;
					++ in[belong[to[i]]];
					Add(belong[x],belong[to[i]]);
				}
		}
	}

	bool e = 0; int z = 0;
	rep(h,1,cnt)
	if(!in[h])
	{
		++ z;
		if((int)v[h].size() != 1) continue;
		bool ee = 1;
		for(register int i = Head[h];~i;i=Nxt[i])
			if(in[To[i]] == 1) ee = 0;
		e |= ee;
	}

	double p = 1.0 / n;

	printf("%.6lf\n",1 - (z - e) * p);

	return 0;
}
