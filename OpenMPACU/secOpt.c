//
// Created by acu on 11/2/20.
//

#include "header.h"

int Fios[5] = {1, 2, 4, 6, 8};

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

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *C, struct quaternion *DP, int N, int Fio){
	int i;

	/*printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);
	
	for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}*/
	
	#pragma omp parallel shared(A,B,C) 
	{
		#pragma omp for
			for(i=0;i<N;i++){
				C[i].a = A[i].a * B[i].a;
				C[i].b = A[i].b * B[i].b;
				C[i].c = A[i].c * B[i].c;
				C[i].d = A[i].d * B[i].d;
			}	
	}
 
	for(i=0;i<N;i++){
		(*DP).a = (*DP).a + C[i].a * C[i].a;
		(*DP).b = (*DP).b + C[i].b * C[i].b;
		(*DP).c = (*DP).c + C[i].c * C[i].c;
		(*DP).d = (*DP).d + C[i].d * C[i].d;
	}
	
	//printf("\n--------------------------------------\n");
	
	/*for(i=0;i<N;i++){
		printf("N=%d\n\tA= [%lf, %lf, %lf, %lf]\n\tB= [%lf, %lf, %lf, %lf]\n\tC= [%lf, %lf, %lf, %lf] \n", i, A[i].a,A[i].b,A[i].c,A[i].d, B[i].a,B[i].b,B[i].c,B[i].d, C[i].a,C[i].b,C[i].c,C[i].d);
	}

	printf("\n## DP [%lf,%lf,%lf,%lf] ##\n",(*DP).a,(*DP).b,(*DP).c,(*DP).d);*/
}

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *C){
	free(A);
	free(B);
	free(C);
}

