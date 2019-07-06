#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x =  x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int M = 4e5 + 50;
int n,m,cnt;

struct EDGE { int u,v;ll w; }e[M];

const bool cmp(EDGE a,EDGE b) { return a.w < b.w; }
ll v[M];int p[M];
ll ans;

int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }

int main()
{
	read(n); read(m);
	rep(i,0,2 * n) v[i] = INT_MAX;
	rep(i,1,m)
	{
		int a,b,c;
		read(a); read(b); read(c);
		e[++cnt].u = a+1;e[cnt].v = b+1;e[cnt].w = c;
		v[a] = min(v[a],c+1LL);	
		v[b] = min(v[b],c+2LL);
	}

	rep(i,1,2*n)
	{
		v[i] = min(v[i],v[i-1]+2);
		v[i%n] = min(v[i%n],v[i]);
	}

	rep(i,0,n-1)
		e[++cnt].u = i + 1,
		e[cnt].v = (i+1)%n + 1,
		e[cnt].w = v[i];

	sort(e + 1,e + 1 + cnt,cmp);
	rep(i,1,n) p[i] = i;
	rep(i,1,cnt)
	{
		int u = get_fa(e[i].u),v = get_fa(e[i].v);
		if(u != v)
		{
			p[u] = v;
			ans += e[i].w;
		}
	}
	
	cout << ans << endl;

	return 0;
}
