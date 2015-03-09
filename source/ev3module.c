#include"ev3module.h"

#ifndef LMS2012
#define LMS2012
#include"lms2012.h"
#endif

//#defien DEBUG_EV3MODULE 1


//---------------------------------UART(UW,CS,GYRO) SENSOR-----------------------------------------------
/**
 * @brief UART系センサ(UW,CS,GYRO)のモードを変更する
 * @method ChgSonarMode
 * @param{unsigned char} [IN] ch
 * @param{int} [IN] mode
 * @param{int} [IN] sensorfp
 */
int ChgSensorMode(unsigned char ch, int mode)
{
	int i;
	int ret;
	static DEVCON DevCon;
	static int initialize = FALSE;

	if(initialize){
		initialize = TRUE;
		for (i=0; i < 4; i++) {
			DevCon.Connection[i] = CONN_NONE;
		}
	}

	DevCon.Connection[ch] = CONN_INPUT_UART;
	DevCon.Mode[ch] = (unsigned char)mode;

	ret = ioctl(uartfp, UART_SET_CONN, &DevCon);

	return ret;
}
/**
 * @brief UART系センサ(UW,CS,GYRO)の初期化をする
 * @method initUARTSensor
 * @param{unsigned char}[OUT]*csRes
 */
int initUARTSensor(){
	static int initialize = FALSE;

	if(!initialize){
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@UART\n");
		#endif
		
		uartfp = open("/dev/lms_uart", O_RDWR | O_SYNC);
		if (uartfp < 0) {
			#ifdef DEBUG_EV3MODULE
			printf("		Cannot open UART_DEVICE\n");
			#endif
			exit(-1);
		}
		// mmap()によりUARTデバイスドライバの共有メモリをマップします
		pUart  =  (UART*)mmap(0, sizeof(UART), 
			    PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, uartfp, 0);
		if (pUart == MAP_FAILED) {
			#ifdef DEBUG_EV3MODULE
			printf("		Failed to map device\n");
			#endif
			exit(-1);
		}
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE END  @UART\n");
		#endif
	}
	return TRUE;
}


/**
 * @brief カラーセンサ値を返す
 * @method getColorSensor
 * @param{unsigned char}[OUT]*csRes
 */
int getColorSensor(unsigned char *csRes){
	static int initialize = FALSE;
	unsigned char buff;
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("		READING@CS\n");
		#endif
		buff = (unsigned char)(pUart->Raw[COLOR_CH][pUart->Actual[COLOR_CH]][0]);
		#ifdef DEBUG_EV3MODULE
		printf(" CS:%d\n",buff);
		#endif
		*csRes = buff;
		//csRes = (unsigned char)(pColorSensor->Raw[COLOR_CH][pColorSensor->Actual[COLOR_CH]][0]);
	}
	else{
		//初期化をして再呼び出しを行う
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALIZE START@CS\n");
		#endif
		initUARTSensor();
		#ifdef DEBUG_EV3MODULE
		printf("		SET MODE@CS\n");
		#endif
		//ChgSensorMode(COLOR_CH, MOD_COL_REFLECT, colorfp); // カラーセンサーの動作モードを設定
		ChgSensorMode(COLOR_CH, MOD_COL_REFLECT); // カラーセンサーの動作モードを設定
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALIZE END@CS\n");
		#endif
		getColorSensor(csRes);
		
	}
	return TRUE;
}

//Mode：距離cm/距離inch/存在
//0:DIST-CM 1:DIST-INC 2:LISTEN
/**
 * @brief 超音波の値を返す
 * @method getUWSensor
 * @param｛unsigned char *｝[OUT]uwRes
 */
int getUWSensor(unsigned char *uwRes){
	static int initialize = FALSE;
	unsigned char buff;
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("		READING@UW\n");
		#endif
		buff = (unsigned char)pUart->Raw[UW_CH][pUart->Actual[UW_CH]][0];
		#ifdef DEBUG_EV3MODULE
		printf("		UW:%d\n",buff);
		#endif
		//uwRes = (unsigned char)pUart->Raw[UW_CH][pUart->Actual[UW_CH]][0];
		*uwRes = buff;
	}
	else{
		//初期化をして再呼び出しを行う
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE START@UW\n");
		#endif
		initUARTSensor();
		ChgSensorMode(UW_CH,UW_MODE_DIST_CM);
		
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE END@UW\n");
		#endif
		//再呼び出し
		getUWSensor(uwRes);
	}
	return TRUE;
}


/**
 * @brief ジャイロセンサの値を返す
 * @method getTouchSensor
 * @param{TOUCH_SENSOR_DATA}[OUT]*touchSensorData
 */
//int getGyroSensor(unsigned char *gyroRes){
int getGyroSensor(float *gyroRes){
	static int initialize = FALSE;
	static float initialValue;
	unsigned char buff0,buff1;
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("		READING@GYRO\n");
		#endif
		buff0 = (unsigned char)pUart->Raw[GYRO_CH][pUart->Actual[GYRO_CH]][0];
		buff1 = (unsigned char)pUart->Raw[GYRO_CH][pUart->Actual[GYRO_CH]][1];
		#ifdef DEBUG_EV3MODULE
		printf("		GRYO_1:%d GRYO_0:%d\n",buff1,buff0);
		#endif
		*gyroRes = (buff1 << 4) + buff0 - initialValue;
	}
	else{
		//初期化をして再呼び出しを行う
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE START@GYRO\n");
		#endif
		initUARTSensor();
		//set UW mode
		//ChgSensorMode(GYRO_CH,GYRO_MODE_ANGLE, uartfp);
		ChgSensorMode(GYRO_CH,0);
		
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE END@GYRO\n");
		#endif
		//再呼び出し
		getGyroSensor(gyroRes);
		initialValue = *gyroRes;
	}
	return TRUE;
}
/**
 * @brief UART通信(UW,CS,GYRO)を開放する
 * @method closeUART
 * @param{none}none
 */
int closeUART(){
	#ifdef DEBUG_EV3MODULE
	printf("		CLOSE@UART(UW,CS,GYRO)\n");
	#endif
	munmap(pUart, sizeof(UART));

	close(uartfp);
	return TRUE;
}
//---------------------------------TOUCH SENSOR-----------------------------------------------
/**
 * @brief タッチセンサの値を返す
 * @method getTouchSensor
 * @param{TOUCH_SENSOR_DATA}[OUT]*touchSensorData
 */
int getTouchSensor(TOUCH_SENSOR_DATA *touchSensorData){
	static int initialize = FALSE;
	unsigned char buffL, buffR;
	
	if(initialize){
	
		#ifdef DEBUG_EV3MODULE
		printf("		READING@TS\n");
		#endif
		//左側タッチセンサデータを取得する
		buffL = pTouch->Pin6[TOUCH_L_CH][pTouch->Actual[TOUCH_L_CH]];
		//右側タッチセンサデータを取得する
		buffR = pTouch->Pin6[TOUCH_R_CH][pTouch->Actual[TOUCH_R_CH]];
		
		#ifdef DEBUG_EV3MODULE
		printf("		S_VALUE L: %d R: %d@TS\n", buffL,buffR);
		#endif
		
		if(buffL < PUSHED_THRESHOLD){
			touchSensorData->left = TS_ON;
			#ifdef DEBUG_EV3MODULE
			printf("		LEFT  ON  |");
			#endif
		}
		else{
			touchSensorData->left = TS_OFF;
			#ifdef DEBUG_EV3MODULE
			printf("		LEFT  OFF |");
			#endif
		}
		if(buffR < PUSHED_THRESHOLD){
			touchSensorData->right = TS_ON;
			#ifdef DEBUG_EV3MODULE
			printf(" RIGHT ON @TS\n");
			#endif
		}
		else{
			touchSensorData->right = TS_OFF;
			#ifdef DEBUG_EV3MODULE
			printf(" RIGHT OFF@TS\n");
			#endif
		}
		#ifdef DEBUG_EV3MODULE
		//printf("		READING@TS\n");
		#endif
	}
	else{
		//初期化をして再呼び出しを行う
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALIZE START@TS\n");
		#endif
		
		
		//AnalogデバイスファイルをOpenする
		analogfp = open("/dev/lms_analog",O_RDWR | O_SYNC);//読み書き、動機モードでオープン
		if(analogfp < 0){
			#ifdef DEBUG_EV3MODULE
			printf("		Cann't open /dev/lms_analog @LEFT\n");
			#endif
			exit(-1);
		}
		
		//mmap()によりドライバ共有メモリにアクセスできるように設定
		pTouch = (ANALOG*)mmap(0,sizeof(ANALOG),
			PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, analogfp, 0);
		if(pTouch == MAP_FAILED){
			#ifdef DEBUG_EV3MODULE
			printf("		Failed to map device \n");
			#endif
			exit(-1);
		}
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALIZE END@TS\n");
		#endif
		//再呼び出し
		getTouchSensor(touchSensorData);
	}
	return TRUE;
}

/**
 * @brief タッチセンサを開放する
 * @method closeTouchSensor
 * @param{none}[none]none
 */
int closeTouchSensor(){
	#ifdef DEBUG_EV3MODULE
	printf("		CLOSE@TS\n");
	#endif
	munmap(pTouch, sizeof(ANALOG));
	close(analogfp);
	return TRUE;
}
//--------------------------------MOTOR-----------------------------------------
/**
 * @brief Motorを初期化する
 * @method startMotorFunc
 * @param{none}none 
 */
int startMotorFunc(){
	unsigned char Buf[4];
	int ret;
	static int initialize = FALSE;

	if(!initialize){
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@MOTOR\n");
		#endif
		initialize = TRUE;
		//デバイスオープン		
		pwmfp = open("/dev/lms_pwm",O_RDWR);
		if (pwmfp < 0) {
				#ifdef DEBUG_EV3MODULE
				printf("Cannot open dev/lms_pwm\n");
				#endif
				exit(-1);
		}
		
		Buf[0] = opPROGRAM_STOP;
		ret = write(pwmfp,Buf,1);
		if(ret == -1) return FALSE;

		Buf[0] = opPROGRAM_START;
		ret = write(pwmfp,Buf,1);
		if(ret == -1) return FALSE;

		Buf[0] = opOUTPUT_RESET;
		Buf[1] = CH_A | CH_B | CH_C | CH_D;
		ret = write(pwmfp,Buf,2);
		if(ret == -1) return FALSE;

		Buf[0] = opOUTPUT_START;
		Buf[1] = CH_A | CH_B | CH_C | CH_D;
		ret = write(pwmfp,Buf,2);
		if(ret == -1) return FALSE;
		

		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE END  @MOTOR\n");
		#endif
	}
	return ret;
}
/**
 * @brief Motorの値を設定する
 * @method closeUART
 * @param{unsigned char}ch 
 * @param{unsigned char}power 
 */
int setMotorPower(unsigned char ch, unsigned char power){
	static int initialize = FALSE;
    unsigned char Buf[4];
    int ret;
    
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("		SET@MOTOR : %d\n",power);
		#endif

		Buf[0] = opOUTPUT_POWER;
		Buf[1] = ch;
		Buf[2] = power;
		ret = write(pwmfp,Buf,3);
		
	}
	else{
		//初期化をして再呼び出しを行う
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE START@MOTOR\n");
		#endif
		startMotorFunc();
		#ifdef DEBUG_EV3MODULE
		printf("		INITIALISE END@MOTOR\n");
		#endif
		//再呼び出し
		setMotorPower(ch,power);
	}
	return ret;
}
/**
 * @brief Motor機能を停止する
 * @method stopMotorFunc
 * @param{none}none 
 */
int stopMotorFunc(){
    unsigned char Buf[4];
    int ret;
	
	Buf[1] = CH_A | CH_B | CH_C | CH_D;
	
	//一度モータに0をセットする
	Buf[0] = opOUTPUT_STOP;
	setMotorPower(Buf[1],0);
	
	//モータを停止する処理を走らせる
	ret = write(pwmfp,Buf,2);
	if(ret == -1){
		return FALSE;
	}

	Buf[0] = opPROGRAM_STOP;
	ret = write(pwmfp,Buf,1);
	if(ret == -1){
		return FALSE;
	}
	
	close(pwmfp);
	
	return ret;
}

//--------------------------------UI（LED,Key）-----------------------------------------
/**
 * @brief UI関連(KEY、LED)を初期化する
 * @method getKeySensor
 * @param{none} none
 */
int initializeUI(){
	static int initialize = FALSE;
	if(!initialize){
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@UI\n");
		#endif
		uifp = open("/dev/lms_ui",O_RDWR);
        if (uifp < 0) {
			#ifdef DEBUG_EV3MODULE
			printf("Cannot open /dev/lms_ui\n");
			#endif
			exit(-1);
		}
        // 共有メモリをmmap()によりマッピングします
        keyPt = (KEYBUF *)mmap(0, sizeof(KEYBUF),
                    PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, uifp, 0);
        if (keyPt == MAP_FAILED) {
			#ifdef DEBUG_EV3MODULE
			printf("mmap failed\n");
			#endif
			exit(-1);
		}
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE END  @UI\n");
		#endif
	}
	return TRUE;
}
/**
 * @brief keySensorの値を取得する
 * @method getKeySensor
 * @param{int*} key[6]
 */
int getKeySensor(int *key){
	int i;
	static int initialize = FALSE;
	
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("			READING START@KEY\n");
		printf("			");
		#endif
		for(i=0;i<6;i++){
			key[i] = (int)((*keyPt).Pressed[i]);
			#ifdef DEBUG_EV3MODULE
			printf("%d |",key[i]);
			#endif
		}
		#ifdef DEBUG_EV3MODULE
		printf("\n");
		printf("			READING END  @KEY\n");
		#endif
	}
	else{
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@KEY\n");
		#endif
		initializeUI();
        initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE END  @KEY\n");
		#endif
		getKeySensor(key);
	}
	return TRUE;
}
/**
 * @brief keySensorの値を取得する
 * @method getKeySensor
 * @param{int*} key[6]
 */
int setLED(unsigned char color){
    unsigned char Buf[2];
    int ret;

	static int initialize = FALSE;
	
	if(initialize){
		#ifdef DEBUG_EV3MODULE
		printf("			SET START@LED\n");
		#endif
        Buf[0] = color;
        Buf[1] = 0;
        ret = write(uifp, Buf, 2);
		#ifdef DEBUG_EV3MODULE
		printf("			SET END  @LED\n");
		#endif
	}
	else{
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@LED\n");
		#endif
		initializeUI();
		initialize = TRUE;
		#ifdef DEBUG_EV3MODULE
		printf("			INITIALISE START@LED\n");
		#endif
		setLED(color);
	}
	return ret;
}
/**
 * @brief UI(key,LED)を終了する
 * @method closeUI
 * @param{none} none
 */
int closeUI(){
    munmap(keyPt, sizeof(KEYBUF));
    close(uifp);
    return TRUE;
}

