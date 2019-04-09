#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
}

const int N = 3e3 + 50;
const int mod = 998244353;
int n,c,k,f[N],g[N],dp[31][2][N][303];
int c0,c1,d0,d1,num[N];
bool vis[N][4];

struct DATA { int num,bel,to; }a[N],b[N];

const bool cmp(DATA a,DATA b) { return a.bel < b.bel; }

inline void clear()
{
	memset(dp,0,sizeof dp);
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	memset(vis,0,sizeof vis);
	memset(num,0,sizeof num);
}

inline int get(bool op,int l,int r)
{
	-- l ;
	if(op == 0) return (f[r] - (l == -1?0:f[l]) + mod) % mod;
	else return (g[r] - (l==-1?0:g[l]) + mod) % mod;
}

inline void solve()
{
	clear();
	read(n); read(c);
	read(c0); read(c1); read(d0); read(d1);
	int M = max(max(c0,c1),max(d0,d1)),sum = 0;
	rep(i,1,n)
	{
		read(a[i].bel); read(a[i].num);
		a[i].to = -1; num[a[i].bel] += a[i].num;
		sum += a[i].num;
	}
	read(k);
	rep(i,1,k)
	{
		int x; read(x);	read(a[x].to);
		b[i] = a[x];
		vis[a[x].bel][a[x].to] = 1;
	}

	sort(b + 1,b + 1 + k,cmp);

	f[0] = 1; g[0] = 1;
	rep(x,1,c) if(!vis[x][0] && !vis[x][1] && !vis[x][2] && ! vis[x][3] && num[x])
		repd(i,M,num[x]) f[i] = (f[i] + f[i-num[x]]) % mod;

	rep(x,1,n) if(a[x].to == -1)
		repd(i,M,a[x].num) g[i] = (g[i] + g[i-a[x].num]) % mod;
	
	rep(i,1,M) 
		f[i] = (f[i] + f[i-1]) % mod,
		g[i] = (g[i] + g[i-1]) % mod;

	int res = 0,tot = 0;
	dp[0][0][0][0] = 1;
	rep(x,1,k) 
	{
		res += b[x].num; tot += b[x].num;

		rep(op,0,1) rep(i,0,c0) repd(j,res,0)
		{
			if(b[x].to != 0 && i >= num[b[x].bel] && j >= b[x].num && (b[x].bel != b[x-1].bel || op == 0))
				dp[x][0][i][j] = (dp[x][0][i][j] + dp[x-1][op][i - num[b[x].bel]][j-b[x].num]) % mod;
			if(b[x].to != 1 && i >= num[b[x].bel] && (b[x].bel != b[x-1].bel || op == 0))
				dp[x][0][i][j] = (dp[x][0][i][j] + dp[x-1][op][i - num[b[x].bel]][j]) % mod;
			if(b[x].to != 2 && j >= b[x].num && (b[x].bel != b[x-1].bel || op == 1))
				dp[x][1][i][j] = (dp[x][1][i][j] + dp[x-1][op][i][j-b[x].num]) % mod;
			if(b[x].to != 3 && (b[x].bel != b[x-1].bel || op == 1))
				dp[x][1][i][j] = (dp[x][1][i][j] + dp[x-1][op][i][j]) % mod;
		}

		num[b[x].bel] = 0;
	}

	int ans = 0;
	rep(op,0,1) rep(i,0,c0) rep(j,0,res) if(dp[k][op][i][j])
	{
		int r = c0 - i,l = max(0,sum - i - c1);
		int R = d0 - j,L = max(0,sum - j - d1);
		if(l > r || L > R) continue;
		ans = (ans + 1ll * dp[k][op][i][j] * get(0,l,r) % mod * get(1,L,R) %mod) % mod;
	}
	printf("%d\n",ans);
}

int main()
{
	int t;
	read(t);
	while(t -- ) solve();

	return 0;
}
