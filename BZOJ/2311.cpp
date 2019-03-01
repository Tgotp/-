#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;
typedef long double ld;
template<typename T>inline void read(T&x)
{
    char c;int sign = 1; x = 0;
    do { c = getchar(); if(c == '-') sign = - 1; }while(!isdigit(c));
    do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
    x *= sign;
}

const int N = 2503;
ld a[N][N],f[N];
vector<int>g[N];
map<int,bool> mp[N];
int id[53][53];
int n,m;

int main()
{
//	freopen("10.in","r",stdin);
//	freopen("11.out","w",stdout);
    read(n); read(m);
	
//	rep(k,1,4) rep(i,1,n) rep(j,1,m) read(a[k][i][j]);
//	
//	repd(i,n,1) repd(j,m,1)
//	{
//		f[i][j] = f[i];
//	}	
	
//    /*
    rep(i,1,n) rep(j,1,m) id[i][j] = (i-1) * m + j;
 	rep(i,1,n) rep(j,1,m)
 		cin>>a[id[i][j]][id[i+1][j]];
 	rep(i,1,n) rep(j,1,m)
 		cin>>a[id[i][j]][id[i][j+1]];
 	rep(i,1,n) rep(j,1,m)
 		cin>>a[id[i][j]][id[i-1][j]];
 	rep(i,1,n) rep(j,1,m)
 		cin>>a[id[i][j]][id[i][j-1]];

 	rep(i,1,n) rep(j,1,m)
		a[id[i][j]][id[i][j]] = -1,
		a[id[i][j]][n*m+1] = 1;
		
	int M = n * m,K = M + 1; 
 	
 	rep(i,1,M)
	{
//		printf("%d\n",i);
		int k,j;
		for(k = i , j = i + 1 ; j <= min(M,i + m); j ++ )
            if(fabs(a[k][i]) < fabs(a[j][i]))
                k = j;
        for(j = 1 ; j <= K ; j ++ ) swap(a[i][j] , a[k][j]);
        
        for(j = i + 1 ; j <= min(M,i + m) ; j ++ ) 
        {
            double t = a[j][i] / a[i][i];
            rep(k,i,min(M,i+2*m)) a[j][k] -= a[i][k] * t;
            a[j][K] -= a[i][K] * t; 
        }
		
	} 
 	
 	f[n * m] = 0;
 	repd(i,n*m - 1,1)
 	{
 		rep(j,i + 1,n*m)
 			a[i][n*m+1] -= a[i][j] * f[j],a[i][j] =0;
 		f[i] = a[i][n * m + 1] / a[i][i];
 		
	}
	
	
//	rep(i,1,K) cout << fixed << setprecision(3) << a[M][i] << ' ';puts(""); 
	cout << fixed << setprecision(3) << -f[1] << endl;
// 	*/
    return 0;
}
