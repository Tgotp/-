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

int n,m,s,t,es,et,rt;

map<int,int>mp;
const int M = 5e6 + 50;
struct Segment_tree
{
	int ls[M],rs[M],lzy[M],sz[M],val[M],cnt,nu;

	void build(int&id,int l,int r,int L,int R)
	{
		if(!id) id = ++ cnt;
		sz[id] = R - L + 1;  val[id] = l;
		if(l == L && r == R) return void (lzy[id] = 1);
		int mid = l + r >> 1;
		if(R <= mid) build(ls[id],l,mid,L,R);
		else if(L > mid) build(rs[id],mid+1,r,L,R);
		else build(ls[id],l,mid,L,mid),build(rs[id],mid+1,r,mid+1,R);
	}

	inline int newnode(int l,int r)
	{
		sz[++ cnt] = min(r,et) - max(l,es) + 1; 
		lzy[cnt] = 1;
		if(l == r) val[cnt] = l - es + 1;
		return cnt;
	}

	int find(int x,int l,int r,int pos)
	{
		if(l == r) return 1;
		int mid = l + r >> 1;
		if(lzy[x]) 
		{
			ls[x] = newnode(l,mid),
			rs[x] = newnode(mid+1,r);
			lzy[x] = 0;
		}
		if(pos <= mid) return find(ls[x],l,mid,pos);
		else return find(rs[x],mid+1,r,pos) + sz[ls[x]];
	}

	int query(int x,int l,int r,int k)
	{
		if(l == r) return val[x];
		int mid = l + r >> 1;
		if(lzy[x]) 
		{
			ls[x] = newnode(l,mid),
			rs[x] = newnode(mid+1,r);
			lzy[x] = 0;
		}
		if(k <= sz[ls[x]]) return query(ls[x],l,mid,k);
		else return query(rs[x],mid+1,r,k - sz[ls[x]]);
	}
	void update(int&x,int l,int r,int pos,int w)
	{
		if(!x) x = ++ cnt;
		sz[x] += w; val[x] = nu;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(lzy[x]) 
		{
			ls[x] = newnode(l,mid),
			rs[x] = newnode(mid+1,r);
			lzy[x] = 0;
		}
		if(pos <= mid) update(ls[x],l,mid,pos,w);
		else update(rs[x],mid+1,r,pos,w);
	}
}seg;

int main()
{
	read(n); read(m);
	s = m + 1,t = n + m;
	es = s,et = t;
	n += 2 * m + 2;
	seg.build(rt,1,n,s,t);
	int op,x,y,lstans=0;
	while(m --)
	{
		read(op); 
		if(op == 1)
		{
			read(x); read(y);
			x -= lstans;y -= lstans;
			printf("%d\n",lstans=seg.find(rt,1,n,mp[x] > 0 ? mp[x] : es + x - 1));
			mp[y] = mp[x] > 0 ? mp[x] : es + x - 1;
			seg.nu = y; seg.update(rt,1,n,mp[y],0);
			mp[x] = 0;
		}
		else if(op == 2)
		{
			read(x);
			x -= lstans;
			printf("%d\n",lstans=seg.find(rt,1,n,mp[x] > 0 ? mp[x] : es + x - 1));
			seg.update(rt,1,n,mp[x] > 0 ? mp[x] : es + x - 1,-1);
			seg.nu = x; seg.update(rt,1,n,-- s,1);
			mp[x] = s;
		}
		else if(op == 3)
		{
			read(x);
			x -= lstans;
			printf("%d\n",lstans=seg.find(rt,1,n,mp[x] > 0 ? mp[x] : es + x - 1));
			seg.update(rt,1,n,mp[x] > 0 ? mp[x] : es + x - 1,-1);
			seg.nu = x; seg.update(rt,1,n,++ t,1);
			mp[x] = t;
		}
		else
		{
			read(x);
			x -= lstans;
			printf("%d\n",lstans= seg.query(rt,1,n,x));
		}
	}
	return 0;
}
