//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(double ***A, double ***B, double **DP, int N){
	(*A)  = (double**)_mm_malloc(sizeof(double*)*N, TAMLINHA);
	(*B)  = (double**)_mm_malloc(sizeof(double*)*N, TAMLINHA);
	(*DP) = (double* )_mm_malloc(sizeof(double )*4, TAMLINHA);

	for(int i=0;i<N;i++){
		(*A)[i] = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
			(*A)[i][0] = rand(); (*A)[i][1] = rand(); (*A)[i][2] = rand(); (*A)[i][3] = rand();
		(*B)[i] = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
			(*B)[i][0] = rand(); (*B)[i][1] = rand(); (*B)[i][2] = rand(); (*B)[i][3] = rand();
	} 
	

	for(int i=0;i<N;i++){
		printf("\tA:[%lf,%lf,%lf,%lf]\n",(*A)[i][0],(*A)[i][1],(*A)[i][2],(*A)[i][3]);
		printf("\tB:[%lf,%lf,%lf,%lf]\n",(*B)[i][0],(*B)[i][1],(*B)[i][2],(*B)[i][3]);
	} 
}

void mult_cuat(__m256 A, __m256 B, __m256 *sol, int N){
	__m256d col1, col2, col3, col4, secA;
	
	__m256d op1 = _mm256_set_pd(-1,+1,-1,+1);
	__m256d op2 = _mm256_set_pd(-1,+1,+1,-1);
	__m256d op3 = _mm256_set_pd(-1,-1,+1,+1);
	
	for(int i = 0; i < N; i++){
		__m256d a = _mm256_load_pd(A[i]);
		__m256d b = _mm256_load_pd(B[i]);
		
		//FILA 1
		secA = _mm256_set1_pd(a[0]);
		col1 = _mm256_mul_pd(secA, b);
	}
	
}

/*void calculos(double **A, double **B, double **DP, int N){
	__m256d result;
	
	for(int i=0;i<N;i++){
		__m256d a = _mm256_load_pd(A[i]);
		__m256d b = _mm256_load_pd(B[i]);
	}
	
	(*DP) = (double *)&result;
	printf("\tDP:[%lf,%lf,%lf,%lf]\n",(*DP)[0],(*DP)[1],(*DP)[2],(*DP)[3]);
}*/

void calculos(double **A, double **B, double **DP, int N){
	__m256d aux,result;
	
	for(int i=0;i<N;i++){
		aux = _mm256_mul_pd( _mm256_load_pd(A[i],  _mm256_load_pd(B[i]));
		result = _mm256_fmadd_pd( aux, aux, result);
	}
	
	(*DP) = (double *)&result;
	printf("\tDP:[%lf,%lf,%lf,%lf]\n",(*DP)[0],(*DP)[1],(*DP)[2],(*DP)[3]);
}

void destruir(double **A, double **B, int N){
	for(int i = 0; i < N; i++){
		_mm_free(A[i]); _mm_free(B[i]);
	}	
	_mm_free(A);
	_mm_free(B);
}

