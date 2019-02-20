#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std;
typedef long long ll;

const int N = 2e5 + 50;

struct SAM
{
	int pre,len,sz;
	int ch[4];
}t[N];
int rt,sz,lst;

inline void clear()
{
	rep(i,1,sz)
	{
		rep(j,0,3)
			t[i].ch[j] = 0;
		t[i].len = t[i].pre = t[i].sz = 0;
	}
	rt = sz = lst = 1;
}

int trans(char s)
{
	if(s == 'A') return 0;
	if(s == 'G') return 1;
	if(s == 'C') return 2;
	if(s == 'T') return 3;
}

inline void insert(int x)
{
	int p = lst,np = ++ sz;
	t[np].len = t[p].len + 1; t[np].sz = 1;
	for(;p && !t[p].ch[x];p = t[p].pre) t[p].ch[x] = np;
	if(!p) t[np].pre = rt;
	else
	{
		int q = t[p].ch[x];
		if(t[q].len == t[p].len + 1) t[np].pre = q;
		else
		{
			int nq = ++ sz;
			t[nq] = t[q]; t[nq].sz = 0;
			t[nq].len = t[p].len + 1;
			t[q].pre = t[np].pre = nq;
			for(;p && t[p].ch[x] == q;p = t[p].pre)t[p].ch[x] = nq;
		}
	}
	lst = np;
}

int n,m;
int buc[N],a[N];
inline void get()
{
	rep(i,1,sz) ++ buc[t[i].len];
	rep(i,1,sz) buc[i] += buc[i-1];
	rep(i,1,sz) a[buc[t[i].len] --]= i;
	repd(i,sz,1) t[t[a[i]].pre].sz += t[a[i]].sz;
	rep(i,0,sz) buc[i] = 0;
}

char s[N];
int ans ;
void dfs(int x,int y,int e)
{
	if(y == m) return void(ans += t[x].sz);
	int z = trans(s[y+1]);
	rep(i,0,3)
	{
		if(!t[x].ch[i]) continue;
		if(i == z) dfs(t[x].ch[i],y + 1,e);
		else if(e < 3) dfs(t[x].ch[i],y + 1,e + 1);
	}
}

inline void solve()
{
	clear();
	scanf("%s",s + 1);
	n = strlen(s + 1);
	rep(i,1,n) insert(trans(s[i]));

	scanf("%s",s + 1);
	m = strlen(s + 1);

	get();
	//rep(i,1,10) printf("%d ",t[i].sz); puts("");
	ans = 0;
	dfs(1,0,0);
	printf("%d\n",ans);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	int t;
	cin >> t ;
	while(t --)
		solve();
	return 0;
}
