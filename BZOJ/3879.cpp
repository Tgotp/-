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

const int N = 5e5 + 50;
const ll mod = 23333333333333333;
char s[N];
int n,m,a[3030000];

int buc[N],sa[N],rk[N],x[N<<1],y[N<<1];
int h[N][21],lg[N];

inline void GET_SA()
{
	int m = 233;
	rep(i,1,n) ++ buc[x[i] = s[i]];
	rep(i,1,m) buc[i] += buc[i-1];
	repd(i,n,1) sa[buc[x[i]]--] = i;
	for(register int k = 1;k <= n; k <<= 1)
	{
		int p = 0;
		repd(i,n,n-k+1) y[++ p] = i;
		rep(i,1,n) if(sa[i] > k) y[++ p] = sa[i] - k;

		rep(i,1,m) buc[i] = 0;
		rep(i,1,n) ++ buc[x[i]];
		rep(i,1,m) buc[i] += buc[i-1];
		repd(i,n,1) sa[buc[x[y[i]]] --] = y[i];

		swap(x,y); x[sa[1]] = p = 1;
		rep(i,2,n)
			if(y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k])
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
		int t = sa[rk[i]-1];
		while(t + p <= n && i + p <= n && s[i+p] == s[t+p]) ++ p;
		h[rk[i]][0] = p;
		p = max(p-1,0);
	}
	
	rep(j,1,20) rep(i,1,n) if(i+(1<<j-1) <= n)
		h[i][j] = min(h[i][j-1],h[i+(1<<j-1)][j-1]);
	
	rep(i,2,n) lg[i] = lg[i>>1] + 1;
}

inline int get(int l,int r)
{
	++ l; int k = lg[r - l + 1];
	return min(h[l][k],h[r-(1<<k)+1][k]);
}

ll ans;

int pos[N],num[N],top;ll sum[N];

inline void solve(int n)
{
	top = ans = 0;
	rep(i,1,n) a[i] = rk[a[i]];
	sort(a + 1,a + 1 + n);
	n = unique(a + 1,a + 1 + n) - a - 1;
	rep(i,2,n)
	{
		int b = get(a[i-1],a[i]),q = 1;
		while(top && pos[top] > b)
		{
			q += num[top];
			top--;
		}
			
		if(top && pos[top] == b)
			num[top] += q,sum[top] += 1ll * b * q;
		else
		{
			pos[++ top] = b;
			num[top] = q;
			sum[top] = 1ll * b * num[top] + sum[top-1];
		}

		ans += sum[top];
	}

#ifndef ONLINE_JUDGE
	ll res = 0;
	rep(i,2,n) rep(j,1,i-1)
		res += get(a[j],a[i]);
	cout << res << endl;
#endif
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("11.out","w",stdout);
#endif
	read(n); read(m);
	scanf("%s",s + 1);

	GET_SA();

	while(m --)
	{
		int t; read(t);
		rep(i,1,t) read(a[i]);

		solve(t);

		printf("%lld\n",ans);
		#ifndef ONLINE_JUDGE
		break;
		#endif
	}
	return 0;
}
