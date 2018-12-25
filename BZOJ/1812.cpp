#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y;-- i)
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

const int N = 1e2 + 50;
int n,k,a[N];
int f[N][N][N];

int head[N],to[N],nxt[N],w[N],tot;
inline void add(int x,int y,int val)
{
	to[tot] = y;
	nxt[tot] = head[x];
	w[tot] = val;
	head[x] = tot ++;
}

int fa[N],d[N],tmp[N][N],top;
void dfs(int x)
{
	int c = 0;
	repd(i,top,1)
	{
		c += d[i];
		f[x][0][fa[i]] = c * a[x];
	}
	fa[++ top] = x;
	f[x][1][x] = 0;
	for(register int i = head[x];~i;i=nxt[i])
	{
		d[top] = w[i];
		dfs(to[i]);
		memset(tmp,0x3f,sizeof tmp);
		rep(j,1,top) rep(t,0,k) rep(q,0,t)
			chkmin(tmp[t][fa[j]],f[x][t-q][fa[j]] + min(f[to[i]][q][to[i]],f[to[i]][q][fa[j]]));
		rep(j,1,top) rep(q,0,k) f[x][q][fa[j]] = tmp[q][fa[j]];
	}
	-- top;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	memset(head,-1,sizeof head);
	memset(f,0x3f,sizeof f);
	read(n); read(k); ++ k;
	rep(i,1,n)
	{
		int fa,d;
		read(a[i]); read(fa); read(d);
		add(fa,i,d);
	}
	dfs(0);
	cout << f[0][k][0] << endl;
	return 0;
}
