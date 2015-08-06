#ifndef BITREE_H
#define BITREE_H
typedef struct BiTreeNode_{
	void *data;
	struct BiTreeNode_ *left;
	struct BiTreeNode_ *right;
}BiTreeNode;

typedef struct BiTree_{
	int size;
	int (*compare)(const void *key1,const void *key2);
	void (*destroy)(void *data);
	BiTreeNode *root;
}BiTree;
#define bitree_size(tree)   ((tree)->size)
#define bitree_root(tree)   ((tree)->root)
#define bitree_is_eob(node) ((node) == NULL)
#endif
