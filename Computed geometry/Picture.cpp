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

const int N = 2e4 + 50,K = 1e4 + 1,mx = 2e4 + 40;
int n,cnt1,cnt2,ans;
struct DATA { int l,r,t,val; }t1[N],t2[N];
const bool cmp(DATA a,DATA b) { return a.t < b.t; }

struct SEGMENT_TREE
{
	int val[N << 2],cnt[N << 2];

	inline void clear() { memset(val,0,sizeof val);memset(cnt,0,sizeof cnt); }

	inline void pd(int id,int len,bool k)
	{
		if(cnt[id]) val[id] = len;
		else if(k) val[id] = 0;
		else val[id] = val[id << 1] + val[id << 1|1];
	}

	void update(int id,int l,int r,int L,int R,int w)
	{
		if(l == L && r == R)
		{
			cnt[id] += w;
			pd(id,r-l+1,l == r);	
			return ;
		}
		int mid = l + r >> 1;
		if(L > mid) update(id<<1|1,mid+1,r,L,R,w);
		else if(R <= mid) update(id<<1,l,mid,L,R,w);
		else update(id<<1,l,mid,L,mid,w),update(id<<1|1,mid+1,r,mid+1,R,w);
		pd(id,r-l+1,0);
	}

}seg;

inline void solve()
{
	ans = 0;cnt1 = 0;cnt2 = 0; seg.clear();
	rep(i,1,n)
	{
		int lx,ly,rx,ry;
		read(lx); read(ly); read(rx); read(ry);
		lx += K; ly += K; rx += K; ry += K;
		t1[i].l = lx;t1[i].r = rx;t1[i].t = ly;t1[i].val = 1;
		t1[i+n].l = lx;t1[i+n].r = rx;t1[i+n].t = ry;t1[i+n].val = -1;
		t2[i].l = ly;t2[i].r = ry;t2[i].t = lx;t2[i].val = 1;
		t2[i+n].l = ly;t2[i+n].r = ry;t2[i+n].t = rx;t2[i+n].val = -1;
	}
	cnt1 = 2 * n;cnt2 = 2 * n;
	sort(t1 + 1,t1 + 1 + cnt1,cmp);
	sort(t2 + 1,t2 + 1 + cnt2,cmp);
	int lst = 0;
	rep(i,1,cnt1) 
	{
		seg.update(1,1,mx,t1[i].l+1,t1[i].r,t1[i].val);
		ans += abs(seg.val[1] - lst);	
		lst = seg.val[1];
	}
	lst = 0;
	seg.clear();
	rep(i,1,cnt2) 
	{
		seg.update(1,1,mx,t2[i].l+1,t2[i].r,t2[i].val);
		ans += abs(seg.val[1] - lst);	
		lst = seg.val[1];
	}
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d",&n) != EOF)
		solve();
	return 0;
}
