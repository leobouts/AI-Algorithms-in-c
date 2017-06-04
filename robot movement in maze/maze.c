#include <stdio.h>
#include <stdlib.h>

#define N 10
#define p 0.25

#define EMPTY 0
#define BLACK 1
#define START 2
#define FINAL 3
#define PATH  4

#define NOTVISITED 0
#define VISITED 1

int maze[N][N]; 
int visited[N][N];


struct node{
	int i,j; 
	int g; 
	struct node *next; 
	struct node *parent; 
};


struct node *head = NULL;
struct node *tail = NULL; 



struct node *createnode(int i, int j, int g, struct node *parent)
{
	struct node *n;
	n= (struct node *)malloc(sizeof(struct node));
	if(n==NULL){
		printf("Error in malloc");
		exit(1);
	}
	
	n->i = i;
	n->j = j;
	n->g = g;
	n->parent = parent;
	n->next = NULL;
	
	return n;
	
}



void insert(struct node *n)
{
	
	struct node *tmp; 
	struct node *prev;
	
	
	if(head==NULL){
		head = tail = n;
		return ;
	}
	
	tmp = head;
	prev = NULL;
	while(tmp!=NULL){
		if(tmp->g > n->g){
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}

	if(prev==NULL){ 
		n->next = head;
		head = n;
	}

	else{
		prev->next = n;
		n->next=tmp;
	}
}

struct node *removeFirst()
{
	struct node *n;
	
	n = head;
	head = head->next;
	return n;
}


int starti=0, startj=0;
int g1i=0, g1j=4;
int g2i=6, g2j=1;

void initMaze()
{
	int i,j;
	float x;
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			x = rand()/(float) RAND_MAX;
			if(x<p){
				maze[i][j] = BLACK;
			}
			else{
				maze[i][j] = EMPTY;
			}
			visited[i][j]  = NOTVISITED;
		}
	}
	
}

void printMaze()
{
	int i,j;
	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(maze[i][j]==BLACK){
				printf("B");
			}
			else if(maze[i][j]==START){
				printf("S");
			}
			else if(maze[i][j]==FINAL){
				printf("F");
			}
			else if(maze[i][j]==PATH){
				printf("*");
			}
			else{
				printf("_");
			}
		}
		printf("\n");
	}
}


int isFinal(int i, int j)
{
	if(   (i==g1i && j ==g1j) ||   (i==g2i && j==g2j)     ){
		return 1;
	}
	return 0;
}


int check(int i, int j)
{
	if(i<0) return 0;
	if(i>=N) return 0;
	if(j<0) return 0;
	if(j>=N) return 0;
	
	if(maze[i][j] == BLACK) return 0;
	if(visited[i][j] == VISITED) return 0;
	return 1;
}


void fillSolution(struct node *n)
{
	while(n->parent!=NULL){
		maze[n->i][n->j] = PATH;
		n = n->parent;
	}
}


void Heuretic()
{
	struct node *current;
	struct node *tmp;
	
	while(head!=NULL){
		current = removeFirst();
		if(isFinal(current->i, current->j)){
			printf("Solution Cost: %d\n",current -> g);
			fillSolution(current->parent);
			break;
		}
		

		if( check(current->i-1,current->j)){
			tmp = createnode(current->i-1, current->j, current->g + 1, current);
			visited[current->i-1][current->j] = VISITED;
			insert(tmp);
		}

		if( check(current->i+1,current->j)){
			tmp = createnode(current->i+1, current->j, current->g + 1, current);
			visited[current->i+1][current->j] = VISITED;
			insert(tmp);
		}

		if( check(current->i,current->j+1)){
			tmp = createnode(current->i, current->j+1, current->g + 0.5, current);
			visited[current->i][current->j+1] = VISITED;
			insert(tmp);
		}

		if( check(current->i,current->j-1)){
			tmp = createnode(current->i, current->j-1, current->g + 0.5, current);
			visited[current->i][current->j-1] = VISITED;
			insert(tmp);
		}
	}
}


int main()
{
	initMaze();
	
	maze[starti][startj] = START;
	maze[g1i][g1j] = FINAL;
	maze[g2i][g2j] = FINAL;
	printMaze();
	printf("\n");
	struct node *n = createnode(starti,startj,0,NULL); 
	visited[starti][startj] = VISITED;
	insert(n);
	
	Heuretic();
	printf("\n");
	printMaze();
	Heuretic();
	printf("\n");
	printf("\n");

	maze[g1i][g1j] = START;
	maze[g2i][g2j] = FINAL;
	maze[g2i][g2j] = FINAL;
	printMaze();
	Heuretic();
	printf("\n");
	printf("\n");

	insert(n);
	
	Heuretic();
	
		
}












