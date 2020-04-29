//
// Created by acu on 11/2/20.
//

#include "header.h"

int Fios[5] = {1, 2, 4, 6, 8};

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion *DP, int N){
	int i;

	(*A)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*B)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);

	for(i=0;i<N;i++){
		(*A)[i].a = rand(); (*A)[i].b = rand(); (*A)[i].c = rand(); (*A)[i].d = rand();
		(*B)[i].a = rand(); (*B)[i].b = rand(); (*B)[i].c = rand(); (*B)[i].d = rand();
	}
	
	(*DP).a = 0;
	(*DP).b = 0;
	(*DP).c = 0;
	(*DP).d = 0;

}

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *DP, int N, int Fio){
	int i;
	double aux = 0;
	
	#pragma omp parallel shared(A,B,DP) private(i, aux) num_threads(Fios[Fio])
	{
		#pragma omp for
			for(i=0;i<N;i++){
				aux = A[i].a * B[i].a;
				(*DP).a += aux * aux;
				aux = A[i].b * B[i].b;
				(*DP).b += aux * aux;
				aux = A[i].c * B[i].c;
				(*DP).c += aux * aux;
				aux = A[i].d * B[i].d;
				(*DP).d += aux * aux;
			}
	}
}

void destruir(struct quaternion *A, struct quaternion *B){
	_mm_free(A);
	_mm_free(B);
}

