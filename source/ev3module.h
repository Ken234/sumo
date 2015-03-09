/* ******************************************************* */
/*   COPYRIGHT(C) 2014                                */
/*   Toshiba TEC Corporation                               */
/*   ALL RIGHTS RESERVED                                   */
/* ******************************************************* */
/**
 *  @file    ev3module.h
 *
 *  @brief  ev3のセンサ(超音波、タッチ、カラー、ジャイロ)、アクチュエータ、UI(LED、KEY)の初期化等を行う
 *
 *  @author seiji_saitou@toshibatec.co.jp
 */
 
/*
[使い方]
    //-----------------------------
    //          モータ
    //-----------------------------
    int MotorSampleCode(){
        //モータの状態を設定
        //(いきなり呼び出しでOK、内部で初期アクセス時に自動で初期化する)
        setMotorPower(CH_A, 30);//<-CH_Aに繋がれたモータをPower30に設定する
        sleep(5);
        setMotorPower(CH_A, 0);//<-CH_Aに繋がれたモータをPower0に設定する
        
        //使い終わったらちゃんと片付ける
        stopMotorFunc();
    }
    //-----------------------------
    //超音波、ジャイロ、カラー センサ
    //-----------------------------
    int UARTSensorSampleCode(){
        //格納用の変数を宣言
        unsigned char csRes;
        unsigned char uwRes;
        float gyroRes;
        
        //センサの状態を取得
        //(いきなり呼び出しでOK、内部で初期アクセス時に自動で初期化する)
        getColorSensor(&csRes);
        getUWSensor(&uwRes);
        getGyroSensor(&gyroRes);
        
        printf("Color: %d  UW: %d  GYRO: %f\n",csRes,uwRes,gyroRes);
        
        //使い終わったらちゃんと片付ける
        closeUART();
    }
    
    //-----------------------------
    //          LED、KEY
    //-----------------------------
    int UISampleCode(){
        //格納用の変数を宣言
        int key[6];
        
        //KEYセンサの状態を取得
        //(いきなり呼び出しでOK、内部で初期アクセス時に自動で初期化する)
        getKeySensor(key);
        
        printf("Touch Left: %d Right: %d\n",tsData.left,tsData.right);
        
        //LEDの色を設定
        //(いきなり呼び出しでOK、内部で初期アクセス時に自動で初期化する)
        setLED(RED);
        sleep(1);
        setLED(GREEN);
        sleep(1);
        setLED(RED_FLASH);
        sleep(1);
        setLED(GREEN_FLASH);
        
        //使い終わったらちゃんと片付ける
        closeUI();
    }
    //-----------------------------
    //        タッチセンサ
    //-----------------------------
    int touchSensorSampleCode(){
        //格納用の変数を宣言
        TOUCH_SENSOR_DATA tsData;
        
        //タッチセンサの状態を取得
        //(いきなり呼び出しでOK、内部で初期アクセス時に自動で初期化する)
        getTouchSensor(&tsData);
        
        printf("Touch Left: %d Right: %d\n",tsData.left,tsData.right);
        
        //使い終わったらちゃんと片付ける
        closeTouchSensor();
    }
*/





#ifndef SENSOR
#define SENSOR

#include  <stdio.h>
#include  <fcntl.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <string.h>
#include  <signal.h>
#include  <sys/mman.h>
#include  <sys/ioctl.h>
#include "lms2012.h"

#define CH_A    0x01
#define CH_B    0x02
#define CH_C    0x04
#define CH_D    0x08

#define CH_1    0x00
#define CH_2    0x01
#define CH_3    0x02
#define CH_4    0x03



//----------- PORT NUMBER -----------
#define COLOR_CH   CH_1
#define TOUCH_L_CH CH_2
#define TOUCH_R_CH CH_3
#define UW_CH      CH_4
#define GYRO_CH    CH_4//利用時はUWと被っているので注意

#define RMOT_CH CH_B	/* 右側モータ */
#define LMOT_CH CH_C	/* 左側モータ */
#define UMOT_CH CH_D	/* 突上モータ */

//------------UWSensor------------
#define UW_MODE_DIST_CM   0
#define UW_MODE_DIST_INCH 1
#define UW_MODE_LISTEN    2

//------------ColorSensor------------
//0:COL_REFLECT 1:COL_AMBIENT 2:CON_COLOR
#define MOD_COL_REFLECT 0//反射光(赤)
#define MOD_COL_AMBIENT 1//周囲の明るさ
#define MOD_COL_COLOR   2//色

//------------TouchSensor------------
#define PUSHED_THRESHOLD 50 //タッチセンサ押下検知閾値

//------------GyroSensor------------
#define GYRO_MODE_ANGLE          0
#define GYRO_MODE_ANGLE_RATE     1
#define GYRO_MODE_ANGLE_AND_RATE 2

//------------LED------------
#define BLACK           0+'0'
#define GREEN           1+'0'
#define RED             2+'0'
#define ORANGE          3+'0'
#define GREEN_FLASH     4+'0'
#define RED_FLASH       5+'0'
#define ORANGE_FLASH    6+'0'
#define GREEN_PULSE     7+'0'
#define RED_PULSE       8+'0'
#define ORANGE_PULSE    9+'0'

//--------UART Type Sensor(UW,CS,GYRO)-------
int uartfp;
UART *pUart;

//-------------UI(key,led)------------------
int uifp;

typedef struct {
	unsigned char Pressed[6];
} KEYBUF;
KEYBUF *keyPt;

//-----------------TouchSensor---------------
//Condition of touch sensor
typedef enum {
	TS_OFF,
	TS_ON
}TOUCH_SENSOR;

//Touch sensor condition
typedef struct{
	TOUCH_SENSOR  left;
	TOUCH_SENSOR  right;
}TOUCH_SENSOR_DATA;
int analogfp;
ANALOG *pTouch;

//-----------------Motor---------------------
int pwmfp;

//-------------------------------------------

int getTouchSensor(TOUCH_SENSOR_DATA *touchSensorData);
int closeTouchSensor();

int getColorSensor(unsigned char *csRes);
int getUWSensor(unsigned char *uwRes);
int getGyroSensor(float *gyroRes);
int closeUART();

int setMotorPower(unsigned char ch, unsigned char power);
int stopMotorFunc();


int getKeySensor(int *key);
int setLED(unsigned char color);
int closeUI();


#endif
