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
	do { x = x * 10 + c - '0';  c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e4 + 50, M = 3e4 + 50;
int head[N],to[M << 1] ,nxt[M << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

const int inf = 1e9;
int z[12],id[M << 1],f[12][M << 1];
int n,m,a[N],deep[N];
bool vis[N];

inline bool And(int x,int y)
{
	while(x && y)
	{
		if((x % 3) == 1 && (y % 3)) return true;
		x /= 3,y /= 3;
	}
	return false;
}

inline int Or(int x,int y)
{
	int ans = 0,t = 0;
	while(x || y)
	{
		if((x % 3) == 0 && (y % 3))
			ans += 2 * id[t] ;
		else ans += (x % 3) * id[t];

		x /= 3,y /= 3; ++ t;
	}
	return ans;
}

void dfs(int x)
{
	vis[x] = 1;

	int d = deep[x];
	if(!d) f[0][0] = 0,f[0][1] = a[x],f[0][2] = inf;
	else
	{
		rep(i,0,z[d])
			f[d][i] = inf;

		int y = 0 ;
		for(register int i = head[x];~i;i=nxt[i])
			if(deep[to[i]] < deep[x])
				y += id[deep[to[i]]];	
		
		int s = z[d-1];
		rep(i,0,s) if(f[d-1][i] < inf)
		{
			if(And(i,y)) chkmin(f[d][i+2*id[d]],f[d-1][i]);
			else chkmin(f[d][i],f[d-1][i]);
			chkmin(f[d][Or(i,y) + id[d]],f[d-1][i] + a[x]);
		}
	}

	//printf("%d %d %d\n",z[d],d,x);	

	for(register int i = head[x];~i;i=nxt[i])
		if(deep[to[i]] > deep[x] && !vis[to[i]])
		{
			deep[to[i]] = d + 1;
			dfs(to[i]);
			int s = z[d];
			rep(j,0,s)
			 	f[d][j] = min(f[d+1][j + id[d+1]],
					f[d+1][j+2*id[d+1]]);
		}
}

int main()
{
	freopen("20.in","r",stdin);
	freopen("20.out","w",stdout);
	memset(head,-1,sizeof head);
	read(n); read(m);
	rep(i,1,n) read(a[i]);
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	id[0] = 1;
	rep(i,1,10) id[i] = id[i-1] * 3; 
	rep(i,0,10) z[i] = id[i+1] - 1;
	memset(deep,0x3f,sizeof deep); int ans = 0;
	rep(i,1,n) if(!vis[i]) deep[i] = 0,dfs(i),ans += min(f[0][1],f[0][2]);
	/*
	cout << f[0][1] << endl;
	cout << f[1][7] << endl;
	cout << f[2][18] << endl;
	*/
	cout << ans << endl;

	return 0;
}
