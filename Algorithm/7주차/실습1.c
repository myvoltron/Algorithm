#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

AVLNode* makeNode(int key);
AVLNode* insertAVL(AVLNode* root, int key);

int getHeight(AVLNode* root);
int getBalance(AVLNode* root);
AVLNode* reBalance(AVLNode* root);
AVLNode* rotateRight(AVLNode* parent);
AVLNode* rotateLeft(AVLNode* parent);

void preOrder(AVLNode* root);

int main(void)
{
	AVLNode* root = NULL;
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		root = insertAVL(root, rand() % 100 + 1);
		preOrder(root);
		printf("\n");
	}
	return 0;
}

AVLNode* makeNode(int key)
{
	AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
AVLNode* insertAVL(AVLNode* root, int key)
{
	if (root == NULL)
		return makeNode(key);

	if (root->key > key)								// 
		root->left = insertAVL(root->left, key);
	else if (root->key < key)							//
		root->right = insertAVL(root->right, key);		
	else												// 중복된 키 
		return root;

	reBalance(root);
	return root;
}

int getHeight(AVLNode* root)
{
	if (root == NULL)
		return 0;

	int leftH, rightH;
	leftH = getHeight(root->left);
	rightH = getHeight(root->right);

	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}
int getBalance(AVLNode* root)
{
	if (root == NULL)
		return 0;

	return getHeight(root->left) - getHeight(root->right);
}
AVLNode* reBalance(AVLNode* root)
{
	int bal = getBalance(root);

	if (bal > 1)
	{

	}
	else if (bal < -1)
	{

	}
}
AVLNode* rotateRight(AVLNode* parent)
{
	AVLNode* c = parent->left;

}
AVLNode* rotateLeft(AVLNode* parent);
void preOrder(AVLNode* root)
{
	if (root == NULL)
		return;

	printf(" %d", root->key);
	preOrder(root->left);
	preOrder(root->right);
}
