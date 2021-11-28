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

int find(int x)//根节点的查找 
{
    
	int temp;
    if(x == p[x].pre)
       return x;
    temp = p[x].pre;//采用路径压缩 
    p[x].pre = find(temp);
    p[x].relation = (p[x].relation + p[temp].relation) % 3;//查找关系更新 
    return p[x].pre;//返回根节点 
}
int main()
{
	int n,k;
	int cat,a,b;
	int fake = 0;//假话数目 
	int rootx,rooty;
	scanf("%d%d",&n,&k);
	int i = 1;
	for(i = 1;i<=n;i++)//进行初始化 
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
