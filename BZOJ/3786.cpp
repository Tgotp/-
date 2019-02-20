#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
inline char gc()
{
	static char *S,*T,buf[1<<16];
	if(S == T)
	{
		T = (S = buf) + fread(buf,1,1<<16,stdin);
		if(T == S) return EOF;
	}
	return *S ++;
}
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = gc(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = gc(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int head[N],to[N],nxt[N],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int n,m;

int sz = 1;
int w[N],val[N];
int in[N],out[N];
bool e[N] ;

void dfs(int x)
{
	in[x] = ++ sz; w[sz] = val[x]; e[sz] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		dfs(to[i]);
	out[x] = ++ sz; w[sz] = - val[x];
}

int rt,fa[N]; ll ans[N],lzy[N],rel[N];
int ch[N][2],num1[N],num2[N];
int build(int l,int r,int f)
{
	if(l > r) return 0;
	int mid = l + r >> 1;
	ans[mid] = w[mid];
	rel[mid] = w[mid];
	num1[mid] = e[mid];
	num2[mid] = !e[mid];
	fa[mid] = f;
	if(l == r) return l;

	ch[mid][0] = build(l,mid-1,mid);
	ch[mid][1] = build(mid+1,r,mid);

	ans[mid] += ans[ch[mid][0]] + ans[ch[mid][1]];
	num1[mid] += num1[ch[mid][0]] + num1[ch[mid][1]];
	num2[mid] += num2[ch[mid][0]] + num2[ch[mid][1]];

	return mid;
}

#define lc ch[x][0]
#define rc ch[x][1]
void put_down(int x)
{
	if(fa[x]) put_down(fa[x]);
	if(lzy[x])
	{		
		ans[lc] += (num1[lc] - num2[lc])*lzy[x];
		ans[rc] += (num1[rc] - num2[rc])*lzy[x];
		rel[lc] += (e[lc]?1:-1) * lzy[x];
		rel[rc] += (e[rc]?1:-1) * lzy[x];
		lzy[lc] += lzy[x];
		lzy[rc] += lzy[x];
		lzy[x] = 0;
	}
}

inline bool get(int x) { return ch[fa[x]][1] == x; }

inline void update(int x)
{
	num1[x] = num1[lc] + num1[rc] + e[x];
	num2[x] = num2[lc] + num2[rc] + (!e[x]);
	ans[x] = ans[lc] + ans[rc] + rel[x];
}

inline void rotate(int x)
{
	int f = fa[x],t = get(x);
	if(fa[f]) ch[fa[f]][get(f)] = x;
	fa[x] = fa[f]; fa[f] = x;
	if(ch[x][t^1]) fa[ch[x][t^1]] = f;
	ch[f][t] = ch[x][t^1]; ch[x][t^1] = f;

	if(f == rt) rt = x;
	update(f); update(x);
}

inline void splay(int x,int y)
{
	put_down(x);
	while(fa[x] != y)
	{
		if(fa[fa[x]] !=	y) rotate(get(fa[x]) == get(x) ? fa[x] : x);
		rotate(x);
	}
}

inline int Nxt(int x)
{
	splay(x,0);
	x = ch[x][1];
	while(ch[x][0])
	{
		if(lzy[x])
		{		
			ans[lc] += (num1[lc] - num2[lc])*lzy[x];
			ans[rc] += (num1[rc] - num2[rc])*lzy[x];
			rel[lc] += (e[lc]?1:-1) * lzy[x];
			rel[rc] += (e[rc]?1:-1) * lzy[x];
			lzy[lc] += lzy[x];
			lzy[rc] += lzy[x];
			lzy[x] = 0;
		}
		x = ch[x][0];
	}

	if(lzy[x])
	{		
		ans[rc] += (num1[rc] - num2[rc])*lzy[x];
		rel[rc] += (e[rc]?1:-1) * lzy[x];
		lzy[rc] += lzy[x];
		lzy[x] = 0;
	}
	return x;
}

inline int Pre(int x)
{
	splay(x,0);

	x = ch[x][0];
	while(ch[x][1])
	{
		if(lzy[x])
		{		
			ans[lc] += (num1[lc] - num2[lc])*lzy[x];
			ans[rc] += (num1[rc] - num2[rc])*lzy[x];
			rel[lc] += (e[lc]?1:-1) * lzy[x];
			rel[rc] += (e[rc]?1:-1) * lzy[x];
			lzy[lc] += lzy[x];
			lzy[rc] += lzy[x];
			lzy[x] = 0;
		}
		x = ch[x][1];
	}

	if(lzy[x])
	{		
		ans[lc] += (num1[lc] - num2[lc])*lzy[x];
		rel[lc] += (e[lc]?1:-1) * lzy[x];
		lzy[lc] += lzy[x];
		lzy[x] = 0;
	}

	return x;
}

void fff(int x)
{
	printf("%d %lld\n",x,rel[x]);
	if(lc) fff(lc);
	if(rc) fff(rc);
}

int main()
{
	memset(head,-1,sizeof head);
	read(n);
	rep(i,2,n)
	{
		int fa;
		read(fa);
		add(fa,i);
	}

	rep(i,1,n) read(val[i]);

	dfs(1);

	++ sz; e[1] = 1;
	rt = build(1,sz,0);

#ifndef ONLINE_JUDGE
	puts("\n");
	rep(i,1,sz) printf("%d %d %d\n",fa[i],ch[i][0],ch[i][1]);
	puts("");
	printf("%d %d %lld\n",num1[rt],num2[rt],ans[rt]);
	puts("");
#endif

	read(m);

	while(m --)
	{
		char c;
		do { c = gc(); }while(c !='Q' && c != 'C' && c != 'F');
		if(c == 'Q')
		{
			int d; read(d);
			splay(1,0);
			splay(out[d],1);
			printf("%lld\n",ans[ch[ch[rt][1]][0]]);
		}

		if(c == 'C')
		{
			int x,y;
			read(x); read(y);

			int a,b;
			a = Pre(in[x]);
			b = Nxt(out[x]);
			splay(a,0); splay(b,a);

			int t = ch[ch[rt][1]][0];
			ch[ch[rt][1]][0] = 0; fa[t] = 0;
			update(ch[rt][1]);
			update(rt);

			int z = Nxt(in[y]);
			ch[z][0] = t; fa[t] = z; splay(t,0);
		}

		if(c == 'F')
		{
			int x,y;
			read(x); read(y);

			int a,b;
			a = Pre(in[x]);
			b = Nxt(out[x]);
			splay(a,0); splay(b,a);
			
			int t = ch[ch[rt][1]][0];
			ans[t] += 1ll*(num1[t] - num2[t])*y;
			rel[t] += (e[t] ? 1 : -1) * y;
			lzy[t] += y;
		}

	}

	return 0;
}
