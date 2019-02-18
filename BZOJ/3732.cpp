#include<bits/stdc++.h>
#define size(x) (((int)que[x].size())-1)
#define rep(i,x,y) for(register int i = x ;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x ;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    x = 0;char c;int sign = 1;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 3e4 + 500;
int n,m,k,p[N],ans[N];
vector<pair<int,int> >que[N];
struct Edge { int x,y,w; }edge[N];
 
const bool cmp(Edge a,Edge b) { return a.w < b.w; }
 
int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }
 
int main()
{
    memset(ans,0x3f,sizeof ans);
    read(n); read(m); read(k);
    rep(i,1,m) read(edge[i].x),read(edge[i].y),read(edge[i].w);
    rep(i,1,k)
    {
        int x,y;
        read(x); read(y);
        que[x].push_back(make_pair(y,i));
    }
     
    sort(edge + 1,edge + 1 + m,cmp);
     
    rep(i,1,n) p[i] = i;
    rep(i,1,m)
    {
        int x = get_fa(edge[i].x),y = get_fa(edge[i].y);
        if(x != y)
        {
            p[x] = y;
            rep(j,0,size(x))
                if(get_fa(que[x][j].first) == get_fa(x)) ans[que[x][j].second] = min(ans[que[x][j].second],edge[i].w);
                else que[y].push_back(que[x][j]);
             
            rep(j,0,size(y))
                if(get_fa(que[y][j].first) == get_fa(y)) ans[que[y][j].second] = min(ans[que[y][j].second],edge[i].w);
        }
    }
     
    rep(i,1,k) printf("%d\n",ans[i]);
     
    return 0;
}
