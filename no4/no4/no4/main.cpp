#include<stdio.h>

int main(){
	signed int a,b;
	signed int comand;
	signed int ans=0;
	signed int count=0;
	
	printf("input(a)");
	scanf("%d",&a);

	printf("input(b)");
	scanf("%d",&b);

	printf("plus:1\nminus:2\nmultiply:3\ndivide:4\n");
	scanf("%d",&comand);

	if(comand==1){//plus
		printf("ans: %d\n",a+b);
	}

	else if(comand==2){//minus
		if(a<b){
			ans=32767;}
		while(1){
			if(a==ans+b){
				printf("ans: %d\n",ans);break;
			}
			ans++;
		}
	}

	else if(comand==3){//multiply
		for(count=1;count<=b;count++){
			ans=a+ans;
		}
		printf("ans: %d\n",ans);
	}

	else if(comand==4){//devide
		while(1){
			ans=b+ans;
			if(ans==a){
				printf("ans: %d\n",count+1);
				break;
			}
			if(ans>a){
				printf("ans: %d\n",count);
				break;
			}
			count++;
		}
	}
	return 0;
}