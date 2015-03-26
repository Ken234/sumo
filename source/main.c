#include "ev3module.h" // ありがたいライブラリをインクルード
// mindstormを使うためのおまじない
#ifndef LMS2012
#define LMS2012
#include"lms2012.h"
#endif
#include "sakuma.h"

// メイン関数
int main(int argc, char *argv[])
{
	int ret;
    while(TRUE){
		ret = attack_lift_up();
#if DEBUG_ARM
//アーム動作に失敗したらLEDを赤色点滅させる
		if(!ret){
			setLED(RED_FLASH);
			break;
		}
//アーム動作（1回）が終了したらLEDを緑色点灯させる
		if(!countDown){
			setLED(REEN);
			break;
		}
#endif
		usleep(ONELOOP);
	}
    exit(0);
}

