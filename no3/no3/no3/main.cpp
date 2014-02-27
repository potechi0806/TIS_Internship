#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void){
	int n;
	int i,a;
	int flag[10]={0};
	int ok1,ok2;
	int count=n;
	printf("n=\n");
	scanf("%d",&n);

	a=int(pow(2.0,double(n)))-n;

	printf("(");
	flag[1]=1;
	ok1=1;
	while(1){
	for(i=count;i<=2*n;i++){
		flag[i]=-1;
		ok2=ok1+flag[i];
		ok1=ok2;
		if(ok2<0){
			flag[i]=1;
			ok2=ok1+flag[i]+1;
		    ok1=ok2;
		}
	}
	
	for(i=2;i<=2*n;i++){
		if(flag[i]==1){
			printf("(");
		}
		if(flag[i]==-1){
			printf(")");
		}
	}
	printf(",");
	if(count=a){
		break;
	}
	}

	return 0;
}

