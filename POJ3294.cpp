#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 105, maxm = 1005;

int n, m, len, cur, timer, pos[maxn*maxm], s[maxn*maxm];
char c[maxm];

int tp[maxn*maxm], a[maxn*maxm], tax[maxn*maxm];
int sa[maxn*maxm], rk[maxn*maxm], tong[maxn*maxm], fir[maxn*maxm], sec[maxn*maxm], hei[maxn*maxm];
void RSort() {
	for (int i = 0; i <= m; i ++) tax[i] = 0;
	for (int i = 1; i <= len; i ++) tax[rk[tp[i]]] ++;
	for (int i = 1; i <= m; i ++) tax[i] += tax[i - 1];
	for (int i = len; i >= 1; i --) sa[tax[rk[tp[i]]] --] = tp[i];
}

int cmp(int *f, int x, int y, int w) { return f[x] == f[y] && f[x + w] == f[y + w]; }

void Suffix() {
	for (int i = 1; i <= len; i ++) a[i] = s[i], rk[i] = a[i], tp[i] = i;
	m = 150, RSort();
	
	for (int w = 1, p = 1, i; p < len; w += w, m = p) {
		for (p = 0, i = len - w + 1; i <= len; i ++) tp[++ p] = i;
		for (i = 1; i <= len; i ++) if (sa[i] > w) tp[++ p] = sa[i] - w;
		RSort();
		memcpy(tong, rk, sizeof tong);
		memcpy(rk, tp, sizeof tong);
		memcpy(tp, tong, sizeof tong);
		//swap(rk, tp), 
		rk[sa[1]] = 1, p = 1;
		for (i = 2; i <= len; i ++) rk[sa[i]] = cmp(tp, sa[i], sa[i - 1], w) ? p : ++ p;
	}
	
	int j, k = 0;
	for(int i = 1; i <= len; hei[rk[i ++]] = k) 
		for( k = k ? k - 1 : k, j = sa[rk[i] - 1]; a[i + k] == a[j + k]; ++ k);
}

bool vis[maxn];

bool check(int x)
{
    for(int i = 1; i <= n; ++i)
        vis[i] = 0;
    int p = 1, num = 1;
    vis[0] = 1;
    vis[pos[sa[1]]] = 1;
    for(int i = 2; i <= len; ++i) {
        if(hei[i] < x) {
            if(num > n / 2)
                return 1;
            for(int j = p; j < i; ++j)
                vis[pos[sa[j]]] = 0;
            vis[0] = 1;
            p = i;
            num = 0;
        }
        if(!vis[pos[sa[i]]])
            num ++, vis[pos[sa[i]]] = 1;
    }
    return num > n / 2;
}

void write(int x)
{
    for(int i = 1; i <= n; ++i)
        vis[i] = 0;
    int p = 1, num = 1;
    vis[0] = 1;
    vis[pos[sa[1]]] = 1;
    for(int i = 2; i <= len; ++i) {
        if(hei[i] < x) {
            if(num > n / 2) {
                int cnt = 0, j = sa[i-1];
                while(cnt < x) {
                    if(pos[j] != 0)
                        printf("%c", s[j]-maxn+'a'), cnt++;
                    j++;
                }
                printf("\n");
            }
            for(int j = p; j < i; ++j)
                vis[pos[sa[j]]] = 0;
            vis[0] = 1;
            p = i;
            num = 0;
        }
        if(!vis[pos[sa[i]]])
            num ++, vis[pos[sa[i]]] = 1;
    }
    if(num > n / 2) {
        int cnt = 0, j = sa[len];
        while(cnt < x) {
            if(pos[j] != 0)
                printf("%c", s[j]-maxn+'a'), cnt++;
            j++;
        }
        printf("\n");
    }
}

void work()
{
    int l = 0, r = len, mid, ans = 0;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(check(mid)) ans = mid, l = mid + 1; else
            r = mid - 1;
    }
    if(ans) write(ans); else
        printf("?\n");
}

void solve() {
	if(cur++) printf("\n");
	len = timer = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%s", c);
		int l = strlen(c);
		for(int j = 0; j < l; ++j)
			s[++len] = c[j] - 'a' + maxn, pos[len] = i;
		s[++len] = ++timer;
		pos[len] = 0;
	}
	if(n == 1) {
		for(int i = 1; i < len; ++i) printf("%c", s[i]-maxn+'a');
		printf("\n");
	}
	else {
		Suffix();
		work();
	}
}

int main()
{
	//freopen("data.in", "r", stdin);
    while(scanf("%d", &n), n != 0) solve();
    return 0;
}

