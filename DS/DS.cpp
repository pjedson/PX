// DS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

typedef struct Btree {
	int data;
	struct Btree *right;
	struct Btree *left;
} node;

// newNode() for creating a node.

node * newNode(int d) {

	node *tmp = (node*)malloc(sizeof(node));
	tmp->data = d;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

bool lookup(node *root, int d) {
	if (root == NULL) {
		return false;
	}
	else {
		if (root->data == d) {
			return true;
		}
		else {
			if (d > root->data) {
				return lookup(root->right, d);
			}
			else {
				return lookup(root->left, d);
			}
		}
	}
}

bool hasPathSum(node *root, int sum) {
	if (root == NULL) {
		return (sum == 0);
	}
	else {
		int Sum = sum - root->data;
		if (Sum == 0){
			return true;
		}
		else{
			return (hasPathSum(root->right, Sum) || hasPathSum(root->left, Sum));
		}
	}
}

void printArray(int path[], int len) {
	for (int i = 0; i < len; i++)
		printf("%d ", path[i]);
	printf("\n");
}

void printPaths(node *root, int path[], int plength) {
	if (root == NULL) {
		return ;
	}
	
	path[plength] = root->data;
	plength++;

	if (root->left == NULL && root->right == NULL) {
		printArray(path, plength);
	}
				
	printPaths(root->right, path, plength);
	printPaths(root->left, path, plength);
}


node* insert(node *root, int d) {
	if (root == NULL) {
		return newNode(d);
	}
	else{
		if (d > root->data) {
			root->right = insert(root->right, d);
		}
		else {
			root->left = insert(root->left, d);
		}
	}
	return root;
}

int size(node* root) {
	if (root == NULL)
		return 0;
	else
		return (size(root->left) + 1 + size(root->right));
}

int bst_minValue( node * root){
	node *current = root;

	while (current->left != NULL)
		current = current->left;

	return current->data;
}

int bst_maxValue(node * root) {
	node *current = root;

	while (current->right != NULL)
		current = current->right;

	return current->data;
}

int maxDepth(node *root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int lDepth = maxDepth(root->left);
		int rDepth = maxDepth(root->right);

		if (lDepth > rDepth) {
			return lDepth + 1;
		}
		else {
			return rDepth + 1;
		}
	}
}

void mirror(node *root) {
	
	if (root == NULL) {
		return;
	}

	else {
		mirror(root->left);
		mirror(root->right);
		node* tmp = root->left;
		root->left = root->right;
		root->right = tmp;
	}
}

void doubleTree(node* root){
	if (root == NULL) {
		return;
	}
	else {

		doubleTree(root->left);
		doubleTree(root->right);
		node *tmp = root->left;
		root->left = newNode(root->data);
		root->left->left = tmp;
	}
}

int minValue(node* root, int min=INT_MAX) {
	if (root == NULL) {
		return min;
	}
	else {
		min = min < root->data ? min : root->data;
		int m_left = minValue(root->left, min);
		int m_right = minValue(root->right, min);
		return (m_left < m_right ? m_left : m_right);
	}
}

int maxValue(node* root, int max = INT_MIN) {
	if (root == NULL) {
		return max;
	}
	else {
		max = max > root->data ? max : root->data;
		int m_left = minValue(root->left, max);
		int m_right = minValue(root->right, max);
		return (m_left > m_right ? m_left : m_right);
	}
}


void printTreeinfo(node *root) {
	int paths[102];
	printf("Tree size = %d\n", size(root));
	printf("Tree max Depth = %d\n", maxDepth(root));
//	printf("Tree min Valuse = %d\n", bst_minValue(root));
//	printf("Tree max Valuse = %d\n", bst_maxValue(root));
	printf("Tree min Valuse = %d\n", minValue(root));
	printf("Tree max Valuse = %d\n", maxValue(root));

	printf("Has Path sum 40  = %d\n", hasPathSum(root, 40));
	printf("Has Path sum 20  = %d\n", hasPathSum(root, 20));
	printPaths(root, paths, 0);

}
int main()
{
	//printf("Hello World!");
	node *root = NULL;
	
	root = insert(root,5);
	root = insert(root,3);
	root = insert(root,1);
	root = insert(root,4);
	root = insert(root,9);
	root = insert(root,6);


	printTreeinfo(root);
	mirror(root);
	printTreeinfo(root);

	return 0;
}

