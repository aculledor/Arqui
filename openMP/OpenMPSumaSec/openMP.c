//
// Created by acu on 11/2/20.
//

#include "header.h"

int Fios[5] = {1, 2, 4, 6, 8};

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion **sol, struct quaternion *DP, int N, int Fio){
	(*A)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*B)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*sol) =(struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	

	for(int i=0;i<N;i++){
		(*A)[i].a = rand(); (*A)[i].b = rand(); (*A)[i].c = rand(); (*A)[i].d = rand();
		(*B)[i].a = rand(); (*B)[i].b = rand(); (*B)[i].c = rand(); (*B)[i].d = rand();
		(*sol)[i].a = 0; (*sol)[i].b = 0; (*sol)[i].c = 0; (*sol)[i].d = 0;
	}
	
	(*DP).a = 0; (*DP).b = 0; (*DP).c = 0; (*DP).d = 0;
	
	omp_set_dynamic(0);     				//Desactivamos la posibilidad de unificar hilos
	omp_set_num_threads(Fios[Fio]);	//Establecemos o numero de fios a empregar

}

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *sol,  struct quaternion *DP, int N, int Fio){
	int i = 0;
	#pragma omp parallel num_threads(Fios[Fio])
	{
		struct quaternion ab, sol_prev;
		#pragma omp for
			for(i=0;i<N;i++){
				ab.a = A[i].a*B[i].a - A[i].b*B[i].b - A[i].c*B[i].c - A[i].d*B[i].d;
				ab.b = A[i].a*B[i].b + A[i].b*B[i].a + A[i].c*B[i].d - A[i].d*B[i].c;
				ab.c = A[i].a*B[i].c - A[i].b*B[i].d + A[i].c*B[i].a + A[i].d*B[i].b;
				ab.d = A[i].a*B[i].d + A[i].b*B[i].c - A[i].c*B[i].b + A[i].d*B[i].a;

				sol[i].a = (ab.a*ab.a - ab.b*ab.b - ab.c*ab.c - ab.d*ab.d);
				sol[i].b = (ab.a*ab.b + ab.b*ab.a + ab.c*ab.d - ab.d*ab.c);
				sol[i].c = (ab.a*ab.c - ab.b*ab.d + ab.c*ab.a + ab.d*ab.b);
				sol[i].d = (ab.a*ab.d + ab.b*ab.c - ab.c*ab.b + ab.d*ab.a);
			}

	}
	for(i=0;i<N;i++){
		(*DP).a += sol[i].a ;
		(*DP).b += sol[i].b ;
		(*DP).c += sol[i].c ;
		(*DP).d += sol[i].d ;
	}
}

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *sol){
	_mm_free(A);
	_mm_free(B);
}

