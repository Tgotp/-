#include<cstdio>
#include<map>
#include<algorithm>
#include<cmath>
#include<iostream>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;

const int N = 250;
int n,cnt,tot;
struct DATA { double l,r,t;int val; }a[N];

double b[N],z[N];
map<double,int>mp;

struct Segment_tree
{
	double val[N << 2];
	int num[N << 2];
	void update(int id,int l,int r,int pos,int t)
	{
		if(l == r)
		{
			num[id] += t;
			if(num[id]) val[id] = z[l];
			else val[id] = 0;
			return ;
		}
		int mid = l + r >> 1;
		if(pos <= mid) update(id<<1,l,mid,pos,t);
		else update(id<<1|1,mid+1,r,pos,t);
		val[id] = val[id<<1] + val[id<<1|1];
	}
}seg;

const bool cmp(DATA a,DATA b) { return a.t < b.t; }
double ans;

inline void solve()
{
	cnt = 0; tot = 0; ans = 0;
	rep(i,1,n)
	{
		double lx,rx,ly,ry;
		scanf("%lf%lf%lf%lf",&lx,&ly,&rx,&ry);	
		a[++ cnt].l = ly;a[cnt].r = ry;a[cnt].t = lx;a[cnt].val = 1;
		a[++ cnt].l = ly;a[cnt].r = ry;a[cnt].t = rx;a[cnt].val = -1;
		b[++ tot] = ly;b[++ tot] = ry;
	}
	sort(a + 1,a + 1 + cnt,cmp);
	sort(b + 1,b + 1 + tot);
	rep(i,1,tot) mp[b[i]] = i,z[i] = b[i] - b[i-1];
	rep(i,1,cnt)
	{
		ans += (a[i].t - a[i-1].t) * seg.val[1];
		rep(j,mp[a[i].l] + 1,mp[a[i].r])
			seg.update(1,1,tot,j,a[i].val);
	}
}

int main()
{
	int cas = 0;
	while(scanf("%d",&n),n!=0)
	{
		solve();
		printf("Test case #%d\n",++cas);
		printf("Total explored area: %.2f\n\n",ans);
	}
	return 0;
}
