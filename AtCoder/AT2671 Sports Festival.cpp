#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
 
const int N = 340;
int a[N][N],nxt[N][N],pos[N][N];
vector<int>v[N],g[N];
bool vis[N];
 
int n,m;
inline bool check(int x)
{
	rep(i,1,m) vis[i] = 0;
	rep(i,1,m) g[i].clear();
	rep(i,1,n) g[pos[i][1]].push_back(i);
	while(1)
	{
		bool e = 1;
		rep(i,1,m)
		{
			int sz = g[i].size();
			if(((int)g[i].size()) <= x) continue;
			vis[i] = 1; e = 0; -- sz;
			rep(j,0,sz)
			{
				int num = g[i][j],pos = i;
				while(vis[pos]) pos = nxt[num][pos];
				if(pos == 0) return false;
				g[pos].push_back(num);
			}
			g[i].clear();
		}
		if(e) break;
	}
	rep(i,1,m) if(!vis[i]) return true;
	return false;
}
 
int main()
{
	read(n); read(m);
	rep(i,1,n) 
	{
		rep(j,1,m)
		{
			read(pos[i][j]);
			a[i][pos[i][j]] = j;
		}
		rep(j,1,m)
			nxt[i][j] = pos[i][a[i][j] + 1];
	}
	int l = 1,r = n,ans = n,mid;
	while(l <= r)
	{
		if(check(mid = l + r >> 1)) r = mid - 1,ans = mid;
		else l = mid + 1;
	}
	/*
	puts("");
	rep(i,1,n)  rep(j,1,m) printf("%d%c",nxt[i][j],j==m?'\n':' ');
	rep(i,1,m) printf("%d ",((int)g[i].size()));puts("");
	*/
	cout << ans << endl;
	return 0;
}
