#include <stdio.h>
#include <time.h>
#include <stdlib.h>

clock_t before;
void start_time(void) {	// 정렬 시작시간을 체크하는 함수
	before = clock();
}

void prn_time(void) {	// 정렬시간을 출력하는 함수
	double user_time;
	user_time = (double)(clock() - before)/CLOCKS_PER_SEC;
	//before = clock();
	printf("Time = %3.3lf seconds \n", user_time);
}

void select_sort(int A[], int n) {	// selection정렬 함수
	int j, k;
	for( j = 0; j < n-1; j++ ) {
		k = find_min(A, j, n);
		swap (&A[k], &A[j]);
	}
}
void swap(int *a, int *b){
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}
int find_min(int A[], int j, int n){
	int min = j;
	for(;j<n; j++){
		if (A[min]>A[j]){
			min = j;
		}
	}
	return min;
}

void make_heap(int A[], int n){	// 배열을 heap모양으로 만들어주는 make_heap함수
	int k;
	for(k=n/2-1; k>=0; k--){
		heapify(A, n, k);
	}
}
void heapify(int A[], int n, int k){	// k번째 수의 자기 자리를 찾아주는 heapify함수
	int L = k*2 + 1;	// 왼쪽 자식노드 인덱스
	int R = k*2 + 2;	// 오른쪽 자식노드 인덱스
	int max = k;

	if (L < n && A[L]>A[max]){	// 왼쪽 자식노드가 존재하면 값 비교
		max = L;
	}
	if (R < n && A[R]>A[max]){	// 오른쪽 자식노드가 존재하면 값 비교
			max = R;
		}
	if(max!=k){
		swap(&A[k], &A[max]);
		heapify(A, n, max);		// swap이 일어나면 다시 heapify
	}
}

void heap_sort(int A[], int n){
	make_heap(A, n);
	for (int k = n-1; k>0; k--){
		swap(&A[0], &A[k]);
		heapify(A, k, 0);
	}
}

void print_array(int A[], int n) {
	int k;
	for(k = 0; k < n; k++)
		printf("%d ", A[k]);
	printf("\n\n");
}

void main(){
	FILE *fp;
	#define CNT 2000

	int A[CNT],B[CNT]={0};
	int n, tmp, i;

	fp = fopen( "heap2000.txt", "w" );
	fprintf( fp, "%d\n", CNT);
	for(int i=0; i<CNT; i++){
		fprintf( fp, "%d\n", rand());
	}
	fclose( fp ) ;

	fp = fopen ("heap2000.txt", "r");
	tmp = fscanf(fp, "%d", &n);
	for(i=0; i<n; i++){
		tmp = fscanf(fp, "%d", &A[i]);
		B[i]=A[i];
	}
	fclose( fp ) ;

	start_time();
	select_sort(A, n);
	print_array(A, n);
	prn_time();

	start_time();
	heap_sort(B, n);
	print_array(B, n);
	prn_time();

}
