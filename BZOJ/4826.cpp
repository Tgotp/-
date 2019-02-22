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
int n,m,p1,p2;
int nxt[N],lst[N],a[N];
int s[N],top;

vector<int> v1[N];
vector<pair<int,int> > v2[N],v3[N],v4[N],v5[N];
#define mk(x,y) make_pair(x,y)

struct Segment_tree
{
	ll val[N << 2];int lzy[N << 2];
	void clear(int id,int l,int r)
	{
		val[id] = lzy[id] = 0;
		if(l == r) return;
		int mid = l + r >> 1;
		clear(id<<1,l,mid); clear(id<<1|1,mid+1,r);
	}

	inline void put_down(int id,int l,int r)
	{
		if(!lzy[id]) return ;
		int mid = l + r >> 1;
		val[id << 1] += 1ll * (mid - l + 1) * lzy[id];
		val[id << 1|1] += 1ll * (r - mid) * lzy[id];
		lzy[id << 1] += lzy[id]; lzy[id << 1|1] += lzy[id];
		lzy[id] = 0;
	}

	void add(int id,int l,int r,int L,int R)
	{
		if(l == L && r == R)
		{
			++ lzy[id];
			val[id] += r - l + 1;
			return;
		}
		
		put_down(id,l,r);

		int mid = l + r >> 1;
		if(R <= mid) add(id<<1,l,mid,L,R);
		else if(L > mid) add(id<<1|1,mid+1,r,L,R);
		else add(id<<1,l,mid,L,mid),add(id<<1|1,mid+1,r,mid+1,R);
		val[id] = val[id<<1] + val[id<<1|1];
	}

	ll find(int id,int l,int r,int L,int R)
	{
		if(l == L && r == R) return val[id];

		put_down(id,l,r);

		int mid = l + r >> 1;
		
		if(R <= mid) return find(id<<1,l,mid,L,R);
		else if(L > mid) return find(id<<1|1,mid+1,r,L,R);
		else return find(id<<1,l,mid,L,mid)+find(id<<1|1,mid+1,r,mid+1,R);
	}
}s1,s2;

ll ans[N];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	read(n); read(m); read(p1); read(p2);
	rep(i,1,n) read(a[i]);
	rep(i,1,n)
	{
		while(top && a[s[top]] <= a[i]) -- top;
		if(top) lst[i] = s[top];
		s[++ top] = i;
	}
	top = 0;
	repd(i,n,1)
	{
		while(top && a[s[top]] < a[i]) -- top;
		if(top) nxt[i] = s[top];
		else nxt[i] = n + 1;
		s[++ top] = i;
	}

	rep(i,2,n)
	{
		if(lst[i]) v1[nxt[i]].push_back(lst[i]);
		if(lst[i] < i-1)v2[nxt[i]].push_back(mk(lst[i]+1,i-1));
		if(nxt[i] > i+1)v3[lst[i]].push_back(mk(i+1,nxt[i]-1));
	}


	rep(i,1,m)
	{
		int l,r;
		read(l); read(r);
		ans[i] = (r - l) * p1;
		v4[r].push_back(mk(l,i));
		v5[l].push_back(mk(r,i));
	}

	rep(i,1,n)
	{
		int sz;
		sz = v1[i].size(); -- sz;
		rep(j,0,sz) s1.add(1,1,n,v1[i][j],v1[i][j]);
		sz = v2[i].size(); -- sz;
		rep(j,0,sz) s2.add(1,1,n,v2[i][j].first,v2[i][j].second);
		sz = v4[i].size(); -- sz;
		rep(j,0,sz) ans[v4[i][j].second] += p1 * s1.find(1,1,n,v4[i][j].first,n)
			+ p2 * s2.find(1,1,n,v4[i][j].first,n);
	}

	s1.clear(1,1,n);
	repd(i,n,1)
	{
		int sz = v3[i].size(); -- sz;
		rep(j,0,sz) s1.add(1,1,n,v3[i][j].first,v3[i][j].second);
		sz = v5[i].size(); -- sz;
		rep(j,0,sz) ans[v5[i][j].second] += p2 * s1.find(1,1,n,1,v5[i][j].first);
	}

	rep(i,1,m) printf("%lld\n",ans[i]);

	return 0;
}
