#include "ev3module.h" // ありがたいライブラリをインクルード
#include <time.h>
#include "sakuma.h"// 自作ヘッダファイル
// mindstormを使うためのおまじない
#ifndef LMS2012
#define LMS2012
#include"lms2012.h"
#endif
#define ARMLIMIT 1000

int attack_lift_up(){
	static int timerArm = -1;
	int elapsedTime = clock() - timerArm;
	if(elapsedTime > ARMLIMIT){//アーム上下動作初期化
		timerArm = clock();
		elapsedTime = clock() - timerArm;
	}
	//アームの動作制御
	//200msecまでアーム上昇，300msecまでアーム停止,500msecまでアーム下降
	if(elapsedTime < 200*1000){
		return exe_arm_up();
	}else if(elapsedTime < 300*1000){
		return exe_arm_stop();
	}else if(elapsedTime < 500*1000){
		return exe_arm_down();
	}else{
		return exe_arm_stop();
	}

	if(elapsedTime){
		g_IsAttack = TRUE;
	}else{
		g_IsAttack = FALSE;
	}
}

//アームを上げる; 7-1-2
int exe_arm_up()
{
	return setMotorPower(UMOT_CH, 30);
}

//アームを止める； 7-1-2
int exe_arm_stop()
{
	return stopMotorFunc();
}

//アームを下げる； 7-1-2
int exe_arm_down()
{
	return setMotorPower(UMOT_CH, (unsigned char)(-30));
}

