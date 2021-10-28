#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, z) ((z) = (x), (x) = (y), (y) = (z))
#define SIZE	100 

typedef struct _treenode
{
	int key;
	int height;
	struct _treenode* parent;
	struct _treenode* left;
	struct _treenode* right;
} TreeNode;

TreeNode* root;

TreeNode* getNode()
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

int isExternal(TreeNode* w)
{
	if (w->left == NULL && w->right == NULL)
		return 1;
	else
		return 0;
}
int isInternal(TreeNode* w)
{
	if (w->left != NULL || w->right != NULL)
		return 1;
	else
		return 0;
}
TreeNode* sibling(TreeNode* w)
{
	if (w->parent == NULL)
		exit(1);
	if (w->parent->left == w)
		return w->parent->right;
	else
		return w->parent->left;
}
void expandExternal(TreeNode* w)
{
	TreeNode* left, *right;
	left = getNode();
	right = getNode();

	left->height = 0;
	right->height = 0;
	left->parent = w;
	right->parent = w;

	w->left = left;
	w->right = right;
	w->height = 1;
}
TreeNode* reduceExternal(TreeNode* z)
{
	TreeNode* w, * zs, * g;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL)
	{
		root = zs;
		zs->parent = NULL;
	}
	else
	{
		g = w->parent;
		zs->parent = g;
		if (g->left == w)
			g->left = zs;
		else
			g->right = zs;
	}

	free(z);
	free(w);
	return zs; 
	
}
TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->right;
	while (isInternal(w->left))
		w = w->left;
	return w;
}

TreeNode* treeSearch(TreeNode* w, int key);
int findElement(int key);
void insertItem(int key);
int removeElement(int key);
void preOrderPrint(TreeNode* root);

void searchAndFixAfterInsertion(TreeNode* w);
int updateHeight(TreeNode* w);
int isBalanced(TreeNode* w);
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z);

int main(void)
{
	char opCode;
	int loop = 1, key, val; 

	root = getNode();

	while (loop)
	{
		scanf("%c", &opCode);
		getchar();

		switch (opCode)
		{
		case 'i':
			scanf("%d", &key);
			getchar();
			insertItem(key);
			break;
		case 'd':
			scanf("%d", &key);
			getchar();
			val = removeElement(key);
			if (val == -1)
				printf("X\n");
			else
				printf("%d\n", val);
			break;
		case 's':
			scanf("%d", &key);
			getchar();
			val = findElement(key);
			if (val == -1)
				printf("X\n");
			else
				printf("%d\n", val);
			break;
		case 'p':
			preOrderPrint(root);
			printf("\n");
			break;
		case 'q':
			loop = 0;
			break;
		}
	}
	return 0;
}

TreeNode* treeSearch(TreeNode* w, int key)
{
	if (isExternal(w))
		return w;

	if (w->key == key)
		return w;
	else if (w->key > key)
		return treeSearch(w->left, key);
	else
		return treeSearch(w->right, key);
}
int findElement(int key)
{
	TreeNode* w = treeSearch(root, key);
	if (isExternal(w))
		return -1;
	else
		return w->key;
}
void insertItem(int key)
{
	TreeNode* w = treeSearch(root, key);

	if (isInternal(w))
		return;
	else
	{
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(w);
	}
}
int removeElement(int key)
{
	TreeNode* z, * y, * zs, * w;
	int keyVal;

	w = treeSearch(root, key);
	if (isExternal(w))
		return -1;

	z = w->left;
	keyVal = w->key;
	if (!isExternal(z))
		z = w->right;
	if (isExternal(z))
		zs = reduceExternal(z);
	else
	{
		y = inOrderSucc(w); // 오른쪽에서 제일 왼쪽 
		z = y->left;
		w->key = y->key;
		zs = reduceExternal(z);
	}

	return keyVal;
}
void preOrderPrint(TreeNode* root)
{
	if (isExternal(root))
		return;

	printf(" %d", root->key);
	preOrderPrint(root->left);
	preOrderPrint(root->right);
}

void searchAndFixAfterInsertion(TreeNode* w)
{
	TreeNode* x, * y, * z;
	if (w->parent == NULL)
		return;

	z = w->parent;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)
		x = y->left;
	else
		x = y->right;

	restructure(x, y, z);
}
int updateHeight(TreeNode* w)
{
	int left, right, h;
	left = w->left->height, right = w->right->height;

	if (left > right)
		h = left + 1;
	else
		h = right + 1;

	if (w->height != h)
	{
		w->height = h;
		return 1;
	}
	else
		return 0;
}
int isBalanced(TreeNode* w)
{
	int left, right, diff;
	left = w->left->height;
	right = w->right->height;

	if (left >= right)
		diff = left - right;
	else
		diff = right - left;

	if (diff < 2)
		return 1;
	else
		return 0;
}
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z)
{
	TreeNode* a, * b, * c, * t0, * t1, * t2, * t3;

	if (z->key > y->key && y->key > x->key)
	{
		a = x, b = y, c = z;
		t0 = a->left, t1 = a->right, t2 = b->right, t3 = c->right;
	}
	else if (z->key > y->key && y->key < x->key)
	{
		a = y, b = x, c = z; 
		t0 = a->left, t1 = b->left, t2 = b->right, t3 = c->right;
	}
	else if (z->key < y->key && y->key < x->key)
	{
		a = z, b = y, c = x;
		t0 = a->left, t1 = b->left, t2 = c->left, t3 = c->right;
	}
	else
	{
		a = z, b = x, c = y;
		t0 = a->left, t1 = b->left, t2 = b->right, t3 = c->right;
	}

	// root setting 
	if (z->parent == NULL)
	{
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z)
	{
		z->parent->left = b;
		b->parent = z->parent;
	}
	else
	{
		z->parent->right = b;
		b->parent = z->parent;
	}

	t0->parent = a;
	t1->parent = a;
	a->left = t0;
	a->right = t1;
	updateHeight(a);

	t2->parent = c;
	t3->parent = c;
	c->left = t2;
	c->right = t3;
	updateHeight(c);

	a->parent = b;
	c->parent = b;
	b->left = a;
	b->right = c;
	updateHeight(b);

	return b;
}