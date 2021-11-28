#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int Max = 20008;
#define ll long long

struct cow{
	int x,v;
}p[Max];

int n;
ll dis[Max],num[Max];
int lowbit(int x)
{
	return x&(-x);
}

void update_dis(int x,int num)
{
	while(x < Max){
		dis[x] += num;
		x += lowbit(x);
	}
}

void update_num(int x,int k)
{
	while(x < Max){
		num[x] += k;
		x += lowbit(x);
	}
}

ll sum_dis(int x)
{
	ll sum = 0;
    while(x > 0)
    {
    	sum += dis[x];
    	x -= lowbit(x);
	}
	return sum;
}

ll sum_num(int x)
{
	ll sum = 0;
    while(x > 0)
    {
    	sum += num[x];
    	x -= lowbit(x);
	}
	return sum;
}

bool cmp(cow a,cow b)
{
	return a.x < b.x;
}
int main()
{
	scanf("%d",&n);
	int i;
	for(i = 0;i < n;i++)
	{
		scanf("%d%d",&p[i].v,&p[i].x);
	}
	sort(p,p+n,cmp);
	memset(dis,0,sizeof(dis));
	memset(num,0,sizeof(num));
	ll summ = 0;
	for(i = 0;i < n;i++)
	{
		summ += p[i].v *(p[i].x*sum_num(p[i].v)-sum_dis(p[i].v));
		update_dis(p[i].v,p[i].x);
		update_num(p[i].v,1);
	}
	memset(dis,0,sizeof(dis));
	memset(num,0,sizeof(num));
	for(i = n-1;i >= 0;i--)
	{
		summ += p[i].v *(sum_dis(p[i].v-1)-p[i].x*sum_num(p[i].v-1));
		update_dis(p[i].v,p[i].x);
		update_num(p[i].v,1);
	}
	cout << summ << endl;
	return 0;
}


