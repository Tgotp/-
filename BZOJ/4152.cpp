#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y ,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int n;
bool vis[N];

int head[N],to[N << 3],nxt[N << 3],w[N << 3],tot;
inline void add(int x,int y,int val)
{
	to[tot] = y;
	w[tot] = val;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

vector<pair<int,int> > a1,a2;
priority_queue<pair<int,int> > q;
#define mk(x,y) make_pair(x,y)

int d[N];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2.in","r",stdin);
	//freopen("20.out","w",stdout);
#endif
	memset(head,-1,sizeof head);
	read(n);
	a1.push_back(mk(0,0));
	a2.push_back(mk(0,0));
	rep(i,1,n)
	{
		int x,y;read(x); read(y);
		a1.push_back(mk(x,i));
		a2.push_back(mk(y,i));
	}

	sort(a1.begin(),a1.end());
	sort(a2.begin(),a2.end());

	rep(i,2,n) 
		add(a1[i].second,a1[i-1].second,a1[i].first - a1[i-1].first),
		add(a1[i-1].second,a1[i].second,a1[i].first - a1[i-1].first);

	rep(i,2,n) 
		add(a2[i].second,a2[i-1].second,a2[i].first - a2[i-1].first),
		add(a2[i-1].second,a2[i].second,a2[i].first - a2[i-1].first);

	q.push(mk(0,1));
	memset(d,0x3f,sizeof d);
	d[1] = 0;
	while(!q.empty())
	{
		int x = q.top().second;q.pop();
		if(x == n) break; if(vis[x]) continue; vis[x] = 1;
		for(register int i = head[x];~i;i=nxt[i])
			if(chkmin(d[to[i]],d[x] + w[i]))
				q.push(mk(-d[to[i]],to[i]));
	}

	printf("%d\n",d[n]);
	return 0;
}
