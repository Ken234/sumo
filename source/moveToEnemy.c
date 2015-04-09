#ifndef MOVETOENEMY
#define MOVETOENEMY
#include"moveToEnemy.h"
#endif
#include"ev3module.h"

#ifndef LMS2012
#define LMS2012
#include"lms2012.h"
#endif
#include<stdio.h>

#include "common.h"

/**
 * @brief 敵機に近づく行動を制御する
 * 
 * 
 */
void moveToEnemy()
{
	static int max_num = 0;	

	switch(g_search){
		case NOTSEARCH:
			printf("INFO: g_search is NOTSEARCH...\r\n");
			break;
		case SOUNDSEARCH:
			printf("INFO: g_search is SOUNDSEARCH...\r\n");
			soundSearch();
			break;
		case SEARCHPEAK:
			printf("INFO: g_search is SEARCHPEAK...\r\n");
			max_num = searchSoundPeak();
			break;
		case FACE2FACE:
			printf("INFO: g_search is FACE2FACE...\r\n");
			face2face(HISTORY - max_num);
			break;
		case CLOSE2ENEMY:
			printf("INFO: g_search is CLOSE2ENEMY...\r\n");
			close2enemy();
			break;
		case SEARCHEND:
			printf("INFO: g_search is SEARCHEND...\r\n");
			g_search = NONE;
			break;
	}
	return;
}


/**
 * @brief 索敵状態に入ってからの旋回角度と超音波センサの値の関係を保持する
 *
 * 4/8 正常系のみ、中断された後にカウント値(count_rot)を初期化するのは未実装
 */
void soundSearch()
{
	//索敵状態に移行してから旋回角度と超音波センサの値の関係を保持するために
	//超音波センサの値を一新する (右旋回の予定)
	static int count_rot = HISTORY;
	
	setMotorPower(LMOT_CH, (unsigned char)(10));
	setMotorPower(RMOT_CH, (unsigned char)(-10));
	count_rot--;
	//超音波センサの値をすべて一新したら、旋回を停止してピーク検索を行うフェイズに移行する
	if(count_rot == 0){
		count_rot = HISTORY;
		g_search = SEARCHPEAK;
		setMotorPower(LMOT_CH,(unsigned char)(0));
		setMotorPower(RMOT_CH,(unsigned char)(0));
	}
	return;
}

/**
 * @brief 超音波センサの履歴を5点平均で平滑化して最大値をピークとする
 * @return ピーク値が格納されていた超音波センサの配列（履歴）の添字
 * 
 * 
 */
int searchSoundPeak()
{
	static unsigned char average5ultrawave[HISTORY-5];
	unsigned char max = 0;
	int i,j;
	int num_max = 0;
	for (i=0;i<HISTORY-5;i++){
		for (j=0;j<5;j++){
			average5ultrawave[i] += historyInputSensor.ultrawave[i+j];
		}
		if (max < average5ultrawave[i]){
			max = average5ultrawave[i];
			num_max = i;
		}
	}
	return num_max;
}
/**
 * @brief ピーク値が格納された状態まで旋回運動を行う
 * 
 * 
 */
void face2face(int num_max)
{
	static int counter = 0;
	if (counter == 0){
		counter = num_max;
	}
	setMotorPower(LMOT_CH, (unsigned char)(-10));
	setMotorPower(RMOT_CH, (unsigned char)(10));
	counter--;
	if (counter == 0){
		setMotorPower(LMOT_CH, (unsigned char)(0));
		setMotorPower(RMOT_CH, (unsigned char)(0));
		g_search = CLOSE2ENEMY;
	}
	return;
}

/**
 * @brief 直進して敵に近づく。敵との距離が開く状態 or 正対の状態からはずれたのを検知したら中断する
 *        
 * 
 */
void close2enemy()
{
	setMotorPower(LMOT_CH, (unsigned char)(30));
	setMotorPower(RMOT_CH, (unsigned char)(30));
	//敵を見失ったら停止 and 索敵終了
	if (historyInputSensor.ultrawave[0] > SOUNDTHRESHOLD){
		printf("INFO: Lost enemy...\r\n");
		g_search = SEARCHEND;
	}
	return;
}
