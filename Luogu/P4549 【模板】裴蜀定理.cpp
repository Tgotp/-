#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y;++ i)
using namespace std;

int n;

int gcd(int x,int y)
{
	return !y?x : gcd(y,x % y);
}

int main()
{
	cin >> n ;
	int ans;
	rep(i,1,n)
	{
		int x;
		cin >> x;
		if(i == 1) ans = x;
		else ans = gcd(ans,x);
	}

	cout << abs(ans) << endl;
	
	return 0;
}
