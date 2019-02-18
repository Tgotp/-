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

const int N = 1e5 + 50;
int n,m,in[N],out[N];
int head[N],nxt[N << 1],to[N << 1],w[N << 1],tot;

inline void add(int x,int y,int val)
{
	to[tot] = y;
	w[tot] = val;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

double p[N],ans;
inline void toposort()
{
	p[1] = 1;
	queue<int> q;
	rep(i,1,n) if(!in[i]) q.push(i);

	while(!q.empty())
	{
		int x = q.front(); q.pop(); p[x] /= out[x];
		for(register int i = head[x];~i;i=nxt[i])
		{
			-- in[to[i]];
			ans += w[i] * p[x];
			p[to[i]] += p[x];
			if(in[to[i]] == 0) q.push(to[i]);
		}
	}
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m);

	rep(i,1,m)
	{
		int u,v,w;
		read(u); read(v); read(w);
		add(u,v,w); ++ in[v]; ++ out[u];
	}

	toposort();
	printf("%.2lf\n",ans);

	return 0;
}
