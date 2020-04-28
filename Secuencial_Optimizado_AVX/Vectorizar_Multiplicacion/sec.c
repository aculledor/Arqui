//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, __m256d **C, __m256d *DP, int N){
	int i;

	(*A)  = (__m256d*)malloc(sizeof(__m256d)*N);
	(*B)  = (__m256d*)malloc(sizeof(__m256d)*N);
	(*C)  = (__m256d*)malloc(sizeof(__m256d)*N);
	

	for(i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd(rand(),rand(),rand(),rand());
		(*B)[i] = _mm256_set_pd(rand(),rand(),rand(),rand());
		(*C)[i] = _mm256_setzero_pd();
	}
	(*DP)= _mm256_setzero_pd();

}

void calculos(__m256d *A, __m256d *B, __m256d *C, __m256d *DP, int N){
	int i;

	/*printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);
	
	for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}*/
	
	for(i=0;i<N;i++){
		C[i].a = A[i].a * B[i].a;
		C[i].b = A[i].b * B[i].b;
		C[i].c = A[i].c * B[i].c;
		C[i].d = A[i].d * B[i].d;
	}

 
	for(i=0;i<N;i++){
		(*DP).a = (*DP).a + C[i].a * C[i].a;
		(*DP).b = (*DP).b + C[i].b * C[i].b;
		(*DP).c = (*DP).c + C[i].c * C[i].c;
		(*DP).d = (*DP).d + C[i].d * C[i].d;
	}
	
	//printf("\n--------------------------------------\n");
	
	/*for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}

	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);*/
}

void destruir(__m256d *A, __m256d *B, __m256d *C){
	free(A);
	free(B);
	free(C);
}

