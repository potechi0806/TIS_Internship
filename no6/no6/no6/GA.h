#include <time.h>

#define N_GENE 5 // Number of variables // Rosenbrock, Rastrigin�Ȃ�100�Ag01�Ȃ�13�Ag02�Ȃ�20
#define IDUM -1 // Seed of ran2 and gasdev // ������ς��ĂT����s�B���̒l�Ȃ�Ȃ�ł��悢�B

#define N_GENERATION 1000 // �ő吢�㐔
#define N_POPULATION 200 // �W�c�T�C�Y
#define N_CHILDREN 200 // Number of children in MGG
#define ALLOWABLE_ERROR  -1e+10 // ����͓K���x�ɂ��T���ł��؂���s��Ȃ��̂ŏ\���ɏ������l�����Ă���

#define OUT_SOLUTION "solution.dat" // �ŗǂ̌̂̏o�̓t�@�C����
#define OUT_TRANSITION "transition.dat" // �K���x�̑J�ڂ̏o�̓t�@�C����


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


