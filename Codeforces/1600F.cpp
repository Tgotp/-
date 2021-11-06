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

const int N = 2e5 + 50;

int n,m,a[6];
set<int> s[N]; 
int main()
{
	read(n); read(m);
	
	rep(i,1,m)
	{
		int u,v;
		read(u); read(v);
		s[u].insert(v);
		s[v].insert(u);
	}
	
	rep(qqqq,1,1000000)
	{
		rep(i,1,5)
			a[i] = rand() % n + 1;
			
		bool flag = 1;
		int k = s[a[1]].count(a[2]);
		
		rep(i,1,5) rep(j,i + 1,5)
			if(a[i] == a[j] || k != s[a[i]].count(a[j]))
			{
				flag = 0;
				break;
			}
		if(flag)
		{
			sort(a + 1,a + 1 + 5);
			rep(i,1,5) printf("%d ",a[i]);
			return 0;
		}
	}
	puts("-1");
	return 0;
} 
