//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, int N){
	(*A)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	(*B)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	

	for(int i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand()); 
		(*B)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand());
	} 
}


void calculos(__m256d *A, __m256d *B, double **DP, int N){
	int i;
	__m256d aux = _mm256_setzero_pd();
	__m256d aux2 = _mm256_setzero_pd();
	__m256d resultado = _mm256_setzero_pd();

	for(i=0;i<N;i=i+4){

		aux = _mm256_mul_pd(A[i],B[i]);
		aux = _mm256_mul_pd(aux,aux);
		aux2 = _mm256_permute2f128_pd(aux,aux,1);
		aux = _mm256_add_pd(aux,aux2);
		aux = _mm256_hadd_pd(aux,aux);
		resultado = _mm256_set_pd( resultado[3], resultado[2], resultado[1], resultado[0]+aux[0]);

		aux = _mm256_mul_pd(A[i+1],B[i+1]);
		aux = _mm256_mul_pd(aux,aux);
		aux2 = _mm256_permute2f128_pd(aux,aux,1);
		aux = _mm256_add_pd(aux,aux2);
		aux = _mm256_hadd_pd(aux,aux);
		resultado = _mm256_set_pd( resultado[3], resultado[2], resultado[1]+aux[0], resultado[0]);

		aux = _mm256_mul_pd(A[i+2],B[i+2]);
		aux = _mm256_mul_pd(aux,aux);
		aux2 = _mm256_permute2f128_pd(aux,aux,1);
		aux = _mm256_add_pd(aux,aux2);
		aux = _mm256_hadd_pd(aux,aux);
		resultado = _mm256_set_pd( resultado[3], resultado[2]+aux[0], resultado[1], resultado[0]);

		aux = _mm256_mul_pd(A[i+3],B[i+3]);
		aux = _mm256_mul_pd(aux,aux);
		aux2 = _mm256_permute2f128_pd(aux,aux,1);
		aux = _mm256_add_pd(aux,aux2);
		aux = _mm256_hadd_pd(aux,aux);
		resultado = _mm256_set_pd( resultado[3]+aux[0], resultado[2], resultado[1], resultado[0]);
	
	}

	//(*DP) = (double*)_mm_malloc(sizeof(double)*4, TAMLINHA);
	(*DP)= (double *)&resultado;

	//printf(" Resultado: [ \n%lf + %lfi + %lfj + %lfk ]\n", (*DP)[0], (*DP)[1], (*DP)[2], (*DP)[3]);

}

void destruir(__m256d *A, __m256d *B, int N){

	_mm_free(A);
	_mm_free(B);

}


