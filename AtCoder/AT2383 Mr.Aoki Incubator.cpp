#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int mod = 1e9 + 7,N = 2e5 + 50;
int n,mx[N],f[N];
struct DATA { int v,x,l,r; }a[N];
const bool cmp(DATA a,DATA b) { return a.v < b.v || a.v == b.v && a.x < b.x; }
const bool cmp2(DATA a,DATA b) { return a.l < b.l || a.l == b.l && a.r < b.r; }

struct BIT_TREE
{
    int t[N];
    #define lowbit(x) (x & -x)

    inline void add(int x,int w)
    {
        for(register int i = x;i <= n + 1; i += lowbit(i))
            t[i] = (t[i] + w) % mod;
    }
    inline int find(int x)
    {
        int ans = 0;
        for(register int i = x; i ; i -= lowbit(i))
            ans = (ans + t[i]) % mod;
        return ans;
    }
}t;

int main()
{
    read(n);
    rep(i,1,n) read(a[i].x),read(a[i].v);
    sort(a + 1,a + 1 + n,cmp);
    rep(i,1,n) 
    {
        mx[i] = max(mx[i-1],a[i].x);
        int l = 1,r = i,mid;
        while(l <= r)
        {
            mid = l + r >> 1;
            if(mx[mid] >= a[i].x) a[i].l = mid,r = mid - 1;
            else l = mid + 1;
        }
    }
    mx[n + 1] = 1e9 + 7;
    repd(i,n,1) 
    {
        mx[i] = min(mx[i+1],a[i].x);
        int l = i,r = n,mid;
        while(l <= r)
        {
            mid = l + r >> 1;
            if(mx[mid] <= a[i].x) a[i].r = mid,l = mid + 1;
            else r = mid - 1;
        }
    }
    sort(a + 1,a + 1 + n,cmp2);
    f[0] = 1; t.add(n + 1,1);
    rep(i,1,n)
    {
        int z = t.find(n + 1 - (a[i].l - 1));
        t.add(n + 1 - a[i].r,z);
        f[a[i].r] = (f[a[i].r] + z) % mod;
    }

    //rep(i,1,n) printf("%d %d\n",a[i].l,a[i].r);

    cout << f[n] << endl;

    return 0;
}
