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

int n,m,a,b,cnt;
int vised,vis[1010][1010];
char s[1010][1010],t[1010][1010];
int x[1010 * 1010],y[1010 * 1010];
inline void solve()
{
	read(n); read(m); read(a); read(b);
	rep(i,1,n) scanf("%s",s[i] + 1);
	rep(i,1,a) scanf("%s",t[i] + 1);

	int c = -1,d; cnt = 0;
	rep(i,1,a) rep(j,1,b)
		if(t[i][j] == 'x')
		{
			if(c == -1)
				c = i,d = j;
			else x[++cnt] = i - c,y[cnt] = j - d;
		}
	
	++ vised;
	rep(i,1,n) rep(j,1,m)
		if(s[i][j] == 'x' && vis[i][j] != vised)
		{
			if(c == -1) 
			{
				puts("NIE");
				return ;
			}

			vis[i][j] = vised;

			rep(k,1,cnt)
				if(i + x[k] <= 0 || j + y[k] <= 0 || i + x[k] > n || j + y[k] > m ||
					vis[i + x[k]][j + y[k]] == vised 
					|| s[i + x[k]][j + y[k]] == '.')
				{
					puts("NIE");
					return;
				}
				else vis[i + x[k]][j + y[k]] = vised;
		}

	puts("TAK");
}

int main()
{
	int t;
	read(t);
	while(t --)	solve();
	return 0;
}
