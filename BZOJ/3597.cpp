#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y, 1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 5e4 + 50,M = 2e4 + 50;
int head[N],to[M],nxt[M],w[M],tot;
int n,m;

inline void add(int x,int y,int val)
{
	to[tot] = y;
	w[tot] = val;
	nxt[tot] = head[x];
	head[x] = tot ++ ;	
}
const int inf = 0x3f3f3f3f;

double dis[N],z;
bool inq[N];
inline bool dfs(int x)
{
	inq[x] = 1;
	for(register int i = head[x];~i;i=nxt[i])
		if(chkmin(dis[to[i]],dis[x] + w[i] + z))
		{
			if(inq[to[i]]) return true;
			if(dfs(to[i])) return true;
		}

	inq[x] = 0;
	return false;
}

ll num,o;
inline bool check(double x)
{
	memset(dis,0,sizeof dis); z = x;
	memset(inq,0,sizeof inq);
	rep(i,1,n + 2) if(dfs(i)) return true;
	return false;
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m);
	rep(i,1,m)
	{
		int u,v,a,b,c,d;
		read(u); read(v); read(a); read(b);
		read(c); read(d); 
		if(c) add(v,u,a - d);
		add(u,v,b + d);
	}

	double l = 0,r = inf,mid;
	while(fabs(l - r) > 1e-3)
	{
		if(check(mid = (l + r) / 2)) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(2) << mid << endl;
	return 0;
}
