
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

//#define ll __int128

ll Mul(ll x,ll y,ll mod)
{
    ll ans = 0; 
    y = (y% mod + mod) % mod;
    x = (x% mod + mod) % mod;
    while(y)
    {
        if(y&1) ans = (ans + x) % mod;
        x = (x + x) % mod; y >>= 1;
    }
    return ans;
}

int n;
ll m = 1,x = 0;

ll gcd(ll a,ll b) { return !b ? a : gcd(b,a % b); }

ll exgcd(ll a,ll b,ll&x,ll&y)
{
    if(!b) { x = 1;y = 0; return a; }
    ll z = exgcd(b,a%b,y,x);
    y -= (a/b) * x;
    return z;
}

int main()
{
    read(n);
    rep(i,1,n)
    {
        ll a,b,X,Y;
        read(a); read(b);
        
        ll z = exgcd(m,a,X,Y);
        X = Mul(X,((b - x) / z),a);
        x = x + m * X;
        m = m / gcd(m,a) * a;
        x %= m;
    }

    printf("%lld\n",x);

    return 0;
}
