#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
inline char gc()
{
	static char *S,*T,buf[1 << 16];
	if(S == T) { T = (S = buf) + fread(buf,1,1<<16,stdin); if(S == T) return EOF; }
	return *S ++;
}
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = gc(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = gc(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 50;
int n,k;
struct DATA { int l,r,id; }a[N];
const bool cmp(DATA a,DATA b) { return a.l < b.l; }
priority_queue<int,vector<int>,greater<int> >s;
int res,l,r;

int main()
{
	read(n); read(k);
	rep(i,1,n) { read(a[i].l); read(a[i].r);a[i].id= i; }
	sort(a + 1,a + 1 + n,cmp);
	rep(i,1,k-1) s.push(a[i].r);
	rep(i,k,n)
	{
		s.push(a[i].r);
		if(chkmax(res,s.top() - a[i].l))
			l = a[i].l,r = s.top();
		s.pop();
	}
	printf("%d \n",res);
	rep(i,1,n) if(a[i].l <= l && a[i].r >= r && k)
		printf("%d " ,a[i].id),-- k;
	return 0;
}
