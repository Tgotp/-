#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
template<typename T> inline void read(T & x)
{
	x = 0;char c;int sign = 1;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
 
int s,n,t,k,res,a[101],num[10];
 
void dec(int x)
{
	if(res >= n || x == 0 || !num[x]) return ;
	-- num[x]; num[x - 1] += 10; res += 9;
	while(num[x - 1] && x - 1 && res < n) dec(x - 1);
}
 
inline void solve()
{
	k = 0;res = 0;t = 1;
	memset(num,0,sizeof num);
	memset(a,0,sizeof a);
	
	read(s); read(n);
	while(s) num[k ++] = s % 10,s /= 10;
	rep(i,0,10) res += num[i];
	rep(i,1,10)
	{
		if(res >= n) break;
		while(num[i] && res < n) dec(i);
	}
	
	k = 0;
	rep(i,1,n)
	{
		while(!num[k]) ++k,t *= 10;
		a[i] = t; -- num[k];
	}
	while(k <= 9)
	{
		a[n] += num[k] * t;
		
		++k; t *= 10;
	}
	
	rep(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
}
 
int main()
{
	int t;
	read(t);
	while(t --) solve();
	return 0;
}
