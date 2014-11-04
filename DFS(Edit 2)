//Author :  V.Manikantan
//          B.Tech,2nd year
//          NIT - Trichy

#include<iostream>
#include<queue>
using namespace std;

struct node
{
	int data;
	node* next;
};


void dfs(int cur,node* arr[],int visited[],int start[],int finish[],int* time,bool* cycle)
{
	visited[cur] = 1;
	(*time)++;
	start[cur] = (*time);
	cout<<cur+1<<" ";
	node* temp = new node;
	temp = *(arr+cur); 
	while(temp!=NULL)
	{
		if(visited[temp->data]==0)
		{
			dfs(temp->data,arr,visited,start,finish,time,cycle);
		}
		else if(visited[temp->data]==1)
		{
			(*cycle) = true;
		}
		temp = temp->next;
	}
	(*time)++;
	visited[cur] = 2;
	finish[cur] = (*time);
	return ;
}

int main()
{
	int v,i,e,j;
	cout<<"\nEnter how many vertices:";
	cin>>v;
	
	node* arr[v];
	int visited[v];
	int start[v],finish[v];
	for(i=0;i<v;i++)
	{
		arr[i] = NULL;
		visited[i] = 0;
	}
	
	cout<<"\nEnter how many edges:";
	cin>>e;
	int a,b;
	while(e--)
	{
		cout<<"\nEnter edge connection:";
		cin>>a>>b;
		
		if(arr[a-1]==NULL)
		{
			node* temp = new node;
			temp->data = b-1;
			temp->next = NULL;
			arr[a-1] = temp;
		}
		else
		{
			node* temp = new node;
			temp->data = b-1;
			temp->next = NULL;
			node* temp1 = new node;
			temp1 = arr[a-1];
			
			while(temp1->next!=NULL)temp1=temp1->next;
			temp1->next = temp;
			
		}
	}
	
	bool cycle = false;
	
	cout<<"\nThe DFS order is:\n";
	int time = 0;
	for(i=0;i<v;i++)
	{
		if(!visited[i])
		{
			dfs(i,arr,visited,start,finish,&time,&cycle);
		}
	}
	
	cout<<"\nThe starting and finishing times for each vertex are:\n";
	
	for(i=0;i<v;i++)
	{
		cout<<i+1<<"   Start:"<<start[i]<<" , Finish:"<<finish[i]<<"\n";
	}
	
	cout<<"\n\n";
	
	if(cycle)
	{
		cout<<"\nThere is a cycle in this graph.\n";
	}
	else
	{
		cout<<"\nThere is no cycle in this graph.\n";
	}		
	return 0;
}
