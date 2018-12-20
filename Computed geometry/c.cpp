#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i )
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

#define eps 1e-12
#define ld double
struct Point
{
	ld x,y;
	Point(){}
	Point(ld _x,ld _y) { x = _x;y = _y;}
	inline Point operator -(const Point a) const { return Point(x - a.x,y - a.y); }
}p[5];

inline ld cross(Point a,Point b) { return a.x * b.y - a.y * b.x; }
inline ld dot(Point a,Point b) { return a.x * b.x + a.y * b.y; }
inline ld len(Point a) { return a.x * a.x + a.y * a.y; }
inline ld ldgcd(ld a,ld b)
{
	#define epi 1e-2

	a = fabs(a); b = fabs(b);
	if(a < epi) return b;
	if(b < epi) return a;
	return ldgcd(b,a-b);
}

int main()
{
	rep(i,1,3) scanf("%lf%lf",&p[i].x,&p[i].y);
	if(len(p[1]-p[2]) > len(p[1]-p[3])) swap(p[2],p[3]);
	ld k1 = -1/((p[1].y-p[2].y)/(eps+p[1].x - p[2].x));
	ld k2 = -1/((p[1].y-p[3].y)/(eps+p[1].x - p[3].x));
	ld b1 = ((p[1].y+p[2].y)-k1*(p[1].x+p[2].x))/2;
	ld b2 = ((p[1].y+p[3].y)-k2*(p[1].x+p[3].x))/2;
	p[4].x = (b2-b1)/(k1-k2);
	p[4].y = k1 * p[4].x + b1;
	ld r2 = (p[4].x-p[1].x)*(p[4].x-p[1].x)+(p[4].y-p[1].y)*(p[4].y-p[1].y);
	ld t1 = acos(dot(p[1]-p[4],p[2]-p[4])/r2);
	ld t2 = acos(dot(p[2]-p[4],p[3]-p[4])/r2); 
	ld t3 = 2 * acos(-1) - t1 - t2;
	ld t4 = ldgcd(fabs(t1),ldgcd(fabs(t2),fabs(t3)));
	ld ans = 2 * (acos(-1)/t4)*r2*sin(t4/2)*cos(t4/2);
	cout << fixed << setprecision(10) << ans << endl;
	/*
	cout << fixed << setprecision(10) << t1 << endl;
	cout << fixed << setprecision(10) << t2 << endl;
	cout << fixed << setprecision(10) << t3 << endl;
	cout << fixed << setprecision(10) << t4 << endl;
	*/
	return 0;
}
