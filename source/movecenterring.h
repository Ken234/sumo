#ifndef MOVECENTERRING
#define MOVECENTERRING

#include"common.h"
#include"sakuma.h"

// サンプル数
#define SAMPLENUMBER 5
// 回転時のモーター値
#define ROTATEMOTORVALUE 30
// 前進時のモーター値
#define STRAIGHTMOTORVALUE 30

typedef enum{
	DR_RIGHT = 0,
	DR_LEFT
}DIRECTION_ROTATE; 

typedef enum{
	DC_INSUFFICIENT_SAMPLE = 0,
	DC_GET_WORSE,
	DC_GET_BETTER,
	DC_CENTER,
}DIRECTION_CENTER; 

// 関数
void moveCenterRing();
DIRECTION_CENTER getDirection();
void rotateCenterRing(DIRECTION_ROTATE direction);
void moveCenter();

#endif
