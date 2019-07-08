#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
inline char gc()
{
	static char *S,*T,buf[1<<16];
	if(S == T)
	{
		T = (S = buf) + fread(buf,1,1<<16,stdin);
		if(S == T) return EOF;
	} 
	return *S++;
}
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = gc(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = gc(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 60;
int n,m,cnt,ans[N],f[N];
int a[N],b[N],c[N],lf[N],rf[N],pre[N],nxt[N];

inline bool chk(int*a,int x,int y) { return a[lf[x] + y] <= a[y] && a[rf[x] + y] >= a[y]; }

int main()
{
	read(n); read(m);
	rep(i,1,n) read(a[i]),b[a[i]] = i;
	rep(i,1,m) read(c[i]);
	rep(i,1,n) pre[i] = i - 1,nxt[i] = i + 1;
	repd(i,n,1)
	{
		int j = b[i];
		if(pre[j]) lf[i] = a[pre[j]] - i;
		if(nxt[j] <= n) rf[i] = a[nxt[j]] - i;
		nxt[pre[j]] = nxt[j]; pre[nxt[j]] = pre[j];
	}
	rep(i,2,n)
	{
		f[i] = f[i-1]; while(f[i] && !chk(b,f[i] + 1,i)) f[i] = f[f[i]];
		if(chk(b,f[i] + 1,i)) ++ f[i];
	}
	int j = 0;
	rep(i,1,m)
	{
		while(j && !chk(c,j + 1,i)) j = f[j];
		if(chk(c,j + 1,i)) ++ j;
		if(j == n) 
		{
			ans[++ cnt] = i - n + 1;
			j = f[j];
		}
	}
	printf("%d\n",cnt);
	rep(i,1,cnt) printf("%d ",ans[i]);
	puts("");
	return 0;
}
