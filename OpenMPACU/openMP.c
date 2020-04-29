//
// Created by acu on 11/2/20.
//

#include "header.h"

int Fios[5] = {1, 2, 4, 6, 8};

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion **C, struct quaternion *DP, int N){
	int i;

	(*A)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*B)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*C)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	

	for(i=0;i<N;i++){
		(*C)[i].a= 0; (*C)[i].b= 0; (*C)[i].c= 0; (*C)[i].d= 0;
		
		(*A)[i].a = rand(); (*A)[i].b = rand(); (*A)[i].c = rand(); (*A)[i].d = rand();
		(*B)[i].a = rand(); (*B)[i].b = rand(); (*B)[i].c = rand(); (*B)[i].d = rand();
	}
	
	(*DP).a = 0;
	(*DP).b = 0;
	(*DP).c = 0;
	(*DP).d = 0;

}

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *C, struct quaternion *DP, int N, int Fio){
	int i;
	
	#pragma omp parallel shared(A,B,C) num_threads(Fios[Fio])
	{
		#pragma omp for
			for(i=0;i<N;i++){
				C[i].a = A[i].a * B[i].a;
				C[i].b = A[i].b * B[i].b;
				C[i].c = A[i].c * B[i].c;
				C[i].d = A[i].d * B[i].d;
				
				C[i].a = C[i].a * C[i].a;
				C[i].b = C[i].b * C[i].b;
				C[i].c = C[i].c * C[i].c;
				C[i].d = C[i].d * C[i].d;
				
			}
	}
 
	for(i=0;i<N;i++){
		(*DP).a = (*DP).a + C[i].a;
		(*DP).b = (*DP).b + C[i].b;
		(*DP).c = (*DP).c + C[i].c;
		(*DP).d = (*DP).d + C[i].d;
	}
}

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *C){
	_mm_free(A);
	_mm_free(B);
	_mm_free(C);
}

