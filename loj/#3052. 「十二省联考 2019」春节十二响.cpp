#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int m[N],sz[N],hson[N],rt[N],n;

ll ans;
vector<int> g[N];
priority_queue<int> s[50];

void dfs(int x)
{
	sz[x] = 1;
	for(auto&i:g[x])
	{
		dfs(i);
		sz[x] += sz[i];
		if(sz[i] > sz[hson[x]])
			hson[x] = i;
	}

}

int Tak[50],top,cnt;

inline void add(int&x,int y)
{
	if(!x) x = top ? Tak[top--]: ++ cnt;
	s[x].push(y);
}

int l[N],tot;
inline int merge(int x,int y)
{
	if(s[x].size() < s[y].size()) swap(x,y);
	
	tot = 0;
	while(!s[y].empty())
	{
		int x1 = s[x].top(),x2 = s[y].top();
		s[x].pop(); s[y].pop();
		l[++tot] = max(x1,x2);
	}
	
	rep(i,1,tot) s[x].push(l[i]);

	Tak[++top] = y;

	return x;
}

void dfs2(int x)
{
	if(hson[x]) 
	{
		dfs2(hson[x]);
		rt[x] = rt[hson[x]];
	}

	for(auto&i:g[x])
		if(i != hson[x])
		{
			dfs2(i);
			rt[x] = merge(rt[x],rt[i]);
		}
	add(rt[x],m[x]);
}

int main()
{
	read(n);
	rep(i,1,n) read(m[i]);

	rep(i,2,n)
	{
		int fa;
		read(fa);
		g[fa].push_back(i);
	}

	dfs(1);

	dfs2(1);
	
	while(!s[rt[1]].empty())
		ans += s[rt[1]].top(),s[rt[1]].pop();
		
	cout << ans << endl;

	return 0;
}
