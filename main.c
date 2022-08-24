//GAME OF LIFE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

#define INTEGER 19

typedef struct{
	char init[INTEGER][INTEGER];
	char snaped[INTEGER][INTEGER];
} World;

void disable_canonical(void)
{
	struct termios info;
	tcgetattr(0, &info);          
	info.c_lflag &= ~ICANON;      
	info.c_cc[VMIN] = 1;          
	info.c_cc[VTIME] = 0;         
	tcsetattr(0, TCSANOW, &info); 
}

void enable_canonical(void)
{
	struct termios info;
	tcgetattr(0, &info);
	info.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &info);
}

void show_world(char init[INTEGER][INTEGER], int ROW, int COL){
	for(int i=0; i<INTEGER; i++){
		for(int j=0; j<INTEGER; j++){
			if(i==ROW && j==COL){
				printf("\b[%c]", init[i][j]);
			}
			else{
				printf("%c ", init[i][j]);
			}
		}
		printf("\n");
	}
}


void start_gol(char world[INTEGER][INTEGER]){
	for(int i=0; i<INTEGER; i++){
		for(int j=0; j<INTEGER; j++){
			printf("%c ", world[i][j]);
		}
		printf("\n");
	}	
}

void scan_neighbours(char world[INTEGER][INTEGER]){
	int offset_row[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
	int offset_col[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
	for(int i=0; i<INTEGER; i++){
		for(int j=0; j<INTEGER; j++){
			int alive = 0;
			for(int k=0; k<8; k++){
				if(((i - offset_row[k]) < 0) || ((j - offset_col[k]) < 0)){ 
					continue;
				}
				else if(world[i-offset_row[k]][j-offset_col[k]] == '#'){
						alive += 1;
				}
			}
			if(world[i][j] == '#' && (alive < 2 || alive > 3)){
				world[i][j] = '.';
			}
			else if(world[i][j] == '#' && (alive == 2 || alive == 3)){
				world[i][j] = '#';
			}
			else if(world[i][j] == '.' && alive == 3){
				world[i][j] = '#';
			}
			printf("%c ", world[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	World world;
	int center = (INTEGER+1) / 2;
	for(int i=0; i<INTEGER; i++){
		for(int j=0; j<INTEGER; j++){
				world.init[i][j] = '.';
		}
	}
	for(int i=0; i<INTEGER; i++){
		for(int j=0; j<INTEGER; j++){
			world.snaped[i][j] = '.';
		}
	}

	disable_canonical();

	int ROW, COL;
	ROW = COL = center;
	show_world(world.init, ROW, COL);
	int boolean = 0;

	while(boolean != 1){
		char input; 
		input = getchar();
		switch(input){
			case 'w':
				system("clear");
				ROW -= 1;
				show_world(world.init, ROW, COL);
				break;
			case 's':
				system("clear");
				ROW += 1;
				show_world(world.init, ROW, COL);
				break;
			case 'a':
				system("clear");
				COL -= 1;
				show_world(world.init, ROW, COL);
				break;
			case 'd':
				system("clear");
				COL += 1;
				show_world(world.init, ROW, COL);
				break;
			case ' ':
				system("clear");
				world.init[ROW][COL] = '#';
				world.snaped[ROW][COL] = '#';
				show_world(world.init, ROW, COL);
				break;
			case 'x':
				boolean = 1;
			default:
				continue;
		}
	}
	enable_canonical();

	while(true){
			system("clear");
			scan_neighbours(world.snaped);
			sleep(0.900);
	}

	return 0;
}
