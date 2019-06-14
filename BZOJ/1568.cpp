#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    int sign = 1; x = 0; char c;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
  
const int N = 1e5 + 50;
int tot;
struct Line
{
    double k,b;
      
    inline double f(int x)
    {
        return x * k + b;
    }
  
}line[N];
  
struct Segment_Tree
{
    int val[N << 2];
    void update(int id,int l,int r,int L,int R,int x)
    {
        if(l == L && r == R)
        {
            if(!val[id]) val[id] = x;
            else
            {
                bool ls = line[x].f(l) > line[val[id]].f(l);
                bool rs = line[x].f(r) > line[val[id]].f(r); 
                if(ls && rs) val[id] = x;
                else if(ls || rs)
                {
                    double z = (line[x].b - line[val[id]].b) / 
                        (line[val[id]].k - line[x].k);
                    int mid = l + r >> 1;
                    if(ls) update(id<<1,l,mid,l,mid,x);
                    if(ls && z > mid) update(id<<1|1,mid+1,r,mid+1,r,x);
                    if(rs) update(id<<1|1,mid+1,r,mid+1,r,x);
                    if(rs && z <= mid) update(id<<1,l,mid,l,mid,x);
                }
            }
            return ;
        }
        int mid = l + r >> 1;
        if(R <= mid) update(id<<1,l,mid,L,R,x);
        else if(L > mid) update(id<<1|1,mid+1,r,L,R,x);
        else update(id<<1,l,mid,L,mid,x),update(id<<1|1,mid+1,r,mid+1,R,x);
    }
  
    int find(int id,int l,int r,int pos,double h)
    {
        if(val[id])
        {
            double h1 = line[val[id]].f(pos);
            h = max(h1,h);
        }
        if(l == r) return h;
        int mid = l + r >> 1;
        if(pos <= mid) return find(id<<1,l,mid,pos,h);
        else return find(id<<1|1,mid+1,r,pos,h);
    }
}seg;
  
int n;
int lstans;
 
char s[20];
  
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("2.out","w",stdout);
#endif
    read(n);
 
    rep(i,1,n) 
    {
        scanf("%s",s + 1);
        if(s[1] == 'Q')
        {
            int k; read(k);
            printf("%d\n",(int)(seg.find(1,1,50000,k,0)/100));
        }
        else
        {
            ++ tot;
            scanf("%lf%lf",&line[tot].b,&line[tot].k);
            line[tot].b -= line[tot].k;
  
            seg.update(1,1,50000,1,50000,tot);
        }
    }
    return 0;
}
﻿
