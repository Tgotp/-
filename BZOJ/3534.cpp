#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
int n;
typedef long double ld;
ld a[52][52],tmp;
#define eps 1e-8

inline ld gauss(int n)
{
	ld ans = 1;
	rep(i,1,n)
	{
		int num = i;
		rep(j,i+1,n) if(fabs(a[j][i]) > fabs(a[num][i])) num=j;
		if(num!=i)swap(a[num],a[i]);
		if(fabs(a[i][i]) < eps) return 0;
		ans *= a[i][i];
		rep(j,i+1,n) if(fabs(a[j][i]) > eps)
		{
			ld t = a[j][i]/a[i][i];	
			rep(k,i,n) a[j][k] -= a[i][k] * t;
		}
	}
	//rep(i,1,n) rep(j,1,n) printf("%.3lf%c",a[i][j],j==n?'\n':' ');
	return fabs(ans);
}

int main()
{
	cin >> n;

	tmp = 1;
	rep(i,1,n) rep(j,1,n)
	{
		cin >> a[i][j];
		
		if(fabs(1-a[i][j]) < eps) a[i][j] = 1.0-eps;
		if(fabs(a[i][j]) < eps) a[i][j] = eps;
		if(i < j) tmp *= 1.0 - a[i][j];
		a[i][j] = a[i][j] / (1.0-a[i][j]);
	}

	rep(i,1,n) 
	{
		a[i][i] = 0;
		rep(j,1,n) if(j != i)
			a[i][i] -= a[i][j];
	}

	cout<<fixed << setprecision(10) << tmp * gauss(n-1);

	return 0;
}
