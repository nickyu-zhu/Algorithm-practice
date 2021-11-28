#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 50010

struct node
{
	int pre;
	int relation;
};
node p[N];

int find(int x)//���ڵ�Ĳ��� 
{
    
	int temp;
    if(x == p[x].pre)
       return x;
    temp = p[x].pre;//����·��ѹ�� 
    p[x].pre = find(temp);
    p[x].relation = (p[x].relation + p[temp].relation) % 3;//���ҹ�ϵ���� 
    return p[x].pre;//���ظ��ڵ� 
}
int main()
{
	int n,k;
	int cat,a,b;
	int fake = 0;//�ٻ���Ŀ 
	int rootx,rooty;
	scanf("%d%d",&n,&k);
	int i = 1;
	for(i = 1;i<=n;i++)//���г�ʼ�� 
	{
		p[i].pre = i;
		p[i].relation = 0;
	}
	for(i = 1;i<=k;i++)
	{
		scanf("%d%d%d",&cat,&a,&b);
		if(a > n||b > n)
		{
			fake++;
			continue;
		}
		if(cat == 2 && a==b)
		{
			fake++;
			continue;
		}
		rootx = find(a);
		rooty = find(b);
		if(rootx != rooty)
		{
			p[rooty].pre = rootx;
			p[rooty].relation = (3+(cat-1)+p[a].relation-p[b].relation) % 3;
		}
		else
		{
		    if(cat == 1 && p[a].relation != p[b].relation)	
		    {
		    	fake++;
		    	continue;
			}
			if(cat == 2 && ((3-p[a].relation+p[b].relation) % 3 != cat - 1))
			{
				fake++;
				continue;
			}
		}
	 } 
	printf("%d\n",fake);
	return 0;
	
 } 
