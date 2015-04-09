/*
		索敵フェイズで使用するモジュール、変数を宣言するヘッダファイル
*/

//敵と正面で向かい合っていると想定している状態のときの超音波センサの閾値
#define SOUNDTHRESHOLD (unsigned char)(30)

// 索敵状態
typedef enum
{
	NOTSEARCH = 0,			//非索敵状態
	SOUNDSEARCH,		//超音波センサーで索敵中
	SEARCHPEAK,			//超音波センサーのピークを検索する
	FACE2FACE,			//自機を回転して向かい合う
	CLOSE2ENEMY,		//敵機に接近する
	SEARCHEND			//索敵終了
}SEARCH;

SEARCH g_search;	//索敵フェイズのマシン状態

//　索敵行動に関係する関数の宣言
void moveToEnemy();		//索敵行動を制御する
void soundSearch();		//超音波センサーで索敵を行う
int searchSoundPeak();	//超音波センサーの履歴からピークを検索する
void face2face(int);	//敵機と向き合うように自機を回転させる
void close2enemy();		//敵機と向き合った状態から接近するように行動する
