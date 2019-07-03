#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y;-- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50,M = 1e6 + 650;
int n,W,sz,s,t;
int head[N],nxt[M],to[M],w[M],f[M],tot;
int zc[N],zr[N],fc[N],fr[N];

inline void add(int x,int y,int flow,int val)
{
	to[tot] = y;
	w[tot] = val;
	f[tot] = flow;
	nxt[tot] = head[x];
	head[x] = tot ++ ;
}

struct DATA { int w,id; }a[N],b[N],c[N];

const bool cmp(DATA a,DATA b) { return a.w < b.w; }
const bool cmp2(DATA a,DATA b) { return a.id < b.id; }

void cdq_build(int l,int r)
{
	if(l == r) return;
	int mid = l + r >> 1;
	nth_element(a + l,a + mid + 1,a + r + 1,cmp);
	sort(a + l,a + mid + 1,cmp2);
	sort(a + mid + 1,a + r + 1,cmp2);
	int now = mid;

	rep(i,l,mid) 
	{
		if(now < r && a[now + 1].id < a[i].id)
		{
			++ sz;
			if(now != mid) 
			{
				add(sz,sz - 1,INT_MAX,0);
				add(sz - 1,sz,0,0);
			}
			
			while(now < r && a[now + 1].id < a[i].id) 
			{
				++ now;
				add(sz,zc[a[now].id],1,0);	
				add(zc[a[now].id],sz,0,0);	
			}
		}
		if(now > mid) 
		{
			add(fr[a[i].id],sz,1,0);
			add(sz,fr[a[i].id],0,0);
		}
	}
	now = l - 1;
	rep(i,mid + 1,r)
	{
		if(now < mid && a[now + 1].id < a[i].id)
		{
			++ sz;
			if(now != l - 1)
			{
				add(sz,sz - 1,INT_MAX,0);
				add(sz - 1,sz , 0 , 0 );
			}
			
			while(now < mid && a[now + 1].id < a[i].id) 
			{
				++ now;
				add(sz,fc[a[now].id],1,0);
				add(fc[a[now].id],sz,0,0);
			}
		}
		if(now >= l) 
		{
			add(zr[a[i].id],sz,1,0);
			add(sz,zr[a[i].id],0,0);
		}
	}
	cdq_build(l,mid); cdq_build(mid+1,r);
}

ll d[N]; int from[N]; bool vis[N];
queue<int>q;
inline bool bfs()
{
	rep(i,1,sz) d[i] = 1e18;
	d[s] = 0;
	#define mk(x,y) make_pair(x,y)
	q.push(s);
	while(!q.empty())
	{
		int x = q.front(); q.pop(); vis[x] = 0;
		for(register int i = head[x];~i;i=nxt[i])
			if(d[to[i]] > d[x] + w[i] && f[i])	
			{
				d[to[i]] = d[x] + w[i];
				from[to[i]] = i;
				if(!vis[to[i]])
					q.push(to[i]),vis[to[i]] = 1;
			}
	}

	return d[t] != 1e18;
}

inline ll get()
{
	ll ans = 0;int flow = 1e9; from[s] = -1;
	for(register int i = from[t];~i;i = from[to[i^1]])
		flow = min(f[i],flow);
	for(register int i = from[t];~i;i = from[to[i^1]])
		f[i] -= flow,f[i ^ 1] += flow,ans += w[i] * flow;
	return ans;
}
	

ll ans;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	memset(head,- 1,sizeof head);
	read(n); read(W);
	rep(i,1,n) read(a[i].w),a[i].id = i;

	s = ++ sz;t = ++ sz;
	rep(i,1,n)
	{
		int id = ++ sz;
		add(s,id,1,0); add(id,s,0,0);
		zr[i] = ++ sz; fr[i] = ++ sz;
		add(id,zr[i],1,a[i].w); add(zr[i],id,0,-a[i].w);
		add(id,fr[i],1,-a[i].w); add(fr[i],id,0,a[i].w);

		add(id,t,1,W); add(t,id,0,-W);

		id = ++ sz;
		add(id,t,1,0); add(t,id,0,0);
		zc[i] = ++ sz; fc[i] = ++ sz;
		add(zc[i],id,1,a[i].w); add(id,zc[i],0,-a[i].w);
		add(fc[i],id,1,-a[i].w); add(id,fc[i],0,a[i].w);

	}

	cdq_build(1,n);
	//printf("%d %d\n",sz,tot);
	/*
	rep(i,1,n) rep(j,1,i-1)
		if(a[i].w < a[j].w)
			add(fr[i],zc[j],1,0),
			add(zc[j],fr[i],0,0);
		else add(zr[i],fc[j],1,0),
			 add(fc[j],zr[i],0,0);
	*/

	while(bfs()) ans += get();

	cout << ans << endl;
	
	return 0;
}
