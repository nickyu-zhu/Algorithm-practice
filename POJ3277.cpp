#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 400010

#define l_tag k<<1
#define r_tag k<<1|1

using namespace std;
typedef long long ll;

struct node
{
	ll lf,rf;
	ll cnt,sum;
	ll l,r;
}q[N<<3];

struct tt
{
	ll x_left;
	ll x_right;
	ll h;
	ll lazy;
}p[N<<3];

int n;
int k;
ll c[N<<2];

bool cmp(tt a,tt b)
{
	if(a.h == b.h)
	{
		return a.x_left < b.x_left;
	}
	return a.h < b.h;
}

void build(ll l,ll r,ll k)
{
	q[k].l = l;
	q[k].r = r;
	q[k].sum = 0;
	q[k].cnt = 0;
	q[k].lf = c[l];
	q[k].rf = c[r];
	if(l+1 == r)
	{
		return;
	}
	int m = (l+r)>>1;
	build(l,m,l_tag);
	build(m,r,r_tag);
}

void update(ll k)
{
	if(q[k].sum > 0)
	{
		q[k].cnt= q[k].rf - q[k].lf;
		return;
	}
	else
	{
		q[k].cnt = 0;
	}
	if(q[k].l+1 == q[k].r)
	 return;
	else
	{
		q[k].cnt = q[l_tag].cnt + q[r_tag].cnt;
	}
}

void insert(ll k,tt building)
{
	if(q[k].lf == building.x_left && q[k].rf == building.x_right)
	{
		q[k].sum += building.lazy;
		update(k);
		return;
	}
	if(q[l_tag].rf>=building.x_right)
	{
		insert(l_tag,building);
	}
	else if(q[r_tag].lf <=building.x_left)
	{
		insert(r_tag,building);
	}
	else
	{
		struct tt pt = building;
		pt.x_right = q[l_tag].rf;
		insert(l_tag,pt);
		pt = building;
		pt.x_left = q[r_tag].lf;
		insert(r_tag,pt);
	}
	update(k);
}

int main()
{
    scanf("%d",&n);
    int i;
    k = 1;
    ll x_left,x_right,h; 
    for(i = 1 ;i<=n;i++)
     {
      	scanf("%lld%lld%lld",&x_left,&x_right,&h);
      	p[k].x_left = x_left;
      	p[k].x_right = x_right;
      	p[k].h = 0;
      	p[k].lazy = 1;
      	c[k] = x_left;
      	k++;
      	p[k].x_left = x_left;
      	p[k].x_right = x_right;
      	p[k].h = h;
      	p[k].lazy = -1;
      	c[k] = x_right;
      	k++;
	} 
	k--;
	sort(p+1,p+k+1,cmp);
	sort(c+1,c+1+k);
	build(1,k,1);
	insert(1,p[1]);
	ll summing = 0;
	for(i = 2;i<=k;i++)
	{
		summing += q[1].cnt *(p[i].h - p[i-1].h);
		insert(1,p[i]);
	}
	printf("%lld\n",summing);
}
