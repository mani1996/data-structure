#include<iostream>
#include<queue>
using namespace std;

struct node
{
	int data;
	node* next;
};


void dfs(int v,node** arr,bool visit[])
{
	//Vertex v is visited
	visit[v-1] = true;
	cout<<v<<" ";
	
	node* q;
	q = new node;
	q = *(arr+v-1);
	
	while(q!=NULL)
	{
		if(visit[(q->data)-1]==false)	//Unvisited Node
		{
			dfs((q->data),arr,visit);
		}
		else	//Visited Node
		{
			q = q->next;
		}
	}
	return ;
}

void bfs(int v,node** arr,bool visit[],queue<int> qu)
{
	node* p;
	int x;
	//Vertex v has been visited
	visit[v-1] = true;
	cout<<v<<" ";
	qu.push(v);
	
	while(!qu.empty())
	{
		x = qu.front();
		qu.pop();
		
		p = *(arr+x-1);
		
		while(p!=NULL)
		{
			if(visit[(p->data)-1]==false)
			{
				visit[(p->data)-1] = true;
				cout<<p->data<<" ";
				qu.push(p->data);
			}
			p = p->next;
		}
		
	}
	return ;
}


int main()
{
	freopen("ip.txt","r",stdin);
	int n,m,a,b,i;
	queue<int> qu;
	cout<<"\nEnter how many vertices:";
	cin>>n;
	
	node* arr[n],*v1,*v2,*v3,*v4,*temp,*temp1;
	bool visited[n];
	
	for(i=0;i<n;i++)
	{
		visited[i]=false;
		arr[i] = NULL;
	}
	
	cout<<"\n\nHow many unique edge connections?:";
	cin>>m;
	
	//Creation of node connections
	
	while(m--)
	{
		cout<<"\nEnter incident edges(with spaces):";
		cin>>a>>b;
		
		//Put vertex b in adjacency list of vertex a
		
		if(arr[a-1]==NULL)
		{
			temp1 = new node;
			temp1->data = b;
			temp1->next = NULL;
			arr[a-1] = temp1;
		}
		else
		{
			temp = arr[a-1];
			while(temp->next!=NULL)
			{
				temp = temp->next;
			}
			temp1 = new node;
			temp1->data = b;
			temp1->next = NULL;
			temp->next = temp1;
		}
		
		//Put vertex a in adjacency list of vertex b
		
		
		
		if(arr[b-1]==NULL)
		{
			temp1 = new node;
			temp1->data = a;
			temp1->next = NULL;
			arr[b-1] = temp1;
		}
		else
		{
			temp = arr[b-1];
			while(temp->next!=NULL)
			{
				temp = temp->next;
			}
			temp1 = new node;
			temp1->data = a;
			temp1->next = NULL;
			temp->next = temp1;
		}
		
	}
	
	
	
	//Calling DFS function
	cout<<"\n\nThe DFS order is:\n";
	dfs(1,arr,visited);
	
	//Reset all nodes as unvisited
	for(i=0;i<n;i++)
	{
		visited[i] = false;
	}
	
	//Calling BFS function
	cout<<"\n\nThe BFS order is:\n";
	bfs(1,arr,visited,qu);
	
	return 0;
}
