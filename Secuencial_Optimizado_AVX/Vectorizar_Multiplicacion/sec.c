//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(double ***A, double ***B, double **DP, int N){
	int i;

	(*A)  = (double**)_mm_malloc(sizeof(double)*N, TAMLINHA);
	(*B)  = (double**)_mm_malloc(sizeof(double)*N, TAMLINHA);
	

	for(i=0;i<N;i++){
		(*A)[i] = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
			(*A)[i][0] = (double)rand(); 
			(*A)[i][1] = (double)rand(); 
			(*A)[i][2] = (double)rand(); 
			(*A)[i][3] = (double)rand();
		(*B)[i] = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
			(*B)[i][0] = (double)rand(); 
			(*B)[i][1] = (double)rand(); 
			(*B)[i][2] = (double)rand(); 
			(*B)[i][3] = (double)rand();
	} 
	(*DP)= (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
	
	printf("\n--------------------------------------\n");
	
	for(i=0;i<N;i++){
		printf("N=%d", i);
		printf("\n\tA= [%lf, %lf, %lf, %lf]",(*A)[i][0],(*A)[i][1],(*A)[i][2],(*A)[i][3]);
		printf("\n\tB= [%lf, %lf, %lf, %lf]\n",(*B)[i][0],(*B)[i][1],(*B)[i][2],(*B)[i][3]);
	}
	
	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP)[0],(*DP)[1],(*DP)[2],(*DP)[3]);
}

void calculos(__m256d *A, __m256d *B, __m256d *DP, int N){
	int i;
	double *f;
	__m256d aux = _mm256_setzero_pd();
	
	for(i=0;i<N;i++){
		aux = _mm256_add_pd(A[i],B[i]);
		//(*DP) = _mm256_fmadd_pd(aux, aux, (*DP));
		(*DP) = _mm256_add_pd(_mm256_mul_pd(aux, aux), (*DP));
	}
	
	printf("\n--------------------------------------\n");
	
	for(i=0;i<N;i++){
		printf("N=%d", i);
		f = (double*)&A[i];
		printf("\n\tA= [%lf, %lf, %lf, %lf]",f[0],f[1],f[2],f[3]);
		f = (double*)&B[i];
		printf("\n\tB= [%lf, %lf, %lf, %lf]",f[0],f[1],f[2],f[3]);
	}
	f = (double *)DP;
	
	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",f[0],f[1],f[2],f[3]);
}

void destruir(__m256d *A, __m256d *B){
	_mm_free(A);
	_mm_free(B);
}

