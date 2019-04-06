#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int M = 6e7 + 50;
const int N = 5e5 + 50;

int n,k; ll a[N];
int rt[N],ls[M],rs[M],num[M],cnt;

void insert(int&x,int y,int d,ll w)
{
	x = ++ cnt;
	ls[x] = ls[y];rs[x] = rs[y];
	num[x] = num[y] + 1;
	if(d == -1) return ;

	if(w & (1LL << d)) insert(rs[x],rs[y],d-1,w);
	else insert(ls[x],ls[y],d-1,w);
}

ll find(int&x,int d,ll w,ll now)
{	
	//if(!num[x]) return 0;
	int y = x;x = ++ cnt; 
	ls[x] = ls[y];rs[x] = rs[y];
	num[x] = num[y] - 1;
	if(d == -1) return now;

	if(w & (1LL << d))
	{
		if(num[ls[x]])
			return find(ls[x],d - 1,w,now | (1LL << d));
		else return find(rs[x],d - 1,w,now);
	}
	else
	{
		if(num[rs[x]])
			return find(rs[x],d - 1,w,now | (1LL << d));
		else return find(ls[x],d - 1,w,now);
	}
}

#define mk(x,y) make_pair(x,y)
priority_queue<pair<ll,int> > q;

ll ans;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
#endif
	read(n); read(k);
	rep(i,1,n) read(a[i]),a[i] = a[i-1]^a[i];
	insert(rt[0],rt[0],40,0);
	rep(i,1,n) insert(rt[i],rt[i-1],40,a[i]);

	rep(i,1,n) q.push(mk(find(rt[i],40,a[i],0),i));

	while(k --)
	{
		pair<ll,int> x = q.top(); q.pop();
		q.push(mk(find(rt[x.second],40,a[x.second],0),x.second));	

		ans += x.first;
		//if(k > 199900)printf("%lld %lld\n",ans,x.first);
	}

	cout << ans << endl;

	return 0;
}
