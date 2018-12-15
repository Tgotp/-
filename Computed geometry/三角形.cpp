#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
inline char gc()
{
	static char *S,*T,buf[1 << 16];
	if(S == T) { T = (S = buf) + fread(buf,1,1<<16,stdin); if(S == T)return EOF;}
	return * S ++;
}
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0 ; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0 ;
	do { c = gc(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = gc(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e4 + 50;
ll ans;
int n,cnt,tot,b[N],z[N];
struct DATA { int t,pos,val; }a[N];
const bool cmp(DATA a,DATA b) { return a.t < b.t; }

int c[N];

inline ll find(int x)
{
	int t = 0;ll ans = 0;
	#define q max(0,t - x)
	rep(i,1,tot)
	{
		t = max(t,c[i]);
		if(z[i] >= t)
		{
			ans += t * t;
			ans -= q * q;
			t = 0;
		}
		else
		{
			ans += (t - z[i] + t) * z[i];
			ans -= (max(q - z[i],0) + q) * min(z[i],q);
			t -= z[i];
		}
		c[i] = max(0,c[i] - x);
	}

	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	read(n);
	rep(i,1,n)
	{
		int x,y,m;
		read(x); read(y); read(m);
		a[++ cnt].pos = y; a[cnt].t = x; a[cnt].val = m;
		b[++ tot] = y;
	}
	sort(a + 1,a + 1 + cnt,cmp);
	sort(b + 1,b + 1 + tot);
	tot = unique(b + 1,b + 1 + tot) - b - 1;
	map<int,int>mp;
	b[tot + 1] = 1e9;
	rep(i,1,tot) mp[b[i]] = i,z[i] = b[i + 1] - b[i];
	a[0].t = a[1].t;
	rep(i,1,cnt)
	{
		ans += find(a[i].t-a[i-1].t);
		chkmax(c[mp[a[i].pos]],a[i].val);
	}
	ans += find(1e9 - a[cnt].t);
	cout << fixed << setprecision(1) << ans * 0.5 << endl;
	printf("%.3lf\n",clock()/(double)CLOCKS_PER_SEC);
	return 0;
}
