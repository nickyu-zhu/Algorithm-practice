#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace std;

const int N = 1e7;
int a[N * 2],d[N], tmp,bel[N];

bool solve(int n) {
    int cnt = 0;
    tmp = 0;
    for (int i = 0; i < n; i++) {
		if (a[i] < 0) d[tmp++] = abs(a[i]); else {
			if (d[tmp - 1] != a[i])
				return false;
			bel[d[--tmp]] = 0;
			bel[d[tmp - 1]] += a[i];
			if(tmp && d[tmp - 1] <= bel[d[tmp - 1]]) return false;
			cnt += (tmp == 0);
		}
	}
	return (!(tmp || cnt > 1));
}

int main() {
    char c;
    while(scanf("%c", &c) != EOF) {
        int cnt = 0;
        while(c != '\n') {
            int ans=0, sign = 1;
            for (;!isdigit(c); c = getchar()) if (c == '-') sign = -1;
			for (;isdigit(c);c = getchar())ans = ans * 10 + c - '0';
            a[cnt++] = ans * sign;
        }
        printf("%s\n", solve(cnt) ? ":-) Matrioshka!" : ":-( Try again.");
    }
    return 0;
}
