#include<iostream>
using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
};

void createbst(node** root,int v)
{
	node* temp = new node;
	temp->data = v;
	temp->left = temp->right = NULL;
	if((*root)==NULL)
	{
		(*root) = temp;
		return ;
	}
	else
	{
		if(v > (*root)->data)
		{
			createbst(&((*root)->right),v);
		}
		else
		{
			createbst(&((*root)->left),v);
		}
	}
	return ;
}

void inorder(node* root)
{
	if(root==NULL)
	{
		return ;
	}
	
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
	return ;
}

int main()
{
	node* root = new node;
	root = NULL;
	int n,i,v;
	cout<<"\nEnter how many values to be updated to BST:";
	cin>>n;
	
	for(i=0;i<n;i++)
	{
		cout<<"\nEnter a value:";
		cin>>v;
		createbst(&root,v);
	}
	
	cout<<"\nThe sorted list using BST(using inorder traversal) is:\n";
	
	inorder(root);
	
	return 0;
}
	
