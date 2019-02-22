#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
const int mod = 12345678;
int n,m,z;
char s[6][9];

int x[9] = {0,1,1,1,0,0,-1,-1,-1};
int y[9] = {0,1,0,-1,1,-1,0,1,-1};

int ans;

int num[1 << 9];
int f[30][1 << 9];
int tot,X[9],Y[9];
bool vis[30][30];

#define lowbit(x) (x&-x)

inline int solve()
{
	tot = 0; 
	rep(i,1,n) rep(j,1,m)
		if(s[i][j] == 'X')
			{++tot;X[tot] = i,Y[tot] = j;}
	
	int s = (1 << tot) - 1;
	rep(i,0,s)
	{
		memset(vis,0,sizeof vis);
		rep(j,1,tot)	
			if(!(i>>(j-1)&1))
			{
				vis[X[j]][Y[j]] = 1;
				rep(k,1,8)
				{
					int xx = X[j] + x[k],yy = Y[j] + y[k];
					if(!xx || !yy || xx > n || yy > m) continue;
					vis[xx][yy] = 1;
				}
			}
		num[i] = z;
		rep(j,1,n) rep(k,1,m)
			if(vis[j][k]) -- num[i];
	}
	
	memset(f,0,sizeof f);
	f[0][0] = 1;
	rep(i,1,z) rep(j,0,s)
	{
		for(register int k = j;k;k -= lowbit(k))
			f[i][j] = (f[i][j] + f[i-1][j^lowbit(k)])%mod;
		f[i][j] = (f[i][j] + 1ll*f[i-1][j] * max(num[j]-i+1,0))%mod;
	}
	return f[z][s];
}

void dfs(int X,int Y,int k)
{
	if(Y == m + 1) return void(dfs(X+1,1,k));
	if(X == n + 1) return void(ans = (ans + (k&1?-1:1)*solve() + mod)%mod);

	dfs(X,Y+1,k);

	if(s[X][Y] == 'X') return;
	rep(k,1,8)
	{
		int xx = X + x[k],yy = Y + y[k];
		if(!xx || !yy || xx > n || yy > m) continue;
		if(s[xx][yy] == 'X')
			return;
	}

	s[X][Y] = 'X';
	dfs(X,Y+1,k+1);
	s[X][Y] = '.';
}

int main()
{
	cin >> n >> m;
	rep(i,1,n) scanf("%s",s[i] + 1);
	rep(i,1,n) rep(j,1,m) if(s[i][j] == 'X') rep(k,1,8)
	{
		int xx = i + x[k],yy = j + y[k];
		if(!xx || !yy || xx > n || yy > m) continue;
		if(s[xx][yy] == 'X')
			return puts("0"),0;
	}
	
	z = n * m;

	dfs(1,1,0);
	cout << ans << endl;
	return 0;
}
