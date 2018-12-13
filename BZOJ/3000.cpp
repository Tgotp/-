#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x; i >= y; -- i)
using namespace std;
typedef long long ld;
int n,k;
long double ans;

inline void solve()
{
	ans = 0;
	if(n <= 100000)
	{
		rep(i,1,n) ans += log(i);
		ans /= log(k);
		#define eps 1e-10
		ans = ceil(ans + eps);
		printf("%.0Lf\n",ans);
	}
	#define log(x,y) (log(x)/log(y))
	else cout<<fixed << setprecision(0) <<
		0.5*log(2*acos(-1)*n,k) + n * log(n,k) - 
			n * log(exp(1),k) + 0.5 << endl;
}

int main()
{
	while(scanf("%d%d",&n,&k)!=EOF)
		solve();
	return 0;
}
