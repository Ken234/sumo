/* 
	main.cで呼ばれるヘッダファイル
	
	モジュール構造図における全体図にある関数ごとにCファイルが作成されるので、
	ここではそのCファイルに対応するヘッダファイルをincludeする
	また、システム全体で使うグローバル変数などを記述したcommon.hもここでincludeする
*/

#ifndef SUMO
#define SUMO

#include"announcecurrentaction.h"
#include"common.h"
#include"decideaction.h"
#include"ev3module.h"
#include"exeaction.h"
#include"exeattack.h"
#include"getinputsensor.h"
#include"getTimeLeft.h"
#include"sakuma.h"
#include"startsystem.h"

#endif
