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
	double aba,abb,abc,abd;
	double C[Fios[Fio]][4];
	
	#pragma omp parallel shared(A,B,DP,C) private(i,aba,abb,abc,abd) num_threads(Fios[Fio])
	{
		#pragma omp for
			for(i=0;i<N;i++){
				aba = A[i].a*B[i].a - A[i].b*B[i].b - A[i].c*B[i].c - A[i].d*B[i].d;
				abb = A[i].a*B[i].b + A[i].b*B[i].a + A[i].c*B[i].d - A[i].d*B[i].c;
				abc = A[i].a*B[i].c - A[i].b*B[i].d + A[i].c*B[i].a + A[i].d*B[i].b;
				abd = A[i].a*B[i].d + A[i].b*B[i].c - A[i].c*B[i].b + A[i].d*B[i].a;

				C[omp_get_thread_num()][0] += (aba*aba - abb*abb - abc*abc - abd*abd);
				C[omp_get_thread_num()][1] += (aba*abb + abb*aba + abc*abd - abd*abc);
				C[omp_get_thread_num()][2] += (aba*abc - abb*abd + abc*aba + abd*abb);
				C[omp_get_thread_num()][3] += (aba*abd + abb*abc - abc*abb + abd*aba);

			}
		#pragma omp barrier
		#pragma omp single
		{ 
			for(i=0;i<Fios[Fio];i++){
				(*DP).a += C[i][0];
				(*DP).b += C[i][1];
				(*DP).c += C[i][2];
				(*DP).d += C[i][3];
			}
		}
	}
}

void destruir(struct quaternion *A, struct quaternion *B){
	_mm_free(A);
	_mm_free(B);
}

