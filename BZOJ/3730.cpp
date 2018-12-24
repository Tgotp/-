#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 1e5 + 50;
int w[N],n,m;
int head[N],to[N << 1],nxt[N << 1],tot;

inline void add(int x,int y)
{
	nxt[tot] = head[x];
	to[tot] = y;
	head[x] = tot ++;
}

int mx[N],sz[N],num,rt; bool vis[N];
void dfs1(int x,int fa)
{
	mx[x] = sz[x] = 1; ++ num;
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]] && to[i] != fa){
			dfs1(to[i],x);	
			sz[x] += sz[to[i]];
			mx[x] = max(mx[x],sz[to[i]]);
	}
}

void dfs2(int x,int fa)
{
	for(register int i = head[x];~i;i=nxt[i])	
		if(!vis[to[i]] && to[i] != fa) dfs2(to[i],x);
	chkmax(mx[x],num-sz[x]);
	if(mx[x] < mx[rt]) rt = x;
}

void get_rt(int x)
{
	num = 0;rt = 0;
	dfs1(x,x); dfs2(x,x);
}

int sx[N],sy[N];
vector<int>ax[N];
vector<int>ay[N];
map<int,int>mp1[N],mp2[N];
void dfs(int x,int w,int fa,bool p)
{
	if(p) chkmax(sx[rt],w),ax[rt].push_back(x);
	else chkmax(sy[rt],w),ay[rt].push_back(x);
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]] && to[i] != fa)
			dfs(to[i],w + 1,x,p);
}

int pos1,pos2,p1[N],p2[N];
ll t1[N << 4],t2[N << 4];
#define lowbit(x) (x&-x)
inline void update1(int x,int w) { for(register int i = x;i <= pos1; i += lowbit(i)) t1[i] += w; }
inline void update2(int x,int w) { for(register int i = x;i <= pos2; i += lowbit(i)) t2[i] += w; }
inline ll find1(int x) { ll ans = 0; for(register int i = x;i;i-=lowbit(i)) ans += t1[i]; return ans; }
inline ll find2(int x) { ll ans = 0;for(register int i = x;i;i-=lowbit(i)) ans += t2[i]; return ans; }

int fa[N];
void solve(int x)
{
	dfs(x,0,x,1); vis[x] = 1;
	p1[x] = pos1++;pos1 += sx[x] + 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(!vis[to[i]]){
			get_rt(to[i]); dfs(to[i],1,x,0);
			p2[rt] = pos2 ++ ; pos2 += sy[rt] + 1;
			fa[rt] = x; solve(rt);
	}
}

int pos[N],p[N << 2][21],lg[N << 2],id;
void dfs3(int x,int fa,int w)
{
	pos[x] = ++ id; p[id][0] = w;
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa) dfs3(to[i],x,w + 1),p[++id][0] = w;
}

inline int dis(int x,int y)
{
	x = pos[x],y = pos[y];
	if(x > y) swap(x,y);
	int k = lg[y - x + 1];
	return p[x][0] + p[y][0] - 2*min(p[x][k],p[y-(1<<k)+1][k]);
}

inline int find(int x,int y)
{
	int a = x,b = x,ans = 0;
	while(a) { ans += find1(p1[a]+max(min(sx[a],y-dis(x,a)),-1)) - find1(p1[a]-1);a = fa[a]; }
	while(fa[b]) { ans -= find2(p2[b]+max(min(sy[b],y-dis(x,fa[b])),-1)) - find2(p2[b]-1); b = fa[b]; }
	return ans;
}

inline void update(int x,int y)
{
	int a = x;
	while(a)
	{
		update1(p1[a]+dis(x,a),y-w[x]);
		if(fa[a]) update2(p2[a]+dis(fa[a],x),y-w[x]);
		a = fa[a];
	}
	w[x] = y;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	memset(head,-1,sizeof head);
	read(n); read(m);
	rep(i,1,n) read(w[i]);
	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs3(1,1,1);
	rep(j,1,20) rep(i,1,id) if(i+(1<<j-1) <= id) p[i][j] = min(p[i][j-1],p[i+(1<<j-1)][j-1]);
	rep(i,2,id) lg[i] = lg[i>>1] + 1;
	
	pos1 = pos2 = 1;
	mx[0] = 1e8;
	get_rt(1);
	solve(rt);
	rep(x,1,n)
	{
		rep(i,0,((int)ax[x].size())-1)
			update1(p1[x]+dis(x,ax[x][i]),w[ax[x][i]]);
		rep(i,0,((int)ay[x].size())-1)
			update2(p2[x]+dis(fa[x],ay[x][i]),w[ay[x][i]]);
	}
	int lstans = 0,x,y,op;
	while(m -- )
	{
		read(op); read(x); read(y);
		x ^= lstans;y ^= lstans;
		if(op == 0) printf("%d\n",lstans = find(x,y));
		else update(x,y);
	}

	return 0;
}
