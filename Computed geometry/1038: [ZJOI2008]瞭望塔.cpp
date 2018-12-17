#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
const int N = 404;
#define eps 1e-9
int n,st,en; 
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y) { x = _x;y = _y; }
}p[N],a[N];
Point operator - (Point a,Point b) { return Point(a.x - b.x,a.y - b.y); }
 
struct Line 
{
    double k;
    Point s,t;
    Line(){}
    Line(Point a,Point b)
    {
        s = a,t = b - a;
        k = (b.y - a.y)/(b.x - a.x);
    }
}l[N],q[N];
 
inline double cross(Point a,Point b) { return a.x * b.y - a.y * b.x; }
inline bool OnRight(Line a,Point b) { return cross(a.t,b - a.s) < eps;}
inline bool cmp(Line a,Line b) { return a.k < b.k; }
inline Point Get(Line a,Line b)
{
    double x = (a.k * a.s.x - a.s.y + b.s.y - b.k * b.s.x)/(a.k - b.k);
    double y = a.k * x + a.s.y - a.k * a.s.x; 
    return Point(x,y);
}
 
int main()
{
    read(n);
    rep(i,1,n) read(p[i].x);
    rep(i,1,n) read(p[i].y);
    rep(i,1,n-1) l[i] = Line(p[i],p[i+1]);
    sort(l + 1,l + n,cmp);
    double ans = 1e15;
    st = 1;
    rep(i,1,n-1)
    {
        while(st < en && OnRight(l[i],a[en-1])) -- en;
        while(st < en && OnRight(l[i],a[st])) ++ st;
        q[++ en] = l[i];
        if(st < en && fabs(cross(q[en].t,q[en-1].t)) < eps)
        {
            -- en;  
            if(!OnRight(q[en],l[i].s)) q[en] = l[en];
        }
        if(st < en) a[en - 1] = Get(q[en],q[en-1]);
    }
    rep(i,1,n)
    {
        double now = 0;
        rep(j,st,en)
            chkmax(now,q[j].s.y + q[j].k*(p[i].x - q[j].s.x) - p[i].y);
        chkmin(ans,now);
    }
    rep(i,st,en-1)
        rep(j,1,n)
            if(p[j+1].x > a[i].x)
            {
                l[0] = Line(p[j],p[j+1]);
                chkmin(ans,a[i].y - (l[0].s.y + l[0].k*(a[i].x - l[0].s.x)));
                break;
            }
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}
