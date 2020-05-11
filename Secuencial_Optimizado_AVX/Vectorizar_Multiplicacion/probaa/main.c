#include "header.h"


int main(int argc, char **argv) {
	__m256d col = _mm256_set_pd(1,2,3,4);
	__m256d invcol = _mm256_permute_pd(col, 5);
	
	__m256d revcol = _mm256_set_pd(col[0],col[1],col[2],col[3]);
	__m256d rev1 = _mm256_permute_pd(revcol, 5);
	
	
	printf("X=16\ncol-> %lf %lf %lf %lf\ninvcol-> %lf %lf %lf %lf\nrev1-> %lf %lf %lf %lf\nrevcol-> %lf %lf %lf %lf\n",
		col[0],col[1],col[2],col[3],
		invcol[0],invcol[1],invcol[2],invcol[3],
		rev1[0],rev1[1],rev1[2],rev1[3],
		revcol[0],revcol[1],revcol[2],revcol[3]);

  return 0;
}
