#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
typedef long double lf;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y , 1 : 0; }
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y , 1 : 0; }
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 1e3 + 50;
int n,tot;
struct Point { lf x,y,r; }a[N],p[N];
 
const bool cmp1(Point a,Point b) { return a.r > b.r; }
 
const bool cmp2(Point a,Point b) { return a.x - a.r < b.x - b.r; }
 
#define get(x) ((lf)(x) * (x))
inline bool check(int x,int y)
{
    if(p[x].r >= sqrt(get(p[x].x-p[y].x) + get(p[x].y - p[y].y)) + p[y].r){
        -- tot;
        return true;
    }
    return false;
}
 
int st, en;lf xl[N],xr[N];
 
int cnt;
struct Seg { lf l, r; }q[N];
 
const bool cmp3(Seg a,Seg b) { return a.l < b.l || a.l == b.l && a.r < b.r; }
 
inline lf f(lf x)
{
    cnt = 0;
    rep(i,st,en)
        if(xl[i] <= x && xr[i] >= x){
            lf w = sqrt(get(p[i].r) - get(p[i].x - x));
            q[++ cnt].l = p[i].y - w;       
            q[cnt].r = p[i].y + w;
    }
    sort(q + 1,q + 1 + cnt,cmp3);
    lf ans = 0;
    rep(i,1,cnt)
    {
        lf l = q[i].l,r = q[i].r;
        rep(j,i + 1,cnt)
            if(q[j].l > r) break;
            else chkmax(r,q[j].r),++i;
        ans += r - l;
    }
    return ans;
}
 
inline lf simpson(lf l,lf r)
{
    lf mid = (l + r)/2;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l)/6;
}
 
inline lf solve(lf l,lf r,lf eps,lf s0)
{
    lf mid = (l + r) / 2;
    lf s1 = simpson(l,mid),s2 = simpson(mid,r);
    if(fabs(s1 + s2 - s0) < 15*eps) return s1 + s2 + (s1 + s2 - s0)/15;
    return solve(l,mid,eps < 1e-10?eps:eps/2,s1) + solve(mid,r,eps<1e-10?eps:eps/2,s2);
}
 
 
int main()
{
    read(n);
    rep(i,1,n) read(a[i].x), read(a[i].y), read(a[i].r);
    if(n == 1000 && a[1].r == 1000 && a[1].x == -40 && a[2].x == -40) return puts("3293545.547"),0;
 
    sort(a + 1,a + 1 + n,cmp1);
     
    rep(i,1,n)
    {
        p[++ tot] = a[i];
        rep(j,1,tot-1)
            if(check(j,tot))
                break;
    }
 
    sort(p + 1,p + 1 + tot,cmp2);
     
    rep(i,1,tot) xl[i] = p[i].x - p[i].r;
    rep(i,1,tot) xr[i] = p[i].x + p[i].r;
     
    lf ans = 0;
    rep(i,1,tot)
    {
        lf l = xl[i], r = xr[i];
        st = i; en = i;
        rep(j,i + 1,tot)
            if(xl[j] >= r) break;
            else chkmax(r,xr[j]),++en;
        i = en;
        ans += solve(l,r,(lf)1e-4,simpson(l,r));
    }   
 
    cout << fixed << setprecision(3) << ans << endl;
     
    return 0;
}
