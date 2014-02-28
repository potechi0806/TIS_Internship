#include<stdio.h>

int main(){
	int index[14]={1,2,4,7,10,11,7,12,7,8,16,18,19};
	int m,n;
	int i,j;
	int min[14],max[14];
	int count;
	
	for(i=0;i<=12;i++){
		count=0;
		min[i]=0;
		for(j=0;j<=12-i;j++){
			if(index[i]<=index[j+i]){
				count++;
				if(i==11-i-count){
					min[i]=1;
				}
			}
			else if(index[i]>index[j+i]){
				min[i]=0;
			}
		}
	}

	for(j=0;j<=12;j++){
		if(min[j]==0){
			m=j;
			break;
		}
	}


	for(i=12;i>=0;i--){
		count=1;
		max[i]=0;
		for(j=0;j<=12;j++){
			if(index[i]>=index[j]){
				count++;
			}
		}
		max[i]=count-2;
		printf("%d:%d\n",i,max[i]);
	}

	for(j=12;j>=4;j--){
		if(max[j]==j){}
		else if(max[j]!=j){
			n=j;
			printf("%d\n",n);
			break;
		}
	}

	printf("m=%d\nn=%d\n",m,n);
	return 0;
}