#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x; i <= y; ++ i)
#define repd(i,x,y) for(register int i = x ;i >= y ;-- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    x = 0;char c;int sign = 1;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 1e6 + 500,inf = 1e9+7;
int n,m;
bool Now;
struct RELP
{ 
	int x[2],id;
	inline bool operator < (const RELP C) const { return x[Now] < C.x[Now]; }
}a[N];
struct Point
{
    int x[2],mi[2],ma[2],l,r,sz;
    void clear() { rep(i,0,1) x[i] = mi[i] = ma[i] = 0;l = r = 0; }
    bool operator < (const Point C) const { return x[Now] < C.x[Now]; }
}p[N];
struct KD_tree
{
    Point T;
    int ans,cnt,root;
 
    const bool cmp(Point a,Point b) { return a.x[Now] < b.x[Now]; }
    int dis(Point a,Point b) { return abs(a.x[0] - b.x[0]) + abs(a.x[1] - b.x[1]); }
     
    void update(int x)
    {
        rep(i,0,1)
        {
			p[x].mi[i] = p[x].ma[i] = p[x].x[i];
            if(p[x].l) p[x].mi[i] = min(p[x].mi[i],p[p[x].l].mi[i]),p[x].ma[i] = max(p[x].ma[i] ,p[p[x].l].ma[i]);
            if(p[x].r) p[x].mi[i] = min(p[x].mi[i],p[p[x].r].mi[i]),p[x].ma[i] = max(p[x].ma[i] ,p[p[x].r].ma[i]);
        }
		p[x].sz = p[p[x].l].sz + p[p[x].r].sz + 1;
    }
     
    int build(int l,int r,bool now)
    {
        Now = now;
        int mid = l + r >> 1;
        nth_element(p + l,p + mid,p + r + 1);
        if(l < mid) p[mid].l = build(l,mid - 1,now ^ 1);
        if(r > mid) p[mid].r = build(mid + 1,r,now ^ 1);
         
        update(mid);
         
        return mid;
    }
     
	int k;

	void Get(int x)
	{
		++cnt; rep(i,0,1) a[cnt].x[i] = p[x].x[i];a[cnt].id = x;
		if(p[x].l) Get(p[x].l);
		if(p[x].r) Get(p[x].r);
	}

	int rebuild(int l,int r,bool now)
	{
		int mid = l + r >> 1;
		Now = now;
		nth_element(a + l,a + mid,a + r + 1);
		int x = a[mid].id;p[x].clear();
		rep(i,0,1)p[x].x[i] = a[mid].x[i]; 
		if(l < mid) p[x].l = rebuild(l,mid-1,now^1);
		if(r > mid) p[x].r = rebuild(mid+1,r,now^1);
		update(x);
		return x;
	}

	void dfs(int x)
	{
		printf("%d %d\n",p[x].x[0],p[x].x[1]);
		if(p[x].l) dfs(p[x].l);
		if(p[x].r) dfs(p[x].r);
	}

	int pia(int x,bool now)
	{
		if(x != k)
		{
			if(p[x].x[now] < T.x[now]) 
				p[x].r = pia(p[x].r,now^1);
			else p[x].l = pia(p[x].l,now^1);
			return x;
		}
		cnt = 0; Get(x);
		return rebuild(1,cnt,now);	
	}

    void insert(int x,bool now)
    {
        if(p[x].x[now] < T.x[now])
        {
            if(!p[x].r) 
            {
                p[x].r = ++n;
                p[n] = T;
            }
            else insert(p[x].r,now^1);
        }
        else
        {
            if(!p[x].l) 
            {
                p[x].l = ++n;
                p[n] = T; 
            }
            else insert(p[x].l,now^1);
        }
        update(x);
		if(max(p[p[x].l].sz,p[p[x].r].sz) > p[x].sz * 0.75) k = x;
    }
     
    void modify(Point x) { T = x; insert(root,0); }
     
    int get(int x)
    {
        if(!x) return inf;
        int ans = 0;
        rep(i,0,1) ans += max(0,p[x].mi[i] - T.x[i]);
        rep(i,0,1) ans += max(0,T.x[i] - p[x].ma[i]);
        return ans;
    }
     
    void query(int x)
    {
        int d = dis(T,p[x]);
        ans = min(d,ans);
         
        int d1 = get(p[x].l),d2 = get(p[x].r);
        if(d1 < d2)
        {
            if(d1 < ans) query(p[x].l);
            if(d2 < ans) query(p[x].r);
        }
        else
        {
            if(d2 < ans) query(p[x].r);
            if(d1 < ans) query(p[x].l);
        }
    }
     
    inline int find(Point P)
    {
        T = P;ans = inf; query(root);
        return ans;
    }
}tree;
 
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("5.in","r",stdin);
	//freopen("3.out","w",stdout);
#endif
    read(n); read(m);
    rep(i,1,n) read(p[i].x[0]),read(p[i].x[1]); 
     
    tree.root = tree.build(1,n,0);
     
	int lst = n;
    rep(i,1,m)
    {
        int op;Point P;P.clear(); P.sz = 1;
        read(op); read(P.x[0]); read(P.x[1]);
        rep(j,0,1) P.mi[j] = P.ma[j] = P.x[j];
        if(op == 1)
		{
			tree.k = 0;
			tree.modify(P);
			if(tree.k) tree.root=tree.pia(tree.root,0);
		}
        else printf("%d\n",tree.find(P));
    }
    return 0;
}
