#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#define MAX 100100
#define l_tag p<<1
#define r_tag p<<1|1
using namespace std;

struct node{
	int l,r;
	int color;
	int lazy; 
}node[MAX<<2];

int mark[80];

void build(int l,int r,int p)
{
	node[p].l = l;
	node[p].r = r;
	node[p].color = 1;
	node[p].lazy = 1;
	if(l == r) return;
	else{
		int m;
		m = (l+r)>>1;
		build(l,m,l_tag);
		build(m+1,r,r_tag);
	}
}

void update(int l,int r,int p,int c)
{
	if(node[p].l==l&&node[p].r==r)
	{
		node[p].lazy = 1;
		node[p].color = c;
		return;
	}
	if(node[p].color!=c&&node[p].lazy)
	{
		node[p].lazy = 0;
		node[l_tag].lazy = node[r_tag].lazy = 1;
		node[l_tag].color = node[r_tag].color = node[p].color;
	}
	int m = (node[p].l+node[p].r)>>1;
	if(r<=m) update(l,r,l_tag,c);
	else if(l>m) update(l,r,r_tag,c);
	else
	{
		update(l,m,l_tag,c);
		update(m+1,r,r_tag,c);
	}
	if(node[l_tag].lazy&&node[r_tag].lazy&&node[l_tag].color==node[r_tag].color)
	{
		node[p].lazy = 1;
		node[p].color = node[l_tag].color;
	}
}
void query(int l,int r,int p)
{
	if(node[p].lazy)
	{
		mark[node[p].color]=1;
		return;
	}
	int m = (node[p].l+node[p].r)>>1;
	if(r<=m) query(l,r,l_tag);
	else if(l>m) query(l,r,r_tag);
	else{
		query(l,m,l_tag);
		query(m+1,r,r_tag);
	}
}
int main()
{
	int L,T,O;
    scanf("%d%d%d",&L,&T,&O);
    build(1,L,1);
    while(O--)
    {
    	char ch[10];
    	int a,b,c;
    	scanf("%s",ch);
    	if(ch[0] == 'C')
    	{
    		scanf("%d%d%d",&a,&b,&c);
    		update(a,b,1,c);
		}
		else
		{
			int i;
			scanf("%d%d",&a,&b);
			memset(mark,0,sizeof(mark));
			query(a,b,1);
			int sum = 0;
			for(i = 1;i<=T;i++) if(mark[i]) sum++;
			printf("%d\n",sum); 
		}
	}
	return 0;
 } 

