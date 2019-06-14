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
 
const int N = 2e5 + 50;
int n; double ans = 1;
int a[N],b[N],c[N],s[N],x[N],d[N];
 
int sta[N],top;
 
int main()
{
    read(n);
    rep(i,1,n) 
    {
        int x;
        read(x);
        a[x] = i;
    }
    rep(i,1,n)
    {
        int x;
        read(x);
        c[i] = a[x];
        b[a[x]] = i;
    }
 
    x[1] = 1;s[1] = 1; ++ ans;
    rep(i,2,n-1)
    {
        if(c[i] > c[i+1]) x[i] = 1, ++ ans;
        if(x[i] == 1)
        {
            ++ d[i],--d[i+1];
        }
        s[i] = s[i-1] + x[i];
    }
 
    rep(i,1,n-1)
        if(b[i] < b[i + 1])
        {
            if(s[b[i+1]-1] - s[b[i]-1] > 0)
            {
                ++ d[b[i]];
                -- d[b[i+1]];
            }
            else sta[++top] = b[i];
        }
 
    rep(i,1,n) d[i] += d[i-1];
     
    rep(i,1,top) if(!d[sta[i]]) ans += 0.5;
 
    cout << fixed << setprecision(3) << ans-0.001 << endl;
    cout << fixed << setprecision(3) << ans << endl;
    cout << fixed << setprecision(3) << ans+0.001 << endl;
 
    return 0;
}
