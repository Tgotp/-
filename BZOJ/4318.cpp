#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0';c = getchar(); }while(isdigit(c));
	x *= sign;
}
int n;
double g,l,x,ans;
int main()
{
	read(n);
	rep(i,1,n)
	{
		scanf("%lf",&x);
		ans += (3*g+3*l+1) * x;
		g = (g + 2*l + 1) * x;
		l = (l + 1) * x;
	}
	printf("%.1lf\n",ans);
	return 0;
}
