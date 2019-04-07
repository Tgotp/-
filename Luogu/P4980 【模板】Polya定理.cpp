// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int mod = 1e9 + 7;
int n;

inline int ksm(int x,int y)
{
    int ans = 1;
    while(y)
    {
        if(y&1) ans = 1ll * ans * x % mod;
        x = 1ll * x * x % mod; y >>= 1;
    }
    return ans;
}

inline int el(int x)
{
    int res = 1;
    for(register int i = 2;i * i <= x;++ i)
        if(x % i == 0)
        {
            x /= i;
            res *= i - 1;
            while(x % i == 0)
                x /= i,res *= i;
        }
 
    if(x > 1) res *= x - 1;

    return res;
}

inline void solve()
{
    read(n); ll ans = 0;
    int d = sqrt(n);
    rep(i,1,d)
    {
        if(n % i) continue;

        ans = (ans + 1ll * el(n/i) * ksm(n,i) % mod) % mod;

        if(i * i != n) ans = (ans + 1ll * el(i) * ksm(n,n/i) % mod) % mod;
    }
    printf("%lld\n",ans * ksm(n,mod - 2) % mod);
}

int main()
{
    int t;
    read(t);
    while(t --) solve();

    return 0;
}
