#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i )
#define repd(i,x,y) for(register int i = x;i >= y; -- i )
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c = getchar(); if(c == '-')  sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e4 + 50,M = 1e6 + 560;
int head[N],nxt[M],to[M],f[M],tot;
int n,al,a1,a2,bl,b1,b2;
char S[55][55];

inline void add(int x,int y,int w)
{
	f[tot] = w;
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

int vis[N],vised;
int d[N],s,t;
inline bool bfs()
{
	d[s] = 1; vis[s] = ++vised;queue<int> q; q.push(s);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		for(register int i = head[x];~i;i=nxt[i])
			if(f[i] && vis[to[i]] != vised)
			{
				d[to[i]] = d[x] + 1;
				vis[to[i]] = vised;
				q.push(to[i]);
			}
	}
	return vis[t] == vised;
}

int dfs(int x,int w)
{
	if(x == t || !w) return w;
	int F,flow = 0;
	for(register int i = head[x];~i;i=nxt[i])
		if(vis[to[i]] == vised && d[to[i]] == d[x] + 1 && (F = dfs(to[i],min(w,f[i]))))
		{
			f[i] -= F; f[i^1] += F;
			w -= F; flow += F;
			if(!w) break;
		}
	return flow ;
}

inline int get()
{
	memset(head,-1,sizeof head); tot = 0;
	int cnt = n * n;
	rep(i,1,n) rep(j,i + 1,n)
		if(S[i][j] == 'N')
			add(i,j,505), add(j,i,505);
		else if(S[i][j] == 'O')
		{
			++ cnt;
			add(i,cnt,1); add(cnt,i,0);
			add(j,cnt,1); add(cnt,j,0);
			++ cnt;
			add(cnt-1,cnt,1); add(cnt,cnt-1,0);
			add(cnt,i,1); add(i,cnt,0);
			add(cnt,j,1); add(j,cnt,0);
		}
	
	t = cnt + 1;
	
	add(s,a1,al); add(a1,s,0);
	add(s,b1,bl); add(b1,s,0);
	add(a2,t,al); add(t,a2,0);
	add(b2,t,bl); add(t,b2,0);

	int ans = 0;
	while(bfs())
		ans += dfs(s,550);
	
	return ans;
}

inline void solve()
{
	read(a1); read(a2); read(al); read(b1); read(b2); read(bl);
	rep(i,1,n) scanf("%s",S[i] + 1);
	++ a1; ++ a2; ++ b1; ++ b2;
	if(get() != al + bl) return void(puts("No"));
	swap(b1,b2);
	if(get() != al + bl) return void(puts("No"));
	puts("Yes");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4.in","r",stdin);
#endif
	while(scanf("%d",&n) != EOF)
		solve();
	return 0;
}
