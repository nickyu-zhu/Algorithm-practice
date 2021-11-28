#include<cstdio>
#include<cstring>
#include<ctype.h>
#include<algorithm>
#include<functional>
#pragma GCC optimize(2)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pLL;
#define pb push_back
#define mk make_pair
#define fi first
#define se second
#define ls (i<<1)
#define rs (i<<1|1)
#define mem(a,b) memset(a,b,sizeof(a))
const int N=1e6+5;
const int inf=0x3f3f3f3f;
const LL mod=1e9+7;
LL read(){
    LL x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); }
    while(isdigit(ch)){ x=10*x+ch-'0'; ch=getchar(); }
    return f*x;
}
int sa[N],rk[N],x[N],y[N],he[N],c[N],n,m,sta[N],num[N],tax[N],tong[N],tp[N],a[N];
char s[N],s1[N];
void RSort() {
	for (int i = 0; i <= m; i ++) tax[i] = 0;
	for (int i = 1; i <= n; i ++) tax[rk[tp[i]]] ++;
	for (int i = 1; i <= m; i ++) tax[i] += tax[i - 1];
	for (int i = n; i >= 1; i --) sa[tax[rk[tp[i]]] --] = tp[i];
}
int cmp(int *f, int x, int y, int w) { return f[x] == f[y] && f[x + w] == f[y + w]; }
void Suffix() {
	for (int i = 1; i <= n; i ++) a[i] = s[i], rk[i] = a[i], tp[i] = i;
	m = 150, RSort();
	
	for (int w = 1, p = 1, i; p < n; w += w, m = p) {
		for (p = 0, i = n - w + 1; i <= n; i ++) tp[++ p] = i;
		for (i = 1; i <= n; i ++) if (sa[i] > w) tp[++ p] = sa[i] - w;
		RSort();
		memcpy(tong, rk, sizeof tong);
		memcpy(rk, tp, sizeof tong);
		memcpy(tp, tong, sizeof tong);
		rk[sa[1]] = 1, p = 1;
		for (i = 2; i <= n; i ++) rk[sa[i]] = cmp(tp, sa[i], sa[i - 1], w) ? p : ++ p;
	}
	int j, k = 0;
	for(int i = 1; i <= n; he[rk[i ++]] = k) 
		for( k = k ? k - 1 : k, j = sa[rk[i] - 1]; a[i + k] == a[j + k]; ++ k);
}
int main(){
    int k;
    while(scanf("%d",&k)!=EOF&&k){
        scanf("%s",s+1);
        scanf("%s",s1+1);
        int l1=strlen(s+1),l2=strlen(s1+1);
        n=l1+l2+1;
        s[l1+1]='#';
        for (int i=1;i<=l2;i++) s[l1+1+i]=s1[i];
		Suffix();
        int top=0;
        LL res=0,ans=0;
        for (int i=1;i<=n;i++) {
            if(he[i]<k) top=res=0; else {
                num[i]=0;
                if(sa[i-1]<=l1) {
					num[i]++;
					res+=he[i]-k+1;
				}
                while(top>0&&he[sta[top]]>=he[i]) {
                    num[i]+=num[sta[top]];
                    res-=num[sta[top]]*(he[sta[top]]-he[i]);
					top--;
				}
                sta[++top]=i;
                if(sa[i]>l1+1) ans+=res;
            }
        }
        for (int i=1;i<=n;i++) {
            if (he[i]<k) top=res=0; else {
                num[i]=0;
                if(sa[i-1]>l1+1) num[i]++,res+=he[i]-k+1;
                while(top>0&&he[sta[top]]>=he[i]) {
                    num[i]+=num[sta[top]];
                    res-=num[sta[top]]*(he[sta[top]]-he[i]);
					top--;
				}
                sta[++top]=i;
                if (sa[i]<=l1) ans+=res;
            }
        }
        printf("%lld\n",ans);
        for (int i=1;i<=n;i++) x[i]=y[i]=0;
    }
    return 0;
}
