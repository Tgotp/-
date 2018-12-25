#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int n,r[N]; ll d[N],t[N];
vector<int>v[N];
vector<ll>g[N];
int head[N],to[N << 4],nxt[N << 4],w[N << 4],tot;
inline void add(int x,int y,int val)
{
	to[tot] = y;
	nxt[tot] = head[x];
	w[tot] = val;
	head[x] = tot ++;
}

bool vis[N];
int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n)
	{
		read(t[i]); read(d[i]); read(r[i]);
		rep(j,1,r[i])
		{
			int x; read(x);
			v[i].push_back(x);
		}
	}
	rep(i,1,n) rep(j,0,((int)v[i].size())-1)
		g[i].push_back(d[v[i][j]]),
		t[i] += d[v[i][j]],
		add(v[i][j],i,j);
	queue<int> q;
	rep(i,1,n) q.push(i),vis[i] = 1;
	while(!q.empty())
	{
		int x = q.front();q.pop();vis[x] = 0; 
		if(chkmin(d[x],t[x]))
		for(register int i = head[x];~i;i=nxt[i])
		{
			if(chkmin(t[to[i]],t[to[i]] - g[to[i]][w[i]] + d[x]))		
			{
				g[to[i]][w[i]] = d[x];
				if(!vis[to[i]])
					q.push(to[i]),vis[to[i]] = 1;
			}
		}

	}
	cout << d[1] << endl;
	return 0;
}
