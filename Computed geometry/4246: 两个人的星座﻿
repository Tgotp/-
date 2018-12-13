/**************************************************************
    Problem: 4246
    User: scgwwgyxin
    Language: C++
    Result: Accepted
    Time:25856 ms
    Memory:1604 kb
****************************************************************/
 
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
inline char gc()
{
    static char *S,*T,buf[1<<16];
    if(S == T) { T = (S = buf) + fread(buf,1,1<<16,stdin); if(S == T) return EOF; }
    return *S ++;
}
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = gc(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = gc(); }while(isdigit(c));
    x *= sign;
}
const int N = 6e3 + 50;
int n,num[3],sum[3]; ll ans;
struct Point
{
    int x,y,c;double k;
    inline bool operator < (const Point b) const { return k < b.k;}
}p[N],A[N];
 
inline bool OnRight(int x,int y) { return 1ll * A[x].x * A[y].y - 1ll * A[x].y * A[y].x < 0; }
inline bool OnLeft(int x,int y) { return 1ll * A[x].x * A[y].y - 1ll * A[x].y * A[y].x > 0; }
 
inline void solve(int x)
{
    -- num[p[x].c];
    int cnt = 0;
    rep(i,1,n) if(i != x)
    {
        ++ cnt;
        A[cnt].x = p[i].x - p[x].x;
        A[cnt].y = p[i].y - p[x].y;
        A[cnt].c = p[i].c; A[cnt].k = atan2(A[cnt].y,A[cnt].x);
    }
    sort(A + 1,A + 1 + cnt);
    int now = 1; sum[0] = sum[1] = sum[2] = 0;
    sum[A[1].c] = 1;
    int a,b,c = 0,d = 1;
    if(p[x].c == 0) c = 2;
    if(p[x].c == 1) d = 2;
    rep(i,1,cnt) A[i+cnt] = A[i];
    rep(i,1,cnt)
    {
        while(now < i || OnLeft(i,now + 1))
            now = now + 1,++ sum[A[now].c];
        a = 0;b = 1;
        if(A[i].c == 0) a = 2;
        if(A[i].c == 1) b = 2;
        ans += 1ll * (num[c] - sum[c]) * (num[d] - sum[d]) * sum[a] * sum[b];
        -- sum[A[i].c];
    }
    ++ num[p[x].c];
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    read(n);
    rep(i,1,n) read(p[i].x), read(p[i].y), read(p[i].c),++ num[p[i].c];
    rep(i,1,n) solve(i);
    cout << ans / 2 << endl;
    return 0;
}
