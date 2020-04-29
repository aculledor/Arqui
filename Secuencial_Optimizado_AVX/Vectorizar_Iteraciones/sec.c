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

}


void calculos(double **A, double **B, double **DP, int N){
	int i;
	__m256d aux = _mm256_setzero_pd();
	__m256d aux2 = _mm256_setzero_pd();
	__m256d aux3 = _mm256_setzero_pd();

	for(i=0;i<N;i=i+4){
		aux = _mm256_add_pd(_mm256_set_pd(A[i][0],A[i][1],A[i][2],A[i][3]), _mm256_set_pd(B[i][0],B[i][1],B[i][2],B[i][3]) );
		aux = _mm256_add_pd(aux,aux);

		/*aux2 = _mm256_mul_pd(_mm256_set_pd(A[i+2][0],A[i+2][1],A[i+2][2],A[i+2][3]), _mm256_set_pd(B[i+2][0],B[i+2][1],B[i+2][2],B[i+2][3]) );
		aux2 = _mm256_mul_pd(aux2,aux2);
		
		aux3= _mm256_hadd_pd(aux,aux2);
		aux3=_mm256_permute_pd(aux3, 0b00100111);
		
		aux = _mm256_mul_pd(_mm256_set_pd(A[i+1][0],A[i+1][1],A[i+1][2],A[i+1][3]), _mm256_set_pd(B[i+1][0],B[i+1][1],B[i+1][2],B[i+1][3]) );
		aux = _mm256_mul_pd(aux,aux);

		aux = _mm256_mul_pd(_mm256_set_pd(A[i+3][0],A[i+3][1],A[i+3][2],A[i+3][3]), _mm256_set_pd(B[i+3][0],B[i+3][1],B[i+3][2],B[i+3][3]) );
		aux2 = _mm256_mul_pd(aux2,aux2);
		
		aux2= _mm256_hadd_pd(aux,aux2);
		aux2=_mm256_permute_pd(aux2, 0b00100111);
		
		aux=_mm256_hadd_pd(aux3,aux2);*/
		
	}

	(*DP) = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
	(*DP)= (double *)&aux;

	//printf("Resultado: [ \n%lf + %lfi + %lfj + %lfk ]\n", (*DP)[0], (*DP)[1], (*DP)[2], (*DP)[3]);

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


