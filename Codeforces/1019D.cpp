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

const int N = 2e3 + 50;
#define eps 1e-10
struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y){ x = _x,y = _y;}
	inline bool operator < (Point a)const { return x < a.x; }
	inline Point operator - (Point a) const{ return Point(x - a.x,y - a.y); }
}p[N];
struct Line { int x,y;double k; }L[N * N];
int n,cnt; ll s;
const bool cmp(Line a,Line b) { return a.k < b.k; }

inline ll cross(Point x,Point y) { return 1ll * x.x * y.y - 1ll * x.y * y.x; }
inline ll dot(Point x,Point y) { return 1ll * x.x * y.x + 1ll * x.y * y.y; }

int rk[N],pos[N];

inline bool check(Point a,Point b,int l,int r,bool e)
{
	int mid;
	while(l <= r)
	{
		ll t = abs(cross(a-b,p[pos[mid=l+r>>1]]-b));
		if(t == s)
		{
			puts("Yes");
			printf("%d %d\n",a.x,a.y);
			printf("%d %d\n",b.x,b.y);
			printf("%d %d\n",p[pos[mid]].x,p[pos[mid]].y);
			return true;
		}
		if((t < s && e) || (t > s && !e)) l = mid + 1;
		else r = mid - 1;
	}
	return false;
}

int main()
{
	read(n); read(s); s <<= 1;
	rep(i,1,n) read(p[i].x), read(p[i].y);
	sort(p + 1,p + 1 + n);
	rep(i,1,n) rep(j,i + 1,n)
	{
		L[ ++ cnt].x = i;
		L[ cnt].y = j;
		L[ cnt].k = (p[j].y - p[i].y)/(p[j].x - p[i].x + eps);
	}
	sort(L + 1,L + 1 + cnt,cmp);
	rep(i,1,n) rk[i] = pos[i] = i;
	rep(i,1,cnt)
	{
		int x = L[i].x,y = L[i].y;
		if(rk[x] > rk[y]) swap(x,y);
		if(rk[x] > 1)if(check(p[x],p[y],1,rk[x]-1,0)) return 0;
		if(rk[y] < n)if(check(p[x],p[y],rk[y]+1,n,1)) return 0;
		swap(rk[x],rk[y]);
		swap(pos[rk[x]],pos[rk[y]]);
	}
	puts("No");
	return 0;
}
