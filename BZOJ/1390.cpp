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

inline void init(string name)
{
	string in = name + ".in",out = name + ".out";
	freopen(in.c_str(),"r",stdin);
	freopen(out.c_str(),"w",stdout);
}

const int N = 205;
struct Point 
{
	int x,y;
	Point(){}
	Point(int _x,int _y) { x = _x;y = _y; }
	
	inline int operator * (Point b) { return x * b.y - y * b.x; }
	inline Point operator - (Point b) { return Point(x - b.x,y - b.y); }
}a[N],b[N];

inline bool cmp(Point a,Point b) { return a.x < b.x || a.x == b.x && a.y < b.y; }

int s[N],top,n,m;

inline bool check(int x)
{
	rep(i,2,top) if((b[x] - a[s[i-1]]) * (a[s[i]] - a[s[i-1]]) < 0) return false;
	return true;
}

int d[N][N];

int main()
{
	init("C");
	read(n); read(m);
	rep(i,1,n) read(a[i].x),read(a[i].y);
	rep(i,1,m) read(b[i].x),read(b[i].y);
	sort(a + 1,a + 1 + n,cmp);
	rep(i,1,n)
	{
		while(top > 1 && (a[i] - a[s[top]]) * (a[s[top]] - a[s[top-1]]) <= 0) -- top;
		s[++ top] = i ;
	}
	int cnt = top;
	repd(i,n-1,1)
	{
		while(top > cnt && (a[i] - a[s[top]]) * (a[s[top]] - a[s[top-1]]) <= 0) -- top;
		s[++ top] = i ;
	}

	int ans = 0; cnt = 0;
	rep(i,1,m)
	{
		if(check(i)) b[++cnt] = b[i];
		else ans += 111;
	}

	m = cnt;
	if(m)
	{
		memset(d,0x3f,sizeof d);
		rep(i,1,n) rep(j,1,n) if(i != j)
		{
			bool ok = 1;
			rep(k,1,m)
				if((b[k] - a[i]) * (a[j] - a[i]) < 0)
				{
					ok = 0;
					break;
				}
			if(!ok) continue;
			d[i][j] = 1;
		}
		rep(k,1,n) rep(i,1,n) rep(j,1,n)
			d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
		int res = INT_MAX;
		rep(i,1,n) res = min(res,d[i][i]);
		ans += res * 20;
	}
	cout << ans << endl;
	return 0;
}
