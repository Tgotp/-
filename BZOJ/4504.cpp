#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e5 + 50;
int n,k;
map<int,int> pre;

struct DATA
{
	ll mx; int id,l,r,pos;
	DATA(){}
	DATA(int _id,int _l,int _r,int _pos,ll _mx)
	{
		id = _id; l = _l; r = _r; 
		pos = _pos; mx = _mx;
	}
	inline bool operator < (const DATA a) const{ return mx < a.mx; }
};
priority_queue<DATA> q;

const int M = 4e6 + 50;
int rt[N],ls[M],rs[M],pos[M],sz;
ll mx[M],lzy[M];

void build(int&id,int l,int r)
{
	id = ++ sz; pos[id] = l;
	if(l == r) return ;
	int mid = l + r >> 1;
	build(ls[id],l,mid);
	build(rs[id],mid+1,r);
	
}

void add(int&x,int y,int l,int r,int L,int R,int w)
{
	x = ++ sz;
	ls[x] = ls[y];rs[x] = rs[y];mx[x] = mx[y];pos[x] = pos[y];lzy[x] = lzy[y];
	if(l == L && r == R)
	{
		mx[x] += w;
		lzy[x] += w;
		return ;
	}

	int mid = l + r >> 1;
	if(R <= mid) add(ls[x],ls[y],l,mid,L,R,w);
	else if(L > mid) add(rs[x],rs[y],mid+1,r,L,R,w);
	else add(ls[x],ls[y],l,mid,L,mid,w),add(rs[x],rs[y],mid+1,r,mid+1,R,w);
	mx[x] = max(mx[ls[x]],mx[rs[x]]) + lzy[x];
	pos[x] = mx[ls[x]] > mx[rs[x]] ? pos[ls[x]] : pos[rs[x]];
}

pair<int,ll> find(int x,int l,int r,int L,int R)
{
	pair<int,ll> a;
	if(l == L && r == R)
	{
		a.first = pos[x];
		a.second = mx[x];
		return a;
	}
	
	int mid = l + r >> 1;
	if(R <= mid) a = find(ls[x],l,mid,L,R);
	else if(L > mid) a = find(rs[x],mid+1,r,L,R);
	else	
	{
		a = find(ls[x],l,mid,L,mid);	
		pair<int,ll> b;
		b = find(rs[x],mid+1,r,mid+1,R);
		if(b.second > a.second)
			a.first = b.first,
			a.second = b.second;
	}

	a.second += lzy[x];
	return a;	
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("20.in","r",stdin);
	//freopen("11.out","w",stdout);
#endif
	read(n); read(k);
	build(rt[0],1,n);
	rep(i,1,n)
	{
		int x; read(x);
		add(rt[i],rt[i-1],1,n,pre[x]+1,i,x);
		pre[x] = i;
		pair<int,ll> a = find(rt[i],1,n,1,i);
		q.push(DATA(rt[i],1,i,a.first,a.second));	
	}

	while(k-- > 1)
	{
		DATA a = q.top(); q.pop();	
		if(a.pos != a.l)
		{
			pair<int,ll> b = find(a.id,1,n,a.l,a.pos-1);
			q.push(DATA(a.id,a.l,a.pos-1,b.first,b.second));
		}

		if(a.pos != a.r)
		{
			pair<int,ll> b = find(a.id,1,n,a.pos+1,a.r);
			q.push(DATA(a.id,a.pos+1,a.r,b.first,b.second));
		}
	}

	printf("%lld\n",q.top().mx);

	return 0;
}
