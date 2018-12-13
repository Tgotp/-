#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 1e3 + 50;
int n,cnt;
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y) { x = _x,y = _y; }

	inline bool operator < (const Point a) const { return x < a.x; }
	inline Point operator - (const Point a) const { return Point(x-a.x,y-a.y); }
}p[N];
struct Line { int x,y; double k; }L[N * N];
ll ans = 4e18;

const bool cmp(Line a,Line b) { return a.k < b.k; }
inline ll cross(Point a,Point b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

int pos[N],rk[N];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	read(n);
	rep(i,1,n) read(p[i].x), read(p[i].y);
	sort(p + 1,p + 1 + n);
	rep(i,1,n) rep(j,i + 1,n)
	{
		L[ ++ cnt].x = i;
		L[ cnt].y = j;	
		#define eps 1e-10
		L[ cnt].k = (p[j].y - p[i].y)/(double)(p[j].x - p[i].x + eps);
	}
	sort(L + 1,L + 1 + cnt,cmp);
	rep(i,1,n) pos[i] = rk[i] = i;
	rep(i,1,cnt)
	{
		int x = L[i].x,y = L[i].y;	
		if(rk[x] > rk[y]) swap(x,y);
		if(rk[x] > 1) chkmin(ans,abs(cross(p[y]-p[x],p[pos[rk[x]-1]]-p[x])));
		if(rk[y] < n) chkmin(ans,abs(cross(p[y]-p[x],p[pos[rk[y]+1]]-p[x])));
		swap(rk[x],rk[y]);
		swap(pos[rk[x]],pos[rk[y]]);
	}
	printf("%.2lf\n",ans * 0.5);
	return 0;
}
