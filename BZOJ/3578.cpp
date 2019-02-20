
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1;x = 0;
    do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}
 
const int N = 1e5 + 50;
int n,m,q;
int id[N];
 
int val[N];ull w[N],num[N];
set<int>s;
map<ull,bool> mp;
char S[5];
 
int main()
{
    srand(time(NULL));
    read(n); read(m); read(q);
    rep(i,1,n) id[i] = 1;
    rep(i,1,n) 
    {
        w[i] = (ull)rand() * rand() * rand();
        num[1] ^= w[i];
    }
    val[1] = n;
 
    s.insert(1);
     
 
#ifndef ONLINE_JUDGE
    puts("\n");
#endif
    rep(i,1,q)
    {
        int a,b;
        scanf("%s",S + 1);
        read(a); read(b);
        if(S[1] == 'W')
        {
            set<int>::iterator it = lower_bound(s.begin(),s.end(),a);
            int ans = 0;
            while(it != s.end() && *it <= b)
            {
                if(!mp[num[*it]])
                {
                    ans += val[*it];
                    mp[num[*it]] = 1;
                }
                s.erase(it);
                it = lower_bound(s.begin(),s.end(),a);
            }
            printf("%d\n",ans);
        }
        else
        {
            set<int>::iterator it = lower_bound(s.begin(),s.end(),id[a]);
            if(it == s.end() || *it != id[a])
                s.insert(id[a]);
 
            -- val[id[a]];
            num[id[a]] ^= w[a];
            num[b] ^= w[a];
            ++ val[b];
            id[a] = b;
 
            it = lower_bound(s.begin(),s.end(),b);
            if(it == s.end() || *it != b)
                s.insert(b);
 
        }
    }
    return 0;
}
