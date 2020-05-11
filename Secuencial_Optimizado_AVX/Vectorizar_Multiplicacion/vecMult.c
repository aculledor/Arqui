//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, double **DP, int N){
	(*A)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	(*B)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	
	(*DP) = (double *)_mm_malloc(sizeof(double)*4, TAMLINHA);

	for(int i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd(rand(),rand(),rand(),rand()); 
		(*B)[i] = _mm256_set_pd(rand(),rand(),rand(),rand());
	} 
}




/*	Col1	op1	Col2	op2	Col3	op3	Col4
*		a0*b0	 - 	a1*b1	 - 	a2*b2	 - 	a3*b3
*		a0*b1	 + 	a1*b0	 + 	a2*b3	 - 	a3*b2
*		a0*b2	 - 	a1*b3	 + 	a2*b0	 + 	a3*b1
*		a0*b3	 + 	a1*b2	 - 	a2*b1	 + 	a3*b0
*/

void calculos(__m256d *A, __m256d *B, double **DP, int N){
	__m256d brev, aux, col1, col2, secA;
	
	__m256d op1 = _mm256_setr_pd(-1,+1,-1,+1);
	__m256d op2 = _mm256_setr_pd(-1,+1,+1,-1);
	__m256d op3 = _mm256_setr_pd(-1,-1,+1,+1);
	
	for(int i=0;i<N;i++){
		brev =  _mm256_set_pd(B[i][0],B[i][1],B[i][2],B[i][3]);

		/*
		*	A*B
		*/
		//Columna 1
		secA = _mm256_set1_pd(A[i][0]);
		col1 = _mm256_mul_pd(secA, B[i]);
		
		//Columna 2
		secA = _mm256_set1_pd(A[i][1]);
		col1 = _mm256_add_pd(
							_mm256_mul_pd(
								_mm256_mul_pd(secA, _mm256_permute_pd(B[i], 5)),
								op1),
							col1);
		
		//Columna 3
		secA = _mm256_set1_pd(A[i][2]);
		col1 = _mm256_add_pd(
							_mm256_mul_pd(
								_mm256_mul_pd(secA, _mm256_permute_pd(brev, 5)),
								op2),
							col1);
		
		//Columna 4
		secA = _mm256_set1_pd(A[i][3]);
		col1 = _mm256_add_pd(
							_mm256_mul_pd(
								_mm256_mul_pd(secA, brev),
								op3),
							col1);

		/*
		*	C*C
		*/
		brev =  _mm256_set_pd(col1[0],col1[1],col1[2],col1[3]);

		//Columna 1
		secA = _mm256_set1_pd(col1[0]);
		col2 = _mm256_mul_pd(secA, col1);
		
		//Columna 2
		secA = _mm256_set1_pd(col1[1]);
		col2 = _mm256_add_pd(
						_mm256_mul_pd(
							_mm256_mul_pd(secA, _mm256_permute_pd(col1, 5)),
							op1),
						col2);
		
		//Columna 3
		secA = _mm256_set1_pd(col1[2]);
		col2 = _mm256_add_pd(
						_mm256_mul_pd(
							_mm256_mul_pd(secA, _mm256_permute_pd(brev, 5)),
							op2),
						col2);
		
		//Columna 4
		secA = _mm256_set1_pd(col1[3]);
		aux = 	_mm256_add_pd(
								_mm256_add_pd(
									_mm256_mul_pd(
										_mm256_mul_pd(secA, brev),
										op3),
									col2),
								aux);
	
	}
		(*DP)[0] += aux[0]; (*DP)[1] += aux[1]; (*DP)[2] += aux[2]; (*DP)[3] += aux[3];
	
}


void destruir(__m256d *A, __m256d *B,  double *DP){
	_mm_free(A);
	_mm_free(B);
	_mm_free(DP);
}

