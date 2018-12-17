#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c =='-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 50;
int n;
struct Point
{	
	int a,b;
	Point(){}
	Point(int _a,int _b) { a = _a,b = _b; }
	inline Point operator - (Point x) { return Point(a - x.a,b - x.b); }
	inline ll operator * (Point x) { return 1ll * a * x.b - 1ll * b * x.a; }
}a[N];
inline bool cmp(Point a,Point b) { return a.a < b.a || a.a == b.a && a.b > b.b; }

int s[N],top;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	read(n);
	rep(i,1,n) read(a[i].a),read(a[i].b);
	sort(a + 1,a + 1 + n,cmp);

	rep(i,1,n) if(a[i].a != a[i-1].a)
	{
		while((top && a[i].b >= a[s[top]].b)|| (top > 1 && (a[i] - a[s[top-1]])*(a[s[top]] - a[s[top-1]]) <= 0)) -- top;
		s[++top] = i;
	}
	double ans = 1e18;
	rep(i,1,top)
	{
		double l,r;
		#define eps 1e-9
		if(i == 1) r = 0; else r = (a[s[i]].b - a[s[i-1]].b) / (double)(a[s[i]].a - a[s[i-1]].a);
		if(i == top) l = -1e18; else l = (a[s[i]].b - a[s[i+1]].b) / (double)(a[s[i]].a - a[s[i+1]].a);
		double k = -sqrt(a[s[i]].b/(a[s[i]].a+eps));
		if(k < l) k = l;
		if(k > r) k = r;
		ans = min(ans,a[s[i]].a + a[s[i]].b - (a[s[i]].a * k + a[s[i]].b * (1/k))) ;
	}
	
	cout << fixed << setprecision(4) << ans << endl;

	return 0;
}
