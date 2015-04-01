#include"getTimeLeft.h"
#include"stdio.h"
#include <time.h>

/**
 * @brief 競技残り時間を計算して返す
 * @return 競技残り時間(ミリ秒単位)
 *
 */

int getTimeLeft()
{
	int left_time;
	
	left_time = clock() - g_startTime;
	if(left_time < 0){
		printf("INF: Time is over!!");
	}
	return left_time;
}
