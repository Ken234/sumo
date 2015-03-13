/* 
	main.cで呼ばれるヘッダファイル
	
	モジュール構造図における全体図にある関数ごとにCファイルが作成されるので、
	ここではそのCファイルに対応するヘッダファイルをincludeする
	また、システム全体で使うグローバル変数などを記述したcommon.hもここでincludeする
*/

#ifndef SUMO
#define SUMO

#include"common.h"
#include"startsystem.h"
#include"getinputsensor.h"
#include"decideaction.h"

#endif
