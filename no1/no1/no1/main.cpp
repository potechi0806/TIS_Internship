#include <stdio.h>
#include <time.h>
#include <string.h>
#include "header.h"

/********************************************************************************************
*                                                                                           *
*                                             main                                          *
*                                                                                           *
*********************************************************************************************/
int main(void)
{
	char input[10],test[10];
	int i=0, j=0, flag=0,count=0;
	int k;
	time_t t0,t;

	t0=time(NULL); // tic

	printf("input >>\n");
	scanf("%s",input);
	while(1){
		if(input[count]=='\0'){
			break;}
		count++;
	}

	strcpy(test,input);

	for(j=0;j<=count;j++){
		for(i=0;i<=count;i++){

			if(test[j]==input[i]){
				for(k=1;k<=count-j;k++){
					if(test[j+k]==input[i]){
						flag=1;
						break;
					}
				}
			}
			else{
				flag=0;
			}
			if(flag==1){
			break;
		}
		}
		if(flag==1){
			break;
		}
	}

	if(flag==1){
		printf("false\n");
	}
	else{
		printf("true\n");
	}


	t=time(NULL)-t0; // toc
	PrintTime(t);

	return(0);
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
