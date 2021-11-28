#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef int ll;

const int N=30;
const int M=40005;
const int inf=0x3f3f3f3f;
int n,r[N],pp[N];
int tot=0,nxt[M],to[M],head[N],val[M];
bool flag[N];

inline void link(int x,int y,int z) {
    nxt[++tot]=head[x]; to[tot]=y; val[tot]=z; head[x]=tot;
}

int dis[N],cnt[N];
inline bool spfa(int ans)
{
    int i;
    for(i=0;i<=24;i++) dis[i]=-inf, cnt[i] = flag[i] = 0;
    queue<int>qu; 
	while(!qu.empty()) qu.pop(); qu.push(0); dis[0]=0;
    while(!qu.empty()) {
        int x = qu.front(); 
		qu.pop(); 
		flag[x]=0;
        for(i=head[x];i;i=nxt[i]) {
			int v = to[i];
            if(dis[v] < dis[x]+val[i]) {
                dis[v]=dis[x]+val[i];
                if(!flag[v]) {
					qu.push(v); 
					flag[v]=1;
				}
                if((++cnt[v])>24) return false;
            }
        }
    }
    return (dis[24]==ans);
}

void solve() {
	int i;
	for (i=1;i<=24;i++) {
		pp[i]=0; 
		scanf("%d", &r[i]);
	}
	scanf("%d", &n);
	for(i=1;i<=n;i++) {
		int x;
		scanf("%d", &x);
		pp[x+1]++;
	}
	int ll=0,rr=n+1,ans=inf;
	while(ll<=rr) {
		tot=0; memset(head,0,sizeof head);
		int mid=(ll+rr)>>1;
		for(i=1;i<=24;i++) {link(i-1,i,0); link(i,i-1,-pp[i]);}
		for(i=9;i<=24;i++) link(i-8,i,r[i]);
		for(i=1;i<=8;i++) link(i+16,i,r[i]-mid);
		link(0,24,mid);
		if(spfa(mid)) ans=mid,rr=mid-1; else 
			ll=mid+1;
	}
	if(ans<=n) printf("%d\n", ans); else printf("No Solution\n");
}

int main() {
    int T;
	scanf("%d", &T);
    while(T--) solve();
    return 0;
}
