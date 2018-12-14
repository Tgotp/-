#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x; i <= y; ++ i)
#define repd(i,x,y) for(register int i = x; i >= y; -- i)
using namespace std;
typedef long long ll;
typedef long double lf;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0;   }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0;   }
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 5e2 + 50;
int n,tot; lf a,pos[N];
struct Point { lf x,r; }p[N];
struct St { lf l1,l2,l,r,Sin,Cos,Tan; }t[N];
 
#define e 1e-9
#define get(x) ((x) * (x))
inline St find(int x,int y)
{
    St k;
    k.Tan = fabs(p[x].r - p[y].r)/sqrt(get(p[y].x-p[x].x) - get(p[x].r - p[y].r));
    lf Sin = (p[x].r - p[y].r)/(p[y].x - p[x].x);
    lf l = p[x].x + p[x].r*Sin,r = p[y].x + p[y].r * Sin;
    lf Cos = sqrt(get(p[y].x-p[x].x) - get(p[x].r - p[y].r))/(p[y].x - p[x].x);
    k.l1 = p[x].r * Cos,k.l2 = p[y].r * Cos;
    k.l = l;k.r = r;k.Sin = Sin;k.Cos = Cos;
    return k;
}
 
inline lf f(lf u)
{
    lf ans = 0;
    rep(i,1,n-1)
        if(t[i].l < u  && t[i].r > u)
        {
            if(t[i].l1 > t[i].l2)
                chkmax(ans,t[i].l1 - (u - t[i].l) * t[i].Tan);
            else chkmax(ans,t[i].l2 - (t[i].r - u) * t[i].Tan);
        }
    rep(i,1,n)
        if(p[i].x - p[i].r < u && p[i].x + p[i].r > u)
            chkmax(ans,sqrt(get(p[i].r) - get(p[i].x - u)));
    return ans;
}
 
inline lf simpson(lf l,lf r)
{
    lf mid = (l + r) / 2;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l)/ 6;
}
 
inline lf solve(lf l,lf r,lf eps,lf s0)
{
    lf mid = (l + r) / 2;
    lf s1 = simpson(l,mid),s2 = simpson(mid,r);
    if(fabs(s1 + s2 - s0) <= eps * 15) return s1 + s2 + (s1 + s2 - s0)/15;
    return solve(l,mid,eps<e?eps:eps/2,s1) + solve(mid,r,eps<e?eps:eps/2,s2);
}
 
int main()
{
    read(n); cin >> a;
    rep(i,1,n + 1) cin >> p[i].x;
    rep(i,1,n) cin >> p[i].r;
    rep(i,1,n) p[i+1].x += p[i].x;
 
    ++ n; lf l = 2e9,r = -2e9;
    rep(i,1,n) p[i].x = p[i].x / tan(a);
    rep(i,1,n-1) t[i] = find(i,i+1);
 
    rep(i,1,n) chkmin(l,p[i].x - p[i].r);
    rep(i,1,n) chkmax(r,p[i].x + p[i].r);
    rep(i,1,n) pos[i] = p[i].x;
 
    cout << fixed << setprecision(2) << 2*solve(l,r,1e-3,simpson(l,r)) << endl;
 
    return 0;
}
