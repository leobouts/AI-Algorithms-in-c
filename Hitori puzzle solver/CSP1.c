#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 8
#define K 8

#define WHITE 0
#define BLACK 1

int hitori[M][M]={
	{4,8,1,6,3,2,5,7},
	{3,6,7,2,1,6,5,4},
	{2,3,4,8,2,8,6,1},
	{4,1,6,5,7,7,3,5},
	{7,2,3,1,8,5,1,2},
	{3,5,6,7,3,1,8,4},
	{6,4,2,3,5,4,7,8},
	{8,7,1,4,2,3,5,6}
};
int color[M][M];

int cost(){
	int errorCounter=0;
	int i,j,k;
	

	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			if(color[i][j]==WHITE){
				for(k=j+1;k<M;k++){
					if(color[i][k]==WHITE && hitori[i][k]==hitori[i][j]){
						errorCounter++;
					}
				}
				
			}
		}
	}

	for(j=0;j<M;j++){
		for(i=0;i<M;i++){
			
			if(color[i][j]==WHITE){
				for(k=i+1;k<M;k++){
					if(color[k][j]==WHITE && hitori[k][j]==hitori[i][j]){
						errorCounter++;
					}
				}
				
			}
		}
	}
	
	

	for(i=0;i<M;i++){
		for(j=0;j<M;j++)	{
			if(j+1<M && color[i][j]==BLACK && color[i][j+1]==BLACK){
				errorCounter++;
			}
			if(i+1<M && color[i][j]==BLACK && color[i+1][j]==BLACK){
				errorCounter++;
			}
		}
	}
	return errorCounter;
}

void print(){
	int i,j;
	printf("cost=%d\n",cost());
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			if(color[i][j]==WHITE){
				printf("%d ",hitori[i][j]);
			}
			else{
				printf("B ");
			}
		}
		printf("\n");
	}

}
void SA(){
	float T=10;
	int N=M*M;
	int randI,randJ;
	int cost1, cost2;
	float p;
	int failure=0;
	int i,j;
	
	while(1){
		for(i=0;i<2*N;i++){
			
			
	
			cost1=cost();
			
			if(cost1==0)
				return;
			
			
			
			if(color[randI][randJ]==WHITE){
				color[randI][randJ]=BLACK;
			}
			else{
				color[randI][randJ]=WHITE;
			}
			
			cost2=cost();

			if(cost2<=cost1){
				failure=0;
			}
			else{

				p = rand()/(float)RAND_MAX;
				if( p < exp(-(cost2-cost1)/T)){
					
					failure=0;
				}
				else{
					failure++;
					
					if(color[randI][randJ]==WHITE){
						color[randI][randJ]=BLACK;
					}
					else{
						color[randI][randJ]=WHITE;
					}	
					if(failure==6*N)
						return;
				}
			}
			
		}
	
		T=0.999*T;
	}
}
main(){
	int i,j;
	
	srand(time(NULL));
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			color[i][j]=WHITE;
			
		}
	}
	print();

	SA();
	print();
	
}