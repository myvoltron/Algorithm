#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
	int key;
	int height;
	struct tree_node* parent;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;

TreeNode* root;

void searchAndFixAfterInsertion(TreeNode* w);
int updateHeight(TreeNode* w);
int isBalanced(TreeNode* w);
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z);
int findMaxHeight(int left, int right);
int isExternal(TreeNode* w);
int isInternal(TreeNode* w);
void expandExternal(TreeNode* w);
TreeNode* searchAVLNode(TreeNode* root, int key);
void insertAVL(TreeNode* root, int key);
int findElemAVL(TreeNode* root, int key);
void preOrder(TreeNode* root);
void searchAndFixAfterRemoval(TreeNode* w);
TreeNode* reduceExternal(TreeNode* w);
TreeNode* sibling(TreeNode* z);
int removeAVL(TreeNode* root, int key);
TreeNode* inOrderSucc(TreeNode* w);

int main(void)
{
	char order;
	int key;
	int val;

	root = (TreeNode*)malloc(sizeof(TreeNode));
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;

	while (1)
	{
		scanf("%c", &order);
		getchar();

		if (order == 'i')
		{
			scanf("%d", &key);
			getchar();
			insertAVL(root, key);
		}
		else if (order == 'd')
		{
			scanf("%d", &key);
			getchar();
			val = removeAVL(root, key);
			if (val == 0)
				printf("X\n");
			else
				printf("%d\n", val);
		}
		else if (order == 's')
		{
			scanf("%d", &key);
			getchar();
			val = findElemAVL(root, key);
			if (val == 0)
				printf("X\n");
			else
				printf("%d\n", val);
		}
		else if (order == 'p')
		{
			preOrder(root);
			printf("\n");
		}
		else if (order == 'q')
			break;
	}
	return 0;
}


void searchAndFixAfterInsertion(TreeNode* w)
{
	TreeNode* x, * y, * z;
	w->left->height = 0;
	w->right->height = 0;
	w->height = 1;
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

	if (z->left->height > z->right->height) // z의 높은 자식을 y라 하자
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height) // y의 높은 자식을 x라 하자
		x = y->left;
	else
		x = y->right;

	restructure(x, y, z);
}
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z)
{
	TreeNode * a, * b, * c, * T0, * T1, * T2, * T3;
	if (z->key < y->key && y->key < x->key)
	{
		a = z, b = y, c = x;
		T0 = a->left, T1 = b->left, T2 = c->left, T3 = c->right;
	}
	else if (x->key < y->key && y->key < z->key)
	{
		a = x, b = y, c = z;
		T0 = a->left, T1 = a->right, T2 = b->right, T3 = c->right;
	}
	else if (z->key < x->key && x->key < y->key)
	{
		a = z, b = x, c = y;
		T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
	}
	else
	{
		a = y, b = x, c = z;
		T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
	}

	if (z->parent == NULL)//z가 루트인 경우
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

	a->left = T0;//b를 루트로 하는 부트리 제작
	T0->parent = a;
	a->right = T1;
	T1->parent = a;
	updateHeight(a);

	c->left = T2;
	T2->parent = c;
	c->right = T3;
	T3->parent = c;
	updateHeight(c);

	b->left = a;
	a->parent = b;
	b->right = c;
	c->parent = b;
	updateHeight(b);

	return b;
}
int findMaxHeight(int left, int right)
{
	if (left >= right)
		return left;
	return right;
}
int updateHeight(TreeNode* w)
{
	TreeNode* l, * r;
	l = w->left;
	r = w->right;

	int h = findMaxHeight(l->height, r->height) + 1;
	if (h != w->height)
	{
		w->height = h;
		return 1;
	}
	else 
		return 0;
}
int isBalanced(TreeNode* w)
{
	int gap;
	TreeNode* l, * r;
	l = w->left;
	r = w->right;
	if (l->height >= r->height)
		gap = l->height - r->height;
	else
		gap = r->height - l->height;

	if (gap < 2)
		return 1;
	else
		return 0;
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
void expandExternal(TreeNode* w)
{
	TreeNode* L = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* R = (TreeNode*)malloc(sizeof(TreeNode));

	L->left = NULL;
	L->right = NULL;
	L->parent = w;

	R->left = NULL;
	R->right = NULL;
	R->parent = w;

	w->left = L;
	w->right = R;
}
TreeNode* searchAVLNode(TreeNode* root, int key)
{
	if (isExternal(root))
		return root;

	if (root->key == key)
		return root;
	else if (root->key > key)
		return searchAVLNode(root->left, key);
	else
		return searchAVLNode(root->right, key);
}
void insertAVL(TreeNode* root, int key)
{
	TreeNode* w = searchAVLNode(root, key);
	if (isInternal(w))
		return;
	else
	{
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(w);
	}
}
int findElemAVL(TreeNode* root, int key)
{
	TreeNode* w = searchAVLNode(root, key);
	if (isExternal(w))
		return 0;
	return w->key;
}
void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;

	printf(" %d", root->key);
	if(!isExternal(root->left))
		preOrder(root->left);

	if (!isExternal(root->right))
		preOrder(root->right);
}

int removeAVL(TreeNode* root, int key)
{
	int e;
	TreeNode* w, * z, * y, * zs;
	
	w = searchAVLNode(root, key);
	if (isExternal(w))
		return 0;
	e = w->key;
	z = w->left;
	if (!isExternal(z))
		z = w->right;

	if (isExternal(z))
		zs = reduceExternal(z);
	else
	{
		y = inOrderSucc(w);
		z = y->left;
		w->key = y->key;
		zs = reduceExternal(z);
	}

	searchAndFixAfterRemoval(zs->parent);
	return e;
}
TreeNode* reduceExternal(TreeNode* z)
{
	TreeNode* w = z->parent;
	TreeNode* zs = sibling(z);

	if (w->parent == NULL)
	{
		root = zs;
		zs->parent = NULL;
	}
	else
	{
		TreeNode* g = w->parent;
		zs->parent = g;
		if (w == g->left)
			g->left = zs;
		else
			g->right = zs;
	}
	free(z);
	free(w);
	return zs;
}
TreeNode* sibling(TreeNode* z)
{
	if (z->parent == NULL)
		exit(1);

	if (z->parent->left == z)
		return z->parent->right;
	else
		return z->parent->left;
}
TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->left;
	if (isExternal(w))
		exit(1);
	while (isInternal(w->left))
		w = w->left;
	return w;
}
void searchAndFixAfterRemoval(TreeNode* w)
{
	TreeNode* x, * y, * z;
	z = w;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->left->height > z->right->height) // z의 높은 자식을 y라 하자
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height) // y의 높은 자식을 x라 하자
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;
	else
	{
		if (z->left == y)
			x = y->left;
		else
			x = y->right;
	}

	TreeNode* b = restructure(x, y, z);
	if (b->parent == NULL)
		return;
	searchAndFixAfterRemoval(b->parent);
}