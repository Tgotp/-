#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
using namespace std;

long long f[55];

int t,n;

int main()
{
	f[1] = 1;
	rep(i,2,44) f[i] = f[i-1] + f[i-2];
	cin >> t;
	while(t --)
	{
		cin >> n;
		bool e = 0;
		if(n == 0) e = 1;
			
		rep(i,1,44) rep(j,1,44) 
			if(f[i] * f[j] == n) e = 1;
		
		puts(e ? "TAK" : "NIE");
	}
	return 0;
}
