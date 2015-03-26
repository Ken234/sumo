#include"getstopkey.h"
#include"stdio.h"

/**
 * @brief 停止ボタンの押下状態を返す
 * @return システム起動前ならFALSE、それ以外はTRUE
 * @g_status 停止ボタンが押されていたらENDに変更
 */
int getStopKey()
{
	int valueStopKey = FALSE; // ストップキーの値
	int key[6];	// UIキー値の配列
	int *p_key;	// キーのポインタ
	p_key = key;	// ポインタに代入
	
	// システムが起動中か確認する
	if(checkSystemIsBeforeStart())
	{
		printf("ERR: sytem hasn't been started yet...");
		return FALSE;
	}

	// keyの押下状態取得
	getKeySensor(p_key);
	valueStopKey = key[5]; //適当に配列の最後にしたので、ストップキーがどのボタンかは実機で確認・設定

	if(valueStopKey){// 停止ボタンが押されていた場合の処理
		printf("INF: pressed END key");
		//initializeSystem(); // システムを初期化する
		g_status = END; // システムのステータスを変更する
	}

	return TRUE;
}

