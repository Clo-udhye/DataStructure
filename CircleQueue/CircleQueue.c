#include <stdio.h>
#include <string.h>
#define MAXSIZE 15
void enqueue(int value);
int dequeue();
int size();
int front();
int Q[MAXSIZE] = {0};
int startPos = 0, endPos = -1;

void main(void) {
	char com[10];
	int d;
	while (1)
	{
		printf("(en)Enqueue, (de)Dequeue, (size)print size of Queue, (front)front Enqueue, (quit), (print)\n");
		fflush(stdout);
		scanf("%s", com);
		if (strcmp(com, "en") == 0) {
			fflush(stdout);
			scanf("%d", &d);
			if (d <= 0) {
				printf("양의 정수만 취급\n");
				continue;
			}
			else
			{
				enqueue(d);
				if(size()!=MAXSIZE)
					printf(" # value %d is enqueued to Q \n", d);

			}
		}
		else if (strcmp(com, "de") == 0) {
			int k = dequeue();
			if(k!=-1)
				printf(" * value %d is dequeued from Q \n", k);
		}
		else if (strcmp(com, "size") == 0) {
			printf(" $ size of Q is %d \n", size( ));
		}
		else if (strcmp(com, "front") == 0) {
			printf(" @ front of Q is %d\n", front( ));
		}
		else if (strcmp(com, "quit") == 0) {
			break;
		}
		else if (strcmp(com, "print") == 0) {
			int k;
			if(size() ==0)
			{
				printf("Circular Queue is empty\n");
			} else{
				for(k=0; k< MAXSIZE ; k++){
					if(Q[k]!=0){
						printf("%d", Q[k]);
						printf("\n");
					}
				}
			}
		}
		else
			printf(" No legal command\n");
	}
}

void enqueue(int value){
	if(size()==MAXSIZE)
	{
		printf("Circular Queue is full\n");
	}
	else
		Q[(++endPos)%MAXSIZE] = value;
}
int dequeue(){
	if(size()==0)
	{
		printf("Circular Queue is empty\n");
		return -1;
	}
	int temp= Q[startPos%MAXSIZE];
	Q[startPos++%MAXSIZE]=0;
	return (temp);
}
int size(){
	return (endPos-startPos+1);
}
int front(){
	return (Q[startPos%MAXSIZE]);
}
