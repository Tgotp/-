#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
int n,m;
int f[45010];
int main()
{
#define read(x) scanf("%d",&x)
	read(m); read(n);
	rep(i,1,n)
	{
		int x;
		read(x);
		repd(j,m,x)
			chkmax(f[j],f[j-x] + x);
	}
	cout << f[m] << endl;
	return 0;
}
