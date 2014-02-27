#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m;
void hantei(void);
int empty(int T[]);
int peek(int T[]);
void pop(int T[]);
void push(void);

int main(){
	int T[100]={0};
	int count=0;
	int nakami;
	int comand;
	m=0;
	while(1){
	printf("yobidashi\n1:empty\n2:peek\n3:pop\n4:push\n");
	scanf("%d",&comand);

	if(comand==1){
		nakami=empty(T);
		printf("nakami:%d\n\n",nakami);
	}
	else if(comand==2){
		peek(T);
		//printf("empty:%d\n\n",nakami);
	}
	else if(comand==3){
		pop(T);
	}
	else if(comand==4){
		push();
	}
	count=m;
	}
return 0;

}

void hantei(void){
		if(m==0) printf("true\n");
}

int empty(int T[]){
	int i;
	hantei();
		i=T[m-1];
		return i;
}

int peek(int T[]){
	int i;
	T[m-1]=0;
	if((m-1)!=0){
		m--;}
	i=empty(T);
	return i;
}

void pop(int T[]){
	printf("input\n");
	scanf("%d",&T[m]);
	m++;
}

void push(void){
	printf("youso: %d\n",m);
}
