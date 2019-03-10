#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 1e6 + 50,inf = 1e9+7;
int n,m;
ll sum[N],s1[N],s2[N],s3[N],s4[N],a[N];
 
int main()
{
    read(n); 
    rep(i,1,n) read(a[i]);
    sort(a + 1,a + 1 + n);
    reverse(a + 1,a + 1 + n);
    rep(i,1,n) sum[i] = sum[i-1] + a[i];
    s1[0] = s3[0] = inf;
    rep(i,1,n)
    {
        s1[i] = s1[i-1];
        s3[i] = s3[i-1];
        if(a[i]&1) s1[i] = min(s1[i],a[i]);
        else s3[i] = min(s3[i],a[i]);
    }
    repd(i,n,1)
    {
        s2[i] = s2[i+1];
        s4[i] = s4[i+1];
        if(a[i]&1) s4[i] = max(s4[i],a[i]);
        else s2[i] = max(s2[i],a[i]);
    }
 
    read(m);
    while(m--)
    {
        int a; read(a);
        if(sum[a] & 1)
            printf("%lld\n",sum[a]);
        else
        {
            ll ans = -1;
            if(s1[a] != inf && s2[a+1])
                ans = max(ans,sum[a] - s1[a] + s2[a+1]);
            if(s3[a] != inf && s4[a+1])
                ans = max(ans,sum[a] - s3[a] + s4[a+1]);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
