#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int n;
char s[40];
int t[301005][27],sz = 1;

int mx;
inline void insert()
{
	int len = strlen(s + 1);
	int x = 1; chkmax(mx,len);
	rep(i,1,len)
	{
		if(!t[x][s[i] - 'a']) t[x][s[i] - 'a'] = ++ sz;
		x = t[x][s[i] - 'a'];
	}
}

int fail[300001],dep[300001],nxt[300001][27];
inline void build_ac()
{
	queue<int> q;
	q.push(1);
	
	int z = 'z' - 'a';
	rep(i,0,z) nxt[0][i] = 1;
	q.push(1);
	while(!q.empty())
	{
		int x = q.front(); q.pop();
		rep(i,0,z)
			if(t[x][i])
			{
				nxt[x][i] = t[x][i];
				fail[nxt[x][i]] = nxt[fail[x]][i];
				dep[nxt[x][i]] = dep[x] + 1;
				q.push(nxt[x][i]);
			}
			else
				nxt[x][i] = nxt[fail[x]][i];
	}
}

ll ans,f[31][300001];

int main()
{
	read(n);
	rep(i,1,n)
	{
		scanf("%s",s + 1);
		insert();
	}
	
	build_ac();

	rep(i,2,sz) if(fail[i] != 1) ++ ans;

	rep(i,2,sz) rep(j,0,'z' - 'a') if(!t[i][j]) ++ f[1][nxt[i][j]];

	rep(i,1,mx) rep(j,2,sz)
		if(f[i][j])
		{
			ans += f[i][j];	
			rep(k,0,'z' - 'a')
				if(dep[nxt[j][k]] > i)
					f[i + 1][nxt[j][k]] += f[i][j];
		}

	cout << ans << endl;

	return 0;
}
