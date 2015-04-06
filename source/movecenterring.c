#include "movecenterring.h"

#include <stdio.h>
#include <unistd.h>

void moveCenterRing()
{	
	static DIRECTION_CENTER directionCenter = DC_INSUFFICIENT_SAMPLE;	// 機体の向き
	static DIRECTION_ROTATE directionRotate = DR_RIGHT;					// 回転の向き
	
	// 前回ループから中心に移動中の場合
	if(g_isMoveCenter == TRUE)
	{
		// 現在の向きを取得
		directionCenter = getDirection();
		
		switch(directionCenter)
		{
			case DC_INSUFFICIENT_SAMPLE:
				// そのまま回転
				rotateCenterRing(directionRotate);
				printf("INF: moveCenterRing: INSUFFICIENT SAMPLE.");
				break;
			case DC_GET_WORSE:
				// 逆回転
				directionRotate = !directionRotate;
				rotateCenterRing(directionRotate);
				printf("INF: moveCenterRing: GET WORSE.");
				break;
			case DC_GET_BETTER:
				// そのまま回転
				rotateCenterRing(directionRotate);
				printf("INF: moveCenterRing: GET BETTER.");
				break;
			case DC_CENTER:
				// 直進する
				moveCenter();
				printf("INF: moveCenterRing: MOVE CENTER.");
			default:
				printf("ERR: moveCenterRing: invalid direction to center.");
		}
	}
	else
	{
		// 今回ループから中心に移動する場合
		rotateCenterRing(directionRotate);
		g_isMoveCenter = TRUE;
	}
}

/**
 * @brief 機体の向きを取得する
 * @retuen 機体の向き
 *
 */
DIRECTION_CENTER getDirection()
{
	int i;
	
	// サンプル数が足りない場合
	for(i=0;i<SAMPLENUMBER-1;i++)
	{
		if(historyAction[i] != MOVECENTER)
			return DC_INSUFFICIENT_SAMPLE;
	}
	
	// 現在ループが前より中心に近づいていた場合
	if(historyInputSensor.color[0] >= historyInputSensor.color[1])
	{
		return DC_GET_BETTER;
	}
	// 少し前にピークがあった場合　→　中心に向いている
	else if((historyInputSensor.color[0] < historyInputSensor.color[2]) && (historyInputSensor.color[2] > historyInputSensor.color[4]) )
	{
		return DC_CENTER;
	}
	// それ以外　→　中心から外れている
	else
	{
		return DC_GET_WORSE;
	}
}

/**
 * @brief 機体を中心に回転させる
 * @direction 回転の向き
 *
 */
void rotateCenterRing(DIRECTION_ROTATE direction)
{
	switch(direction)
	{
		case DR_RIGHT:
			setMotorPower(LMOT_CH, ROTATEMOTORVALUE);
			setMotorPower(RMOT_CH, (-1)*ROTATEMOTORVALUE);
			printf("INF: rotateCenterRing: turn right.");
			break;
		case DR_LEFT:
			setMotorPower(LMOT_CH, (-1)*ROTATEMOTORVALUE);
			setMotorPower(RMOT_CH, ROTATEMOTORVALUE);
			printf("INF: rotateCenterRing: turn left.");
			break;
		default:
			printf("ERR: rotateCenterRing: invalid value.");
	}
}


/**
 * @brief 機体を中心に直進させる
 *
 */
void moveCenter()
{
	setMotorPower(LMOT_CH, STRAIGHTMOTORVALUE);
	setMotorPower(RMOT_CH, STRAIGHTMOTORVALUE);
	printf("INF: moveCenter: move center.");
	
	while(historyInputSensor.color[0] >= historyInputSensor.color[1])
	{
		// 中心に近づいている間は直進し続ける
		usleep(10000);
	}
}
