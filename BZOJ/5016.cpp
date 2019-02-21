#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 5e4 + 50;
int a[N],n,m,cnt;

struct DATA { int l,r,id; bool op; } q[N << 2];

int bel[N];

inline bool cmp(DATA a,DATA b)
{
	return bel[a.l] < bel[b.l] || bel[a.l] == bel[b.l] && (bel[a.l]&1?bel[a.r] < bel[b.r] : bel[a.r] > bel[b.r]);
}

ll ans[N];
ll now;int num[2][N];
inline void add(int x,int e,int w)
{
	now += num[e^1][x] * w;	
	num[e][x] += w;
}

int main()
{
	read(n);
	rep(i,1,n) read(a[i]);
	read(m);
	rep(i,1,m)
	{
		int l1,l2,r1,r2;
		read(l1); read(r1); read(l2); read(r2);
		-- l1; -- l2;
		q[++cnt].op = 1; q[cnt].l = r1; q[cnt].r = r2; q[cnt].id = i;
		if(q[cnt].l > q[cnt].r) swap(q[cnt].l,q[cnt].r);
		if(q[cnt].l == 0) -- cnt;
		q[++cnt].op = 1; q[cnt].l = l1; q[cnt].r = l2; q[cnt].id = i;
		if(q[cnt].l > q[cnt].r) swap(q[cnt].l,q[cnt].r);
		if(q[cnt].l == 0) -- cnt;
		q[++cnt].op = 0; q[cnt].l = l1; q[cnt].r = r2; q[cnt].id = i;
		if(q[cnt].l > q[cnt].r) swap(q[cnt].l,q[cnt].r);
		if(q[cnt].l == 0) -- cnt;
		q[++cnt].op = 0; q[cnt].l = l2; q[cnt].r = r1; q[cnt].id = i;
		if(q[cnt].l > q[cnt].r) swap(q[cnt].l,q[cnt].r);
		if(q[cnt].l == 0) -- cnt;
	}

	int d = sqrt(n);
	rep(i,1,n) bel[i] = i / d;
	sort(q + 1,q + 1 + cnt,cmp);

	int l = 0,r = 0;
	rep(i,1,cnt)
	{
		while(l < q[i].l) add(a[++l],1,1);
		while(r < q[i].r) add(a[++r],0,1);
		while(l > q[i].l) add(a[l--],1,-1);
		while(r > q[i].r) add(a[r--],0,-1);

		ans[q[i].id] += (q[i].op ? 1 : -1) * now;
	}

	rep(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
