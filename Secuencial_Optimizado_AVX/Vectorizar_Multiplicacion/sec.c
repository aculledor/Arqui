//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, __m256d *DP, int N){
	int i;

	(*A)  = (__m256d*)malloc(sizeof(__m256d)*N);
	(*B)  = (__m256d*)malloc(sizeof(__m256d)*N);
	

	for(i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand());
		(*B)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand());
	}
	(*DP)= _mm256_setzero_pd();

	double *f = (double *)DP;
	
	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",f[0],f[1],f[2],f[3]);
}

void calculos(__m256d *A, __m256d *B, __m256d *DP, int N){
	int i;
	__m256d aux = _mm256_setzero_pd();
	
	for(i=0;i<N;i++){
		aux = _mm256_add_pd(A[i],B[i]);
		//(*DP) = _mm256_fmadd_pd(aux, aux, (*DP));
		(*DP) = _mm256_add_pd(_mm256_mul_pd(aux, aux), (*DP));
	}
	
	//printf("\n--------------------------------------\n");
	
	/*for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}

	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);*/
}

void destruir(__m256d *A, __m256d *B){
	free(A);
	free(B);
}

