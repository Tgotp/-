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

const int N = 1e5 + 50,M = 4e6 + 50,mod = 1e9 + 7;
int lg[N];
int f[N][21];
int ch[M][2];
int p[M],vis[M];
int cnt,n,m;

inline int get_fa(int x) { return p[x] == x ? x : p[x] = get_fa(p[x]); }

int main()
{
	read(n); read(m);
	rep(i,2,n) lg[i] = lg[i>>1] + 1;
	rep(i,1,M-50) p[i] = i;
	rep(i,1,m)
	{
		int l1,r1,l2,r2;
		read(l1); read(r1); read(l2); read(r2);
		if(l1 == l2) continue;

		int k = lg[r1 - l1 + 1];

		++ cnt;
		if(f[l1][k]) p[get_fa(f[l1][k])] = cnt;
		if(f[l2][k]) p[get_fa(f[l2][k])] = cnt;
		f[l1][k] = cnt; f[l2][k] = cnt;

		++ cnt;
		if(f[r1-(1<<k)+1][k]) p[get_fa(f[r1-(1<<k)+1][k])] = cnt;
		if(f[r2-(1<<k)+1][k]) p[get_fa(f[r2-(1<<k)+1][k])] = cnt;
		f[r1-(1<<k)+1][k] = cnt; f[r2-(1<<k)+1][k] = cnt;
	}

	repd(j,20,1) rep(i,1,n) if(f[i][j])
	{
		f[i][j] = get_fa(f[i][j]);
		if(!ch[f[i][j]][0]) 
			ch[f[i][j]][0] = ++ cnt,
			ch[f[i][j]][1] = ++ cnt;

		if(f[i][j-1]) p[get_fa(f[i][j-1])] = get_fa(ch[f[i][j]][0]);
		if(f[i+(1<<j-1)][j-1]) p[get_fa(f[i+(1<<j-1)][j-1])] = get_fa(ch[f[i][j]][1]);

		f[i][j-1] = get_fa(ch[f[i][j]][0]);
		f[i+(1<<j-1)][j-1] = get_fa(ch[f[i][j]][1]);
	}

	int ans = 9;
	rep(i,1,n) if(!f[i][0]) f[i][0] = ++ cnt;
	vis[get_fa(f[1][0])] = 1;
	rep(i,1,n) if(!vis[get_fa(f[i][0])])
		vis[get_fa(f[i][0])] = 1,
		ans = 1ll * ans * 10 % mod;

	printf("%d\n",ans);

	return 0;
}
