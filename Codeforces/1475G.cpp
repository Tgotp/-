#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i) 
using namespace std; 
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') c = getchar(); }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int f[N],num[N],ans,MX,n;

inline void solve()
{
	memset(f,0,sizeof f);
	memset(num,0,sizeof num);
	MX = 0; ans = 0;
	
	read(n);
	
	rep(i,1,n) 
	{
		int x;
		read(x);
		++ num[x];
		MX = max(MX,x);
	}
	rep(i,1,MX) if(num[i])
	{
		f[i] = max(f[i],num[i]);
		ans = max(ans,f[i]);
		for(int j = i * 2;j <= MX; j += i)
			if(num[j])
				f[j] = max(f[j],f[i] + num[j]);
	}
	cout << n - ans << endl;
}

int main()
{
//	freopen("1.txt","r",stdin);
	int t;
	read(t);
	while(t--) solve();
	
	return 0;	
}
