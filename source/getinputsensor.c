#include"getinputsensor.h"

#include<stdio.h>

/**
 * @brief 入力センサー値を取得する
 *
 * 取得した値はグローバル変数のhistoryInputSensor構造体に保存される
 * 構造体はインデックスが若いほど新しい履歴になる
 */
void getInputSensorValue()
{
	unsigned char csRes;
	unsigned char uwRes;
	TOUCH_SENSOR_DATA touchSensorData;
	int i;
	
	// センサー値取得
	getColorSensor(&csRes);
	getUWSensor(&uwRes);
	getTouchSensor(&touchSensorData);
	
	// センサ値更新
	// 重かったら履歴を残すセンサ値を減らす、履歴数を減らすなどを考える
	
	// 1つづつずらす
	for(i=0; i<HISTORY-1; i++)
	{
		historyInputSensor.color[HISTORY-i] = historyInputSensor.color[HISTORY-i-1];
		historyInputSensor.ultrawave[HISTORY-i] = historyInputSensor.ultrawave[HISTORY-i-1];
		historyInputSensor.touch[HISTORY-i].left = historyInputSensor.touch[HISTORY-i-1].left;
		historyInputSensor.touch[HISTORY-i].right = historyInputSensor.touch[HISTORY-i-1].right;
	}
	
	// 最新の値を代入
	historyInputSensor.color[0] = csRes;
	historyInputSensor.ultrawave[0] = uwRes;
	historyInputSensor.touch[0].left = touchSensorData.left;
	historyInputSensor.touch[0].right = touchSensorData.right;
}

