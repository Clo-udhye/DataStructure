#include <stdio.h>
#include <stdlib.h>

typedef struct treenode* node;
struct treenode {
	int key;
	node left, right, parent;
};
typedef struct btree* tree;
struct btree {
	node root;
	int size;
};

node createNode(int key)
{
	node v = (node)malloc(sizeof(struct treenode));
	v->key = key;
	v->left = v->right = v->parent = NULL;
	return v;
}
tree createTree(void)
{
	tree T = (tree)malloc(sizeof(struct btree));
	T->root = NULL;
	T->size = 0;
	return T;
}

node search(tree T, int key){
	node p = T->root;
	while(p!=NULL){
		if(p->key==key)
			return p;
		else if(p->key>key)
			p=p->left;
		else p=p->right;
	}
	return p;
}

void insert(tree T, int key){
	node v, p=T->root, parent;
	while (p!=NULL){
		parent = p;
		if(key<=p->key)
			p=p->left;
		else
			p=p->right;
	}
	v = createNode(key);
	if(T->size==0)
		T->root = v;
	else if(parent->key>=key)
		parent->left =v;
	else
		parent->right=v;
	v->parent = parent;
	T->size++;
}
void preorder(node v)
{
	if( v!=NULL ) {
		printf("%d --> ", v->key);
		preorder(v->left);
		preorder(v->right);
	}
}
void inorder(node v){
	if(v!=NULL){
		inorder(v->left);
		printf("%d --> ", v->key);
		inorder(v->right);
	}
}
void postorder(node v){
	if(v!=NULL){
		postorder(v->left);
		postorder(v->right);
		printf("%d --> ", v->key);
	}
}

void deleteByMerging(tree T, node p){
	//p!=NULL
	node temp, a, b, pt, new_root;
	a = p->left; b=p->right;
	if(p!=T->root){
		pt = p->parent;
		if(a==NULL){
			if(p==pt->left)
				pt->left = b;
			else
				pt->right = b;
			b->parent = pt;
		}
		else{
			if(p==pt->left)
				pt->left = a;
			else
				pt->right = a;
			a->parent = pt;
			temp = a;
			while(temp->right != NULL)
				temp = temp->right;
			temp->right = b;
			if(b!=NULL)
				b->parent = temp;
		}
	}
	else {
		if(a==NULL)
			new_root = b;
		else{
			new_root = a;
			temp = a;
			while(temp->right != NULL)
				temp = temp->right;
			temp -> right = b;
			if(b!=NULL)
				b->parent = temp;
		}
		T->root = new_root;
		if(new_root!=NULL)
			new_root ->parent = NULL;
	}
	free(p);
	T->size--;
}

void deleteByCopying(tree T, node p){
	//p!=NULL
	node a, b, max, pt;
	a = p->left; b=p->right;
	pt = p->parent;
	if(p!=T->root){
		if(a!=NULL){
			max = a;
			while(max->right!=NULL)
				max=max->right;
			p->key = max->key;
			if(max!=a)
				(max->parent)->right = max->left;
			else
				p->left = max->left;
			if(max->left!=NULL)
				(max->left)->parent = max->parent;
			free(max);
		}
		else //a==NULL
		{
			if(p==pt->right)
				pt->right = b;
			else
				pt->left = b;
			if(b!=NULL)
				b->parent = pt;
			free(p);
		}
	}
	else //p=T->root
	{
		if(a!=NULL){
			max = a;
			while(max->right!=NULL)
				max=max->right;
			p->key = max->key;
			if(max!=a)
				(max->parent)->right = max->left;
			else
				p->left = max->left;
			if(max->left!=NULL)
				(max->left)->parent = max->parent;
			free(max);
		}
		else //a=NULL
		{
			T->root = b;
			if(b!=NULL)
				b->parent = NULL;
			free(p);
		}
	}
	T->size--;
}

int main(void)
{
	int value;
	char cmd[20];
	node v;
	tree T = createTree();
	while(1) {
		fflush(stdout);
		scanf("%s", cmd);
		if(strcmp(cmd, "insert")==0) { // insert at tree
			fflush(stdout);
			scanf("%d", &value);
			insert(T, value);
		} else if(strcmp(cmd, "search")==0) { // search
			fflush(stdout);
			scanf("%d", &value);
			v = search(T, value);
			if(v != NULL) printf("%d is found!\n", v->key);
			else printf("Not found!\n");
		} else if(strcmp(cmd, "deleteM")==0) { // deleteByMerging
			fflush(stdout);
			scanf("%d", &value);
			v = search(T, value);
			if(v != NULL) deleteByMerging(T, v);
		} else if(strcmp(cmd, "deleteC")==0) { // deleteByCopying
			fflush(stdout);
			scanf("%d", &value);
			v = search(T, value);
			if(v != NULL) deleteByCopying(T, v);
		} else if(strcmp(cmd, "preorder")==0) { // preorder traversal
			preorder(T->root);
			printf("\n");
		} else if(strcmp(cmd, "postorder")==0) { // postorder traversal
			postorder(T->root);
			printf("\n");
		} else if(strcmp(cmd, "inorder")==0) { // inorder traversal
			inorder(T->root);
			printf("\n");
		} else if(strcmp(cmd, "exit")==0)
			break;
	} return 0;
}
