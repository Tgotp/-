#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y , 1 : 0 ; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y , 1 : 0 ; }
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 7e3 + 50;
int n,m;
int head[N],nxt[N],to[N],tot;double f[N];
 
inline void add(int x,int y,double val)
{
    f[tot] = val;   
    to[tot] = y;
    nxt[tot] = head[x];
    head[x] = tot ++ ;
}
 
int s,t;
int d[N],cur[N];
#define eps 1e-8
inline bool bfs()
{
    memset(d,0,sizeof d);
    queue<int>q;
    d[s] = 1; q.push(s);
    while(!q.empty())
    {
        int x = q.front();q.pop();cur[x] = head[x];
        for(register int i =head[x];~i;i=nxt[i])
            if(f[i] > eps && !d[to[i]])  
                d[to[i]] = d[x] + 1,q.push(to[i]);
    }
    return d[t];
}
 
double dfs(int x,double w)
{
    if(x == t || w < eps) return w;
    double flow = 0,F;
    for(register int&i = cur[x] ;~i;i=nxt[i])
        if(d[to[i]] == d[x] + 1 && (F = dfs(to[i],min(w,f[i]))) > eps){
            w -= F; f[i] -= F;
            f[i^1] += F; flow += F;
    }
    return flow;
}
 
int u[N],v[N];
 
inline bool check(double x)
{
    tot = 0;memset(head,-1,sizeof head);
    rep(i,1,n) add(i,t,x),add(t,i,0);
    rep(i,1,m)
    {
        add(s,i + n,1); add(i + n,s,0);
        add(i + n,u[i],999); add(u[i],i + n,0);
        add(i + n,v[i],999); add(v[i],i + n,0);
    }
    double ans = m;
    while(bfs())
        ans -= dfs(s,99999);
    return ans > eps;
}
 
bool vis[N];
int main()
{
    read(n); read(m);
    if(!m) return puts("1"),0;
    rep(i,1,m) { read(u[i]); read(v[i]); }
 
    t = n + m + 2;
 
    int ans = 0;double res,l = 0,r = 500,mid;
    while(fabs(r-l) > 1.0/n/n)
    {
        if(check(mid = (l + r)/2)) l = mid,res = mid;
        else r = mid;
    }
    check(res); bfs();
    rep(i,1,n) if(d[i]) ++ ans;
    cout << ans << endl;
    return 0;
}
