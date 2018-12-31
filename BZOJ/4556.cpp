#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y;-- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x= 0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x=  x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e5 + 50;
int n,m;
char s[N];
int sa[N],rk[N],buc[N],x[N],y[N],h[N][21];
inline void Get_Sa()
{
	int m = 27;
	rep(i,1,n) ++ buc[x[i] = s[i] - 'a'];
	rep(i,1,m) buc[i] += buc[i-1];
	repd(i,n,1) sa[buc[x[i]]--] = i;
	for(int k = 1;k <= n;k <<= 1)
	{
		int p = 0;	
		repd(i,n,n-k+1) y[++p] = i;
		rep(i,1,n) if(sa[i] > k) y[++p] = sa[i] - k;
		rep(i,0,m) buc[i] = 0;
		rep(i,1,n) ++ buc[x[i]];
		rep(i,1,m) buc[i] += buc[i-1];
		repd(i,n,1) sa[buc[x[y[i]]]--] = y[i];
		swap(x,y); x[1] = p = 0;
		rep(i,1,n)
			if(y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i-1] + k])
				x[sa[i]] = p;
			else x[sa[i]] = ++ p;
		if(p == n) break;
		m = p;
	}

	rep(i,1,n) rk[sa[i]] = i;
	int p = 0;
	rep(i,1,n)
	{
		if(rk[i] == 1) continue;
		int t = sa[rk[i] - 1];
		while(i + p <= n && t + p <= n && s[i + p] == s[t + p]) ++ p;
		h[rk[i]][0] = p;
		p = max(0,p-1);
	}
}

const int M = N * 20;
int rt[N],ls[M],rs[M],val[M],sz;

void insert(int&x,int y,int l,int r,int pos)
{
	x = ++ sz; ls[x] = ls[y]; rs[x] = rs[y];
	if(l == r) return void (val[x] = 1);
	int mid = l + r >> 1;
	if(pos <= mid) insert(ls[x],ls[y],l,mid,pos);
	else insert(rs[x],rs[y],mid+1,r,pos);
	val[x] = val[ls[x]] + val[rs[x]];
}

int query(int x,int y,int l,int r,int L,int R)
{
	if(l == L && r == R) return val[x] - val[y];
	int mid = l + r >> 1;
	if(R <= mid) return query(ls[x],ls[y],l,mid,L,R);
	else if(L > mid) return query(rs[x],rs[y],mid+1,r,L,R);
	else return max(query(ls[x],ls[y],l,mid,L,mid),query(rs[x],rs[y],mid+1,r,mid+1,R));
}

int lg[N];
inline int find(int l,int r)
{
	int len = r - l + 1;
	int k = lg[len];
	return min(h[l][k],h[r - (1 << k) + 1][k]);
}

inline bool check(int x,int y,int a,int b)
{
	int L = x + 1,R = x;
	int l = 1,r = x,mid;
	while(l <= r)
	{
		if(find(1 + (mid = l + r >> 1),x) >= y) L = mid,r = mid - 1;
		else l = mid + 1;
	}
	l = x + 1,r = n;
	while(l <= r)
	{
		if(find(x + 1,mid = l + r >> 1) >= y) R = mid,l = mid + 1;
		else r = mid - 1;
	}
	if(R < L) return 0;
	return query(rt[R],rt[L-1],1,n,a,b - y + 1);
}

int main()
{
	read(n); read(m);
	scanf("%s",s + 1);
	Get_Sa();
	rep(i,1,n) insert(rt[i],rt[i-1],1,n,sa[i]);
	rep(i,2,n) lg[i] = lg[i >> 1] + 1;
	rep(j,1,20) rep(i,1,n) if(i + (1<<j-1)<=n)h[i][j] = min(h[i][j-1],h[i+(1<<j-1)][j-1]);
	rep(i,1,m)
	{
		int a,b,c,d;
		read(a); read(b); read(c); read(d);
		int l = 1,r = min(d - c + 1,b - a + 1),mid;
		while(l <= r)
		{
			if(check(rk[c],mid = l + r >> 1,a,b)) l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n",l - 1);
	}
	return 0;
}
