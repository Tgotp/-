#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ?x = y,1 : 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ?x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 5e5 + 50,M = N * 15;
int n,m,S;
int a[N],b[N];

int in[N];
int head[N],nxt[M],to[M],w[M],tot;
inline void add(int x,int y,int val)
{
	++ in[y];
	to[tot] = y;
	w[tot] = val;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int t,rel[N];
void build(int id,int l,int r)
{
	chkmax(t,id);
	if(l == r) return void(rel[l] = id);
	int mid = l + r >> 1;
	build(id << 1,l,mid);
	build(id << 1|1,mid+1,r);
	add(id,id << 1,0);
	add(id,id << 1|1,0);
}

void Add(int id,int l,int r,int L,int R)
{
	if(L > R) return;
	if(l == L && r == R) return void(add(t,id,1));
	int mid = l + r >> 1;
	if(R <= mid) Add(id<<1,l,mid,L,R);
	else if(L > mid) Add(id<<1|1,mid+1,r,L,R);
	else Add(id<<1,l,mid,L,mid),Add(id<<1|1,mid+1,r,mid+1,R);
}

bool inq[N];int s[N],dfn[N],low[N],top,sz;
void tarjan(int x)
{
	inq[x] = 1; s[++ top] = x;
	dfn[x] = low[x] = ++ sz;
	for(register int i = head[x];~i;i=nxt[i])
		if(!dfn[to[i]])
		{
			tarjan(to[i]);		
			chkmin(low[x],low[to[i]]);
		}else if(inq[to[i]]) chkmin(low[x],dfn[to[i]]);
	
	if(dfn[x] == low[x])
	{
		if(s[top] != x)
		{
			puts("NIE");
			exit(0);
		}
		inq[x] = 0;
		-- top;
	}
}

const int inf = 1e9;
bool k[N];

inline void toposort()
{
	queue<int>q;
	rep(i,1,t) if(!k[i]) a[i] = inf;
	rep(i,1,t) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		if(a[x] <= 0) { puts("NIE");exit(0);}
		for(register int i = head[x];~i;i=nxt[i])
		{
			-- in[to[i]];
			if(!in[to[i]]) q.push(to[i]);
			if(k[to[i]])
			{
				if(a[to[i]] > a[x] - w[i])
				{
					puts("NIE");
					exit(0);
				}
			}
			else chkmin(a[to[i]],a[x] - w[i]);
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("55.in","r",stdin);
#endif
	memset(head,-1,sizeof head);
	read(n); read(S); read(m);
	build(1,1,n);
	rep(i,1,S)
	{
		int p,d;
		read(p); read(d);
		a[rel[p]] = d; k[rel[p]] = 1;
	}
	rep(i,1,m)
	{
		int l,r,k; ++ t;
		read(l); read(r); read(k);
		rep(j,1,k) read(b[j]),add(rel[b[j]],t,0);
		b[0] = l-1; rep(j,1,k) Add(1,1,n,b[j-1]+1,b[j]-1);
		Add(1,1,n,b[k]+1,r);
	}

	rep(i,1,t) if(!dfn[i]) tarjan(i);

	toposort();

	puts("TAK");
	rep(i,1,n) printf("%d ",a[rel[i]]);

	return 0;
}
