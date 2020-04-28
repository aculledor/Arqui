#include "header.h"

//Pole

int Q[5] = {2, 4, 6, 7, 1};

void start_counter();

double get_counter();

double mhz();


/* Initialize the cycle counter */


static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;


/* Set *hi and *lo to the high and low order bits of the cycle counter.
Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo) {
  asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
  : "=r" (*hi), "=r" (*lo) /* and move results to */
  : /* No input */ /* the two outputs */
  : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter() {
  access_counter(&cyc_hi, &cyc_lo);
}

/* Return the number of cycles since the last call to start_counter. */
double get_counter() {
  unsigned ncyc_hi, ncyc_lo;
  unsigned hi, lo, borrow;
  double result;

  /* Get cycle counter */
  access_counter(&ncyc_hi, &ncyc_lo);

  /* Do double precision subtraction */
  lo = ncyc_lo - cyc_lo;
  borrow = lo > ncyc_lo;
  hi = ncyc_hi - cyc_hi - borrow;
  result = (double) hi * (1 << 30) * 4 + lo;
  if (result < 0) {
      fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
  }
  return result;
}

double mhz(int verbose, int sleeptime) {
  double rate;

  start_counter();
  sleep(sleeptime);
  rate = get_counter() / (1e6 * sleeptime);
  if (verbose)
    printf("\n Processor clock rate = %.1f MHz\n", rate);
  return rate;
}


int main(int argc, char **argv) {
	srand(SEED);
  int q = 0, N;
  double ck;

  if(argc ==2)
    q = (int)strtol(argv[1], NULL, 10);
  else{
    perror("Por favor introduce o numero de Q a empregar sendo 0=2, 1=4, 2=6 e 3=7.");
    exit(0);
  }
  
  N = pow(BASE, Q[q]);
	
	//printf("q=%d Q=%d N=%d\n", q, Q[q], N);
	
  struct quaternion *A, *B, DP;
  
  inicializarQuaternions(&A, &B, &DP, N);

  start_counter();
  
  calculos(A,B,&DP, N);

  ck = get_counter();

  printf("Clocks = %1.10lf. Resultado: [ \n%lf + %lfi + %lfj + %lfk ]\n", ck, DP.a, DP.b, DP.c, DP.d);

/* Esta rutina imprime a frecuencia de reloxo estimada coas rutinas start_counter/get_counter */
  mhz(1, 1);

	//printf("----------------------------------\n");

	void destruir(A,B,C);

  return 0;
}
