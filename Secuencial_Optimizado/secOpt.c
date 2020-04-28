//
// Created by acu on 11/2/20.
//

#include "header.h"

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

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *C, struct quaternion *DP, int N){
	int i;
	double aux = 0;

	/*printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);
	
	for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}*/
	
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
	
	//printf("\n--------------------------------------\n");
	
	/*for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}

	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);*/
}

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *C){
	_mm_free(A);
	_mm_free(B);
	_mm_free(C);
}

