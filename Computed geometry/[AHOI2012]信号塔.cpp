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

const int N = 1e6 + 50;
#define eps 1e-18
double r;
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y){ x = _x,y = _y;}
	inline double operator * (const Point a) const { return x * a.y - y * a.x; }
	inline Point operator - (const Point a) const { return Point(x - a.x,y - a.y); }
	inline Point operator + (const Point a) const { return Point(x + a.x,y + a.y); }
}p[N],a; int n;

inline double len(Point a) { return sqrt(a.x * a.x + a.y * a.y); }

inline Point get(Point a,Point b,Point c)
{
	if((b-a)*(c-a)==0)
		return Point((min(min(a.x,b.x),c.x)+max(max(a.x,b.x),c.x))/2,
			(min(min(a.y,b.y),c.y)+max(max(a.y,b.y),c.y))/2);
	
	Point d = a + b;d.x/=2;d.y/=2;	
	Point e = a + c;e.x/=2;e.y/=2;	

	double k1 = -1/((b.y-a.y) / (b.x-a.x+eps));
	double k2 = -1/((c.y-a.y) / (c.x-a.x+eps));
	double b1 = d.y - k1 * d.x;
	double b2 = e.y - k2 * e.x;
	double x = (b2 - b1) / (k1-k2);

	return Point(x,k1*x+b1);
}

int main()
{
	read(n);
	rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);
	random_shuffle(p + 1,p + 1 + n);
	
	r = 0; a = p[1];
	rep(i,2,n) if(len(p[i] - a) - r > eps)
	{
		a = p[i]; r = 0;
		rep(j,1,i-1) if(len(p[j] - a) - r > eps)
		{
			a = (p[j] + p[i]); a.x /= 2,a.y /= 2;
			r = len(a - p[j]);
			rep(k,1,j-1) if(len(p[k] - a) - r > eps)
			{
				a = get(p[i],p[j],p[k]);
				r = len(a - p[k]);
			}
		}
	}
	
	cout << fixed << setprecision(2) << a.x << ' ' << a.y << ' ' << r << endl;

	return 0;
}
