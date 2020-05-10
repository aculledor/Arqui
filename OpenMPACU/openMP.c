//
// Created by acu on 11/2/20.
//

#include "header.h"

int Fios[5] = {1, 2, 4, 6, 8};

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion *DP, int N, int Fio){
	(*A)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	(*B)  = (struct quaternion*)_mm_malloc(sizeof(struct quaternion)*N, TAMLINHA);
	

	for(int i=0;i<N;i++){
		(*A)[i].a = rand(); (*A)[i].b = rand(); (*A)[i].c = rand(); (*A)[i].d = rand();
		(*B)[i].a = rand(); (*B)[i].b = rand(); (*B)[i].c = rand(); (*B)[i].d = rand();
	}
	
	(*DP).a = 0; (*DP).b = 0; (*DP).c = 0; (*DP).d = 0;
	
	omp_set_dynamic(0);     				//Desactivamos la posibilidad de unificar hilos
	omp_set_num_threads(Fios[Fio]);	//Establecemos o numero de fios a empregar

}

void calculos(struct quaternion *A, struct quaternion *B,  struct quaternion *DP, int N){
	int i;
	#pragma omp parallel shared(A, B) 
	{
		struct quaternion ab;
		double aux1,aux2,aux3,aux4;
		#pragma omp for 
			for(i=0;i<N;i++){
				ab.a = A[i].a*B[i].a - A[i].b*B[i].b - A[i].c*B[i].c - A[i].d*B[i].d;
				ab.b = A[i].a*B[i].b + A[i].b*B[i].a + A[i].c*B[i].d - A[i].d*B[i].c;
				ab.c = A[i].a*B[i].c - A[i].b*B[i].d + A[i].c*B[i].a + A[i].d*B[i].b;
				ab.d = A[i].a*B[i].d + A[i].b*B[i].c - A[i].c*B[i].b + A[i].d*B[i].a;
				
				aux1 += (ab.a*ab.a - ab.b*ab.b - ab.c*ab.c - ab.d*ab.d);
				aux2 += (ab.a*ab.b + ab.b*ab.a + ab.c*ab.d - ab.d*ab.c);
				aux3 += (ab.a*ab.c - ab.b*ab.d + ab.c*ab.a + ab.d*ab.b);
				aux4 += (ab.a*ab.d + ab.b*ab.c - ab.c*ab.b + ab.d*ab.a);
			}
			
		/*#pragma omp atomic
			(*DP).a += aux1 ;
		#pragma omp atomic
			(*DP).b += aux2 ;
		#pragma omp atomic
			(*DP).c += aux3 ;
		#pragma omp atomic
			(*DP).d += aux4 ;*/
			
			#pragma omp critical
			{
				(*DP).a += aux1 ;
				(*DP).b += aux2 ;
				(*DP).c += aux3 ;
				(*DP).d += aux4 ;
			}
	}
}

void destruir(struct quaternion *A, struct quaternion *B){
	_mm_free(A);
	_mm_free(B);
}

