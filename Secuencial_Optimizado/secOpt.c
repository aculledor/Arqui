//
// Created by acu on 11/2/20.
//

#include "header.h"

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

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *DP, int N){
	struct quaternion ab;
	for(int i=0;i<N;i++){
		ab.a = A[i].a*B[i].a - A[i].b*B[i].b - A[i].c*B[i].c - A[i].d*B[i].d;
		ab.b = A[i].a*B[i].b + A[i].b*B[i].a + A[i].c*B[i].d - A[i].d*B[i].c;
		ab.c = A[i].a*B[i].c - A[i].b*B[i].d + A[i].c*B[i].a + A[i].d*B[i].b;
		ab.d = A[i].a*B[i].d + A[i].b*B[i].c - A[i].c*B[i].b + A[i].d*B[i].a;

		(*DP).a = (*DP).a + (ab.a*ab.a - ab.b*ab.b - ab.c*ab.c - ab.d*ab.d);
		(*DP).b = (*DP).b + (ab.a*ab.b + ab.b*ab.a + ab.c*ab.d - ab.d*ab.c);
		(*DP).c = (*DP).c + (ab.a*ab.c - ab.b*ab.d + ab.c*ab.a + ab.d*ab.b);
		(*DP).d = (*DP).d + (ab.a*ab.d + ab.b*ab.c - ab.c*ab.b + ab.d*ab.a);
	}
}

void destruir(struct quaternion *A, struct quaternion *B){
	_mm_free(A);
	_mm_free(B);
}

