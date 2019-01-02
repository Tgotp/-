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

const int N = 20,mod = 1e8 + 7;
int x[N],y[N],in[N][N];
int n;

inline int cross(int ax,int ay,int bx,int by) { return ax * by - ay * bx; }

inline bool check(int a,int b,int c)
{
	if(x[a] > x[b]) swap(a,b);
	if(x[a] == x[b])
	{
		if(x[c] != x[a]) return 0;
		return y[c] <= max(y[a],y[b]) && y[c] >= min(y[a],y[b]);
	}
	if(x[c] > x[b] || x[c] < x[a]) return 0;
	return cross(x[c]-x[a],y[c]-y[a],x[b]-x[a],y[b]-y[a]) == 0;
}

int f[1 << N][N],id[N],ans;

int main()
{
	read(n);
	rep(i,1,n) { read(x[i]); read(y[i]); }
	rep(i,1,n) id[i] = 1 << i - 1;
	rep(i,1,n) rep(j,i+1,n) if(i != j) rep(k,1,n)
		if(k != i && k != j && check(i,j,k))
			in[i][j] |= id[k],
			in[j][i] |= id[k];

	rep(j,1,n) f[id[j]][j] = 1;
	int s = (1 << n) - 1;
	rep(i,0,s) rep(j,1,n)
	{
		if(!f[i][j]) continue;
		rep(k,1,n)
		{
			if(i&id[k]) continue;
			if((in[j][k]&i)!=in[j][k]) continue;
			f[i|id[k]][k] = (f[i][j] + f[i|id[k]][k]) % mod;
		}
		if(__builtin_popcount(i) >= 4) ans = (ans + f[i][j]) % mod;
	}
	cout << ans << endl;
	return 0;
}
