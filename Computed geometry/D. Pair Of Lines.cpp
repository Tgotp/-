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

const int N = 1e5 + 50;
struct Point
{
	ll x,y;
	Point(){}
	Point(ll _x,ll _y) {x = _x,y = _y;}
	inline Point operator -(const Point a) const {return Point(x - a.x,y - a.y);}
	inline ll operator * (const Point a) const { return x * a.y - y * a.x;};
}p[N],s1[3],s2[3];

int n,k;

inline bool check(int x,int y)
{
	rep(i,1,n) if(i != x && i != y)
	{
		if((p[i] - s1[2]) * (s1[1] - s1[2]) == 0) continue;
		if(k < 2) { s2[++k] = p[i]; continue;} 
		if((p[i] - s2[2]) * (s2[1] - s2[2]) != 0) return false;
	}
	return true;
}

int main()
{
	read(n); 
	rep(i,1,n) read(p[i].x),read(p[i].y);
	if(n <= 2) return puts("YES"),0; 
	int m = min(n,3);
	rep(i,1,m) rep(j,i+1,m)
	{
		s1[1] = p[i]; s1[2] = p[j]; k = 0;
		if(check(i,j)) return puts("YES"),0;
	}
	puts("NO");
	return 0;
}
