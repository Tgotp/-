#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y,1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y,1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 1e3 + 50;
int n;
struct DATA
{
	int x,y;
	double k;
	DATA(){}
	#define eps 1e-9
	DATA(int _x,int _y) { x = _x,y = _y; k = y/(double)x; }

	inline bool operator < (const DATA a) const { return k < a.k; }
}b[N];
vector<DATA>a[N];
ll ans = 4e18;

inline ll cross(DATA a,DATA b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	read(n);
	rep(i,1,n) read(b[i].x), read(b[i].y);
	rep(i,1,n) rep(j,i + 1,n)
	{
		a[i].push_back(DATA(b[j].x - b[i].x,b[j].y - b[i].y));
		a[j].push_back(DATA(b[i].x - b[j].x,b[i].y - b[j].y));
	}
	rep(i,1,n) sort(a[i].begin(),a[i].end());
	rep(i,1,n)
	{
		int sz = a[i].size(); -- sz;
		if(sz == 0) continue;
		chkmin(ans,abs(cross(a[i][0],a[i][sz])));	
		rep(j,0,sz-1)
			chkmin(ans,abs(cross(a[i][j],a[i][j+1])));	
	}
	cout << fixed << setprecision(2) << 0.5 * ans << endl;
	return 0;
}
