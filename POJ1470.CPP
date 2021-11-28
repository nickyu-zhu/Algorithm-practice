#include<iostream>
#include<stdio.h>
#include<string.h>
#define MAX 1010
using namespace std;
int p[MAX];
int cnt[MAX];
void init(int n)
{
	int i;
	for(i=0;i<=n;i++)
	{
		p[i] = i;
	}
} 
int query(int x,int y)
{
	int i,j;
	if(p[x]==y)
	   return y;
	if(p[y]==x)
	   return x;
	for(i=x;p[i]!=i;i=p[i])
	{
		for(j=y;p[j]!=j;j=p[j])
		{
			if(i==j)
			{
				return j;
			}
		}
	}
	return i;
}
int main()
{
	int node,i,num,n,ccnode,x,y,sum,m;
	while(~scanf("%d",&n))
	{
	memset(cnt,0,sizeof(cnt));
	init(n);
	m=n;
	while(n--)
	{
		 scanf("\t%d\t:\t(\t%d\t)",&node,&num);
		 
		 for(i=0;i<num;i++)
		 {
		 	scanf("\t%d\t",&ccnode);
		 	p[ccnode]=node;
		 }
	}
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		getchar();
		scanf("\t(%d\t %d\t)",&x,&y);
		sum=query(x,y);
		cnt[sum]++;
	}
	for(i=0;i<=m;i++)
	{
		if(cnt[i]!=0)
		  printf("%d:%d\n",i,cnt[i]);
	}
    }
	
	return 0;
}
