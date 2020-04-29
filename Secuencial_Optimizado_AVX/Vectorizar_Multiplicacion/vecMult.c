//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(double ***A, double ***B, int N){
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
	
	/*printf("\n--------------------------------------\n");
	
	for(i=0;i<N;i++){
		printf("N=%d", i);
		printf("\n\tA= [%lf, %lf, %lf, %lf]",(*A)[i][0],(*A)[i][1],(*A)[i][2],(*A)[i][3]);
		printf("\n\tB= [%lf, %lf, %lf, %lf]\n",(*B)[i][0],(*B)[i][1],(*B)[i][2],(*B)[i][3]);
	}
	
	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP)[0],(*DP)[1],(*DP)[2],(*DP)[3]);*/
}

void calculos(double **A, double **B, double **DP, int N){
	int i;
	__m256d aux = _mm256_setzero_pd();
	__m256d result = _mm256_setzero_pd();
	
	for(i=0;i<N;i++){
		aux = _mm256_add_pd(
			_mm256_set_pd(A[i][0],A[i][1],A[i][2],A[i][3]), 
			_mm256_set_pd(B[i][0],B[i][1],B[i][2],B[i][3]) );
		result = _mm256_fmadd_pd(aux, aux, result);
	}
	
	(*DP) = (double *)&result;
	
	//printf("\n--------------------------------------\n");
	
	//printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP)[0],(*DP)[1],(*DP)[2],(*DP)[3]);
}

void darVuelta(double **DP){
	double aux = 0;
	aux = (*DP)[0];
	(*DP)[0] = (*DP)[3];
	(*DP)[3] = aux;
	aux = (*DP)[1];
	(*DP)[1] = (*DP)[2];
	(*DP)[2] = aux;
}

void destruir(double **A, double **B, int N){
	int i;
	for(i=0; i<N; i++){
		_mm_free(A[i]);
		_mm_free(B[i]);
	}
	_mm_free(A);
	_mm_free(B);
}

