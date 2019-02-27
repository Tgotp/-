#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1; x = 0;
    do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 5e5 + 50;
struct Segment_tree
{
    int val[50][31];
    vector<int> v[N << 2];
 
    void update(int id,int l,int r,int L,int R,int w)
    {
        if(l == L && r == R)
        {
            v[id].push_back(w);
            return ;
        }
        int mid = l + r >> 1;
        if(R <= mid) update(id<<1,l,mid,L,R,w);
        else if(L > mid) update(id<<1|1,mid+1,r,L,R,w);
        else update(id<<1,l,mid,L,mid,w),update(id<<1|1,mid+1,r,mid+1,R,w);
    }
 
    int a[N],b[N];
    
    inline void ins(int dep,int x)
    {
    	repd(i,30,0)
    		if(!val[dep][i] && (x & (1 << i)))
    		{
    			val[dep][i] = x;
    			
    			return;
			}
    		else if(x & (1 << i))x ^= val[dep][i];
	}
    
    void put_down(int id,int l,int r,int dep)
    {
        //printf("%d %d %d\n",id,l,r);
        int cnt = 0;
        int sz = v[id].size(); -- sz;
        rep(i,0,30) val[dep][i] = val[dep-1][i];
        rep(i,0,sz) ins(dep,v[id][i]);
        
        if(l == r)
        {
            int ans = 0;
            repd(i,30,0)
               if(!(ans & (1<<i))) ans ^= val[dep][i];
            printf("%d\n",ans);
            return ;
        }
        int mid = l + r >> 1;
        put_down(id<<1,l,mid,dep+1);
        put_down(id<<1|1,mid+1,r,dep+1);
    }
}seg;
 
int n;
set<int>s;
map<int,int> mp,pos;
 
int main()
{
    read(n);
 
    set<int> :: iterator it;
    #define mk(x,y) make_pair(x,y)
    rep(i,1,n)
    {
        int x;
        read(x);
        if(x < 0)
        {
            x = - x; -- mp[x];
            if(mp[x] > 0) continue;
            seg.update(1,1,n,pos[x],i-1,x); 
            it = lower_bound(s.begin(),s.end(),x);
            s.erase(it);
        }
        else
        {
            if(mp[x] == 0) pos[x] = i;
            ++ mp[x]; s.insert(x);  
        }
    }
    it = s.begin();
    while(it != s.end())
    {
        seg.update(1,1,n,pos[*it],n,*it);
        ++ it;
    }
    seg.put_down(1,1,n,1);
    return 0;
}
