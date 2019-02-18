#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0 ;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
int main()
{
	int n;
	read(n);
	multiset<int> s;
	ll ans = 0;
	rep(i,1,n)
	{
		int num,w;
		read(num);
		rep(j,1,num)
		{
			read(w);	
			s.insert(w);
		}
		multiset<int>::iterator it;
		it = s.begin();
		ans -= *it;
		s.erase(it);
		it = s.end(); -- it;
		ans += *it;
		s.erase(it);
	}
	cout << ans << endl;
	return 0;
}
