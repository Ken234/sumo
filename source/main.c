#include "sumo.h"

// メイン関数
int main(int argc, char *argv[])
{
	ACTION action = MOVECENTER;

	// システムのステータスを起動前に設定
	g_status = BEFORESTART;

	// システムを起動させる
	// スタートボタンが押下されるまで、この関数内で無限ループ
	startSystem();

	// メインループ
	while(g_status == END)
	{
		// 入力センサ値をチェック
		getInputSensorValue();

		// 取るべき行動を決定する
		action = decideAction();

		// 利用者に現在の行動を知らせる(未実装)
		// confirmCondition(action);

		// 行動を実行する(未実装)
		// exeAction(action);

		// 取るべき行動が停止の場合、 メインループから抜けるステータスに変更
		if(action == STOPTOEND)
		{
			g_status = END;
		}
	}
	exit(0);
}
