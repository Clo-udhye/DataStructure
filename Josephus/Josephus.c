#include <stdio.h>
#include <limits.h>

typedef struct node_elm* node;
struct node_elm {
	int item;
	node next;
};

node createCList(void){ //빈 리스트 생성
	node D = (node)malloc(sizeof(struct node_elm));
	D->item = INT_MAX;
	D->next = D;
	return D;
}
void insertAtFront(node D, int value){ //dummy노드 뒤에 (가장앞에) 새로운 노드를 생성
	node v = (node)malloc(sizeof(struct node_elm));
	v->item = value;
	v->next = D->next;
	D->next = v;
}
node deleteNode(node x, node px){ //노드 x를 삭제, px는 x 전의 노드
	px->next = x->next;
	printf("%d ",x->item); //삭제할 노드의 item값을 출력
	free(x);
	return px;
}
node searchPNode(node D,node v,  int k){ //리스트D에서 v노드로 부터 k번째 노드를 찾아 전 노드를 리턴(dummy노드는 갯수로 세지 않는다.)
	node x, px;
	int i;
	x=v;
	for(i=0; i<k; i++){
		if(x==D)
			i--;
		px=x;
		x=x->next;
		if(x->next==px) //리스트에 노드가 하나 남았을때 dummy노드를 리턴
			return D;
	}
	if(x==D)
		x=D->next;
	return px;
}
int Josephus(int n, int k){
	node D = createCList(); //빈리스트 생성
	node px;
	int i;
	for(i=n; i>0; i--){ //n개만큼 노드 생성
		insertAtFront(D, i);
	}
	px = searchPNode(D, D->next, k);
	printf("탈락하는 사람의 순서는 : ");
	while(1){
		px = deleteNode(px->next, px);
		px = searchPNode(D, px->next, k);
		if(px==D) //리스트에 노드가 하나 남았을때 반복문에서 빠져나옴
			break;
	}
	return ((D->next)->item); //남은 한개의 노드의 item값을 리턴
}

int main(void){
	int n, k;
	printf("n과 k를 입력해주세요 : ");
	fflush(stdout);
	scanf("%d %d", &n, &k);
	printf("\n\n 마지막으로 남은 사람은 : %d", Josephus(n, k));
}
