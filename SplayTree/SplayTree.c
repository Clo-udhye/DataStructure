// Balanced Binary Search Tree - Splay tree 구현

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct binarytreenode * node;
struct binarytreenode{
	int key;
	node left,right,parent;
};

typedef struct btree * tree;
struct btree{
	node root;
	int size;
};

tree T; //트리 T를 전역변수으로 선언

tree createBtree(void) //비어있는 Binarytree를 하나 만든다.
{
	tree T= (tree)malloc(sizeof(struct btree));
	T->root=NULL;
	T->size=0;
	return T;
}

node createnode(int k) //k값을 key값으로 가지는 노드를 생성한다. 연결관계는 다 NULL로 설정
{
	node V = (node)malloc(sizeof(struct binarytreenode));
	V->key=k;
	V->left=V->right=V->parent=NULL;
	return V;
}

void insert(tree T, int key) //트리 T에서 key값의 자리를 찾은 후 key값을 가지는 새로운 노드를 생성
{
	node v, p = T->root, prev;
	prev = p;
	while(p != NULL) {
		prev = p;
		if(key < p->key) p = p->left;
		else p = p->right;
	}
	v = createnode(key);
	if(T->size == 0) T->root = v;
	else if(key < prev->key) prev->left = v;
	else prev->right = v;
	v->parent = prev;
	T->size++;
}

void printpreorder(node v){ //preorder traversal print순서 : MLR
	if(v !=NULL){
		printf("%d -->",v->key);
		printpreorder(v->left);
		printpreorder(v->right);
	}
}

void printinorder(node v){ //inorder traversal print순서 : LMR
	if(v!=NULL){
		printinorder(v->left);
		printf("%d --> ", v->key);
		printinorder(v->right);
	}
}

void printpostorder(node v){//postorder traversal print순서 : LRM
	if(v!=NULL){
		printpostorder(v->left);
		printpostorder(v->right);
		printf("%d --> ", v->key);
	}
}

void left_rotate( node x )  //left_rotate
{
	node y = x->right;
	if(y) { //y가 NULL이 아니면 if문 수행
		x->right = y->left;
		if( y->left ) y->left->parent = x; //y의 left가 NULL이 아니면 if문 수행
		y->parent = x->parent;
	}
	if( !x->parent ) T->root = y; //x의 parent가 NULL이면 수행 = x가 root노드 이면 수행.
	else if( x == x->parent->left ) x->parent->left = y; //x가 root노드가 아니고 x의 parent의 왼쪽노드이면 수행
	else x->parent->right = y; //x가 root노드가 아니고 x의 parent의 오른쪽노드이면 수행
	if(y) { //y가 NULL이 아니면 수행
		y->left = x;
		x->parent = y;
	}
}

void right_rotate( node x )  //right_rotate
{
	node y = x->left;
	if(y){ //y가 NULL이 아니면 수행
		x->left = y->right;
		if( y->right ) y->right->parent = x;//y의 right가 NULL이 아니면 if문 수행
		y->parent = x->parent;
	}
	if( !x->parent ) T->root = y; //x의 parent가 NULL이면 수행 = x가 root노드 이면 수행.
	else if( x == x->parent->left ) x->parent->left = y;//x가 root노드가 아니고 x의 parent의 왼쪽노드이면 수행
	else x->parent->right = y;//x가 root노드가 아니고 x의 parent의 오른쪽노드이면 수행
	if(y){ //y가 NULL이 아니면 수행
		y->right = x;
		x->parent = y;
	}
}

void splay( node x ) {
	while( x->parent )//x의 parent가 NULL일때 까지(=x가 root노드가 될때 까지) 반복
	{
		if( !x->parent->parent ){ //x의 조부모 노드가 NULL이면 수행(=x의 parent가 root노드 일때)
			if( x->parent->left == x ) right_rotate( x->parent ); //x가 x의 parent의 왼쪽노드일때 수행
			else left_rotate( x->parent ); //x가 x의 parent의 오른쪽노드일때 수행
		}
		else if( x->parent->left == x && x->parent->parent->left == x->parent ){ //x가 x의 부모노드의 왼쪽노드이고 x의 부모노드가 x의 조부모노드의 왼쪽노드일때 수행
			right_rotate( x->parent->parent );
			right_rotate( x->parent );
		}
		else if( x->parent->right == x && x->parent->parent->right == x->parent ){//x가 x의 부모노드의 오른쪽노드이고 x의 부모노드가 x의 조부모노드의 오른쪽노드일때 수행
			left_rotate( x->parent->parent );
			left_rotate( x->parent );
		}
		else if( x->parent->left == x && x->parent->parent->right == x->parent ){//x가 x의 부모노드의 왼쪽노드이고 x의 부모노드가 x의 조부모노드의 오른쪽노드일때 수행
			right_rotate( x->parent );
			left_rotate( x->parent );
		}
		else{//x가 x의 부모노드의 오른쪽노드이고 x의 부모노드가 x의 조부모노드의 왼쪽노드일때 수행
			left_rotate( x->parent );
			right_rotate( x->parent );
		}
	}
}

node search(tree T,int key){ //트리 T에서 key값을 갖는 노드를 찾는함수
	node p =T->root;
	while(p){
		if(p->key>key)
			p = p->left;
		else if(p->key<key)
			p = p->right;
		else return p;
	}
	return p;
}

void printtree(node p, int depth) //트리를 출력
{
	int i;
	if (p){
		printtree(p->left, depth+1); //p의 왼쪽 서브트리를 출력
		for (i = 1; i < depth; i++){
			printf("\t") ; // p의 레벨의 수만큼 tab출력
		}
		printf("%d  ", p->key); //p출력

		printtree(p->right, depth+1); //p의 오른쪽 서브트리를 출력
	}
}

int main(void){

	int value;
	char cmd[20];
	node v;
	//node x;

	T = createBtree();

	while(1) {
		fflush(stdout);
		scanf("%s", cmd);

		if(strcmp(cmd, "insert")==0) { // insert at tree
			fflush(stdout);
			scanf("%d", &value);
			insert(T, value);
		}
		else if(strcmp(cmd, "search")==0) { // search
			fflush(stdout);
			scanf("%d", &value);
			v = search(T, value);
			if(v != NULL) printf("%d is found!\n", v->key);
			else printf("Not found!\n");
		}
		else if(strcmp(cmd, "splay")==0) {
			fflush(stdout);
			scanf("%d", &value);
			v = search(T, value);
			splay(v);
		}
		else if(strcmp(cmd, "preorder")==0) {
			printpreorder(T->root);
			printf("\n");
		}
		else if(strcmp(cmd, "postorder")==0) {
			printpostorder(T->root);
			printf("\n");
		}
		else if(strcmp(cmd, "inorder")==0) {
			printinorder(T->root);
			printf("\n");
		}
		else if(strcmp(cmd, "printtree")==0) {
			printtree(T->root,1);
			printf("\n");
		}
		else if(strcmp(cmd, "exit")==0)
			break;
		else
			printf("Invalid command");
	}
	return 0;
}
