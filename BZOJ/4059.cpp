#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = 1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int n;
int a[N],b[N],nxt[N],lst[N],vis[N];

struct DATA { int a,b,c; }c[N];
const bool cmp(DATA a,DATA b) { return a.a < b.a; }

int val[N << 2],t[N << 2];
void add(int id,int L,int R,int l,int r,int w)
{
	if(L == l && r == R) { val[id] += w; t[id] += w;return ;}
	int mid = L + R >> 1;
	if(l > mid) add(id<<1|1,mid+1,R,l,r,w);
	else if(r <= mid) add(id<<1,L,mid,l,r,w);
	else add(id<<1,L,mid,l,mid,w),add(id<<1|1,mid+1,R,mid+1,r,w);
	val[id] = min(val[id<<1],val[id<<1|1]) + t[id];
}

int find(int id,int L,int R,int l,int r)
{
	if(L == l && r == R) return val[id];
	int mid = L + R >> 1;
	if(l > mid) return find(id<<1|1,mid+1,R,l,r);
	else if(r <= mid) return find(id<<1,L,mid,l,r);
	else return min(find(id<<1,L,mid,l,mid),find(id<<1|1,mid+1,R,mid+1,r)) + t[id];
}

void clear(int id,int l,int r)
{
	t[id] = val[id] = 0;
	if(l == r) return;
	int mid = l + r >> 1;
	clear(id<<1,l,mid); clear(id<<1|1,mid+1,r);
}

inline void solve()
{
	read(n);
	rep(i,1,n) read(a[i]),b[i] = a[i];
	
	sort(b + 1,b + 1 + n);
	rep(i,1,n) a[i] = lower_bound(b + 1,b + 1 + n,a[i]) - b;

	rep(i,1,n) vis[i] = 0;
	rep(i,1,n)
	{
		lst[i] = vis[a[i]] + 1;
		vis[a[i]] = i;
	}

	rep(i,1,n) vis[i] = n + 1;
	repd(i,n,1)
	{
		nxt[i] = vis[a[i]] - 1;
		vis[a[i]] = i;
	}

	rep(i,1,n) c[i].a = lst[i],c[i].b = i,c[i].c = nxt[i];
	sort(c + 1,c + 1 + n,cmp);

	int now = 1;
	rep(i,1,n)
	{
		while(now <= n && c[now].a <= i) { add(1,1,n,c[now].b,c[now].c,1); ++ now;}
		if(i != 1) add(1,1,n,i-1,nxt[i-1],-1);
		if(find(1,1,n,i,n) == 0) { puts("boring");clear(1,1,n); return ; }
	}

	clear(1,1,n);
	puts("non-boring");
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.out","w",stdout);
#endif

	int t;
	read(t);
	while(t --) solve();
	return 0;
}
