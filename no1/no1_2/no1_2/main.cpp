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
	char input1[10],input2[10];
	int i=0, j=0, flag=0;
	time_t t0,t;

	t0=time(NULL); // tic

	printf("input1 >>\n");
	scanf("%s",input1);
		while(1){
		if(input1[i]=='\0'){
			break;}
			i++;
		}
	printf("input2 >>\n");
	scanf("%s",input2);
		while(1){
		if(input2[j]=='\0'){
			break;}
			j++;
		}

	isSubstring(input1, input2, i,j);

	t=time(NULL)-t0; // toc
	PrintTime(t);

	return(0);
}

/********************************************************************************************
*                                                                                           *
*                                         PrintTime                                         *
*                                                                                           *
*********************************************************************************************/
void isSubstring(char a[], char b[], int n, int m){
	int i,j,k,count=0;;
	int flag=0;
	for(j=0;j<=n;j++){
	for(i=0;i<=m;i++){
		if(a[j]==b[i]){
			count++;
				for(k=1;k<=n-j;k++){
					if(a[j+k]==b[i]){
next:
						printf("a\n");
						count++;
						if(m>count){
							goto next;
						}else{
							flag=1;
							break;
						}
					}
				}
		}
		else if(a[j]!=b[i]){
			flag=0;
		}
		if(flag==1)
			break;
	}
			if(flag==1)
			break;
	}
	if(flag==1){
		printf("true\n");
	}
	else{
		printf("false\n");
	}
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
