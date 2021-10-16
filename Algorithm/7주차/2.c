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

typedef struct tree
{
	TreeNode* root;
} Tree;

// AVL function 
void searchAndFixAfterInsertion(TreeNode* w, Tree* tree);
int updateHeight(TreeNode* w);
int isBalanced(TreeNode* w);
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z, Tree* tree);

// Tree function 
int isExternal(TreeNode* w);
int isInternal(TreeNode* w);
void expandExternal(TreeNode* w);

// BST function 
void initBST(Tree* tree);
TreeNode* searchBSTNode(TreeNode* root, int key);
void insertBST(Tree* tree, int key);
int findElemBST(Tree* tree, int key);
void preOrder(TreeNode* root);
int findMaxHeight(int left, int right);

int main(void)
{
	char order;
	int key;
	int val;

	Tree tree;
	initBST(&tree);

	while (1)
	{
		scanf("%c", &order);
		getchar();

		if (order == 'i')
		{
			scanf("%d", &key);
			getchar();
			insertBST(&tree, key);
		}
		else if (order == 's')
		{
			scanf("%d", &key);
			getchar();
			val = findElemBST(&tree, key);
			if (val == 0)
				printf("X\n");
			else
				printf("%d\n", val);
		}
		else if (order == 'p')
		{
			preOrder(tree.root);
			printf("\n");
		}
		else if (order == 'q')
			break;
	}
	return 0;
}

void searchAndFixAfterInsertion(TreeNode* w, Tree* tree)
{
	TreeNode* x, * y, * z;	
	if (w->parent == NULL) // root 노드이면 그만둠 
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

	if (z->left->height >= z->right->height) // z의 높은 자식을 y라 하자
		y = z->left;
	else
		y = z->right;
	if (y->left->height >= y->right->height) // y의 높은 자식을 x라 하자
		x = y->left;
	else
		x = y->right;

	restructure(x, y, z, tree);
}
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z, Tree* tree)
{
	TreeNode* a, * b, * c;
	TreeNode* T0, * T1, * T2, * T3;

	if (z->key > y->key && y->key > x->key)
	{
		a = x, b = y, c = z;
		T0 = a->left, T1 = a->right, T2 = b->right, T3 = c->right;
	}
	else if (z->key > y->key && y->key < x->key)
	{
		a = y, b = x, c = z;
		T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
	}
	else if (z->key < y->key && y->key < x->key)
	{
		a = z, b = y, c = x;
		T0 = a->left, T1 = b->left, T2 = c->left, T3 = c->right;
	}
	else
	{
		a = z, b = x, c = y;
		T0 = a->left, T1 = b->left, T2 = b->right, T3 = c->right;
	}

	if (z->parent == NULL)					// z가 루트노드라면 
	{
		tree->root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z)			// z가 부모노드의 왼쪽 자식이라면 
	{
		z->parent->left = b;
		b->parent = z->parent;
	}
	else									// z가 부모노드의 오른쪽 자식이라면 
	{
		z->parent->right = b;
		b->parent = z->parent;
	}

	a->left = T0;
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
	/*
	         b
		   /   \
	      a      c    
	*/
	return b; 
}
int findMaxHeight(int left, int right)
{
	if (left > right)
		return left;
	return right;
}
int updateHeight(TreeNode* w)
{
	TreeNode* left = w->left;
	TreeNode* right = w->right;

	int h = findMaxHeight(left->height, right->height) + 1;
	if (h != w->height)
	{
		w->height = h;
		return 1;
	}

	return 0;
}
int isBalanced(TreeNode* w)
{
	if (w->left->height - w->right->height > 1 || w->left->height - w->right->height < -1)
		return 0;
	return 1;
}

int isExternal(TreeNode* w)
{
	if (w->left == NULL && w->right == NULL)
		return 1;
	return 0;
}
int isInternal(TreeNode* w)
{
	if (w->left != NULL && w->right != NULL)
		return 1;
	return 0;
}
void expandExternal(TreeNode* w)
{
	TreeNode* L = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* R = (TreeNode*)malloc(sizeof(TreeNode));

	L->left = NULL;
	L->right = NULL;
	L->parent = w;
	L->height = 0;

	R->left = NULL;
	R->right = NULL;
	R->parent = w;
	R->height = 0;

	w->left = L;
	w->right = R;
	w->height = 1;
}

void initBST(Tree* tree)
{
	tree->root = (TreeNode*)malloc(sizeof(TreeNode));
	tree->root->parent = NULL;
	tree->root->left = NULL;
	tree->root->right = NULL;
	tree->root->height = 0;
}
TreeNode* searchBSTNode(TreeNode* root, int key)
{
	if (isExternal(root))
		return root;

	if (root->key == key)
		return root;
	else if (root->key > key)
		return searchBSTNode(root->left, key);
	else
		return searchBSTNode(root->right, key);
}
void insertBST(Tree* tree, int key)
{
	TreeNode* w = searchBSTNode(tree->root, key);
	if (isInternal(w))
		return;
	else
	{
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(w, tree);
	}
}
int findElemBST(Tree* tree, int key)
{
	TreeNode* w = searchBSTNode(tree->root, key);
	if (isExternal(w))
		return 0;
	return w->key;
}
void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;

	printf(" %d", root->key);
	preOrder(root->left);
	preOrder(root->right);
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
