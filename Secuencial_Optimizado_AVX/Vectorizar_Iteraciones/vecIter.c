//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, __m256d *resultado, int N){
	(*A)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	(*B)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	
	(*resultado) = _mm256_setzero_pd();

	for(int i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd(rand(),rand(),rand(),rand()); 
		(*B)[i] = _mm256_set_pd(rand(),rand(),rand(),rand());
	} 

}

void calculos(__m256d *A, __m256d *B, __m256d *resultado, int N){
	int i;
	 __m256d a0=_mm256_setzero_pd(), a1=_mm256_setzero_pd(), a2=_mm256_setzero_pd(), a3=_mm256_setzero_pd(), b0=_mm256_setzero_pd(), b1=_mm256_setzero_pd(), b2=_mm256_setzero_pd(), b3=_mm256_setzero_pd();
	 __m256d aba=_mm256_setzero_pd(), abb=_mm256_setzero_pd(), abc=_mm256_setzero_pd(), abd=_mm256_setzero_pd();
	 __m256d aux=_mm256_setzero_pd(), aux1=_mm256_setzero_pd(), aux2=_mm256_setzero_pd(), aux3=_mm256_setzero_pd();
	
	for(i=0;i<N;i=i+4){
		for(int j=0; j<4; j++){
			a0[j]=A[i+j][0];
			a1[j]=A[i+j][1];
			a2[j]=A[i+j][2];
			a3[j]=A[i+j][3];
			
			b0[j]=B[i+j][0];
			b1[j]=B[i+j][1];
			b2[j]=B[i+j][2];
			b3[j]=B[i+j][3];
		}
		
		aba = _mm256_sub_pd(_mm256_sub_pd(_mm256_sub_pd(_mm256_mul_pd(a0,b0), _mm256_mul_pd(a1,b1)), _mm256_mul_pd(a2,b2)), _mm256_mul_pd(a3,b3));
		
		abb = _mm256_sub_pd(_mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(a0,b1), _mm256_mul_pd(a1,b0)), _mm256_mul_pd(a2,b3)), _mm256_mul_pd(a3,b2));
		
		abc = _mm256_add_pd(_mm256_add_pd(_mm256_sub_pd(_mm256_mul_pd(a0,b2), _mm256_mul_pd(a1,b3)), _mm256_mul_pd(a2,b0)), _mm256_mul_pd(a3,b1));
		
		abd = _mm256_add_pd(_mm256_sub_pd(_mm256_add_pd(_mm256_mul_pd(a0,b3), _mm256_mul_pd(a1,b2)), _mm256_mul_pd(a2,b1)), _mm256_mul_pd(a3,b0));
		
		
		aux = _mm256_sub_pd(_mm256_sub_pd(_mm256_sub_pd(_mm256_mul_pd(aba,aba), _mm256_mul_pd(abb,abb)), _mm256_mul_pd(abc,abc)), _mm256_mul_pd(abd,abd));
		
		aux1 = _mm256_sub_pd(_mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(aba,abb), _mm256_mul_pd(abb,aba)), _mm256_mul_pd(abc,abd)), _mm256_mul_pd(abd,abc));
		
		aux2 = _mm256_add_pd(_mm256_add_pd(_mm256_sub_pd(_mm256_mul_pd(aba,abc), _mm256_mul_pd(abb,abd)), _mm256_mul_pd(abc,aba)), _mm256_mul_pd(abd,abb));
		
		aux3 = _mm256_add_pd(_mm256_sub_pd(_mm256_add_pd(_mm256_mul_pd(aba,abd), _mm256_mul_pd(abb,abc)), _mm256_mul_pd(abc,abb)), _mm256_mul_pd(abd,aba));
		

	(*resultado)[0]+=aux[0]+aux[1]+aux[2]+aux[3];
	(*resultado)[1]+=aux1[0]+aux1[1]+aux1[2]+aux1[3];
	(*resultado)[2]+=aux2[0]+aux2[1]+aux2[2]+aux2[3];
	(*resultado)[3]+=aux3[0]+aux3[1]+aux3[2]+aux3[3];

	}



  //printf("Resultado: [ \n%lf + %lfi + %lfj + %lfk ]\n", (*resultado)[0], resultado[1], resultado[2], resultado[3]);

}



void destruir(__m256d *A, __m256d *B){
	_mm_free(A);
	_mm_free(B);
}


