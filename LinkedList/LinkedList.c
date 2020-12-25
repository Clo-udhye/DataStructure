#include <stdio.h>
#include <string.h>

typedef struct node_elm* node;

struct node_elm{
	int item;
	node next;
};

node insertAtHead(node head, int val){
	node v = (node)malloc(sizeof(struct node_elm));
	v->item = val;
	v->next = head;
	return v;
}

node deleteFromHead(node head){
	if(head != NULL){
		node old = head;
		head = head->next;
		free(old);
	}
	return head;
}
node deleteFromTail(node head){
	node tail, prev=NULL;
	if(head==NULL)
		return NULL;
	for(tail=head; tail->next!=NULL; tail=tail->next)
		prev=tail;
	if(prev!=NULL)
		prev->next = NULL;
	free(tail);
	if(prev==NULL) return NULL;
	else return head;
}
node findTail(node head){
	node tail;
	if(head==NULL)
		return NULL;
	for(tail=head; tail->next!=NULL; tail=tail->next);
	return tail;
}
void printList(node v){
	while(v!=NULL){
		printf("%d ", v->item);
		v = v->next;
	}
}
int sumOfList(node head){
	int s=0;
	for(;head!=NULL;head=head->next)
		s += head->item;
	return s;
}
int maxOfList(node head){
	int m=head->item;
	for(head=head->next;head!=NULL;head=head->next)
	{
		if(m < head->item)
			m = head->item;
	}
	return m;
}


void main(void) {
	node head = NULL;
	char com[10];
	int value, d, sum, max;
	while (1) {
		fflush(stdout);
		scanf("%s", com);
		if (strcmp(com, "in") == 0) { // insert하라는 명령
			scanf("%d", &value); // insert할 값을입력받음
			head = insertAtHead(head, value);
			printf("%d is inserted at head \n", value);
			printList(head);
			printf("\n");
		}
		else if (strcmp(com, "dh") == 0) { // Head delete하라는 명령
			printf("%d is deleted from head: \n", head->item);
			head = deleteFromHead(head);
			printList(head);
			printf("\n");
		}
		else if (strcmp(com, "dt") == 0) { // Tail delete하라는 명령
			node tail = findTail(head);
			if(tail != NULL)
				printf("%d is deleted from tail: \n", tail->item);
			head = deleteFromTail(head);
			printList(head);
			printf("\n");
		}
		else if (strcmp(com, "ft") == 0) { // findtail
			node tail = findTail(head);
			if(tail != NULL)
				printf("tail node = %d\n", tail->item);
		}
		else if (strcmp(com, "print") == 0) { // 노드들의 출력
			printList(head);
			printf("\n");
		}
		else if (strcmp(com, "sum") == 0) { // 노드들의 합 계산
			sum = sumOfList(head);
			printf("Sum of list = %d\n", sum);
		}
		else if (strcmp(com, "max") == 0) { // 노드들의 최대값 계산
			max = maxOfList(head);
			printf("Maximum of list = %d\n", max);
		}
		else if (strcmp(com, "exit") == 0) // 프로그램을 종료함
			break;
		else printf(" No legal command\n");
	}
}
