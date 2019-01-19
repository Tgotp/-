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
int n,q,w[N];

int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

const int M = 1e7 + 50;
int rt[N],ch[M][2],val[M],sz;
void insert(int&x,int y,int w,int d)
{
	x = ++ sz; ch[x][0] = ch[y][0];ch[x][1] = ch[y][1]; val[x] = val[y] + 1;
	if(d == -1) return ;
	if(w & (1 << d)) insert(ch[x][1],ch[y][1],w,d-1);
	else insert(ch[x][0],ch[y][0],w,d-1);
}

int find(int x,int y,int w,int d)
{
	if(d == -1) return w;
	if(w & (1 << d))
	{
		if(val[ch[x][0]] - val[ch[y][0]])
			return find(ch[x][0],ch[y][0],w,d-1);
		else return find(ch[x][1],ch[y][1],w^(1 << d),d-1);
	}
	else 
	{
		if(val[ch[x][1]] - val[ch[y][1]])
			return find(ch[x][1],ch[y][1],w^(1<<d),d-1);
		else return find(ch[x][0],ch[y][0],w,d-1);
	}
}

int Rt[N],Ch[M][2],cnt;

int ins(int x,int w,int d)
{
	if(!x) x = ++ cnt; if(d == -1) return x;
	if(w & (1 << d)) Ch[x][1] = ins(Ch[x][1],w,d-1);
	else Ch[x][0] = ins(Ch[x][0],w,d-1);
	return x;
}

int Find(int x,int w,int d)
{
	if(d == -1) return w;
	if(w & (1 << d))
	{
		if(Ch[x][0])
			return Find(Ch[x][0],w,d-1);
		else return Find(Ch[x][1],w^(1<<d),d-1);
	}
	else
	{
		if(Ch[x][1])
			return Find(Ch[x][1],w^(1<<d),d-1);
		else return Find(Ch[x][0],w,d-1);
	}
}

int merge(int x,int y,int d)
{
	if(!x || !y) return x|y;
	if(d == -1) return x;
	Ch[x][0] = merge(Ch[x][0],Ch[y][0],d-1);
	Ch[x][1] = merge(Ch[x][1],Ch[y][1],d-1);
	return x;
}

bool vis[N];
int ans[N],f[N],fa[N];
struct DATA
{
	int x,z,id;
	DATA(){}
	DATA(int _x,int _z,int _id) { id = _id;x = _x;z = _z;	 }
};
vector<DATA> v[N];
vector<DATA> z[N];

int getfa(int x) { return f[x] == x ? x : f[x] = getfa(f[x]); }

void dfs(int x)
{
	vis[x] = 1;
	insert(rt[x],rt[fa[x]],w[x],30);
	Rt[x] = ins(Rt[x],w[x],30);
	
	f[x] = x;
	int sz = z[x].size(); -- sz;
	rep(i,0,sz)
		if(vis[z[x][i].x])
		{
			int y = z[x][i].x;
			int t = fa[getfa(y)];
			ans[z[x][i].id] = max(find(rt[x],rt[t],z[x][i].z,30),find(rt[y],rt[t],z[x][i].z,30));
		}

	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x])
		{
			fa[to[i]] = x;
			dfs(to[i]);
			Rt[x] = merge(Rt[x],Rt[to[i]],30);
		}
	
	sz = v[x].size(); -- sz;
	rep(i,0,sz) ans[v[x][i].id] = Find(Rt[x],v[x][i].z,30);

	f[x] = fa[x];
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(q);
	rep(i,1,n) read(w[i]);
	rep(i,2,n) 
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	rep(i,1,q)
	{
		int op,x,y,Z;
		read(op);
		if(op == 1)
		{
			read(x); read(y);
			v[x].push_back(DATA(x,y,i));
		}
		if(op == 2)
		{
			read(x); read(y); read(Z);
			z[x].push_back(DATA(y,Z,i));
			z[y].push_back(DATA(x,Z,i));
		}
	}

	dfs(1);

	rep(i,1,q) printf("%d\n",ans[i]);

	return 0 ;
}
