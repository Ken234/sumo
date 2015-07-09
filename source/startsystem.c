#include"startsystem.h"

#include"stdio.h"

/**
 * @brief システムを起動する
 * @return 起動成功ならTRUE,失敗ならFALSE
 */
int startSystem()
{
	int valueStartKey = FALSE; // スタートキーの値
	int key[6];	// UIキー値の配列
	int *p_key;	// キーのポインタ
	p_key = key;	// ポインタに代入
	
	// システムが起動中か確認する
	if(!checkSystemIsBeforeStart())
	{
		printf("ERR: sytem already started");
		return FALSE;
	}
	else
	{
		initializeUI();	// 起動していない場合、スタートキーを取得するためにUIだけ初期化
	}
	
	// スタートキーが押されるまでループ
	while(!valueStartKey)
	{
		printf("INF: waiting start key press");
		getKeySensor(p_key);	// センサー値取得
		valueStartKey = key[0];	// 適当に配列の1番目にしたので、スタートキーがどのボタンかで変更すること
		usleep(10000);	// 0.01秒スリープ
	}
	printf("INF: pressed start key");
	
	initializeSystem();	// システムを初期化する
	g_status = STARTED;	// システムのステータスを変更する
	
	return TRUE;
}

/**
 * @brief システムが起動前か確認する
 * @return 起動前ならTRUE,それ以外ならFALSE
 */
int checkSystemIsBeforeStart()
{
	switch(g_status)
	{
		case BEFORESTART:
			printf("INF: check...System is before start");
			return TRUE;
			
		default:
			printf("INF: check...System is started");
			return FALSE;
	}
}


/**
 * @brief システムを初期化する
 */
void initializeSystem()
{
	// 入力センサ値・行動履歴を初期化
	int i;
	for(i=0;i<HISTORY;i++)
	{
		historyInputSensor.color[i] = 0;
		historyInputSensor.ultrawave[i] = 0;
		historyInputSensor.touch[i].left = TS_OFF;
		historyInputSensor.touch[i].right = TS_OFF;
		historyAction[i] = NONE;
	}
	
	// UARTセンサを初期化
	initUARTSensor();
	ChgSensorMode(COLOR_CH, MOD_COL_REFLECT);
	ChgSensorMode(UW_CH, UW_MODE_DIST_CM);
	
	// モータを初期化
	startMotorFunc();

	// 開始時刻を記録
	setStartTime();

	printf("SUMO System is started.");
	
	return;
}
