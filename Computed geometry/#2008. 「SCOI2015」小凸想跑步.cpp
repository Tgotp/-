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

const double eps = 1e-12;
const int N = 1e5 + 50;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y) { x = _x,y = _y; }
	inline Point operator - (Point a) { return Point(x - a.x,y - a.y); } 
	inline double operator * (Point a) { return x * a.y - y * a.x;}
}p[N],q[N];
struct Line
{
	Point s,t;
	double k,b,ang;	
	bool e;

	Line(){}
	Line(Point _s,Point _t)
	{
		s = _s;t = _t; e = 0;
		if(fabs(s.x - t.x) > eps) k = (s.y - t.y) / (s.x - t.x);
		else e = 1,k = 1e18;
		ang = atan2(t.y - s.y ,t.x - s.x);
		b = s.y - s.x * k;
	}
}L[N];
const bool cmp(Line a,Line b) { return a.ang < b.ang; }
int n,cnt,s[N],l,r;
double sum,ans;

void print(Point a) { printf("%.3lf %.3lf\n",a.x,a.y); }
Point get(Line a,Line b)
{
	if(a.e || b.e)
	{
		if(a.e) swap(a,b);
		return Point(b.s.x,b.s.x * a.k + a.b);
	}
	double x = (b.b - a.b)/(a.k-b.k+eps);	
	return Point(x,x*a.k+a.b);
}

int main()
{
	read(n);
	rep(i,1,n) read(p[i].x),read(p[i].y);
	rep(i,3,n) sum += (p[i] - p[i-1]) * (p[1] - p[i-1]); 

	L[cnt = 1] = Line(p[1],p[2]); p[n + 1] = p[1];
	rep(i,2,n)
	{
		double t = -(p[2].x - p[1].x + p[i].x - p[i+1].x);
		double k = (p[i+1].y - p[i].y + p[1].y - p[2].y);
		double b = (p[1].x*p[2].y + p[i+1].x*p[i].y-p[2].x*p[1].y-p[i].x*p[i+1].y);
		if(fabs(t) < eps)
		{
			if(fabs(k) < eps) continue;
			Point x = Point(-b/k,0);
			Point y = Point(-b/k,1);
			if(k < eps) swap(x,y);
			L[i] = Line(x,y);
			continue;
		}
		Point x = Point(1,(k + b)/t);
		Point y = Point(2,(k*2 + b)/t);
		if(t < eps) L[i] = Line(y,x);
		else L[i] = Line(x,y);
	}

	sort(L + 1,L + 1 + n,cmp);
	/*
	rep(i,1,n)
	{
		printf("%.3lf %.3lf\n",L[i].k,L[i].b);
		printf("%.3lf %.3lf\n",L[i].s.x,L[i].s.y);
		printf("%.3lf %.3lf\n",L[i].t.x,L[i].t.y);

		puts("");
	}
	*/
	l = 1;
	rep(i,1,n)
	{
		while(r - l > 0 && (L[i].t - L[i].s) * (q[r] - L[i].s) <= 0) -- r;
		while(r - l > 0 && (L[i].t - L[i].s) * (q[l+1] - L[i].s) <= 0) ++ l;
		s[++ r] = i; if(r - l > 0) q[r] = get(L[i],L[s[r-1]]);
	}
	while(r-l > 2 && (L[s[l]].t - L[s[l]].s) * (q[r] - L[s[l]].s) <= 0) -- r;
	q[l] = get(L[s[l]],L[s[r]]);
	rep(i,l+2,r) ans += (q[i] - q[i-1]) * (q[l] - q[i-1]); 

	cout << fixed << setprecision(4) << ans / sum << endl;
	
	return 0;
}
