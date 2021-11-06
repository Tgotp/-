#include<bits/stdc++.h>
#define lowbit(x) (x & (-x))
#define rep(i,x,y) for(register int i = x;i <= y; ++ i) 
using namespace std; 
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') c = getchar(); }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 1e6 + 60;
int n,m;
int a[N],b[N],t[N],id[N];
priority_queue<int> q;

const bool cmp(int x,int y) { return a[x] < a[y]; }

inline void add(int pos)
{
	for(int i = pos; i <= n; i += lowbit(i))
		++ t[i];
}

inline int find(int pos)
{
	int ans = 0;
	for(int i = pos; i ; i -= lowbit(i))
		ans += t[i];
	return ans;
}

inline void solve()
{
	read(n); read(m);
	rep(i,1,n) read(a[i]);
	rep(i,1,m) read(b[i]);
	sort(b + 1 ,b + 1 + m);
	
	long long ans = 0;
	rep(i,1,n)
	{
		int x = lower_bound(b + 1,b + 1 + m,a[i]) - b - 1;
		int y = upper_bound(b + 1,b + 1 + m,a[i]) - b - 1;
		ans += x;

		q.push(x); q.push(y); q.pop();
	}

	while(!q.empty()) ans -= q.top(),q.pop();

//	printf("111:%d\n",ans);

	rep(i,1,n) id[i] = i;

	sort(id + 1,id + 1 + n,cmp);
	reverse(id + 1,id + 1 + n);

//	rep(i,1,n) printf("%d%c",id[i],i==n?'\n':' ');

	rep(i,1,n) 
	{
		ans += find(id[i] - 1);
//		printf("%d:%d %d\n",i,find(id[i] - 1),id[i]);
		add(id[i]);
	}

	rep(i,1,n) t[i] = 0;
	printf("%lld\n",ans);
}

int main()
{
	int t;
	read(t);
	while(t -- ) solve();
	return 0;
}
