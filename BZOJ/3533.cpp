#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y){ return x < y ? x = y,1 : 0; }
template<typename T>inline bool chkmin(T&x,T y){ return x > y ? x = y,1 : 0; }
ll lstans;bool flag;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
	if(flag) x ^= (lstans&0x7fffffff);
}

int m;
char s[5];

const int N = 4e5 + 50,inf = 1e8;
struct Segment_tree
{
	vector<pair<int,int> > v[N << 2];
	vector<pair<int,int> > up[N << 2],dn[N << 2];
	int n1[N << 2],n2[N << 2],mi[N << 2],mx[N << 2];
	bool op[N << 2];
	#define mk(x,y) make_pair(x,y)

	inline ll cross(pair<int,int> a,pair<int,int> b) { return 1ll * a.first * b.second - 1ll * a.second * b.first; }
	inline pair<int,int> dec(pair<int,int> a,pair<int,int> b) { return mk(a.first - b.first,a.second - b.second); }

	void pre(int id,int l,int r)
	{
		mx[id] = -inf;mi[id] = inf;
		if(l == r) return;
		int mid = l + r >> 1;
		pre(id<<1,l,mid); pre(id<<1|1,mid+1,r);
	}
	
	inline void build(int id)
	{
		sort(v[id].begin(),v[id].end());
		int sz = v[id].size(); -- sz;
		rep(i,0,sz+1) up[id].push_back(mk(0,0));
		rep(i,0,sz+1) dn[id].push_back(mk(0,0));
		rep(i,0,sz)
		{
			while(n1[id] > 1 && cross(dec(v[id][i],up[id][n1[id]]),dec(up[id][n1[id]],up[id][n1[id]-1])) <= 0) -- n1[id];
			up[id][++n1[id]] = v[id][i];	
		}
		rep(i,0,sz)
		{
			while(n2[id] > 1 && cross(dec(v[id][i],dn[id][n2[id]]),dec(dn[id][n2[id]],dn[id][n2[id]-1])) >= 0) -- n2[id];
			dn[id][++n2[id]] = v[id][i];	
		}
	}

	void insert(int id,int l,int r,int pos,int a,int b)
	{
		v[id].push_back(mk(a,b));
		mx[id] = max(mx[id],a);
		mi[id] = min(mi[id],a);
		if(l == r) return;
		int mid = l + r >> 1;
		if(pos <= mid) insert(id<<1,l,mid,pos,a,b);
		else insert(id<<1|1,mid+1,r,pos,a,b);
	}

	inline ll query(int id,int x,int y)
	{
		if(!op[id]) build(id),op[id] = 1;
		int l,r,t1,t2;
		ll ans = - 1e18;
		if(y < 0)
		{
			l = 1; r = n2[id];
			while(l <= r)	
			{
				t1 = (r - l) / 3;
				t2 = r - t1; t1 = l + t1;
				ll a = 1ll * dn[id][t1].first * x + 1ll * dn[id][t1].second * y;
				ll b = 1ll * dn[id][t2].first * x + 1ll * dn[id][t2].second * y;
				ans = max(ans,max(a,b));
				if(a > b) r = t2 - 1;
				else l = t1 + 1; 
			}
		}
		else
		{	
			l = 1; r = n1[id];
			while(l <= r)	
			{
				t1 = (r - l) / 3;
				t2 = r - t1; t1 = l + t1;
				ll a = 1ll * up[id][t1].first * x + 1ll * up[id][t1].second * y;
				ll b = 1ll * up[id][t2].first * x + 1ll * up[id][t2].second * y;
				ans = max(ans,max(a,b));
				if(a > b) r = t2 - 1;
				else l = t1 + 1;
			}
		}
		return ans;
	}
	
	ll find(int id,int l,int r,int L,int R,int x,int y)
	{
		if(l == L && r == R) return y != 0? query(id,x,y) : x > 0 ? 1ll * mx[id] * x : 1ll * mi[x] * x;
		int mid = l + r >> 1;
		if(R <= mid) return find(id<<1,l,mid,L,R,x,y);
		else if(L > mid) return find(id<<1|1,mid+1,r,L,R,x,y);
		else return max(find(id<<1,l,mid,L,mid,x,y),find(id<<1|1,mid+1,r,mid+1,R,x,y));
	}
}seg;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4.in","r",stdin);
	freopen("1.out","w",stdout);
#endif
	read(m); scanf("%s",s + 1);
	if(s[1] != 'E') flag = 1;
	seg.pre(1,1,m);
	int sz = 0;
	rep(i,1,m)
	{
		int x,y,l,r;
		scanf("%s",s + 1);
		read(x); read(y);
		if(s[1] == 'A')
			seg.insert(1,1,m,++sz,x,y);
		else 
		{
			read(l),read(r);
			//printf("%d %d %d %d\n",x,y,l,r);
			printf("%lld\n",lstans = seg.find(1,1,m,l,r,x,y));
		}
	}
#ifndef ONLINE_JUDGE
		printf("%.3lf\n",clock()/(double)CLOCKS_PER_SEC);
#endif
	return 0;
}
