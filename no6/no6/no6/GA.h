#include <time.h>

#define N_GENE 5 // Number of variables // Rosenbrock, Rastriginなら100、g01なら13、g02なら20
#define IDUM -1 // Seed of ran2 and gasdev // ここを変えて５回実行。負の値ならなんでもよい。

#define N_GENERATION 1000 // 最大世代数
#define N_POPULATION 200 // 集団サイズ
#define N_CHILDREN 200 // Number of children in MGG
#define ALLOWABLE_ERROR  -1e+10 // 今回は適合度による探索打ち切りを行わないので十分に小さい値を入れておく

#define OUT_SOLUTION "solution.dat" // 最良の個体の出力ファイル名
#define OUT_TRANSITION "transition.dat" // 適合度の遷移の出力ファイル名


typedef struct Chromosome{
	double gene[N_GENE+1];
	double fitness;
} Chromosome;


Chromosome GA(double SearchRegion[][2+1]);
void MGGvariant(double SearchRegion[][2+1], Chromosome *Individual, int n_population, int n_gene);
Chromosome getNewChild(Chromosome *p1, Chromosome *p2, Chromosome *p3, double SearchRegion[][2+1], int n);
Chromosome UNDX(Chromosome *p1, Chromosome *p2, Chromosome *p3, int n);
void setFitness(double SearchRegion[][2+1], Chromosome *chrom, int n);
void decodeGene2Variable(double SearchRegion[][2+1], Chromosome *chrom, double *x, int n_gene);
void setInitialPopulation(Chromosome Individual[], double SearchRegion[][2+1], int n_population, int n_gene);
void writeSolution(Chromosome *chrom, double SearchRegion[][2+1],int n_gene);
void writeTransition(int generation, Chromosome *chrom, double SearchRegion[][2+1], int n_gene);
void setSearchRegion(double SearchRegion[][2+1]);
double gasdev(long *idum);
double ran2(long *idum);
void sort(int n, Chromosome ra[]);
void PrintTime(time_t t);

void nrerror(char error_text[]);
double *vector(long nl, long nh);
int *ivector(long nl, long nh);
double **matrix(long nrl, long nrh, long ncl, long nch);
void free_vector(double *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_matrix(double **m, long nrl, long nrh, long ncl, long nch);


