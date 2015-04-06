#include"exeaction.h"
#include"exeattack.h"
#include"sakuma.h"

#include<stdio.h>

/**
 * @brief 行動を実行する
 *
 * 引数で指定された行動を実行する
 * 想定外の行動を指定された場合はエラーを出力して停止する
 * また、攻撃用アーム制御のタイマーが1以上(g_IsAttackがtrue)の場合は必ず攻撃関数を呼ぶ
 */
void exeAction(ACTION action)
{
	// 攻撃中なら、exeAttack()を毎回呼ぶ
	if(g_IsAttack)
	{
		printf("INF: exeAction: Now is attacking, So exe attack.");
		exeAttack();
	}

	switch(action)
	{
		// 攻撃
		case ATTACK:
			exeAttack();
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
			stopSystem();
			break;
		// それ以外（起動前など）
		default:
			g_action = STOPTOEND;
			printf("ERR: exeAction: the action is unexpected.");
			stopSystem();
	}
}

/**
 * @brief 機体を停止させる
 *
 */
void stopSystem()
{
	// 入出力型を閉じる
	closeTouchSensor();
	closeUART();
	stopMotorFunc();	// モータ値が0になる
	closeUI();

	printf("SUMO System is finished.");
}
