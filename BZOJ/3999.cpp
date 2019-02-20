#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y;-- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 5e4 + 50;
int n,q,val[N];

int head[N],to[N << 1],nxt[N << 1],tot;
inline void add(int x,int y)
{
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int sz[N],fa[N],top[N],hson[N],deep[N];

void dfs1(int x)
{
	sz[x] = 1;
	for(register int i = head[x];~i;i=nxt[i]) if(to[i] != fa[x])
	{
		deep[to[i]] = deep[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		sz[x] += sz[to[i]];
		if(sz[to[i]] > sz[hson[x]])
			hson[x] = to[i];
	}

}

int id[N],idx[N],cnt;
void dfs2(int x,int t)
{
	top[x] = t;
	id[x] = ++ cnt;
	idx[cnt] = x;
	if(hson[x]) dfs2(hson[x],t);
	for(register int i = head[x];~i;i=nxt[i])
		if(to[i] != fa[x] && to[i] != hson[x])
			dfs2(to[i],to[i]);
}

int lzy[N << 2];
struct DATA 
{
	int mi,mx,ans1,ans2;
	DATA(){}
	DATA(int _mi,int _mx,int _ans1,int _ans2)
	{
		mi = _mi,mx = _mx,ans1 = _ans1,ans2 = _ans2;
	}
}w[N << 2];

DATA merge(DATA x,DATA y) 
{ 
	return DATA(min(x.mi,y.mi),max(x.mx,y.mx),
		max(max(x.ans1,y.ans1),x.mx - y.mi),max(max(x.ans2,y.ans2),y.mx - x.mi));
}

void build(int id,int l,int r)
{
	if(l == r)
	{
		w[id] = DATA(val[idx[l]],val[idx[l]],0,0);
		return ;
	}
	int mid = l + r >> 1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	w[id] = merge(w[id<<1],w[id<<1|1]);
}

inline void put_down(int id)
{
	if(!lzy[id]) return ;
	w[id<<1].mx += lzy[id];
	w[id<<1].mi += lzy[id];
	w[id<<1|1].mx += lzy[id];
	w[id<<1|1].mi += lzy[id];
	lzy[id<<1] += lzy[id];
	lzy[id<<1|1] += lzy[id];
	lzy[id] = 0;
}

int z;
DATA find(int id,int l,int r,int L,int R)
{
	if(l == L && r == R) return w[id];
	put_down(id);
	int mid = l + r >> 1;

	if(L > mid) return find(id<<1|1,mid+1,r,L,R);
	else if(R <= mid) return find(id<<1,l,mid,L,R);
	else return merge(find(id<<1,l,mid,L,mid),find(id<<1|1,mid+1,r,mid+1,R));
}

void update(int id,int l,int r,int L,int R)
{
	if(l == L && r == R)
	{
		lzy[id] += z;
		w[id].mi += z;w[id].mx += z;
		return ;
	}
	put_down(id);
	int mid = l + r >> 1;

	if(L > mid) update(id<<1|1,mid+1,r,L,R);
	else if(R <= mid) update(id<<1,l,mid,L,R);
	else update(id<<1,l,mid,L,mid),update(id<<1|1,mid+1,r,mid+1,R);

	w[id] = merge(w[id<<1],w[id<<1|1]);
}

inline int get_lca(int u,int v)
{
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u,v);
		u = fa[top[u]];
	}
	return deep[u] > deep[v] ? v : u;
}

int ans,oo;
inline void find1(int x,int y)
{
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		DATA c = find(1,1,n,id[top[x]],id[x]);
		update(1,1,n,id[top[x]],id[x]);
		ans = max(ans,c.ans1);
		ans = max(ans,c.mx - oo);
		oo = min(oo,c.mi);
		x = fa[top[x]];
	}

	if(deep[x] < deep[y]) swap(x,y);
	DATA c = find(1,1,n,id[y],id[x]);
	update(1,1,n,id[y],id[x]);
	ans = max(ans,c.ans1);
	ans = max(ans,c.mx - oo);
	oo = min(oo,c.mi);	
}

inline void find2(int x,int y)
{
	int k = 0;
	while(top[x] != top[y])
	{
		if(deep[top[x]] < deep[top[y]]) swap(x,y);
		DATA c = find(1,1,n,id[top[x]],id[x]);
		update(1,1,n,id[top[x]],id[x]);
		ans = max(ans,c.ans2);
		ans = max(ans,c.mx - oo);
		ans = max(ans,k - c.mi);
		k = max(k,c.mx);
		x = fa[top[x]];
	}

	if(deep[x] < deep[y]) swap(x,y);
	DATA c = find(1,1,n,id[y],id[x]);
	update(1,1,n,id[y],id[x]);
	ans = max(ans,c.ans2);
	ans = max(ans,c.mx - oo);
	ans = max(ans,k - c.mi);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
	freopen("22.out","w",stdout);
#endif
	memset(head,-1,sizeof head);
	read(n);
	rep(i,1,n) read(val[i]);

	rep(i,2,n)
	{
		int u,v;
		read(u); read(v);
		add(u,v); add(v,u);
	}

	dfs1(1);

	dfs2(1,1);

	build(1,1,n);

	read(q);

#ifndef ONLINE_JUDGE
	puts("\n");
#endif

	while(q --)
	{
		int u,v;
		read(u); read(v); read(z);
		int lc = get_lca(u,v);

		ans = 0; oo = INT_MAX;

		find1(u,lc);
		
		z = -z; update(1,1,n,id[lc],id[lc]); z = -z;
		
		find2(v,lc);

		printf("%d\n",ans);
	}

	return 0;
}
