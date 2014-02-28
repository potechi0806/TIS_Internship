#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GA.h"

long idum=IDUM;
extern int n_evaluation;

/********************************************************************************************
*                                                                                           *
*                                             GA                                            *
*                                                                                           *
*********************************************************************************************/
Chromosome GA(double SearchRegion[][2+1])
{
	Chromosome Individual[N_POPULATION+1];
	int i,j;
	double x[6];

	setInitialPopulation(Individual,SearchRegion,N_POPULATION,N_GENE);//初期集団形成
	printf("%d: Best Fitness= %e\n",1,Individual[1].fitness);
	
	writeTransition(1,&Individual[1],SearchRegion,N_GENE);//ファイル出力
	
	if(Individual[1].fitness<ALLOWABLE_ERROR){
		return(Individual[1]);
	}

	for(i=2;i<=N_GENERATION;i++){
		MGGvariant(SearchRegion,Individual,N_POPULATION,N_GENE);//getNewCjildren,etc....

		if(i%100==0){
			printf("%d: Best Fitness= %e\n",i,Individual[1].fitness);
			for(j=1;j<=5;j++){
					x[j]=Individual[1].gene[j]*(50-0)+0;
				}
			printf("(x,y)=(%lf,%lf),(%lf,%lf)\tR=%lf\n",x[1],x[2],x[3],x[4],x[5]);
		}

		writeTransition(i,&Individual[1],SearchRegion,N_GENE);//ファイル出力
		
		if(Individual[1].fitness<ALLOWABLE_ERROR){
			return(Individual[1]);
		}

	}

	return(Individual[1]);

}


/********************************************************************************************
*                                                                                           *
*                                        MGGvariant                                         *
*                                                                                           *
*********************************************************************************************/
void MGGvariant(double SearchRegion[][2+1], Chromosome *Individual, int n_population, int n_gene)
{
	/*
	Minimal Generation Gap Selection for UNDX
	See Hiroaki Kitano, "Genetic Algorithms 4", Sangyo-tosho, pp234, 2000 
	*/

	const int maxitr=10;
	int ip[3+1];
	Chromosome Children[(N_CHILDREN+2)+1];
	int i,j;

	// Picking up two parents from main population randomly
	for(i=1;i<=maxitr;i++){
		for(j=1;j<=2;j++){
			ip[j]=(int)(ran2(&idum)*(double)n_population)+1;//??
		}
		if(ip[1]!=ip[2]){//different parent
			break;
		}
	}

	// Generating children
	for(i=1;i<=N_CHILDREN;i++){
		// The third parent are randomly chosen each time.
		for(j=1;j<=maxitr;j++){
			ip[3]=(int)(ran2(&idum)*(double)n_population)+1;
			if(ip[3]!=ip[1] && ip[3]!=ip[2]){
				break;
			}
		}
		Children[i]=getNewChild(&Individual[ip[1]],&Individual[ip[2]],&Individual[ip[3]],SearchRegion,n_gene);
	}
	// Adding main two parents into group of children 
	for(i=1;i<=2;i++){
		Children[N_CHILDREN+i]=Individual[ip[i]];
	}
	// Replacing main two parents with best individual and randomly chosen individual 
	sort(N_CHILDREN+2, Children);
	Individual[ip[1]]=Children[1];
	Individual[ip[2]]=Children[(int)(ran2(&idum)*(double)(N_CHILDREN+1))+2];
	sort(n_population,Individual);
}


/********************************************************************************************
*                                                                                           *
*                                       getNewChild                                         *
*                                                                                           *
*********************************************************************************************/
Chromosome getNewChild(Chromosome *p1, Chromosome *p2, Chromosome *p3, double SearchRegion[][2+1], int n)
{
	/*
	Hander of UNDX function
	Checking wheather children are in search region 
	*/

	Chromosome c;//gene[],fitness
	const int maxitr=100;
	int flg;
	int i,j;

	for(i=1;i<=maxitr;i++){
		flg=0;
		c=UNDX(p1,p2,p3,n);
		for(j=1;j<=n;j++){
			if(c.gene[j] < 0.0 || 1.0 < c.gene[j]){
				flg=1;
			}
		}
		if(flg==0){
			break;
		}
	}
	if(flg==1){
		for(j=1;j<=n;j++){
			if(1.0 < c.gene[j]){
				c.gene[j]=1.0;
			}else if(c.gene[j] < 0.0){
				c.gene[j]=0.0;
			}
		}
	}

	setFitness(SearchRegion,&c,n);

	return(c);//gene[],fitness
}


/********************************************************************************************
*                                                                                           *
*                                          UNDX                                             *
*                                                                                           *
*********************************************************************************************/
Chromosome UNDX(Chromosome *p1, Chromosome *p2, Chromosome *p3, int n)
{
	/*
	Function of "Unimordal Distribution Crossover"
	p1 and p2 are main parents, and p3 is sub parent.
	See Hiroaki Kitano, "Genetic Algorithms 4", Sangyo-tosho, pp261, 2000
	*/

	const double alpha=0.5,beta=0.35; // Parameters for UNDX
	double d1,d2=0.0;
	double *v12,*v13,*e1,*t;
	double temp1=0.0,temp2=0.0;
	Chromosome c;
	int i;

	v12=vector(1,n);
	v13=vector(1,n);
	e1=vector(1,n);
	t=vector(1,n);

	// v12 is a vector from p1 to p2, v13 is a vector from p1 to p3
	for(i=1;i<=n;i++){
		v12[i]=p2->gene[i]-p1->gene[i];
		v13[i]=p3->gene[i]-p1->gene[i];
	}
	// temp1 is an inner product (v12,v13), temp2 is (v12,v12)
	for(i=1;i<=n;i++){
		temp1+=v12[i]*v13[i];
		temp2+=v12[i]*v12[i];
	}
	d1=sqrt(temp2); // d1 is distance between p1 and p2
	if(temp2==0.0 || d1==0.0){
		for(i=1;i<=n;i++){
			d2+=v13[i]*v13[i];
			e1[i]=0.0;
		}
	}else{
		for(i=1;i<=n;i++){
			d2+=(temp1/temp2*v12[i]-v13[i])*(temp1/temp2*v12[i]-v13[i]);
			e1[i]=v12[i]/d1;
		}
	}
	d2=sqrt(d2); //d2 is distance between primary search line and p13

	for(i=1;i<=n;i++){
		t[i]=gasdev(&idum)*beta*d2/sqrt((double)n);
	}

	temp1=0.0; // temp1 is the inner product (t,e1)
	for(i=1;i<=n;i++){
		temp1+=t[i]*e1[i];
	}
	temp2=alpha*d1*gasdev(&idum); // temp2 is standard deviation for direction of e1
	for(i=1;i<=n;i++){
		c.gene[i]=0.5*(p1->gene[i]+p2->gene[i])+t[i]+(temp2-temp1)*e1[i];
	}
	free_vector(v12,1,n);
	free_vector(v13,1,n);
	free_vector(e1,1,n);
	free_vector(t,1,n);

	return(c);
}




/********************************************************************************************
*                                                                                           *
*                                    decodeGene2Variable                                    *
*                                                                                           *
*********************************************************************************************/
void decodeGene2Variable(double SearchRegion[][2+1], Chromosome *chrom, double *x, int n_gene)
{
	int i;

	for(i=1;i<=n_gene;i++){
		x[i]=chrom->gene[i]*(SearchRegion[i][2]-SearchRegion[i][1])+SearchRegion[i][1];
	}
	
}


/********************************************************************************************
*                                                                                           *
*                                    setInitialPopulation                                   *
*                           　　　　　　 初期集団形成                                       *
*********************************************************************************************/
void setInitialPopulation(Chromosome Individual[], double SearchRegion[][2+1], int n_population, int n_gene)
{
	int i,j;

	for(i=1;i<=n_population;i++){
		for(j=1;j<=n_gene;j++){
			Individual[i].gene[j]=ran2(&idum);//ランダムに個体を割り当てる
		}
		setFitness(SearchRegion,&Individual[i],n_gene);//(探索範囲,個体,遺伝子数)
	}
	sort(n_population,Individual);
}



/********************************************************************************************
*                                                                                           *
*                                           gasdev                                          *
*                                                                                           *
*********************************************************************************************/
double gasdev(long *idum)
{
	double ran2(long *idum);
	static int iset=0;
	static double gset;
	double fac,rsq,v1,v2;

	if  (iset == 0) {
		do {
			v1=2.0*ran2(idum)-1.0;
			v2=2.0*ran2(idum)-1.0;
			rsq=v1*v1+v2*v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac=sqrt(-2.0*log(rsq)/rsq);
		gset=v1*fac;
		iset=1;
		return v2*fac;
	} else {
		iset=0;
		return gset;
	}
}
/* (C) Copr. 1986-92 Numerical Recipes Software 1+5-5i. */


#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)


/********************************************************************************************
*                                                                                           *
*                                             ran2                                          *
*                                                                                           *
*********************************************************************************************/
double ran2(long *idum)
{
	int j;
	long k;
	static long idum2=123456789;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	if (*idum <= 0) {
		if (-(*idum) < 1) *idum=1;
		else *idum = -(*idum);
		idum2=(*idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(*idum)/IQ1;
			*idum=IA1*(*idum-k*IQ1)-k*IR1;
			if (*idum < 0) *idum += IM1;
			if (j < NTAB) iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ1;
	*idum=IA1*(*idum-k*IQ1)-k*IR1;
	if (*idum < 0) *idum += IM1;
	k=idum2/IQ2;
	idum2=IA2*(idum2-k*IQ2)-k*IR2;
	if (idum2 < 0) idum2 += IM2;
	j=iy/NDIV;
	iy=iv[j]-idum2;
	iv[j] = *idum;
	if (iy < 1) iy += IMM1;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX
/* (C) Copr. 1986-92 Numerical Recipes Software 1+5-5i. */


/********************************************************************************************
*                                                                                           *
*                                             sort                                          *
*                                                                                           *
*********************************************************************************************/
void sort(int n, Chromosome ra[])
{
	int l,j,ir,i;
	Chromosome rra;

	l=(n >> 1)+1;
	ir=n;
	for (;;) {
		if (l > 1)
			rra=ra[--l];
		else {
			rra=ra[ir];
			ra[ir]=ra[1];
			if (--ir == 1) {
				ra[1]=rra;
				return;
			}
		}
		i=l;
		j=l << 1;
		while (j <= ir) {
			if (j < ir && ra[j].fitness < ra[j+1].fitness) ++j;
			if (rra.fitness < ra[j].fitness) {
				ra[i]=ra[j];
				j += (i=j);
			}
			else j=ir+1;
		}
		ra[i]=rra;
	}
}


/********************************************************************************************
*                                                                                           *
*                                       writeSolution                                       *
*                                                                                           *
*********************************************************************************************/
void writeSolution(Chromosome *chrom, double SearchRegion[][2+1],int n_gene)
{
	double *x;
	FILE *out;
	int i;

	x=vector(1,n_gene);
	if((out= fopen(OUT_SOLUTION,"w"))==NULL){
		printf("File error in writeSolution\n");
	}else{
		fprintf(out,"Fitness\t");
		for(i=1;i<=n_gene;i++){
			fprintf(out,"x[%d]\t",i);
		}
		fprintf(out,"\n");
		decodeGene2Variable(SearchRegion,chrom,x,n_gene);
		fprintf(out,"%e\t",chrom->fitness);
		for(i=1;i<=n_gene;i++){
			fprintf(out,"%e\t",x[i]);
		}
		fprintf(out,"\n");
		fclose(out);
	}

	free_vector(x,1,n_gene);

}


/********************************************************************************************
*                                                                                           *
*                                       writeSolution                                       *
*                                                                                           *
*********************************************************************************************/
void writeTransition(int generation, Chromosome *chrom, double SearchRegion[][2+1], int n_gene)
{
	double *x;
	FILE *out;
	int i;

	x=vector(1,n_gene);
	if((out= fopen(OUT_TRANSITION,"a"))==NULL){
		printf("File error in writeTransition\n");
	}else{
		decodeGene2Variable(SearchRegion,chrom,x,n_gene);//探索範囲調整
		fprintf(out,"%d\t%e\t",generation,chrom->fitness);
		for(i=1;i<=n_gene;i++){
			fprintf(out,"%e\t",x[i]);
		}
		fprintf(out,"\n");
		fclose(out);
	}
	free_vector(x,1,n_gene);
}


/********************************************************************************************
*                                                                                           *
*                                         PrintTime                                         *
*                                                                                           *
*********************************************************************************************/
void PrintTime(time_t t)
{
	long h,m,s;
	t=(long)t;
	h=t/3600;
	m=((t%3600)/60);
	s=((t%3600)%60);
	printf("Performance...%ldhour %ldmin %ldsec\n",h,m,s);
}
