#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 2e5 + 50;
int n;
char s[N];

map<pair<int,int>,int> mp;

int a,b,c,ans;

int main()
{
	read(n);
	#define mk(x,y) make_pair(x,y)
	mp[mk(0,0)] = 0;
	scanf("%s",s + 1);
	rep(i,1,n)
	{
		if(s[i] == 'J') ++ a;		
		if(s[i] == 'O') ++ b;		
		if(s[i] == 'I') ++ c;		
		if(mp.count(mk(b - a,c - a)))
			chkmax(ans,(int)(i - mp[mk(b - a,c - a)]));
		else mp[mk(b - a,c - a)] = i;
	}
	cout << ans << endl;
	return 0;
}
