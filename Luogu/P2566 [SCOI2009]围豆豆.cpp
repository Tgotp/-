// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x =0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

int n,m,d;
int dw[10],dx[10],dy[10];
char s[12][12];

int X[5] = {0,0,0,1,-1};
int Y[5] = {0,1,-1,0,0};

struct DATA
{
	int w,sta,x,y;

	DATA(){}
	DATA(int _w,int _sta,int _x,int _y)
	{
		w = _w; sta = _sta; x = _x; y = _y;
	}

	bool operator < (DATA b)const { return w > b.w; }
};

priority_queue<DATA> q;

int f[11][11][1 << 10],ans;

inline void SPFA(int sx,int sy)
{
	f[sx][sy][0] = 0;
	q.push(DATA(0,0,sx,sy));

	while(!q.empty())
	{
		DATA a = q.top(); q.pop();
		if(a.x == sx && a.y == sy) chkmax(ans,a.w);

		rep(i,1,4)
		{
			int nx = a.x + X[i],ny = a.y + Y[i];
			if(nx <= 0 || nx > n || ny <= 0 || ny > m || s[nx][ny] != '0') continue;

			int k = a.sta,w = 0;
			rep(j,1,d) if(i >= 3 && min(a.x,nx) == dx[j] && a.y < dy[j])
			{
				k ^= 1 << j - 1;
				w += (k & (1 << j - 1) ? 1 : -1) * dw[j];
			}

			if(chkmax(f[nx][ny][k],f[a.x][a.y][a.sta] + w - 1))
				q.push(DATA(f[nx][ny][k],k,nx,ny));
		}
	}
}

int main()
{
	memset(f,-0x3f,sizeof f);
	read(n); read(m); read(d);
	rep(i,1,d) read(dw[i]);
	rep(i,1,n) scanf("%s",s[i] + 1);
	rep(i,1,n) rep(j,1,m) if(s[i][j] != '0')
		rep(k,1,d) if(s[i][j] == k + '0')
			dx[k] = i,dy[k] = j;
	rep(i,1,n) rep(j,1,m)
		if(s[i][j] == '0')
			SPFA(i,j);
	cout << ans << endl;
	 
	return 0;
}
