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
const int N = 1e5 + 50;
int head[N],nxt[N],to[N],tot;
int n,q,w[N];

inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int p[N][21],deep[N];
void dfs(int x)
{
	for(register int i = head[x];~i;i = nxt[i])
	{
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
	}
}

inline int get_lca(int x,int y)
{
	if(deep[x] < deep[y]) swap(x,y);
	repd(i,20,0) if(deep[x] - (1 << i) >= deep[y]) x = p[x][i];
	if(x == y) return x;
	repd(i,20,0) if(p[x][i] != p[y][i]) x = p[x][i],y = p[y][i];
	return p[x][0];
}

int v[N],cnt;

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(q);
	rep(i,1,n) read(w[i]);
	rep(i,2,n)
	{
		int a,b;
		read(a); read(b);
		p[b][0] = a;
		add(a,b);
	}

	dfs(1);
	
	rep(j,1,20) rep(i,1,n)
		p[i][j] = p[p[i][j-1]][j-1];

	while(q--)
	{
		int t,a,b;
		read(t); read(a); read(b);
		if(t == 1) w[a] = b;

		if(t == 0)
		{
			int c = get_lca(a,b);
			if(deep[a] + deep[b] + 1 - 2 * deep[c] > 50) puts("Y");
			else
			{
				v[cnt=1] = w[c];
				while(a != c)
				{
					v[++cnt] = w[a];
					a = p[a][0];
				}
				while(b != c)
				{
					v[++cnt] = w[b];
					b = p[b][0];
				}
				sort(v + 1,v + 1 + cnt);
				bool e = 0;
				rep(i,3,cnt)
					if(v[i-2] > v[i] - v[i-1])
					{
						e = 1;
						break;
					}
				puts(e?"Y":"N");
			}
		}
	}
	
	return 0;
}
