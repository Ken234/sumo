/* 
	グローバル変数などのヘッダファイル
	
	システム全体で使うグローバル変数などを記述する
*/

#ifndef COMMON
#define COMMON

#include "ev3module.h"

#define GAMETIME 300
#define HISTORY 100

// enum関係
// マシンの状態
typedef enum
{
	BEFORESTART = 0,
	STARTED,
	END
}STATUS;

// マシンの行動
typedef enum
{
	ATTACK = 0,
	CLOSEENEMY,
	MOVECENTER,
	STOPTOEND
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

#endif
