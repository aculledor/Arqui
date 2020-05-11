//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, double **DP, int N){
	(*A)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	(*B)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	
	(*DP) = (double *)_mm_malloc(sizeof(double)*4, TAMLINHA);

	for(int i=0;i<N;i++){
		//(*A)[i] = _mm256_set_pd(1,2,3,4); 
		//(*B)[i] = _mm256_set_pd(5,6,7,8);
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

__m256d mult_cuat(__m256d A, __m256d B){
	__m256d brev, col1, secA, aux1, aux2;
	
	__m256d op1 = _mm256_setr_pd(-1,+1,-1,+1);
	__m256d op2 = _mm256_setr_pd(-1,+1,+1,-1);
	__m256d op3 = _mm256_setr_pd(-1,-1,+1,+1);
	
	/*printf("OP1-> %lf %lf %lf %lf \nOP2-> %lf %lf %lf %lf \nOP3-> %lf %lf %lf %lf\n",
						op1[0],op1[1],op1[2],op1[3],
						op2[0],op2[1],op2[2],op2[3],
						op3[0],op3[1],op3[2],op3[3]);*/
	

		brev =  _mm256_set_pd(B[0],B[1],B[2],B[3]);
		
		/*printf("A-> %lf %lf %lf %lf \nB-> %lf %lf %lf %lf \nBREV-> %lf %lf %lf %lf\n",
						A[0],A[1],A[2],A[3],
						B[0],B[1],B[2],B[3],
						brev[0],brev[1],brev[2],brev[3]);
		aux1=_mm256_permute_pd(B, 5);
		aux2=_mm256_permute_pd(brev, 5);
		printf("Bper-> %lf %lf %lf %lf \nBrevper-> %lf %lf %lf %lf \n",
						aux1[0],aux1[1],aux1[2],aux1[3],
						aux2[0],aux2[1],aux2[2],aux2[3]);*/
		
		//Columna 1
		secA = _mm256_set1_pd(A[0]);
		col1 = _mm256_mul_pd(secA, B);
		
		//Columna 2
		secA = _mm256_set1_pd(A[1]);
		col1 = _mm256_add_pd(
										_mm256_mul_pd(
															_mm256_mul_pd(secA, _mm256_permute_pd(B, 5)),
															op1),
										col1);
		
		//Columna 3
		secA = _mm256_set1_pd(A[2]);
		col1 = _mm256_add_pd(
										_mm256_mul_pd(
															_mm256_mul_pd(secA, _mm256_permute_pd(brev, 5)),
															op2),
										col1);
		
		//Columna 4
		secA = _mm256_set1_pd(A[3]);
		col1 = _mm256_add_pd(
										_mm256_mul_pd(
															_mm256_mul_pd(secA, brev),
															op3),
										col1);
										
		return col1;
}

void calculos(__m256d *A, __m256d *B, double **DP, int N){
	__m256d aux;
	
	for(int i=0;i<N;i++){
		aux = mult_cuat(A[i], B[i]);
		(*DP)[0] += aux[0]; (*DP)[1] += aux[1]; (*DP)[2] += aux[2]; (*DP)[3] += aux[3];
	}
	
}


void destruir(__m256d *A, __m256d *B){
	_mm_free(A);
	_mm_free(B);
}

