#include <stdio.h>
#include <stdlib.h>
#define MAX 4
void PUSH(int num);
int POP();
int STACK[MAX] = {0}, top = -1;
int main(void){
	FILE *fp ;
	int A[MAX],B[MAX]={0};
    int i, count, k=1, j;
	fp = fopen( "stack.txt", "w" );
	fprintf( fp, "%d\n", MAX );
	fprintf( fp, "%d\n", 4 );
	fprintf( fp, "%d\n", 2 );
	fprintf( fp, "%d\n", 1 );
	fprintf( fp, "%d\n", 3 );


	fclose( fp ) ;

	fp = fopen( "stack.txt", "r" );
	fscanf( fp, "%d", &count);

	for( i = 0 ; i < MAX ; i++ )
		fscanf( fp, "%d", &A[i] );
	fclose(fp) ;

	for(i=0; i<MAX; i++){
		PUSH(A[i]);
		for(j=0; j<i; j++)
		{
			if(STACK[top]==k){
				B[k-1] = POP();
				k++;
			}
		}
	}
	printf("\n");
	if(k-1==MAX)
	{
		for(i=0; i<MAX; i++)
			printf("B[%d] = %d\n",i, B[i]);

	}
	else
		printf("IMPOSSBLE");
}
void PUSH(int num){
/* STACK의 Push 기능을 수행하도록 구현 */
	STACK[++top] = num;
	printf("PUSH(%d) ", num);
}

int POP(){
/* STACK의 Pop 기능을 수행하도록 구현 */
	printf("POP ");
	return STACK[top--];
}
