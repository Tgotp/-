#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1: 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y, 1: 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 5e4 + 50;
int n;
#define eps 1e-9
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y) { x = _x,y = _y; }
	inline Point operator - (const Point b) const { return Point(x - b.x,y - b.y); }
	inline Point operator + (const Point b) const { return Point(x + b.x,y + b.y); }
	inline double operator * (const Point b) const { return x * b.y - y * b.x;}
	inline bool operator < (const Point b) const { return x < b.x || x == b.x && y > b.y; }

}p[N],a[N << 1],res[5]; 
int s[N],top;
double ans = 1e9;

const bool cmp(Point a,Point b) { return a.y < b.y || (fabs(a.y-b.y)<eps&&a.x < b.x);};
inline void print(Point a) { printf("%.5lf %.5lf\n",fabs(a.x)>eps?a.x:0,fabs(a.y)>eps?a.y:0); }
inline double rlen(Point a) { return sqrt(a.x * a.x + a.y * a.y);}

int main()
{
	read(n);
	rep(i,1,n) scanf("%lf%lf",&p[i].x,&p[i].y);

	sort(p + 1,p + 1 + n);
	rep(i,1,n)
	{
		while(top > 1 && (p[i] - p[s[top-1]]) * (p[s[top]] - p[s[top-1]]) >= 0) -- top;
		s[++top] = i;
	}
	int zz = top;
	repd(i,n-1,1)
	{
		while(top > zz && (p[i] - p[s[top-1]]) * (p[s[top]] - p[s[top-1]]) >= 0) -- top;
		s[++top] = i;
	}

	-- top; n = top;
	rep(i,1,n) a[i] = p[s[i]];
	rep(i,1,n) a[i+n] = a[i];

	//rep(i,1,n) print(a[i]); puts("");

	int t = 2,m = n << 1,l=0,r=0;
	rep(i,1,n)
	{
		while(t < m && fabs((a[t+1]-a[i])*(a[i+1]-a[i])) >= fabs((a[t]-a[i])*(a[i+1]-a[i]))) ++ t;
		r = max(r,t);
		l = max(l,i+1);
		Point q;
		if(fabs(a[i].x - a[i+1].x) < eps)
			q.x = a[i].x,q.y = a[t].y;
		else if(fabs(a[i].y-a[i+1].y) < eps)
			q.x = a[t].x,q.y = a[i].y;
		else{
		double k1 = (a[i+1].y - a[i].y) / (a[i+1].x - a[i].x + eps);
		double b1 = a[i].y - a[i].x * k1;
		double k2 = -1/k1;
		double b2 = a[t].y - a[t].x * k2;
		q.x = (b2 - b1) / (k1 - k2);
		q.y = q.x * k1 + b1;}
		while(l < t && fabs((a[l+1] - q)*(a[t]-q)) >= fabs((a[l] - q) * (a[t] - q))) ++ l;
		while(r < m && fabs((a[r+1] - q)*(a[t]-q)) >= fabs((a[r] - q) * (a[t] - q))) ++ r;

		//print(a[l]);print(a[r]);print(a[t]); print(q); puts("");

		if(chkmin(ans,fabs((a[l] - q) * (a[t] - q)) + fabs((a[r] - q) * (a[t] - q))))
		{
			Point e;

			if(fabs(a[t].y - q.y) < eps)
				e.x = a[l].x,e.y = q.y;
			else if(fabs(a[t].x - q.x) < eps)
				e.x = q.x,e.y = a[l].y;
			else
			{
				double k1 = (a[t].y - q.y) / (a[t].x - q.x);
				double b1 = q.y - q.x * k1;
				double k2 = -1/k1;
				double b2 = a[l].y - a[l].x * k2;
				e.x = (b2-b1)/(k1 - k2);
				e.y = k1 * e.x + b1;
			}
			e = a[l] - e;
			res[1] = q + e; res[2] = a[t] + e;
			if(fabs(a[t].y - q.y) < eps)
				e.x = a[r].x,e.y = q.y;
			else if(fabs(a[t].x - q.x) < eps)
				e.x = q.x,e.y = a[r].y;
			else
			{
				double k1 = (a[t].y - q.y) / (a[t].x - q.x);
				double b1 = q.y - q.x * k1;
				double k2 = -1/k1;
				double b2 = a[r].y - a[r].x * k2;
				e.x = (b2-b1)/(k1 - k2);
				e.y = k1 * e.x + b1;
			}
			e = a[r] - e;
			res[3] = q + e;res[4] = a[t] + e;
		}
	}
	cout << fixed << setprecision(5) << ans << endl;
	sort(res + 1,res + 5,cmp);
	if(res[2].x < res[1].x) swap(res[2],res[3]);
	print(res[1]); print(res[2]); print(res[4]); print(res[3]);
	return 0;
}
