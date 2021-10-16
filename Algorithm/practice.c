#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node
{
	int key;
	struct _node* left;
	struct _node* right;
} TreeNode;

TreeNode* makeTreeNode(int key);
TreeNode* makeBST(int n);
TreeNode* insertBST(TreeNode* root, int key);
TreeNode* removeBST(TreeNode* root, int key);
TreeNode* searchBST(TreeNode* root, int key);
TreeNode* findMinBST(TreeNode* root);
void printBST(TreeNode* root);

int getHeightDiff(TreeNode* root);
int getHeight(TreeNode* root);
TreeNode* reBalance(TreeNode* root);
TreeNode* rotateLL(TreeNode* root);
TreeNode* rotateRR(TreeNode* root);
TreeNode* rotateLR(TreeNode* root);
TreeNode* rotateRL(TreeNode* root);

int main(void)
{
	int n;
	scanf("%d", &n);
	TreeNode* bstRoot = makeBST(n);
	printBST(bstRoot);
	printf("\n");

	TreeNode* findKey = NULL;
	int key; 
	for (int i = 0; i < n / 2; i++)
	{
		scanf("%d", &key);
		findKey = searchBST(bstRoot, key);
		if (findKey == NULL)
			printf("No result\n");
		else
			printf("result = %d\n", findKey->key);
	}
	for (int i = 0; i < n / 2; i++)
	{
		scanf("%d", &key);
		bstRoot = removeBST(bstRoot, key);
	}
	printBST(bstRoot);
	printf("\n");
	return 0;
}

TreeNode* makeTreeNode(int key)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
TreeNode* makeBST(int n)
{
	TreeNode* root = NULL;
	int key;
	for (int i = 0; i < n; i++)
	{
		key = rand() % 100 + 1;
		root = insertBST(root, key);
	}

	return root;
}
TreeNode* insertBST(TreeNode* root, int key)
{
	if (root == NULL)
		return makeTreeNode(key);
	else
	{
		if (root->key == key)
		{
			printf("Key duplicated\n");
			return root;
		}
		else if (root->key > key)
			root->left = insertBST(root->left, key);
		else
			root->right = insertBST(root->right, key);
	}

	root = reBalance(root);
	return root;
}
TreeNode* removeBST(TreeNode* root, int key)
{
	if (root == NULL)
	{
		printf("No Search result\n");
		return root;
	}

	if (root->key == key)
	{
		if (root->left != NULL && root->right != NULL)
		{
			TreeNode* temp = findMinBST(root->right);
			root->key = temp->key;
			root->right = removeBST(root->right, temp->key);
		}
		else if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		else
		{
			TreeNode* temp = root->left;
			if (temp == NULL)
				temp = root->right;
			free(root);
			return temp;
		}
	}
	else if (root->key > key)
		root->left = removeBST(root->left, key);
	else
		root->right = removeBST(root->right, key);

	root = reBalance(root);
	return root;
}
TreeNode* searchBST(TreeNode* root, int key)
{
	if (root == NULL)
		return NULL;

	if (root->key == key)
		return root;
	else if (root->key > key)
		return searchBST(root->left, key);
	else
		return searchBST(root->right, key);
}
TreeNode* findMinBST(TreeNode* root)
{
	TreeNode* ptr = root;
	while (ptr->left != NULL)
		ptr = ptr->left;
	return ptr; 
}
void printBST(TreeNode* root)
{
	if (root == NULL)
		return;

	printBST(root->left);
	printf(" %d", root->key);
	printBST(root->right);
}


int getHeightDiff(TreeNode* root)
{
	int lSH, rSH;

	if (root == NULL)
		return 0;

	lSH = getHeight(root->left);
	rSH = getHeight(root->right);
	return lSH - rSH;
}
int getHeight(TreeNode* root)
{
	int leftH, rightH;

	if (root == NULL)
		return 0;

	leftH = getHeight(root->left);
	rightH = getHeight(root->right);

	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1; 
}
TreeNode* reBalance(TreeNode* root)
{
	int heightDiff = getHeightDiff(root);

	if (heightDiff > 1)
	{
		if (getHeightDiff(root->left) > 0)
			root = rotateLL(root);
		else
			root = rotateLR(root);
	}

	if (heightDiff < -1)
	{
		if (getHeightDiff(root->right) < 0)
			root = rotateRR(root);
		else
			root = rotateRL(root);
	}

	return root;
}

TreeNode* rotateLL(TreeNode* root)
{
	if (root == NULL)
		return root;

	TreeNode* temp = root->left;

	root->left = temp->right;
	temp->right = root;

	return temp;
}
TreeNode* rotateRR(TreeNode* root)
{
	TreeNode* temp = root->right;

	root->right = temp->left;
	temp->left = root;

	return temp;
}
TreeNode* rotateLR(TreeNode* root)
{
	TreeNode* temp = root->left;

	root->left = rotateRR(root->left);
	return rotateLL(root);
}
TreeNode* rotateRL(TreeNode* root)
{
	TreeNode* temp = root->right;

	root->right = rotateLL(root->right);
	return rotateRR(root);
}