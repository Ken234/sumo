#include"common.h"
#include <time.h>

/**
 * @brief システム起動時の時刻を記録する
 *
 * 単位は(ms)
 */
void setStartTime()
{
	g_startTime = clock();
	printf("INF: set start time");
}

/**
 * @brief システム終了までの時刻を記録する
 *
 * 単位は(ms)
 */
int getReminedTimeToEnd()
{
	int ret;
	ret = GAMETIME * 1000 - g_startTime;
	
	if(ret < 0) ret = 0;	// 既にタイムアウトしていた場合は返り値を0にする
	
	printf("INF: Remind time to the end is %d (ms)", ret);

	return ret;	
}
