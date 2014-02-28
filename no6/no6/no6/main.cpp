#include <stdio.h>
#include <time.h>
#include "GA.h"

int n_evaluation=0;
/********************************************************************************************
*                                                                                           *
*                                             main                                          *
*                                                                                           *
*********************************************************************************************/
int main(void)
{
	/*
	Genetic algorithm program for solving benchmark function
	This program employs UNDX as crossover and MGG as selection
	*/
	double SearchRegion[N_GENE+1][2+1];
	Chromosome chrom;
	time_t t0,t;

	t0=time(NULL); // tic

	setSearchRegion(SearchRegion);//探索範囲を決定
	chrom=GA(SearchRegion);//探索範囲を持ってGAへ
	printf("n_evaluation=\t%d\n",n_evaluation);
	printf("Fitness:\t%e\n",chrom.fitness);//print Fitness
	writeSolution(&chrom,SearchRegion,N_GENE);//ファイル出力
	t=time(NULL)-t0; // toc
	PrintTime(t);

	return(0);
}

