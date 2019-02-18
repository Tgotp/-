#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
#define read(x) scanf("%d",&x)
using namespace std;
const int N = 203,M = N * N << 1;
int n,x[N],y[N],p[N];
int head[N],to[M],nxt[M],tot;
int ans;

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

#define dis(a,b) (x[a] - x[b])*(x[a] - x[b]) + (y[a] - y[b])*(y[a] - y[b])

int vised,vis[N];

void dfs(int x)
{	
	vis[x] = vised;
	for(register int i = head[x];~i;i=nxt[i])
		if(vis[to[i]] != vised)
			dfs(to[i]);
}

int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n) read(x[i]),read(y[i]),read(p[i]);
	rep(i,1,n) rep(j,1,n)
		if(i != j && dis(i,j) <= p[i] * p[i])
			add(i,j);
	
	rep(i,1,n)
	{
		++ vised;
		dfs(i);
		int now = 0;
		rep(j,1,n) if(vis[j] == vised) ++ now;
		ans = max(now,ans);
	}

	cout << ans << endl;

	return 0;
}
