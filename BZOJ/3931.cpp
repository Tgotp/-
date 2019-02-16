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

const int N = 1005,M = 3e5 + 540;
const ll inf = 1e18;
int n,m;
ll d[N];

struct EDGE
{
	int head[N],to[M],nxt[M],tot; ll w[M];
	inline void m() { memset(head,-1,sizeof head); }

	inline void add(int x,int y,ll val)
	{
		w[tot] = val;
		to[tot] = y;
		nxt[tot] = head[x];
		head[x] = tot ++;
	}
}g1,g2;

int s,t;
inline void SPFA()
{
	#define mk(x,y) make_pair(x,y)
	memset(d,0x3f,sizeof d);
	priority_queue<pair<int,int> >q;
	q.push(mk(0,1)); d[1] = 0;
	while(!q.empty())
	{
		int x = q.top().second;q.pop();
		for(register int i = g1.head[x];~i;i=g1.nxt[i])
		{
			int to = g1.to[i];
			if(chkmin(d[to],d[x] + g1.w[i]))
				q.push(mk(-d[to],to));
		}
	}

	rep(x,1,n)
	{
		int z; read(z);
		g2.add(x,x + n,z); g2.add(x + n,x,0);
		for(register int i = g1.head[x]; ~i;i = g1.nxt[i])
			if(d[g1.to[i]] == d[x] + g1.w[i])
				g2.add(x + n,g1.to[i],inf), g2.add(g1.to[i],x + n,0);
	}
	t = n + n + 2;
	g2.add(s,1 + n,inf); g2.add(1 + n,s,0);
	g2.add(n,t,inf); g2.add(t,n,0);
}

inline bool bfs()
{
	queue<int> q;
	memset(d,0,sizeof d);
	q.push(s); d[s] = 1;
	while(!q.empty())
	{
		int x = q.front();q.pop();
		for(register int i = g2.head[x];~i;i=g2.nxt[i])
			if(g2.w[i] && !d[g2.to[i]])
			{
				d[g2.to[i]] = d[x] + 1;
				q.push(g2.to[i]);
			}
	}
	return d[t];
}

ll dfs(int x,ll w)
{
	if(t == x || ! w) return w;
	ll F,flow = 0;
	for(register int i = g2.head[x];~i;i=g2.nxt[i])
		if(d[g2.to[i]] == d[x] + 1 && (F = dfs(g2.to[i],min(g2.w[i],w))))
		{
			flow += F; g2.w[i^1] += F;
			w -= F; g2.w[i] -= F;
			if(!w) break;
		}
	return flow;
}

ll ans;

int main()
{
	g1.m(); g2.m();
	read(n); read(m);
	rep(i,1,m)
	{
		int u,v,w;
		read(u); read(v); read(w);
		g1.add(u,v,w); g1.add(v,u,w);
	}

	SPFA();

	while(bfs())
		ans += dfs(s,inf);

	cout << ans << endl;

	return 0;
}
