#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define Error -9999
typedef struct dnode_elm* dnode;
struct dnode_elm{
	int item;
	dnode next, prev;
};

dnode createList(void){ //빈리스트를 생성
	dnode h = (dnode)malloc(sizeof(struct dnode_elm));
	h->item = INT_MAX;
	h->next=h->prev=h;
	return h;
}
int isEmpty(dnode h) {//리스트 h가 비었는지 체크함. (비었으면 0 있으면 1)다.
	if (h->next==h && h->prev==h &&h->next==h->prev)
		return 1;
	if (h->next!=h && h->prev!=h &&h->next!=h->prev)
		return 0;
}
void splice(dnode a, dnode b, dnode t){ // a에서 b까지의 노드들을 떼어내, t노드 다음에 끼워 넣는 연산
	dnode z = a->prev;
	dnode c = b->next;
	dnode u = t->next;
	z->next = c;
	c->prev = z;
	a->prev = t;
	b->next = u;
	u->prev = b;
	t->next = a;
}
void moveAfter(dnode b, dnode a){ //노드 b를 노드 a 다음으로 이동하는 연산
	dnode x = b->prev;
	dnode y = b->next;
	dnode z = a->next;
	x->next = y;
	y->prev = x;
	b->prev = a;
	b->next = z;
	a->next = b;
	z->prev = b;
}
void insertAfter(dnode a, int value){ // item 값이 value인 새로운 노드 v를할당(malloc)받아 노드 a 다음에 삽입하는 연산
	dnode v = (dnode)malloc(sizeof(struct dnode_elm));
	dnode b = a->next;
	v->item = value;
	v->next = b;
	v->prev = a;
	a->next = v;
	b->prev = v;
}
void pushFront(dnode h, int item){ //: return insertAfter(h, item)(단, h는 리스트의 dummy 노드여야 함.)
	return insertAfter(h, item);
}
void pushBack(dnode h, int item){ // return insertAfter(h->prev, item)(단, h는 리스트의 dummy 노드여야 함.)
	return insertAfter(h->prev, item);
}
int deleteNode(dnode a){ // 노드 a를 삭제한 후 a->item을 리턴함. (단, a는dummy 노드이면 안됨!)
	if(a->item==INT_MAX || a==NULL)
		return Error;
	else{
		dnode b = a->prev;
		dnode c = a->next;
		int ai =a->item;
		b->next = c;
		c->prev = b;
		free(a);
		return ai;
	}
}
int popFront(dnode h) {
	return deleteNode(h->next);
}
int popBack(dnode h){
	return deleteNode(h->prev);
}
dnode findNext(dnode h, dnode from, int item){ // 리스트 h의 from 노드부터 차례로 노드를 방문하면서,
	//item 값을 저장한 첫 번째 노드를 리턴함. 만약 item값을 저장한 노드가 없다면 NULL을 리턴함.
	dnode v = from;
	for(; v!=h; v=v->next){
		if(v->item==item)
			return v;
	}
	return NULL;
}
void printList(dnode h){ //리스트 h의 노드부터 h->prev 노드까지 각 노드의item 값을 출력하는 함수. (출력 예: 3 --> 2 --> 1)
	dnode v = h->next;
	for(; v!=h; v=v->next)
		printf("%d -->", v->item);
	printf("end\n");
}

int main(void)
{
	int e, ea, eb;
	char cmd[20];
	dnode h,a,b,x;
	h = createList(); //더미노드
	while(1)
	{
		fflush(stdout);
		scanf("%s", cmd);
		if(strcmp(cmd, "pushf")==0) { // pushFront
			printf("넣을 값을 입력하시오.\n");
			fflush(stdout);
			scanf("%d", &e);
			pushFront(h,e);
			printList(h);
		}
		else if(strcmp(cmd, "popf")==0) { // popFront
			popFront(h);
			printList(h);
		}
		else if(strcmp(cmd, "insa")==0) { // insertAfter
			printf("노드 a의 오른쪽에 새로운 노드 b를 삽입한다.\n");
			printf("a와 b의 값을 차례로 입력:");
			fflush(stdout);
			scanf("%d %d", &ea, &eb);
			a = findNext(h, h->next, ea);
			if(a != NULL) insertAfter(a, eb);
			else
				printf("a를 찾지못했습니다.\n");
			printList(h);
		}
		else if(strcmp(cmd, "popb")==0){ // popBack
			popBack(h);
			printList(h);
		}
		else if(strcmp(cmd, "pushb")==0){ // pushBack
			printf("넣을 값을 입력하시오.\n");
			fflush(stdout);
			scanf("%d", &e);
			pushBack(h,e);
			printList(h);
		}
		else if(strcmp(cmd, "del")==0){ // deleteNode
			printf("삭제하려는 값을 입력하세요.\n");
			fflush(stdout);
			scanf("%d", &e);
			a = findNext(h, h->next, e);
			if(a != NULL) deleteNode(a);
			else
				printf("a를 찾지못했습니다.\n");

			printList(h);
		}
		else if(strcmp(cmd, "find")==0){ // findNext
			printf("찾으려는 값을 입력하세요.\n");
			fflush(stdout);
			scanf("%d ", &ea);
			a = findNext(h,h->next, ea);
			if(a!=NULL)
				printf("리스트에 값이 존재 합니다.\n");
			else
				printf("찾을수 없습니다.\n");
		}
		else if(strcmp(cmd, "splice")==0){ // splice
			printf("a에서 b까지의 노드들을 떼어내, t노드 다음에 끼워 넣는 연산입니다.\n노드 a, b, t의 값을 순서대로 입력해주세요.\n");
			fflush(stdout);
			scanf("%d %d %d", &ea, &eb, &e);
			a = findNext(h,h->next, ea);
			b = findNext(h,h->next, eb);
			x = findNext(h,h->next, e);
			if(a==NULL||b==NULL||x==NULL)
				printf("a, b 또는 t의 값을 찾을수 없습니다.\n");
			else splice(a,b,x);
			printList(h);
		}
		else if(strcmp(cmd, "movea")==0){ // moveAfter
			printf("노드 b를 노드 a 다음으로 이동하는 연산입니다.\n");
			printf("노드 a, b의 값을 순서대로 입력하세요.\n");
			fflush(stdout);
			scanf("%d %d", &ea, &eb);
			a = findNext(h,h->next, ea);
			b = findNext(h,h->next, eb);
			if(a==NULL||b==NULL)
				printf("a 또는b의 값을 찾을수 없습니다.\n");
			else moveAfter(b,a);
			printList(h);
		}
		else if(strcmp(cmd, "print")==0) { // print
			printList(h);
		}
		else if(strcmp(cmd, "empty")==0) { // isEmpty
			e = isEmpty(h);
			if(e==1)
				printf("리스트가 비어있습니다.\n");
			else
				printf("리스트가 비어있지 않습니다.\n");
		}
		else if(strcmp(cmd, "exit")==0) //exit
			break;
		else
			printf("다시 입력하시오\n");
	}
	return 0;
}


