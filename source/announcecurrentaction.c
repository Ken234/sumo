#include"announcecurrentaction.h"

#include<stdio.h>

/**
 * @brief 現在の行動を知らせる
 *
 * 行動によってLEDの色を変える
 */
void announceCurrentAction(ACTION action)
{
	switch(action)
	{
	// 攻撃 ： 緑
	case ATTACK:
		setLED(GREEN);
		break;
	// 敵に接近 ： オレンジ
	case CLOSEENEMY:
		setLED(ORANGE);
		break;
	// 中心に移動 : 赤
	case MOVECENTER:
		setLED(RED);
		break;
	// 終了 : 赤点滅？
	case STOPTOEND:
		setLED(RED_FLASH);
		break;
	// それ以外（起動前など） : 黒
	default:
		setLED(BLACK);
	}
}
