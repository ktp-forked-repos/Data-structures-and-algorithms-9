#include<stdio.h>
#include <stdlib.h>

struct node{
	int key;
	int height;
	struct node *left,*right;
};

int max(int a,int b)
{
	return (a>b)? a:b;
}

struct node* newNode(int key)
{
    struct node* nodee = malloc(sizeof(struct node));
    nodee->key   = key;
    nodee->left   = NULL;
    nodee->right  = NULL;
    nodee->height = 0; 
    return(nodee);
}

int height(struct node *N)
{
    if (N == NULL)
        return -1;
    return N->height;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* r_zigzag(struct node* z)
{
	struct node *y = z->right;
	struct node *x = y->left;
	struct node *T2 = x->left, *T3 = x->right;
	x->left = z;
	x->right = y;
	z->right = T2;
	y->left = T3;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;



	return x;
}
struct node* l_zigzag(struct node* z)
{
	struct node *y = z->left;
	struct node *x = y->right;
	struct node *T2 = x->left, *T3 = x->right;
	x->left = y;
	x->right = z;
	z->left = T2;
	y->right = T3;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;

	return x;
}
struct node* r_zigzig(struct node* z)
{
	struct node *y = z->right;
	struct node *x = y->right;
	struct node *T2 = y->left;
	y->right = x;
	y->left = z;
	z->right = T2;

	z->height = max(height(z->left),height(z->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	
	return y;
}
struct node* l_zigzig(struct node* z)
{
	struct node *y = z->left;
	struct node *x = y->left;
	struct node *T2 = y->right;
	y->right = z;
	y->left = x;
	z->left = T2;

	z->height = max(height(z->left),height(z->right))+1;
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	
	return y;
}
struct node* insert(struct node* node,int key)
{
	if(node == NULL)
		return newNode(key);
	if(key < node->key)
		node->left = insert(node->left,key);
	else if(key > node->key)
		node->right = insert(node->right,key);
	else
		return node;
	
	node->height = max(height(node->left),height(node->right))+1;
	int balance = 0;
	balance = abs(getBalance(node));

	if(balance > 1)
	{
		if(node->right)
		{	
			if(key > (node->key) && key < ((node->right)->key))
				return r_zigzag(node);
			if(key > (node->key) && key > ((node->right)->key))
				return r_zigzig(node);
		}
		if(node->left)
		{
			if(key < (node->key) && key > ((node->left)->key))
				return l_zigzag(node);
			if(key < (node->key) && key < ((node->left)->key))
				return l_zigzig(node);
		}

	}
	return node;

}

void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d %d\n", root->key,root->height);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
	
	struct node *root = NULL;
 
	root = insert(root, 10);
  	root = insert(root, 20);
  	root = insert(root, 30);
  	root = insert(root, 40);
  	root = insert(root, 50);
  	root = insert(root, 25);
 
  
  	preOrder(root);
  	
 
  	return 0;

}