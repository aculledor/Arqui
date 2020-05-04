//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion **C, struct quaternion *DP, int N){
	int i;

	(*A)  = (struct quaternion*)malloc(sizeof(struct quaternion)*N);
	(*B)  = (struct quaternion*)malloc(sizeof(struct quaternion)*N);
	(*C)  = (struct quaternion*)malloc(sizeof(struct quaternion)*N);
	

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

struct quaternion multCua(struct quaternion A, struct quaternion B){
	struct quaternion ab;
	ab.a = A.a*B.a - A.b*B.b - A.c*B.c - A.d*B.d;
	ab.b = A.a*B.b + A.b*B.a + A.c*B.d - A.d*B.c;
	ab.c = A.a*B.c - A.b*B.d + A.c*B.a + A.d*B.b;
	ab.d = A.a*B.d + A.b*B.c - A.c*B.b + A.d*B.a;
	return ab;
}

struct quaternion sumCua(struct quaternion A, struct quaternion B){
	struct quaternion ab;
	ab.a = A.a+B.a;
	ab.b = A.b+B.b;
	ab.c = A.c+B.c;
	ab.d = A.d+B.d;
	return ab;
}
	

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *C, struct quaternion *DP, int N){
	int i;
	for(i=0;i<N;i++){
		C[i]= multCua(A[i],B[i]);
	}

 
	for(i=0;i<N;i++){
		(*DP)= sumCua( (*DP), multCua(C[i], C[i]) );
	}
}

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *C){
	free(A);
	free(B);
	free(C);
}

