#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 4e4 + 50;
int a[N],b[N],c[N],z[N],q,n;
int k[3002][3002],bel[N],num,res;
int vis[N],vised;

int rt[N],ls[N * 20],rs[N * 20],val[N * 20],sz;
void insert(int&x,int y,int l,int r,int pos)
{
	x = ++ sz; val[x] = val[y]; ls[x] = ls[y];rs[x] = rs[y];
	int mid = l + r >> 1;
	if(mid == pos) return void(++ val[x]);
	if(pos < mid) insert(ls[x],ls[y],l,mid-1,pos);
	else insert(rs[x],rs[y],mid+1,r,pos);
}

int find(int x,int y,int l,int r,int pos)
{
	int mid = l + r >> 1;
	if(mid == pos) return val[x] - val[y];
	if(pos < mid) return find(ls[x],ls[y],l,mid-1,pos);
	else return find(rs[x],rs[y],mid+1,r,pos);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("7.in","r",stdin);
	freopen("8.out","w",stdout);
#endif
	read(n); read(q);
	rep(i,1,n) read(a[i]),b[i] = a[i];
	sort(b + 1,b + 1 + n);
	rep(i,1,n)
	{
		int pos = lower_bound(b + 1,b + 1 + n,a[i]) - b;
		c[pos] = a[i];
		a[i] = pos;
	}
	
	rep(i,1,n) insert(rt[i],rt[i-1],1,n,a[i]);

	int d = max((int)pow(n,1.0/4),1);
	//printf("%d\n",n/d);
	rep(i,1,n) bel[i] = i / d;
	int l = 0;
	while(l < n)
	{
		int r = max(0,l-1);
		res = 0;
		while(r < n)
		{
			if(bel[r] != bel[r+1])
				k[bel[l]][bel[r]] = res;	
			++ z[a[++ r]];	
			if(z[a[r]] == z[res] && c[a[r]] < c[res])
				res = a[r];
			if(z[a[r]] > z[res]) 
				res = a[r];
		}
		r = max(0,l-1);
		while(r < n) -- z[a[++r]];

		l += d;
	}

	//cout << fixed << setprecision(3) << clock()/(double) CLOCKS_PER_SEC << endl;

	int lstans = 0;
	while(q -- )
	{
		int l,r;
		read(l); read(r);
		l = (l + lstans - 1) % n + 1;
		r = (r + lstans - 1) % n + 1;
		if(r < l) swap(l,r);
		//printf("\n%d %d %d %d\n",l,r,bel[l],bel[r]);
		if(bel[l] + 1 >= bel[r])
		{
			res = 0;
			rep(i,l,r)
			{
				++ z[a[i]];
				if(z[a[i]] == z[res] && c[a[i]] < c[res])
					res = a[i];
				if(z[a[i]] > z[res])
					res = a[i];
			}
			rep(i,l,r) -- z[a[i]];
			printf("%d\n",lstans=c[res]);
		}
		else 
		{
			int t = k[bel[l] + 1][bel[r] - 1];	
			++vised; vis[t] = vised;
			int num = find(rt[r],rt[l-1],1,n,t);
			rep(i,l,n) if(vis[a[i]] != vised)
			{
				vis[a[i]] = vised;
				int n2 = find(rt[r],rt[l-1],1,n,a[i]);
				if(n2 == num && c[a[i]] < c[t]) t = a[i],num=n2;
				if(n2 > num) t = a[i],num = n2;
				if(bel[i+1] != bel[i]) break;
			}
			repd(i,r,1) if(vis[a[i]] != vised)
			{
				vis[a[i]] = vised;
				int n2 = find(rt[r],rt[l-1],1,n,a[i]);
				if(n2 == num && c[a[i]] < c[t]) t = a[i],num=n2;
				if(n2 > num) t = a[i],num = n2;
				if(bel[i-1] != bel[i]) break;
			}
			printf("%d\n",lstans=c[t]);
		}
	}
	//cout << fixed << setprecision(3) << clock()/(double) CLOCKS_PER_SEC << endl;
	return 0;
}
