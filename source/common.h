/* 
	グローバル変数などのヘッダファイル
	
	システム全体で使うグローバル変数などを記述する
*/

#ifndef COMMON
#define COMMON

#include "ev3module.h"

#define GAMETIME 300

// マシンの状態のenum
enum STATUS
{
	BEFORESTART = 0,
	STARTED,
	END
};

// ステータス関係
int g_status;	// マシンの状態

// タイマー関係
int g_startTime;			// マシンが起動した時間

void setStartTime();		// マシンが起動した時間を記録する
int getReminedTimeToEnd();	// システム終了までの時間を取得する

#endif
