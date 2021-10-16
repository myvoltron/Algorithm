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
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z);

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

// remove 
//int removeBST(Tree* tree, int key);
//TreeNode* inOrderSucc(TreeNode* w);
TreeNode* sibling(TreeNode* w);
//TreeNode* reduceExternal(TreeNode* z, Tree* tree);


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
		/*else if (order == 'd')
		{
			scanf("%d", &key);
			getchar();
			val = removeBST(&tree, key);
			if (val == 0)
				printf("X\n");
			else
				printf("%d\n", val);
		}*/
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
	updateHeight(w); // 높이 정보 업데이트 

	TreeNode* ptr = w;
	int result = 1;
	while (ptr->parent != NULL && result == 1)
	{
		result = isBalanced(ptr->parent);
		ptr = ptr->parent;
	}
	if (result == 1)
		return;

	TreeNode* z = ptr;
	TreeNode* y = NULL;
	if (z->left->height >= z->right->height) // z의 높은 자식을 y라 하자
		y = z->left;
	else
		y = z->right;
	TreeNode* x = NULL;
	if (y->left->height >= y->right->height) // y의 높은 자식을 x라 하자
		x = y->left;
	else
		x = y->right;

	if (tree->root = ptr)
	{
		tree->root = restructure(x, y, z);
		tree->root->parent = NULL;
		return;
	}
	if(ptr->parent->left == ptr)
		ptr->parent->left = restructure(x, y, z);
	else 
		ptr->parent->right = restructure(x, y, z);




	//if (isInternal(z->left) && isInternal(z->right))
	//{
	//	if (z->left->height > z->right->height) // z의 높은 자식을 y라 하자
	//		y = z->left;
	//	else
	//		y = z->right;
	//}
	//else
	//{
	//	if (isInternal(z->left))
	//		y = z->left;
	//	else
	//		y = z->right;
	//}

	
	//if (isInternal(y->left) && isInternal(y->right))
	//{
	//	if (y->left->height > y->right->height) // y의 높은 자식을 x라 하자
	//		x = y->left;
	//	else
	//		x = y->right;
	//}
	//else
	//{
	//	if (isInternal(y->left))
	//		x = y->left;
	//	else
	//		x = y->right;
	//}
}
TreeNode* restructure(TreeNode* x, TreeNode* y, TreeNode* z)
{
	if (z->left == y && y->left == x)
	{
		z->left = y->right;
		y->right = z;
	}
	if (z->right == y && y->right == x)
	{
		z->right = y->left;
		y->left = z;
	}
	if (z->left == y && y->right == x)
	{
		y->right = x->left;
		x->left = y;

		z->left = x;

		z->left = y->right;
		y->right = z;
	}
	if (z->right == y && y->left == x)
	{
		y->left = x->right;
		x->right = y;

		z->right = x;

		z->right = y->left;
		y->left = z;
	}

	return y;
}
int updateHeight(TreeNode* w)
{
	if (w->parent == NULL)
		return 0;
	if(isInternal(sibling(w)))
		return 0;

	while (w->parent != NULL)
	{
		w->parent->height = w->height + 1;
		w = w->parent;
	}
	return 1;
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
		// updateHeight(w); // 높이 정보 업데이트 
		/*preOrder(tree->root);
		printf("\n");*/
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

//int removeBST(Tree* tree, int key)
//{
//	TreeNode* w = searchBSTNode(tree->root, key);
//	if (isExternal(w))
//		return 0;
//
//	int e = w->key;
//
//	TreeNode* z = w->left;
//	if (!isExternal(z))
//		z = w->right;
//	if (isExternal(z))
//	{
//		TreeNode* zs = sibling(z);
//		zs = reduceExternal(z, tree);
//	}
//	else
//	{
//		TreeNode* y = inOrderSucc(w);
//		z = y->left;
//		w->key = y->key;
//		TreeNode* zs = sibling(z);
//		zs = reduceExternal(z, tree);
//	}
//
//	return e;
//}
//TreeNode* inOrderSucc(TreeNode* w)
//{
//	w = w->right;
//	if (isExternal(w))
//		exit(1);
//	while (isInternal(w->left))
//		w = w->left;
//	return w;
//}
TreeNode* sibling(TreeNode* w)
{
	if (w->parent == NULL)
		exit(1);

	if (w->parent->left == w)
		return w->parent->right;
	else
		return w->parent->left;
}
//TreeNode* reduceExternal(TreeNode* z, Tree *tree)
//{
//	TreeNode* w = z->parent;
//	TreeNode* zs = sibling(z);
//
//	if (w->parent == NULL)
//	{
//		tree->root = zs;
//		tree->root->parent = NULL;
//	}
//	else
//	{
//		TreeNode* g = w->parent;
//		zs->parent = g;
//		if (w == g->left)
//			g->left = zs;
//		else
//			g->right = zs;
//	}
//
//	free(z);
//	free(w);
//	return zs; 
//}
