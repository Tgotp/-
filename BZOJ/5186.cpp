#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y ; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y ; -- i)
using namespace std;
namespace IO{//orz laofu
    const int maxn((1 << 21) + 1);

    char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf, *oT = obuf + maxn - 1, c, st[55];
    int f, tp;
    char Getc() {
        return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++)) : *iS++);
    }

    void Flush() {
        fwrite(obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }

    void Putc(char x) {
        *oS++ = x;
        if (oS == oT) Flush();
    }
    
    template <class Int> void Input(Int &x) {
        for (f = 1, c = Getc(); c < '0' || c > '9'; c = Getc()) f = c == '-' ? -1 : 1;
        for (x = 0; c <= '9' && c >= '0'; c = Getc()) x = (x << 3) + (x << 1) + (c ^ 48);
        x *= f;
    }
    
    template <class Int> void Print(Int x) {
        if (!x) Putc('0');
        if (x < 0) Putc('-'), x = -x;
        while (x) st[++tp] = x % 10 + '0', x /= 10;
        while (tp) Putc(st[tp--]);
    }

    void Getstr(char *s, int &l) {
        for (c = Getc(); c < 'a' || c > 'z'; c = Getc());
        for (l = 0; c <= 'z' && c >= 'a'; c = Getc()) s[l++] = c;
        s[l] = 0;
    }
    
    void Putstr(const char *s) {
        for (int i = 0, n = strlen(s); i < n; ++i) Putc(s[i]);
    }
}

const int N = 1e6 + 60;
int n,in[N];
int d[N];
queue<int>q;
vector<int>g[N];
vector<pair<int,int> >G[N];
#define mk(x,y) make_pair(x,y)

int fa[N],deep[N];
int dfs(int x,int lst)
{
    int sz = g[x].size();
    if(lst && (sz > 2 || sz == 1))
    {
        int y = fa[x];
        while(y!=lst)
        {
            G[y].push_back(mk(x,deep[x] - deep[y]));
            G[y].push_back(mk(lst,deep[y] - deep[lst]));
            y = fa[y];
        }
        G[lst].push_back(mk(x,deep[x] - deep[lst]));
        G[x].push_back(mk(lst,deep[x] - deep[lst]));
        lst = x;
    }
    if(sz > 2 || sz == 1 || x == 1) lst = x;
    for(auto&i:g[x]) if(i != fa[x])
    {
        fa[i]=x;
        deep[i] = deep[x] + 1;
        dfs(i,lst);
    }
}

int vis[N],t[N],vised;
int bfs(int x)
{
    ++ vised;
    vis[x] = vised;
    if(d[x] <= 0) return 1;
    q.push(x); t[x] = 0; int ans = 0;
    while(!q.empty())
    {
        x = q.front(); q.pop();
        if(d[x] <= t[x]) {++ ans;continue;}
        for(auto&i:G[x]) if(vis[i.first] != vised)
        {
            vis[i.first] = vised;
            t[i.first] = t[x] + i.second;
            q.push(i.first);
        }
    }
    return ans;
}

int main()
{
/*
    freopen("4.in","r",stdin);
    freopen("41.out","w",stdout);
*/
    #define read(x) IO::Input(x)
    read(n); 
    rep(i,2,n)
    {
        int u,v;
        read(u); read(v);
        g[u].push_back(v);
        g[v].push_back(u);
        ++ in[u];++ in[v];
    }
    memset(d,0x3f,sizeof d);
    rep(i,1,n) if(in[i] == 1) q.push(i),d[i] = 0;
    while(!q.empty())
    {
        int x = q.front();q.pop();
        for(auto&i:g[x])
            if(d[i] > d[x]+1)
            {
                d[i] = d[x]+1;
                q.push(i);
            }
    }
    dfs(1,0);
    //for(auto&i:G[2]) printf("%d\n",i.first);
    rep(i,1,n) IO::Print(bfs(i)),IO::Putstr("\n");
    IO::Flush();
    return 0;
}
