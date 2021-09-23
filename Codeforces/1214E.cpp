#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
using namespace std;
template<typename T> inline void read(T & x)
{
	x = 0;char c;int sign = 1;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int n,t[N],f[N];
bool k[N];

struct STR { int w,id,pos; }d[N];

const bool cmp(STR a,STR b) { return a.w > b.w; }

int main()
{
	read(n);
	rep(i,1,n) read(d[i].w),d[i].id = i;
	
	sort(d + 1,d + 1 + n,cmp);
	
	int st = 1,en = 0;
	rep(i,1,n)
	{
		t[++ en] = 2 * d[i].id; d[i].pos = i;
		if(d[i].w == 1) t[++ en] = 2 * d[i].id - 1,k[i] = 1;
		else if(en - st + 1 >= d[i].w) f[2 * d[i].id - 1] = t[en - d[i].w + 1],k[i] = 1;
	}
	
	rep(i,1,n) if(!k[i]) 
	{
		if(d[i].pos + d[i].w - 1 < en) f[2 * d[i].id - 1] = t[d[i].pos + d[i].w - 1];
		else if(d[i].pos + d[i].w - 1 == en) t[++ en] = 2 * d[i].id - 1; 
		else puts("ERROR"); 
	}
	
	
	rep(i,st + 1,en) printf("%d %d\n",t[i - 1],t[i]);
	
	rep(i,1,2 * n) if(f[i]) printf("%d %d\n",f[i],i);
	
	return 0;
 } 
