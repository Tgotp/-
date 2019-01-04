#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y? x = y,1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 11;
int n,m,cnt;
int f[N][N][1 << N];
int a[N][N],b[N][N];

int X[5] = {0,1,-1,0,0};
int Y[5] = {0,0,0,1,-1};
queue<int> q; bool vis[N][N];
pair<int,int> from[N][N][1 << N];
#define mk(x,y) make_pair(x,y)
inline void SPFA(int now)
{
	while(!q.empty())
	{
		int x = q.front()/m,y = q.front()%m; q.pop();
		if(!y) y = m,--x; vis[x][y] = 0;
		rep(i,1,4)
		{
			int xx = x + X[i],yy = y + Y[i];
			if(!xx || ! yy || xx > n || yy > m) continue;
			if(!chkmin(f[xx][yy][now],f[x][y][now] + a[xx][yy])) continue;
			if(!vis[xx][yy]) q.push(xx * m + yy),vis[xx][yy] = 1;
			from[xx][yy][now] = mk(x*m+y,now); 
		}
	}
}

bool c[N][N];
void dfs(int u,int now)
{
	int x = u / m,y = u%m;
	if(!y) y = m,--x;
	c[x][y] = 1;
	if(!from[x][y][now].second) return;
	if(now != from[x][y][now].second) dfs(from[x][y][now].first,now ^ from[x][y][now].second);
	dfs(from[x][y][now].first,from[x][y][now].second);
}

int main()
{
	read(n); read(m); int rt;
	memset(f,0x3f,sizeof f);
	rep(i,1,n) rep(j,1,m)
	{
		read(a[i][j]);
		if(!a[i][j])
		{
			++ cnt; rt = i * m + j;
			f[i][j][1 << cnt - 1] = 0;
			b[i][j] = 1 << cnt - 1;
		}
	}
	int s = (1 << cnt) - 1;
	rep(now,0,s)
	{
		rep(i,1,n) rep(j,1,m) 
		{
			for(int k = now;k;k = (k-1)&now)
				if(chkmin(f[i][j][now],f[i][j][k] + f[i][j][now^k] - a[i][j]))
					from[i][j][now] = mk(i*m+j,k);
			if(f[i][j][now] < 0x3f3f3f3f) q.push(i*m + j),vis[i][j] = 1;
		}	
		SPFA(now);
	}

	dfs(rt,s);
	int x = rt/m,y = rt%m;
	if(!y) --x,y = m;
	cout << f[x][y][s] << endl;
	rep(i,1,n) rep(j,1,m)
	{
		if(!a[i][j]) putchar('x');
		else putchar(c[i][j]?'o':'_');
		if(j == m) puts("");
	}

	return 0;
}
