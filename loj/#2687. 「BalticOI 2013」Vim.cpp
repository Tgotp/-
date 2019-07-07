#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y , 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e5 + 50;
int n,m,Ecnt,a[N],must[N];
int q[N][11][11],p[N][11];
char s[N];

int main()
{
	read(n);
	scanf("%s",s + 1);
	bool k = 1;
	rep(i,1,n)
	{
		if(s[i] == 'e')
			k = 1,++ Ecnt;
		else
		{
			a[++ m] = s[i] - 'a';
			must[m] = k; k = 0;
		}
	}
	int z = 10;
	memset(q,0x3f,sizeof q);
	memset(p,0x3f,sizeof p);
	p[0][a[1]] = 0;
	rep(i,1,m) rep(j,0,z)
	{
		int&t = p[i][j];
		if(a[i] != j && !must[i]) chkmin(t,p[i-1][j]);
		if(j != a[i]) chkmin(t,q[i-1][a[i]][j]);
		chkmin(t,q[i-1][a[i]][a[i]] + 2);
		chkmin(t,p[i-1][a[i]] + 2);
		rep(k,0,z)
		{
			int&t2 = q[i][j][k];
			if(a[i] != j && a[i] != k) chkmin(t2,q[i-1][j][k] + 1);
			if(j != a[i]) chkmin(t2,p[i-1][j] + 3);
			if(j != a[i]) chkmin(t2,q[i-1][j][a[i]] + 3);
			if(k != a[i]) chkmin(t2,q[i-1][a[i]][k] + 3);
			chkmin(t2,p[i-1][a[i]] + 5);
			chkmin(t2,q[i-1][a[i]][a[i]] + 5);
		}
	}
	cout << p[m][10] + Ecnt * 2 - 2 << endl;
	return 0;
}
