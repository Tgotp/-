#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int N = 403,M = 1e5 + 50;
int n,m,a[M],b[M];
bool k[N];
bitset<N> z[N];

int main()
{
    read(n); read(m);
    rep(i,1,m) read(a[i]),read(b[i]);
    rep(i,1,n)
    {
        z[i][i] = 1;
        repd(j,m,1)
        {
            int x = z[i][a[j]],y = z[i][b[j]];
            if(x & y)
            {
                k[i] = 1;
                break;
            }
            if(x) {z[i][b[j]] = 1; continue;} 
            if(y) {z[i][a[j]] = 1; continue;}

        }
    }

    int ans = 0;

    rep(i,1,n)
    {
        if(k[i]) continue;
        rep(j,i + 1,n)
        {
            if(k[j]) continue;
            if(!((z[i] & z[j]).any())) ++ ans;
        }
    }

    cout << ans << endl;
    return 0;
}
