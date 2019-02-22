#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
using namespace std;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
int n,m;
int c[101][17],d[101];
int f[1<<17],g[1 << 17];

int main()
{
	cin >> n >> m;
	rep(i,1,n) 
	{
		cin >> d[i];
		rep(j,1,m)
			cin >> c[i][j];
	}

	memset(f,0x3f,sizeof f);
	f[0] = 0;
	int s = (1 << m) - 1;

	rep(i,1,n)
	{
		memcpy(g,f,sizeof f);	
		rep(j,0,s) if(g[j] != 0x3f3f3f3f) g[j] += d[i];
		rep(j,0,s) if(g[j] != 0x3f3f3f3f) rep(k,1,m)
			if(!(j & (1 << k - 1)))
				chkmin(g[j|(1<<k-1)],g[j] + c[i][k]);
		rep(j,0,s) chkmin(f[j],g[j]);
	}

	cout << f[s] << endl;
	return 0;
}
