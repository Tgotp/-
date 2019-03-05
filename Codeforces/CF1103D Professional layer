#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x =0 ;
    do { c =  getchar(); if(c == '-') sign = -1; } while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int N = 1e6 + 50;
int n,cnt;
ll a[N],e[N],f[12][2050],k,d;
ll pri[N],ans,inf;
map<ll,vector<ll> > m;
vector<ll> ok;

ll gcd(ll x,ll y) { return !y ? x : gcd(y,x % y); }

int main()
{
    read(n); read(k);
    rep(i,1,n)
    {
        read(a[i]);
        if(i == 1) d = a[i];
        else d = gcd(d,a[i]);
    }
    rep(i,1,n) read(e[i]);
    for(register ll i = 2;i * i <= d; ++ i)
        if(d % i == 0) 
        {
            pri[++ cnt] = i;
            while(d % i == 0) d /= i;
        }
    if(d > 1) pri[++ cnt] = d;
    rep(i,1,n)
    {
        ll x = 1;
        rep(j,1,cnt) 
            while(a[i] % pri[j] == 0) x *= pri[j],a[i]/=pri[j];
        m[x].push_back(e[i]);
    }
    
    int s = (1 << cnt) - 1;
    memset(f,0x3f,sizeof f);
    ans = inf = f[0][0];f[0][0] = 0;
    for(auto&pr:m)
    {
        ok.clear();
        rep(i,1,s)
        {
            ll x = 1,y = pr.first;
            rep(j,1,cnt)
                if(i&(1<<j-1))
                    while(y%pri[j] == 0)
                        y/=pri[j],x*=pri[j];
            if(x <= k) ok.push_back(i);
        }
        sort(pr.second.begin(),pr.second.end());
        if(pr.second.size() > cnt)pr.second.resize(cnt);
        for(auto&cost:pr.second)
        {
            repd(i,cnt,1)
                for(auto&x:ok)
                {
                    for(register int j = s^x,T = j;T;T=(T-1)&j)
                        f[i][T|x] = min(f[i][T|x],f[i-1][T]+cost);
                    f[i][x] = min(f[i][x],f[i-1][0]+cost);
                }
        }
    }
    rep(i,0,cnt) if(f[i][s] < inf)
        ans = min(ans,f[i][s] * i);
    if(ans == inf) puts("-1");
    else cout << ans << endl;
    return 0;
} 
