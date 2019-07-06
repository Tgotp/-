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

const int N = 2e5 + 50;
int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

char s[N];
int l[N],r[N],mx[N],se[N],sz[N],n;

void dfs1(int x,int fa)
{
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa)
		{
			dfs1(to[i],x);
			sz[x] += sz[to[i]];
			if(mx[x] < mx[to[i]] + 1)	
				se[x] = mx[x],mx[x] = mx[to[i]] + 1;
			else if(se[x] < mx[to[i]] + 1)
				se[x] = mx[to[i]] + 1;
			if(sz[to[i]]) l[x] = min(l[x],mx[to[i]] + 1);
		}
}

ll ans;

void dfs2(int x,int fa)
{
	r[x] = min(se[x] + 1,mx[x] - 1);
	if(l[x] <= r[x]) ans += r[x] - l[x] + 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa)
		{
			int k = mx[to[i]]+1==mx[x]?se[x]+1:mx[x]+1;
			if(k > mx[to[i]]) se[to[i]] = mx[to[i]],mx[to[i]] = k;
			else if(k > se[to[i]]) se[to[i]] = k;
			if(sz[1] - sz[to[i]]) l[to[i]] = min(l[to[i]],k);
			dfs2(to[i],x);
		}
}
int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}
	scanf("%s",s + 1);
	rep(i,1,n)
		if(s[i] == '1') l[i] = 0,sz[i] = 1;
		else l[i] = n + 1;

	dfs1(1,1); 
	dfs2(1,1);

	cout << ans + 1<< endl;

	return 0;
}
