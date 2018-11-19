#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int bodyX[100];
int bodyY[100];
int bodyLength = 3;

int screenWidth = 50;
int screenHeight = 20;

char input = -1;

int dir = 1;

void move();
void spawnFood();
bool checkCollision();

int foodX = 10;
int foodY = 10;
	
main(){
	srand(time(NULL));
	spawnFood();
	bodyX[0] = 10;
	bodyY[0] = 5;
	bodyX[1] = 9;
	bodyY[1] = 5;
	bodyX[2] = 8;
	bodyY[2] = 5;
	system("color A");
	for(;;){
		if(kbhit()){
			input = getch();
			if(input == 'w'){
				dir = 4;
			} else if(input == 'a'){
				dir = 3;
			} else if(input == 's'){
				dir = 2;
			} else if(input == 'd'){
				dir = 1;
			}
		}
		sleep(1);
		move();
		system("cls");
		for(int y = 0; y < screenHeight; y++){
			for(int x = 0; x < screenWidth; x++){
				if(y != 0 && y != screenHeight-1){
					if(x == 0 || x == screenWidth-1){
						printf("=");
					} else {
						bool has = false;
						for(int i = 0; i < bodyLength; i++){
							if(bodyX[i] == x && bodyY[i] == y){
								has = true;
							}
						}
						if(has){
							printf("o");
						} else if(x == foodX && y == foodY){
							printf("x");
						} else {
							printf(" ");
						}
					}
				} else {
					printf("=");
				}
			}
			printf("\n");
		}
		printf("X: %d Y: %d", bodyX[2], bodyY[2]);
	}
}

void move(){
	if(!checkCollision()){
		for(int i = bodyLength-1; i > -1; i--){
			if(i != 0){
				bodyX[i] = bodyX[i-1];
				bodyY[i] = bodyY[i-1];
			} else {
				if(dir == 1){
					bodyX[i] = bodyX[i] + 1;
				} else if(dir == 2){
					bodyY[i] = bodyY[i] + 1;
				} else if(dir == 3){
					bodyX[i] = bodyX[i] - 1;
				} else {
					bodyY[i] = bodyY[i] - 1;
				}
			}
		}
	} else {
		for(int i = bodyLength; i > 0; i--){
			bodyX[i] = bodyX[i-1];
			bodyY[i] = bodyY[i-1];
		}
		bodyY[0] = foodY;
		bodyX[0] = foodX;
		bodyLength++;
		spawnFood();
	}
}

void spawnFood(){
	foodX = rand() % (screenWidth-1 + 1 - 1) + 1;
	foodY = rand() % (screenHeight-1 + 1 - 1) + 1;
}

bool checkCollision(){
	if(dir == 1) {
		if((bodyX[0] + 1) == foodX && bodyY[0] == foodY){
			return true;
		}
	} else if(dir == 2){
		if((bodyY[0] + 1) == foodY && bodyX[0] == foodX){
			return true;
		}
	} else if(dir == 3){
		if((bodyX[0] - 1) == foodX && bodyY[0] == foodY){
			return true;
		}
	} else {
		if((bodyY[0] - 1) == foodY && bodyX[0] == foodX){
			return true;
		}
	}
		return false;
}