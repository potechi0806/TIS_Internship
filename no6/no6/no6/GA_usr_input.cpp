#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GA.h"

extern int n_evaluation;

/********************************************************************************************
*                                                                                           *
*                                         setFitness                                        *
*                                                                                           *
*********************************************************************************************/
void setFitness(double SearchRegion[][2+1], Chromosome *chrom, int n)
{
	double *x;
	double Fitness=0.0;
	int i,j;
	double alpha,beta,gamma; // for g02;
	double R;
	double X[4]={0,20,20,40};
	double Y[4]={0,10,20,10};
	double r[4]={0,2,2,3};
	double zahyoux[4][37],zahyouy[4][37];
	double zahyouX[4][37],zahyouY[4][37];
	double kukan[3];
	int flag=0,count,flagcount;

	x=vector(1,n);
	decodeGene2Variable(SearchRegion,chrom,x,n);//íTçıîÕàÕí≤êÆ

	R=abs(x[5]);

	for(i=1;i<=3;i++){
		for(j=1;j<=36;j++){
			zahyoux[i][j]=X[i]+r[i]*sin(10*j*3.14/180);//êAï®ÇÃâ~é¸ÇÃç¿ïWx
			zahyouy[i][j]=Y[i]+r[i]*cos(10*j*3.14/180);//êAï®ÇÃâ~é¸ÇÃç¿ïWy
		}
	}

	for(i=1;i<=2;i++){
		for(j=1;j<=36;j++){
			zahyouX[i][j]=x[2*i-1]+R*sin(10*j*3.14/180);//ÉXÉvÉäÉìÉNÉâÅ[ÇÃâ~é¸ÇÃç¿ïWx
			zahyouY[i][j]=x[2*i]+R*cos(10*j*3.14/180);//ÉXÉvÉäÉìÉNÉâÅ[ÇÃâ~é¸ÇÃç¿ïWx
		}
	}

	//èåèÇñûÇΩÇµÇƒÇ¢ÇÈÇ©
	count=0;
	flagcount=0;
	for(i=1;i<=3;i++){
		for(j=1;j<=36;j++){

			if(j<=9){//0<theata<=90: x>X,y>Y
			if(zahyouX[1][j]>=zahyoux[i][j]|| zahyouX[2][j]>=zahyoux[i][j]){
				if(zahyouY[1][j]>=zahyouy[i][j] || zahyouY[2][j]>=zahyouy[i][j]){
					count++;
					Fitness=10;
					if(count==9*3){
						flagcount=1;}
				}
				else{
					Fitness=100;
					flag=0;
				}
			}
			else{
				Fitness=1000;
				flag=0;
			}
			}

			if(j>9 && j<=18){//90<theata<=180: x<X,y>Y
			if(zahyouX[1][j]<=zahyoux[i][j]|| zahyouX[2][j]<=zahyoux[i][j]){
				if(zahyouY[1][j]>=zahyouy[i][j] || zahyouY[2][j]>=zahyouy[i][j]){
					count++;
					Fitness=10;
					if(count==9*3*2){
						flagcount=2;}
				}
				else{
					Fitness=100;
					flag=0;
				}
			}
			else{
				Fitness=1000;
				flag=0;
			}
			}

			if(j>18 && j<=27){//180<theata<=270: x<X,y<Y
			if(zahyouX[1][j]<=zahyoux[i][j]|| zahyouX[2][j]<=zahyoux[i][j]){
				if(zahyouY[1][j]<=zahyouy[i][j] || zahyouY[2][j]<=zahyouy[i][j]){
					count++;
					Fitness=10;
					if(count==9*3*3){
						flagcount=3;}
				}
				else{
					Fitness=100;
					flag=0;
				}
			}
			else{
				Fitness=1000;
				flag=0;
			}
			}


			if(j<27){//270<theata<=360: x>X,y<Y
			if(zahyouX[1][j]>=zahyoux[i][j]|| zahyouX[2][j]>=zahyoux[i][j]){
				if(zahyouY[1][j]<=zahyouy[i][j] || zahyouY[2][j]<=zahyouy[i][j]){
					count++;
					Fitness=10;
					if(count==9*3*4 && flagcount==3){
						flag=1;}
				}
				else{
					Fitness=100;
					flag=0;
				}
			}
			else{
				Fitness=1000;
				flag=0;
			}
			}
		}
	}



	if(flag==1){
		Fitness=0;
		Fitness=R;
	}


next:
	free_vector(x,1,n);
	chrom->fitness=Fitness;
	n_evaluation++;
}

/********************************************************************************************
*                                                                                           *
*                                       setSearchRegion                                     *
*                                                                                           *
*********************************************************************************************/
void setSearchRegion(double SearchRegion[][2+1])
{
	int i;

	//// Sphere /////////
	for(i=1;i<=N_GENE;i++){
		SearchRegion[i][1]=5;
		SearchRegion[i][2]=100;
	}
	////////////////////////

	
}