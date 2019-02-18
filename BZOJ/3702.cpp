
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
 
const int N = 7e6 + 50,M = 1e6 + 50;
int n,rt[M],ch[M][2],sz[M],ls[N],rs[N],val[N],size,cnt;
ll ans,res;
 
void insert(int&x,int l,int r,int pos)
{
    if(!x) x = ++ size;
    if(l == r) return void(val[x] = 1);
    int mid = l + r >>1;
    if(pos <= mid) insert(ls[x],l,mid,pos);
    else insert(rs[x],mid+1,r,pos);
    val[x] = val[ls[x]] + val[rs[x]];
}
 
int merge(int x,int y,int l,int r,ll nr)
{
    if(!x) return y;
    if(!y) { res += val[x] * nr;return x;}
    int mid = l + r >> 1;
    ls[x] = merge(ls[x],ls[y],l,mid,nr + val[rs[y]]);
    rs[x] = merge(rs[x],rs[y],mid+1,r,nr);
    val[x] = val[ls[x]] + val[rs[x]];
    return x;
}
 
void get(int&x)
{
    x = ++ cnt; int t; read(t);
    #define ls ch[x][0]
    #define rs ch[x][1]
    if(t)
    {
        insert(rt[x],1,n,t);
        sz[x] = 1; return ;
    }
    get(ls); get(rs);
    res = 0; rt[x] = merge(rt[ls],rt[rs],1,n,0LL);
 
    ans += min(res,1ll * sz[ls] * sz[rs] - res);
    sz[x] = sz[ls] + sz[rs];
}
 
int main()
{
    read(n);
    int rt; get(rt);
    cout << ans << endl;
    return 0;
}
