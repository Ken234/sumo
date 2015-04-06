#ifndef DECIDEACTION
#define DECIDEACTION

#include"common.h"

/// しきい値
// 接近度判定
#define TH_ACCESS_NEAR 30
#define TH_ACCESS_FAR 60

// 危険度判定
#define TH_RISK_CENTER 200
#define TH_RISK_NEARCENTER 100
#define TH_RISK_NEARRING 100

/// enum
// 相手との接近度
typedef enum
{
	DA_CONTACT = 0,	// 接触している
	DA_NEAR,		// 近い
	DA_FAR,			// 遠い
	DA_NOTDETECT	// 検出できていない
}DEGREE_ACCESS;

// 危険度
typedef enum
{
	DR_CENTER = 0,	// 中心
	DR_NEARCENTER,	// 中心寄り
	DR_NEARRING,	// 土俵寄り
	DR_RINGEDGE,	// 土俵際
	DR_RINGOUT		// 土俵の外
}DEGREE_RISK;

/// 関数
ACTION decideAction();
DEGREE_ACCESS getDegreeAccess();
DEGREE_RISK getDegreeRisk();
void updateHistoryAction(ACTION action);

#endif
