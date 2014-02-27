#include<stdio.h>

int main(){
	int a,b;
	int comand;
	int ans=0;
	int count=0;
	
	printf("input(a)");
	scanf("%d",&a);

	printf("input(b)");
	scanf("%d",&b);

	printf("plus:1\nminus:2\nmultiply:3\ndivide:4\n");
	scanf("%d",&comand);

	if(comand==1){
		printf("ans: %d",a+b);
	}
	else if(comand==2){
		while(1){
			if(a==ans+b){
				printf("ans: %d",ans);break;
			}
			ans++;
		}
	}
	else if(comand==3){
		for(count=1;count<=b;count++){
			ans=a+ans;
		}
		printf("ans: %d",ans);
	}
	else if(comand==4){
		while(1){
			ans=b+ans;
			if(ans==a){
				printf("ans: %d",ans);break;
			}
			if(ans>a){
				printf("ans: %d",ans-1);break;
			}
		}
	}
	return 0;
}