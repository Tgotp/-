#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i) 
using namespace std; 
template<typename T>inline void read(T&x)
{
	char c;int sign = 1; x = 0;
	do { c = getchar(); if(c == '-') c = getchar(); }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 1e3 + 50;
int n,m,cnt;
int a[N][N],sz[N * N];
bool vis[N][N];

int X[4] = {-1,0,1,0};
int Y[4] = {0,1,0,-1};
int w[4] = {8,4,2,1};

void dfs(int x,int y)
{
	vis[x][y] = 1; ++ sz[cnt];
	rep(i,0,3) 
		if((a[x][y] & w[i]) == 0)
		{
			int xx = x + X[i];
			int yy = y + Y[i];
			if(xx <= 0 || yy <= 0 || xx > n || yy > m || vis[xx][yy]) 
				continue;
			
			if((a[xx][yy] & w[(i + 2) % 4]) == 0)
			
			dfs(xx,yy);
		}
}

int main()
{
	read(n); read(m);
	
	rep(i,1,n) rep(j,1,m) read(a[i][j]);
	
	rep(i,1,n) rep(j,1,m) if(!vis[i][j])
	{
		++ cnt;
		dfs(i,j);
	}
	
	sort(sz + 1,sz + 1 + cnt);
	reverse(sz + 1,sz + 1 + cnt);
	
	rep(i,1,cnt) printf("%d ",sz[i]);
	
	return 0;
 } 
