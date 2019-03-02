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

inline void init(string name)
{
	string in = name + ".in",out = name + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
}


const int M = 4e6 + 60;
const int N = 1e3 + 50;
char s[N][N];
int n,Q,cnt;
int id[N][N],v[N][N];
struct EDGE { int u,v,w; }e[M];
const bool cmp(EDGE a,EDGE b) { return a.w > b.w; }
int sum[N][N];

int p[M];
int get_fa(int x ) { return x == p[x] ? x : p[x] = get_fa(p[x]); }

int head[M],to[M],nxt[M],w[M],deep[M],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

int fa[M],sz[M],top[M],hson[M];
void dfs1(int x)
{
	sz[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
	{
		deep[to[i]] = deep[x] + 1;
		dfs1(to[i]);
		sz[x] += sz[to[i]];
		if(sz[hson[x]] < sz[to[i]])
			hson[x] = to[i];
	}
}
void dfs2(int x,int t)
{
	top[x] = t;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
		if(hson[x] != to[i])
			dfs2(to[i],to[i]);
}

inline int get_lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		x = fa[top[x]];
	}
	return deep[x] < deep[y] ? x : y;
}

int x[9] = {0,1,1,1,-1,-1,-1,0,0};
int y[9] = {0,1,0,-1,1,0,-1,1,-1};
inline void getv()
{
	queue<int> q;
	rep(i,1,n) rep(j,1,n) if(s[i][j] == '#')
		q.push(id[i][j]);
	if(q.empty())
	{
		rep(i,1,n) rep(j,1,n) 
			v[i][j] = INT_MAX;
	}
	while(!q.empty())
	{
		int X = q.front();q.pop();
		int a = X/n + 1,b = X % n;
		if(!b) --a ,b = n;
		rep(i,1,8)
		{
			int xx = a + x[i],yy = b + y[i];
			if(xx > n && !xx && yy > n && !yy) continue;
			if(v[xx][yy] || s[xx][yy] == '#') continue;
			v[xx][yy] = v[a][b] + 1;	
			q.push(id[xx][yy]);
		}
	}

	rep(i,1,n) rep(j,1,n) if(s[i][j] != '#')
		v[i][j] = min(v[i][j]-1,min(min(i-1,j-1),min(n-i,n-j)));
	rep(i,1,n) rep(j,1,n) if(s[i][j] != '#')
		v[i][j] = v[i][j]*2+1;
}

inline int get(int a,int b)
{
	int l = 0 ,r = min(min(n-a,n-b),min(a-1,b-1)),mid,ans = 0;
	while(l <= r)
	{
		mid = l + r >> 1;
		int res = sum[a + mid][b + mid] + sum[a - mid - 1][b - mid - 1];
		res -= sum[a-mid-1][b + mid] + sum[a + mid][b - mid - 1];
		if(res == 0 ) ans = mid*2+1,l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}

inline void print(int a,int b)
{
	rep(i,a-7,a+7) 
	
	{	
	rep(j,b-7,b+7)
		if(i==a&&b==j) putchar('x');
		else printf("%c",s[i][j]);
	puts("");
	}
	puts("");
		
}

int main()
{
	//init("B");
	freopen("1.in","r",stdin);
	//freopen("17.out","w",stdout);
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n)
		scanf("%s",s[i] + 1);
	
	rep(i,1,n) rep(j,1,n)
		sum[i][j] = (s[i][j] == '#') + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];

	rep(i,1,n) rep(j,1,n) id[i][j] = (i - 1) * n + j;
	getv();

	rep(i,1,n) rep(j,1,n) if(s[i][j] != '#')
	{
		int x,y;
		x = i + 1,y = j;
		if(x <= n && s[x][y] != '#')
		{
			e[++ cnt].u = id[i][j];
			e[cnt].v = id[x][y];
			e[cnt].w = min(v[x][y],v[i][j]);
			//min(2*min(r[i][j],r[x][y]) +1,2* min(l[i][j],l[x][y]) + 1);
		}
		x = i,y = j + 1;
		if(y <= n && s[x][y] != '#')
		{
			e[++ cnt].u = id[i][j];
			e[cnt].v = id[x][y];
			e[cnt].w = min(v[x][y],v[i][j]);
			//min(min(u[i][j],u[x][y]) * 2 + 1,2* min(d[i][j],d[x][y]) + 1);
		}
	}

	sort(e + 1,e + 1 + cnt,cmp);

	repd(i,n * n,1) p[i] = i; int num = n * n;
	repd(i,n * n,1) w[i] = INT_MAX;
	rep(i,1,cnt)
	{
		int u = get_fa(e[i].u),v = get_fa(e[i].v);
		if(u != v)
		{
			++ num;
			add(num,u); add(num,v);
			w[num] = e[i].w;
			fa[u] = num; fa[v] = num;
			p[u] = num;p[v] = num;
			p[num] = num;
		}
	}
	rep(i,1,num) if(get_fa(i) == i)
	{
		dfs1(i);
		dfs2(i,i);
	}
	
	read(Q);
	rep(i,1,Q)
	{
		int a,b,c,d;
		read(a); read(b); read(c); read(d);
		if(get_fa(id[a][b]) != get_fa(id[c][d])) { puts("0"); continue; }

		int ans = min(v[a][b],v[c][d]);

		printf("%d\n",min(w[get_lca(id[a][b],id[c][d])],ans));
	}

    return 0;
}

