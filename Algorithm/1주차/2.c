#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _btreeNode
{
	struct _btreeNode* left;
	struct _btreeNode* right;
	int num;
} BTreeNode;

typedef BTreeNode TreeNode;

TreeNode* makeTree();
TreeNode* makeTreeNode(int num);
void makeLeftSubTree(TreeNode* root, TreeNode* left);
void makeRightSubTree(TreeNode* root, TreeNode* right);
TreeNode* findNode(TreeNode* root, int num);
void preOrder(TreeNode* root);
void traverseTree(TreeNode* root);

int main(void)
{
	TreeNode* root = makeTree();
	//preOrder(root);
	traverseTree(root);
	return 0;
}

TreeNode* makeTree()
{
	int numOfNode;
	int root, left, right;
	TreeNode* newTree;

	scanf("%d", &numOfNode);

	scanf("%d %d %d", &root, &left, &right);
	newTree = makeTreeNode(root);
	makeLeftSubTree(newTree, makeTreeNode(left));
	makeRightSubTree(newTree, makeTreeNode(right));

	for (int i = 1; i < numOfNode; i++)
	{
		scanf("%d %d %d", &root, &left, &right);

		TreeNode* temp = findNode(newTree, root);

		if (left != 0)
			makeLeftSubTree(temp, makeTreeNode(left));
		if (right != 0)
			makeRightSubTree(temp, makeTreeNode(right));
	}
	return newTree;
}
TreeNode* makeTreeNode(int num)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->num = num;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void makeLeftSubTree(TreeNode* root, TreeNode* left)
{
	root->left = left;
}
void makeRightSubTree(TreeNode* root, TreeNode* right)
{
	root->right = right;
}

TreeNode* findNode(TreeNode* root, int num)
{
	if (root == NULL)
		return NULL;
	if (root->num == num) // 이게 먼저 오면 오류가 남 root가 null인데도 num을 참조하게 됨
		return root;

	TreeNode* pnode = findNode(root->left, num);
	if (pnode)
		return pnode;

	return findNode(root->right, num);
}

void preOrder(TreeNode* root)
{
	if (root == NULL)
		return;

	printf("[%d] ", root->num);
	preOrder(root->left);
	preOrder(root->right);
}

void traverseTree(TreeNode* root)
{
	int numOfTraver;
	char traverInfo[101]; // only string L or R 

	scanf("%d", &numOfTraver);
	for (int i = 0; i < numOfTraver; i++)
	{
		int strLen;
		TreeNode* pnode = root;

		scanf("%s", traverInfo);
		strLen = strlen(traverInfo);

		printf(" %d", pnode->num);
		for (int j = 0; j < strLen; j++)
		{
			if (traverInfo[j] == 'L')
			{
				pnode = pnode->left;
				if (pnode == NULL)
					break;

				printf(" %d", pnode->num);
			}
			else if (traverInfo[j] == 'R')
			{
				pnode = pnode->right;
				if (pnode == NULL)
					break;

				printf(" %d", pnode->num);
			}
		}
		printf("\n");
	}
}

/*
9
5 3 9
3 8 15
8 0 2
2 0 0
15 0 0
9 7 10
7 12 0
12 0 0
10 0 0
3
RLL
LL
LR
*/