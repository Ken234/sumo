#include"decideaction.h"

#include<stdio.h>

/**
 * @brief 行動を実行する
 *
 */
void exeAction(ACTION action)
{
	switch(action)
	{
		// 攻撃
		case ATTACK:
			// exeAttack() 未実装 - 作田
			break;
		// 敵に接近
		case CLOSEENEMY:
			// moveToEnemy() 未実装 - 佐久間
			break;
		// 中心に移動
		case MOVECENTER:
			// moveCenterRing() 未実装 - 作田
			break;
		// 終了
		case STOPTOEND:
			// stopSystem() 未実装 - 佐久間
			break;
		// それ以外（起動前など）
		default:
			printf("ERR: exeAction: the action is unexpected.");
	}
}
