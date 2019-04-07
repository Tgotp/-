#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
using namespace std; 
typedef long long ll;
template<typename T>inline bool chkmin(T&x,T y) { return x > y ? x = y, 1 : 0; }
template<typename T>inline bool chkmax(T&x,T y) { return x < y ? x = y, 1 : 0; }
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
const int N = 2e5 + 50;
struct SAM
{
	int ch[10],pre,len,pos,sz;
}t[N];
int sz = 1,root = 1,lst = 1;

inline int insert(int x,int i)
{
	int p = lst,np = ++ sz;	
	t[np].len = t[p].len + 1; t[np].sz = 1; t[np].pos = i;
	for(;p && !t[p].ch[x];p = t[p].pre) t[p].ch[x] = np;
	if(!p) t[np].pre = root;
	else
	{
		int q = t[p].ch[x];
		if(t[q].len == t[p].len + 1) t[np].pre = q;
		else
		{
			int nq = ++ sz;
			t[nq] = t[q];
			t[nq].pos = 0; t[nq].sz = 0;
			t[nq].len = t[p].len + 1;
			t[q].pre = t[np].pre = nq;
			for(;p&&t[p].ch[x] == q;p=t[p].pre) t[p].ch[x] = nq;
		}
	}

	lst = np;
	return np;
}

const int M = 2e7 + 60;
int rt[N],Rt[50],ls[M],rs[M],mx[M],mi[M],cnt;
ll val1[M],val2[M]; 

void ins(int&x,int l,int r,int pos,int nxt)
{
	int y = x; x = ++ cnt;
	ls[x] = ls[y];rs[x] = rs[y];
	if(l == r)
	{
		mi[x] = mx[x] = nxt;
		val1[x] = 1ll * (nxt - pos) * nxt;
		val2[x] = nxt - pos;
		return ;
	}
	int mid = l + r >> 1;
	if(pos <= mid) ins(ls[x],l,mid,pos,nxt);
	else ins(rs[x],mid+1,r,pos,nxt);
	mx[x] = max(mx[ls[x]],mx[rs[x]]); 
	mi[x] = min(mi[ls[x]],mi[rs[x]]);
	val1[x] = val1[ls[x]] + val1[rs[x]];
	val2[x] = val2[ls[x]] + val2[rs[x]];
}

int n;

int Tak[50],Top;
set<int> s[50];
set<int> :: iterator it,it1;

inline void add(int x,int w)
{
	if(!w) return ;

	it1 = s[x].lower_bound(w);	

	if(s[x].empty())
	{
		ins(Rt[x],1,n,w,1e7);	
	}
	else if(it1 == s[x].end())
	{
		-- it1;
		ins(Rt[x],1,n,w,1e7);
		ins(Rt[x],1,n,*it1,w);
	}
	else if(it1 == s[x].begin())
	{
		ins(Rt[x],1,n,w,*it1);
	}
	else
	{
		ins(Rt[x],1,n,w,*it1);
		-- it1;
		ins(Rt[x],1,n,*it1,w);
	}

	s[x].insert(w);
}

int tot = 1;
inline void merge(int x,int y)
{
	it = s[y].begin();	
	while(it != s[y].end())
		add(x,*(it++));
	s[y].clear();
	Tak[++Top] = y;
	Rt[y] = 0;
}

vector<int> g[N];
void dfs1(int x) { for(auto&i:g[x]) { dfs1(i); t[x].sz += t[i].sz; } }

int L[N],R[N];
void dfs(int x,int z)
{
	int mx = -1,hson;
	for(auto&i:g[x])
		if(chkmax(mx,t[i].sz))
			hson = i;
	
	if(~mx)
	{
		dfs(hson,z);
		for(auto&i:g[x]) if(i != hson)
		{
			int q = Top ? Tak[Top--] : ++ tot;
			dfs(i,q);
			merge(z,q);
		}
	}

	add(z,t[x].pos);	
	rt[x] = Rt[z];

	it = s[z].begin(); L[x] = *it;
	it = s[z].end(); if(it!=s[z].begin()) { -- it; R[x] = *it;}
}

ll find(int x,int l,int r,int l1,int l2,int len)
{
	//printf("%d %d %d %d %d\n",l,r,mx[x],l1,l2);
	if(mi[x] - len > l1 || mx[x] < l2 - len) return 0;
	if(mx[x] - len <= l1 && mi[x] >= l2 - len) return val1[x] - val2[x] * (l2 - len);
	int mid = l + r >> 1;
	if(l1 >= mi[rs[x]] - len) return find(ls[x],l,mid,l1,l2,len) + find(rs[x],mid+1,r,l1,l2,len);
	else return find(ls[x],l,mid,l1,l2,len);
}

int fnxt(int x,int l,int r,int pos)
{
	if(l == r) return mi[x];
	int mid = l + r >> 1;
	if(mx[ls[x]] > pos) return fnxt(ls[x],l,mid,pos);
	else return fnxt(rs[x],mid+1,r,pos);
}

int fqmxl(int x,int l,int r,int pos,int len)
{
	if(mx[x] - len + 1 <= pos) return mx[x] - len + 1;
	if(!x) return n + 1;
	int mid = l + r >> 1;
	if(mi[rs[x]] - len + 1 <= pos) return fqmxl(rs[x],l,mid,pos,len);
	else return fqmxl(ls[x],mid+1,r,pos,len);
}

inline ll get(int r,int l,int len,int now)
{
	l = l - len + 1;	
	if(l >= r)
	{
		int qmxl = r - len + 1;
		chkmax(qmxl , fqmxl(rt[now],1,n,r,len));
		int z = fnxt(rt[now],1,n,qmxl + len - 1);
		if(z <= l) return 0;
		return 1ll * (r - qmxl) * (z - l);
	}
	int k = l - (r - len + 1);
	len = r - l + 1;
	return 1ll * (n - len - k) * (len-1) + (1ll * (len - 2) * (len-1)/2);
}

int q,pos[N];
char S[N];

int p[N][21];

int main()
{
	//freopen("cutting20.in","r",stdin);
	//freopen("hnta.out","w",stdout);
	mi[0] = 1e7;
	
	read(n); read(q);
	scanf("%s",S + 1);

	rep(i,1,n) pos[i] = insert(S[i]-'0',i);

	rep(i,1,sz) g[t[i].pre].push_back(i);

	dfs1(root); dfs(root,1);

	rep(i,1,sz) p[i][0] = t[i].pre;
	rep(j,1,20) rep(i,1,sz) p[i][j] = p[p[i][j-1]][j-1];	

	ll ans = 1ll * (n - 1) * (n - 2) / 2;
	//cout << ans << endl;
	while(q--)
	{
		int l,r; read(l); read(r);
		if(l > n || l < 1 || r > n || r < 1 || r < l) 
		{
			printf("%lld\n",ans);
			continue;
		}
		int now = pos[r],len = r - l + 1; 
		repd(i,20,0) if(t[p[now][i]].len >= len) now = p[now][i];
		printf("%lld\n",ans - find(rt[now],1,n,L[now],R[now],len-1) - get(L[now],R[now],len,now));
	}

	return 0;
}
