#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++i)
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

const int N = 5e5 + 50;
int nxt[N],lst[N],val[N],sum[N],jl[N],a[N],b[N],c[N],id[N];
int n,q,cnt; char s[5]; bool op[N];
map<int,int> mp;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
	freopen("22.out","w",stdout);
#endif
	read(n);
	c[++cnt] = 1;
	rep(i,1,n)
	{
		read(a[i]); read(b[i]);
		c[++cnt] = a[i];c[++cnt] = b[i];
		if(a[i]!=1)c[++cnt] = a[i]-1;c[++cnt] = a[i]+1;
		if(b[i]!=1)c[++cnt] = b[i]-1;c[++cnt] = b[i]+1;
	}

	read(q);
	rep(i,1,q)
	{
		scanf("%s",s + 1);
		op[i] = s[1] == 'L';
		read(jl[i]);
		c[++cnt] = jl[i];
		c[++cnt] = jl[i] + 1;
	}

	sort(c + 1,c + 1 + cnt);
	cnt = unique(c + 1,c + 1 + cnt) - c - 1;

	c[cnt + 1] = c[cnt] + 1; 
	nxt[0] = 1;
	rep(i,1,cnt)
	{
		nxt[i] = i + 1;
		lst[i] = i - 1;
		mp[c[i]] = i;
		val[i] = c[i+1] - c[i];
	}
	
	rep(i,1,n)
	{
		a[i] = mp[a[i]];b[i] = mp[b[i]];
		nxt[lst[a[i]]] = nxt[a[i]];
		lst[nxt[a[i]]] = lst[a[i]];
		lst[a[i]] = lst[b[i]];
		lst[b[i]] = a[i];
		nxt[lst[a[i]]] = a[i];
		nxt[a[i]] = b[i];
	}

	int now = nxt[0];
	
	rep(i,1,cnt)
	{
		a[i] = now;
		sum[i] = sum[i-1] + val[now];
		id[now] = i;
		now = nxt[now];
	}

/*
	puts("");
	cout << cnt << endl; rep(i,1,cnt) printf("%d ",c[i]);
	puts("");
	rep(i,1,cnt)
		printf("%d ",a[i]);
	puts("");
	rep(i,1,cnt)
		printf("%d ",sum[i]);
	puts("");
	puts("");
*/

	rep(i,1,q)
	{
		int x = jl[i];
		if(op[i] == 1)	
		{
			int pos = lower_bound(sum + 1,sum + 1 + cnt,x) - sum;	
			printf("%d\n",c[a[pos]] + x - sum[pos-1] - 1);
		}
		else
		{
			int w = lower_bound(c + 1,c + 1 + cnt,x) - c;
			printf("%d\n",sum[id[w]]);
		}
	}
	return 0;
}
