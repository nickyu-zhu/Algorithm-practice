#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#define inf 10000000000000
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
typedef long long ll;
using namespace std;
const int N = 3e6+5;
const int M = 4e5+5;
int n,m,k,tot=0;
int fa[N][20],head[N],dis[N],dep[N];
struct man{
    int to,next,w;
}edg[N];
void add(int u,int v,int w){
    edg[tot].to=v;edg[tot].next=head[u];edg[tot].w=w;head[u]=tot++;
}
void dfs(int u,int f){
    fa[u][0]=f;
    for(int i=1;i<20;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=head[u];i!=-1;i=edg[i].next){
        int v=edg[i].to;
        if(v!=f){
            dis[v]=dis[u]+edg[i].w;
            dep[v]=dep[u]+1;
            dfs(v,u);
        }
    }
}
int lca(int u,int v){
    int U=u,V=v;
    if(dep[u]<dep[v])swap(u,v);
    for(int i=19;i>=0;i--){
        if(dep[fa[u][i]]>=dep[v]){
            u=fa[u][i];
        }
    }
    if(u==v)return (abs(dis[U]-dis[V]));
    for(int i=19;i>=0;i--){
        if(fa[u][i]!=fa[v][i]){
            u=fa[u][i];v=fa[v][i];
        }
    }
    return (dis[U]+dis[V]-2*dis[fa[u][0]]);
}
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    char str[10];
    int u,v,w;
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        scanf("%s",str);
        add(u,v,w);add(v,u,w);
    }
    dep[1]=1;
    dfs(1,0);
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u,v));
    }
    return 0;
}
