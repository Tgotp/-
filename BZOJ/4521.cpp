#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x; i <= y; ++ i)
#define repd(i,x,y) for(register int i = x; i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c =  getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int t[15],len;

ll f[2][2][2][11][4][15];
ll dfs(int now,bool e1,bool e2,bool e3,bool e4,int lst,int num)
{
	if(num >= 3) e4 = 1;
	if(e2 && e3) return f[e2][e3][e4][lst][num][now] = 0;
	if(now == len + 1) return f[e2][e3][e4][lst][num][now] = e4;
	
	if(e1 && ~f[e2][e3][e4][lst][num][now]) return f[e2][e3][e4][lst][num][now];

	int top = e1 ? 9 : t[now];
	f[e2][e3][e4][lst][num][now] = 0;

	rep(i,now == 1 ? 1 : 0,top)
		f[e2][e3][e4][lst][num][now] += dfs(now + 1,e1|(i != top),e2 | (i == 4),e3 | (i == 8),e4,i,lst == i ? min(3,1+num) : 1);

	return f[e2][e3][e4][lst][num][now];
}

inline ll solve(ll x)
{
	if(x < 10000000000) return 0;
	memset(f,-1,sizeof f);
	len = 0;
	while(x)
	{
		t[++ len] = x % 10;	
		x /= 10;
	}
	reverse(t + 1,t + 1 + len);
	return dfs(1,0,0,0,0,10,0);
}

ll l,r;

int main()
{
	read(l); read(r);
	if(l > r) swap(l,r);
	printf("%lld\n",solve(r) - solve(l - 1));
	return 0;
}
