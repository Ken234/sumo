#define ONELOOP 1*1000//main関数での1ループ動作での待機時間 単位はus
#define DEBUG_ARM TRUE//アームの上げ下げ動作の成否をLEDで通知、失敗->赤色点滅

//グローバル変数
unsigned int g_ArmAttackCountDown;
int g_IsAttack;
//関数宣言
int attack_lift_up();
int exe_arm_up();
int exe_arm_stop();
int exe_arm_down();


