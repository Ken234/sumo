/* 
	グローバル変数などのヘッダファイル
	
	システム全体で使うグローバル変数などを記述する
*/

#ifndef COMMON
#define COMMON

#include "ev3module.h"

// 試合時間：300秒
#define GAMETIME 300
// 入力センサ履歴 とりあえず30回
#define HISTORY 30

// enum関係
// マシンの状態
typedef enum
{
	BEFORESTART = 0,	// 起動前：スタートボタン押下前
	STARTED,			// 起動中
	END					// 終了
}STATUS;

// マシンの行動
typedef enum
{
	NONE = 0,	// 起動時
	ATTACK,		// 攻撃
	CLOSEENEMY,	// 相手に近づく
	MOVECENTER,	// 中心に移動する
	STOPTOEND	// 停止する
}ACTION;

// ステータス関係
STATUS g_status;	// マシンの状態
ACTION g_action;	// マシンの行動

// タイマー関係
int g_startTime;			// マシンが起動した時間

void setStartTime();		// マシンが起動した時間を記録する
int getReminedTimeToEnd();	// システム終了までの時間を取得する

// センサ履歴関係
typedef struct{
	unsigned char color[HISTORY];		// カラーセンサ、インデックスが若いほど新しい履歴
	unsigned char ultrawave[HISTORY];	// 超音波センサ
	TOUCH_SENSOR_DATA touch[HISTORY];	// タッチセンサ
}INPUT_SENSOR_VALUE;

INPUT_SENSOR_VALUE historyInputSensor;	// 履歴

// 行動履歴
ACTION historyAction[HISTORY];

#endif
