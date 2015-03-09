#include "sumo.h"

// メイン関数
int main(int argc, char *argv[])
{
	// システムのステータスを起動前に設定
	g_status = BEFORESTART;
	
	// システムを起動させる
	// スタートボタンが押下されるまで、この関数内で無限ループ
	startSystem();
	
	// メインループ
	while(g_status == END)
	{
		// メイン処理
	}
	
    exit(0);
}
