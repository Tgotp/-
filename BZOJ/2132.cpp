#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') c = getchar(); }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e3 + 50,P = N * N,M = N * N << 3,inf = INT_MAX;
int id[N][N],a[N][N],b[N][N],c[N][N];
int f[M],to[M],nxt[M],head[P],tot;
int n,m;

inline void add(int x,int y,int flow)
{
	to[tot] = y;
	f[tot] = flow;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int d[P],s,t;
int q[P],st,en;
int cur[P];

inline bool bfs()
{
	memset(d,0,sizeof d);
	d[s] = 1; st = en = 0; q[st] = s;
	while(st <= en)
	{
		int x = q[st ++]; cur[x] = head[x];
		for(register int i = head[x];~i;i=nxt[i])
			if(!d[to[i]] && f[i])
			{
				d[to[i]] = d[x] + 1;
				q[++en] = to[i];
			}
	}
	return d[t];
}

int dfs(int x,int w)
{
	if(x == t || !w) return w;
	int flow = 0,F;
	for(register int&i = cur[x];~i;i=nxt[i])
		if(d[to[i]] == d[x] + 1 && (F = dfs(to[i],min(w,f[i]))))
		{
			flow += F; w -= F;
			f[i] -= F; f[i^1] += F;
			if(!w) break;
		}
	return flow;
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m); int ans = 0;
	rep(i,1,n) rep(j,1,m) id[i][j] = (i - 1) * m + j;
	rep(i,1,n) rep(j,1,m) read(a[i][j]),ans += a[i][j];
	rep(i,1,n) rep(j,1,m) read(b[i][j]),ans += b[i][j];
	rep(i,1,n) rep(j,1,m) read(c[i][j]),ans += c[i][j] * (4 - (i == 1) - (i == n) - (j == 1) - (j == m));
	s = 0;t = n * m + 2;
	rep(i,1,n) rep(j,1,m) 
		if((i + j) & 1)
		{
			add(s,id[i][j],a[i][j]);
			add(id[i][j],s,0);
			add(id[i][j],t,b[i][j]);
			add(t,id[i][j],0);
		}
		else
		{
			add(s,id[i][j],b[i][j]);
			add(id[i][j],s,0);
			add(id[i][j],t,a[i][j]);
			add(t,id[i][j],0);
		}
	rep(i,1,n) rep(j,1,m)
	{
		if(i > 1)
		{
			add(id[i][j],id[i-1][j],c[i][j] + c[i-1][j]);
			add(id[i-1][j],id[i][j],c[i][j] + c[i-1][j]);
		}
		if(j > 1)
		{
			add(id[i][j],id[i][j-1],c[i][j] + c[i][j-1]);
			add(id[i][j-1],id[i][j],c[i][j] + c[i][j-1]);
		}
	}

	while(bfs()) ans -= dfs(s,inf);
	cout << ans << endl;

	return 0;
}
