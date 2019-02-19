#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int n,num[1 << 21];
double p[1 << 21],ans;
double t[1 << 21];

int main()
{
	read(n);
	int s = (1 << n) - 1;
	rep(i,0,s)
	{
		scanf("%lf",&p[i]); t[i] = p[i];
		num[i] = num[i >> 1] + (i & 1);
	}

	rep(j,1,n)
		repd(i,s,0) 
			if((i & (1 << j - 1)) == 0)
				p[(1 << j - 1) | i] += p[i];
	
	rep(j,1,n)
		repd(i,s,0) 
			if((i & (1 << j - 1)) == 0)
				t[i] += t[i|(1 << j - 1)];
	
	rep(i,1,n) if(t[1 << i - 1] < 1e-10) return puts("INF"),0;
	
	rep(i,1,s) 
		ans += (num[i]&1?1:-1) / (1 - p[s^i]);
	
	printf("%.10lf\n",ans);
	return 0;
}
