#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e3 + 50;
int mxp,w,n;
int f[N][N],mx[N],g[N];
int q[N],st,en;

int main()
{
	read(n); read(mxp); read(w); ++ w;
	memset(f,-0x3f,sizeof f);
	f[0][0] = 0;
	rep(i,1,n)
	{
		int ap,bp,as,bs;
		read(ap); read(bp); read(as); read(bs);
		rep(j,0,as) f[i][j] = -j*ap;
		if(i > w)	
		{
			st = 1;en = 0;
			rep(j,0,mxp)
			{
				while(st <= en && j - q[st] > as) ++ st;
				if(st <= en) f[i][j] = max(f[i][j],f[i-w][q[st]] - (j - q[st]) * ap);
				while(st <= en && f[i-w][q[en]] - ap * (j-q[en]) < f[i-w][j]) -- en;
				q[++en] = j;
			}
			st = 1;en = 0;
			repd(j,mxp,0)
			{
				while(st <= en && q[st] - j > bs) ++ st;
				if(st <= en) f[i][j] = max(f[i][j],f[i-w][q[st]] + (q[st] - j) * bp);
				while(st <= en && f[i-w][q[en]] + bp * (q[en] - j) < f[i-w][j]) -- en;
				q[++en] = j;
			}
		}
		
		rep(j,0,mxp) f[i][j] = max(f[i-1][j],f[i][j]);
	}
	cout << f[n][0] << endl;
	return 0;
}
