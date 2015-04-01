#include "sumo.h"

// メイン関数
int main(int argc, char *argv[])
{
	g_action = NONE;	// マシンの行動：設定なし
	g_status = BEFORESTART;	// マシンのステータス：起動前

	// システムを起動
	startSystem();

	// メインループ：ステータスが終了なら抜ける
	while(g_status != END)
	{
		// 入力センサ値をチェック
		getInputSensorValue();

		// 取るべき行動を決定する
		g_action = decideAction();

		// 利用者に現在の行動を知らせる
		announceCurrentAction(g_action);

		// 行動を実行する(未実装)
		exeAction(g_action);

		// 取るべき行動が停止の場合、 終了ステータスに変更
		if(g_action == STOPTOEND)
		{
			g_status = END;
		}
	}
    exit(0);
}

