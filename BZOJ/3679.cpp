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

ll t[25],len;
ll l,r,n;
map<ll,ll>mp[25];

ll dfs(int x,ll f,int e)
{
	if(x == len + 1) return 1;
	if(e && mp[x].count(f)) return mp[x][f];
	mp[x][f] = 0;

	int top = e ? 9 : t[x];
	ll ans = 0;
	rep(i,(f?1:0),top)
	{
		if(f * i > n) continue;
		if(f == 0) ans += dfs(x + 1,i,e|(i!=t[x]));
		else ans += dfs(x + 1,f * i,e|(i!=t[x]));
	}

	return mp[x][f] = ans;
}

inline ll find(ll x)
{
	len = 0;
	while(x)
	{
		t[++ len] = x % 10;
		x /= 10;
	}
	
	rep(i,0,len+1) mp[i].clear();
	reverse(t + 1,t + 1 + len);

	return dfs(1,0,0);
}

int main()
{
	read(n);
	read(l); read(r); -- r; -- l;
	printf("%lld\n",find(r) - find(l));
	return 0;
}
