#include"decideaction.h"

#include<stdio.h>

/**
 * @brief 行動を決定する
 *
 * しきい値・行動選択は要調整
 */
ACTION decideAction()
{
	ACTION ret = NONE;	// 返り値

	DEGREE_ACCESS degreeAccess;
	DEGREE_RISK degreeRisk;

	degreeAccess = getDegreeAccess();	// 接近度を取得
	degreeRisk = getDegreeRisk();		// 危険度を取得

	if(degreeRisk == DR_RINGOUT)
	{
		// 土俵外の場合は停止させる
		printf("INF: Action: Stop");
		ret = STOPTOEND;
	}
	else if(degreeRisk == DR_RINGEDGE || degreeRisk == DR_NEARRING)
	{
		// 土俵際に近い場合は中心に移動させる
		printf("INF: Action: Move to the center");
		ret = MOVECENTER;
	}
	else if(degreeAccess == DA_NEAR || degreeAccess == DA_FAR)
	{
		// 安全かつ相手と接触していない場合は相手を探す
		printf("INF: Action: Close enemy");
		ret = CLOSEENEMY;
	}
	else if(degreeAccess == DA_CONTACT)
	{
		// 相手と接触している場合は相手を攻撃
		printf("INF: Action: Attack");
		ret = ATTACK;
	}
	else
	{
		// エラー：条件抜け
		printf("ERR: Failed decide action");
		ret = STOPTOEND;
	}

	// 行動の履歴を更新する
	updateHistoryAction(ret);

	return ret;
}

/**
 * @brief 相手との接近度を決定する
 *
 * しきい値は要調整
 */
DEGREE_ACCESS getDegreeAccess()
{
	// 現在ループでのセンサ値を取得
	unsigned char ultrawave = historyInputSensor.ultrawave[0];
	unsigned char touchLeft = historyInputSensor.touch[0].left;
	unsigned char touchRight = historyInputSensor.touch[0].right;

	if(touchLeft == TS_ON || touchRight == TS_ON)
	{
		// 相手と接触している：タッチセンサのどちらかがON
		printf("INF: Degree Access: DA_CANTACT");
		return DA_CONTACT;
	}
	else if(ultrawave < TH_ACCESS_NEAR)
	{
		// 距離が近い
		printf("INF: Degree Access: DA_NEAR");
		return 	DA_NEAR;
	}
	else if(ultrawave < TH_ACCESS_FAR)
	{
		// 距離が遠い
		printf("INF: DegreeA ccess: DA_FAR");
		return DA_FAR;
	}
	else
	{
		// それ以外 = 相手が見つかっていない
		printf("INF: Degree Access: DA_NOTDETECT");
		return DA_NOTDETECT;
	}
}

/**
 * @brief 相手との危険度を決定する
 *
 * しきい値は要調整
 */
DEGREE_RISK getDegreeRisk()
{
	// 現在ループでのセンサ値を取得
	unsigned char colorNow = historyInputSensor.color[0];
	// １つまえのループでのセンサ値を取得
	unsigned char colorBefore = historyInputSensor.color[1];

	if(colorBefore >TH_RISK_NEARRING && colorNow < TH_RISK_CENTER)
	{
		// 土俵の外にいる：負け
		// 前のループの色が濃く、現在のループの色が薄い場合→土俵際を通過
		printf("INF: Degree Risk: DA_RINGOUT");
		return DR_RINGOUT;
	}
	else if(colorNow < TH_RISK_CENTER)
	{
		// 土俵の中心にいる：非常に安全
		printf("INF: Degree Risk: DA_CENTER");
		return DR_CENTER;
	}
	else if(colorNow < TH_RISK_NEARCENTER)
	{
		// 土俵の中心寄りにいる：安全
		printf("INF: Degree Risk: DA_NEARCENTER");
		return DR_NEARCENTER;
	}
	else if(colorNow < TH_RISK_NEARRING)
	{
		// 土俵寄りにいる：危険
		printf("INF: Degree Risk: DA_NEARRING");
		return DR_NEARRING;
	}
	else
	{
		// 土俵際にいる：非常に危険
		printf("INF: Degree Risk: DR_RINGEDGE");
		return DR_RINGEDGE;
	}
}

/**
 * @brief 行動履歴を更新する
 */
void updateHistoryAction(ACTION action)
{
	int i;

	// 1つづつずらす
	for(i=0; i<HISTORY-1; i++)
	{
		historyAction[HISTORY-i] = historyAction[HISTORY-i-1];
	}

	// 最新の値を代入
	historyAction[0] = action;
}

