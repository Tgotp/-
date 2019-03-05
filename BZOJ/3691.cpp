#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 252;
int s,t,n,m,q;
int dis[N][N];

const int M = 1e6;
int head[N << 1],to[M],nxt[M],w[M],f[M],tot;
inline void add(int x,int y,int flow,int val)
{
	to[tot] = y;
	nxt[tot] = head[x];
	f[tot] = flow;
	w[tot] = val;
	head[x] = tot ++;
}

int d[N << 1],from[N << 1]; bool inq[N << 1];
inline bool bfs()
{
	memset(d,0x3f,sizeof d);
	queue<int> q; q.push(s); d[s] = 0;
	while(!q.empty())
	{
		int x = q.front(); q.pop(); inq[x] = 0;
		for(register int i = head[x];~i;i=nxt[i])
			if(f[i] && d[to[i]] > d[x] + w[i])
			{
				d[to[i]] = d[x] + w[i];
				from[to[i]] = i;
				if(!inq[to[i]]) inq[to[i]] = 1,q.push(to[i]);
			}	
	}
	return d[t] < 0x3f3f3f3f;
}

ll val[N],cnt;

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m); read(q);
	memset(dis,0x3f,sizeof dis);
	t = 2 * n + 1;
	rep(i,1,m)
	{
		int a,b,c;
		read(a); read(b); read(c);
		dis[a][b] = min(dis[a][b],c);
	}
	rep(k,1,n) rep(i,1,n) rep(j,1,n) 
		if(dis[i][k] < 0x3f3f3f3f && dis[k][j] < 0x3f3f3f3f)
			dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
	rep(i,1,n)
	{
		add(s,i,1,0); add(i,s,0,0);
		add(i+n,t,1,0); add(t,i+n,0,0);
		rep(j,1,n) if(dis[i][j] < 0x3f3f3f3f)
			add(i,j+n,1,dis[i][j]),
			add(j+n,i,0,-dis[i][j]);
	}
	
	int cnt = 0; from[s] = -1;
	while(bfs())
	{
		++ cnt;
		for(int i = from[t];~i; i = from[to[i^1]])	
			f[i] -= 1,f[i^1] += 1;
		val[cnt] = val[cnt-1] + d[t];
	}
	while(q -- )
	{
		int c; read(c);
		ll ans = c * n;
		int l = 1,r = cnt;
		rep(i,1,cnt) ans = min(ans,val[i] + (n - i) * c);
		while(l <= r)
		{
			int mid = l + r >> 1;
			ll res1 = val[mid] + (n - mid) * c;		
			ll res2 = val[mid-1] + (n - mid+1) * c;		
			ans = min(ans,min(res1,res2));
			if(res1 < res2)
				l = mid + 1;
			else r = mid - 2;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
