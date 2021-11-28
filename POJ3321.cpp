#include <iostream>
#include <cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
const int Max = 1e5+1;
vector<vector<int> > ap(Max);
int n,m;
int c[Max],apple[Max];
int start[Max];
int end[Max];
int Time;
int lowbit(int x)
{
	return x&(-x);
 } 
 
void update(int x,int value)
{
	while(x <= n)
	{
		c[x] += value;
		x += lowbit(x);
	}
}

int sum(int x)
{
	int sum = 0;
	while(x > 0)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}//树状数组构建模板

void dfs(int x)
{

    Time++;
    start[x] = Time;
    int i;
    for( i = 0;i<ap[x].size();i++)
    {
    	dfs(ap[x][i]);
	}
	end[x] = Time;
}

int main()
{
   while(~scanf("%d",&n))
  {
     	

     Time = 0;
     int i;
     for( i = 1;i<=n-1;i++)
     {
     	int a,b;
     	scanf("%d%d",&a,&b);
     	ap[a].push_back(b);
	}
	
	dfs(1);
	i = 1;
	for( i = 1;i<=n;i++)
	{
		update(i,1);
		apple[i] = 1;
	}
	
	scanf("%d",&m);
	while(m--)
	{
		char word[12];
		int t;
		
		scanf("%s%d",&word,&t);
		if(word[0] == 'Q')
		{
			printf("%d\n",sum(end[t]) - sum(start[t]-1));
		}
		else
		{
			if(apple[t])
			{
				update(start[t],-1);
				apple[t] = 0;
			}
			else{
				update(start[t],1);
				apple[t] = 1;
			}
		}
	}
  }
  return 0;
}

 
