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

const int N = 22;
int n,m;
int id[N][N];
char s1[N][N],s2[N][N],s3[N][N];
int x[9] = {0,1,1,1,-1,-1,-1,0,0};
int y[9] = {0,1,0,-1,1,0,-1,-1,1};

const int M = N * N * 3,K = M << 6;
int head[M],nxt[K],to[K],f[K],w[K],tot;

inline void add(int x,int y,int flow,int val)
{
	to[tot] = y;
	w[tot] = val;
	f[tot] = flow;
	nxt[tot] = head[x];
	head[x] = tot ++;
}

int s,t;
int d[M],from[M];
#define mk(x,y) make_pair(x,y)

inline bool bfs()
{
	priority_queue<pair<int,int> > q;
	memset(d,0x3f,sizeof d);d[s] = 0;
	q.push(mk(0,s));
	while(!q.empty())
	{
		int x = q.top().second; q.pop();
		for(register int i = head[x];~i;i=nxt[i])
			if(f[i] && d[to[i]] > d[x] + w[i])
			{
				d[to[i]] = d[x] + w[i];
				from[to[i]] = i;
				q.push(mk(-d[to[i]],to[i]));
			}
	}
	return d[t] < 0x3f3f3f3f;
}

inline int get()
{
	int flow = INT_MAX; from[s] = -1;
	int ans = 0;
	for(register int i = from[t];~i; i = from[to[i^1]])
		flow = min(flow,f[i]);
	for(register int i = from[t];~i; i = from[to[i^1]])
		ans += flow * w[i],f[i] -= flow,f[i^1] += flow;
	return ans;
}

int main()
{
	memset(head,-1,sizeof head);
	read(n); read(m);
	rep(i,1,n) scanf("%s",s1[i] + 1);
	rep(i,1,n) scanf("%s",s2[i] + 1);
	rep(i,1,n) scanf("%s",s3[i] + 1);

	int z = n * m ,q = 2 * n * m; t = n*m*3+5;
	rep(i,1,n) rep(j,1,m) id[i][j] = m * (i - 1) + j;
	rep(i,1,n) rep(j,1,m)
		if(s1[i][j] == s2[i][j])
		{
			add(id[i][j]+z,id[i][j],(s3[i][j]-'0')/2,0); add(id[i][j],id[i][j]+z,0,0);
			add(id[i][j],id[i][j]+q,(s3[i][j]-'0')/2,0); add(id[i][j]+q,id[i][j],0,0);
		}
		else if(s1[i][j] == '1')
		{
			add(s,id[i][j],1,0); add(id[i][j],s,0,0);

			add(id[i][j]+z,id[i][j],(s3[i][j]-'0')/2,0); add(id[i][j],id[i][j]+z,0,0);
			add(id[i][j],id[i][j]+q,(s3[i][j]-'0'+1)/2,0); add(id[i][j]+q,id[i][j],0,0);
		}
		else
		{
			add(id[i][j],t,1,0); add(t,id[i][j],0,0);

			add(id[i][j]+z,id[i][j],(s3[i][j]-'0'+1)/2,0); add(id[i][j],id[i][j]+z,0,0);
			add(id[i][j],id[i][j]+q,(s3[i][j]-'0')/2,0); add(id[i][j]+q,id[i][j],0,0);
		}
	rep(i,1,n) rep(j,1,m)
		rep(k,1,8)
		{
			int xx = i + x[k],yy = j + y[k];
			if(!xx || !yy || xx > n || yy > m) continue;
			add(id[i][j] + q,id[xx][yy] + z,1000,1);
			add(id[xx][yy] + z,id[i][j] + q,0,-1);
		}
	
	int ans = 0;
	while(bfs())
		ans += get();
	
	for(register int i = head[t];~i;i=nxt[i])
		if(f[i] == 0) ans = -1;
	for(register int i = head[s];~i;i=nxt[i])
		if(f[i] == 1) ans = -1;
	cout << ans << endl;

	return 0;
}
