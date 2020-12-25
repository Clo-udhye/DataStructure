#include <stdio.h>
#include <time.h>
#include <stdlib.h>

clock_t before;
void start_time(void) {
	before = clock();
}

double prn_time(void) {
	double user_time;
	user_time = (double)(clock() - before)/CLOCKS_PER_SEC;
	before = clock();
	printf("Time = %3.3lf seconds \n", user_time);
	return user_time;
}

void select_sort(int A[ ], int n) {
	int j, k;
	for( j = 0; j < n; j++ ) {
		k = find_min(A, j, n - 1);
		swap (&A[k], &A[j]);
	}
}
void swap(int *a, int *b){
	int temp;
	temp = *b;
	b = a;
	a = temp;
}
int find_min(int A[], int j, int n){
	int min = j;
	for(;j<n; j++){
		if (A[min]>A[j]){
			min = j;
		}
	}
}
void make_heap(int A[], int n){
	int k;
	for(k=n/2;k>=0;k--){
		heapify(A, n, k);
	}
}
void heapify(int A[], int n, int k){
	int L, R, max;
	while(L<n){
		L = 2*k+1;
		R = 2*k+2;
		max = L;
		if(A[max]<A[k]){
			max = k;
		}
		if(A[max]<A[R]&&R<n){
			max = R;
		}
		if(max!=k){
			swap(&A[k], &A[max]);
			k = max;
		}
		else
			break;
	}
}
void heap_sort(int A[], int n){
	int k;
	make_heap(A, n);
	for (k = n-1; k>0; k--){
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
	int A[2000],B[2000]={0};
	int n, tmp, i;
	fp = fopen ("heap2000.txt", "r");
	tmp = fscanf(fp, "%d", &n);
	for(i=0; i<n; i++){
		tmp = fscanf(fp, "%d", &A[i]);
		B[i]=A[i];
	}
	start_time();
	select_sort(A, n);
	print_array(A, n);
	prn_time();

	heap_sort(B, n);
	print_array(B, n);
	prn_time();

}
