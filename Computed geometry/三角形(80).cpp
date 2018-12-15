#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0 ;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int N = (2e3 + 50) * 2001;
ll ans;
int n,cnt,tot,b[N];
struct DATA { int t,l,r,val; }a[N];
const bool cmp(DATA a,DATA b) { return a.t < b.t; }
struct Segment_tree
{
    int val[N << 2];
    int num[N << 2];
    
    inline void pd(int id,int len,bool k)
    {
        if(num[id]) val[id] = len;
        else if(k) val[id] = 0;
        else val[id] = val[id<<1] + val[id<<1|1];
    }

    void update(int id,int l,int r,int L,int R,int t)
    {
        if(l == L && r == R)
        {
            num[id] += t;
            pd(id,r-l+1,l == r);
            return ;
        }
        int mid = l + r >> 1;
        if(R <= mid) update(id<<1,l,mid,L,R,t);
        else if(L > mid) update(id<<1|1,mid+1,r,L,R,t);
        else update(id<<1,l,mid,L,mid,t),update(id<<1|1,mid+1,r,mid+1,R,t);
        pd(id,r-l+1,0);
    }
}seg;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    read(n);
    rep(i,1,n)
    {
        int x,y,m;
        read(x); read(y); read(m); --m; y <<= 1;
        a[++cnt].l = y; a[cnt].r = y + 2 * m; a[cnt].t = x; a[cnt].val = 1;
        b[++tot] = y; b[++tot] = a[cnt].r;
        int j = 2 * m + y;
        rep(k,1,m)
        {	
            a[++cnt].l = y;
            a[cnt].r = j-2;
            a[cnt].t = x + k;
            a[cnt].val = 1;

            a[++cnt].l = y;
            a[cnt].r = j;
            a[cnt].t = x + k;
            a[cnt].val = -1;
            b[++tot] = j - 1; 
            b[++tot] = j;
            j -= 2;
        }
        a[++cnt].l = y;a[cnt].r = y;a[cnt].val = -1; a[cnt].t = x + m + 1;
    }
    sort(a + 1,a + 1 + cnt,cmp);
    sort(b + 1,b + 1 + tot);
    tot = unique(b + 1,b + 1 + tot) - b - 1;
    map<int,int>mp;
    rep(i,1,tot) mp[b[i]] = i;
    //rep(i,1,tot) printf("%d ",b[i]);puts("");
    rep(i,1,cnt)
    {
        ans += (a[i].t - a[i-1].t) * seg.val[1];
        seg.update(1,1,tot,mp[a[i].l],mp[a[i].r],a[i].val);
    }
    cout << fixed << setprecision(1) << ans * 0.5 << endl;
// 	printf("%.3lf\n",clock()/(double)CLOCKS_PER_SEC);
    return 0;
}
