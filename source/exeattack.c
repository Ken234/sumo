#include "exeattack.h"
#include "sakuma.h"

#include <stdio.h>

/**
 * @brief 相手を攻撃する
 *
 * 現在の行動が「相手に近づく」や「土俵の中心に移動する」場合でも
 * アームのタイマーが1以上（アーム制御中）なら呼ばれる
 * そのため、「アーム制御関数」は必ず実行する
 * 一方で「相手を押す関数」は現在のアクションが「攻撃」の場合にのみ実行する
 */
void exeAttack()
{
	// この関数が呼ばれた際には、アーム制御は必ず実行する
	// これは、アームを上げる→下げる制御を一連の流れとして必ず実行させるためである
	attack_lift_up();

	// 現在の取るべきアクションが「攻撃」の場合にのみ,相手を押す
	if(g_action == ATTACK)
	{
		attackPush();
	}
}

/**
 * @brief 相手を押す
 *
 * とりあえず直進だけ
 * カーブさせるかは、実際の動きを見てから
 */
void attackPush()
{
	// 注意！ 直進しかしないので、追加実装必要かも
	setMotorPower(LMOT_CH, PUSH_STRAIGHT);
	setMotorPower(RMOT_CH, PUSH_STRAIGHT);
}
