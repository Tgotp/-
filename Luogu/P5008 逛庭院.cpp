#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y ; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y ; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e6 + 50;
int n,m,k;
int w[N],bel[N],tot;
int in[N];
vector<int> v[N],g[N];

int dfn[N],low[N],cnt;
int s[N],top; bool inq[N];
void tarjan(int x)
{
	dfn[x] = low[x] = ++ cnt;
	inq[x] = 1; s[++ top] = x;
	for(auto&i:g[x])
		if(!dfn[i])
		{
			tarjan(i);
			low[x] = min(low[x],low[i]);
		}else if(inq[i]) low[x] = min(low[x],dfn[i]);
	if(low[x] == dfn[x])
	{
		inq[x] = 0; bel[x] = ++ tot; v[tot].push_back(w[x]);
		while(s[top] != x)
		{
			bel[s[top]] = tot;
			v[tot].push_back(w[s[top]]);
			inq[s[top--]] = 0;
		}
		-- top;
	}
}

int a[N],num; ll ans;

int main()
{
	read(n); read(m); read(k);
	rep(i,1,n) read(w[i]);
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		g[u].push_back(v);
	}
	rep(i,1,n) if(!dfn[i]) tarjan(i);

	rep(x,1,n) for(auto&i:g[x])
		if(bel[i] != bel[x])
			++ in[bel[i]];

	rep(i,1,tot)
	{
		if(in[i]) { for(auto&j:v[i]) a[++num] = j; continue; }
			
		sort(v[i].begin(),v[i].end());	
		for(auto&j:v[i]) a[++num] = j;
		a[num - ((int)v[i].size()) + 1] = 0;
	}
	sort(a + 1,a + 1 + num);

	repd(i,num,max(1,num - k + 1)) ans += a[i];

	cout << ans << endl;

	return 0;
}
