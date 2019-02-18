#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int gcd(int a,int b) { return !b ? a : gcd(b,a%b); }

int ax,ay,bx,by;
inline void solve()
{
	read(ax); read(ay); read(bx); read(by);
	if(ay > by) swap(ax,bx),swap(ay,by);
	if(bx <= ay) return void(printf("%d\n",ay));

	int ans = 1; --ax;--bx;
	for(int i = 1,lst;i <= ay; i = lst + 1)
	{
		if(i > ax)
		{
			lst = min(ay/(ay/i),min(bx/(bx/i),by/(by/i)));
			if(by/i > bx/i) ans = lst;
			continue;	
		}
		lst = min(min(ax/(ax/i),ay/(ay/i)),min(bx/(bx/i),by/(by/i)));

		if(ay/i > ax/i && by/i > bx/i) ans = lst;
	}
	printf("%d\n",ans);
}

int main()
{
	int t ;
	read(t);
	rep(i,1,t)
		solve();
	return 0;
}
