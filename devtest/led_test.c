/********************************************************
@function:  对GPIO操作
@author:    caoyang
@date:       2017.10.27
@blog:       https://cy-hello.github.io/
*********************************************************/

#include <pthread.h>
#include <unistd.h>
#include "dev_so.h"


/********用来定义led对应的GPIO的编号和状态************/

/*由于qa701-00的LAN口必须是通过回环测试状态下才能点亮*/
#define LAN_ON(N)           "ssdk_sh debug phy set " #N " 29 0xb",  \
							 "ssdk_sh debug phy set " #N " 30 0x3c80",  \
							 "ssdk_sh debug phy set " #N " 29 0x11",  \
							 "ssdk_sh debug phy set " #N " 30 0x7553",  \
							 "ssdk_sh debug phy set " #N " 0 0x8140",  \
							 "ssdk_sh debug phy set " #N " 0 0x140"
							 
#define LAN_OFF(N)          "ssdk_sh port poweroff set "#N 

#define LAN1_ON             LAN_ON(0)
#define LAN1_OFF            LAN_OFF(1)

#define LAN2_ON             LAN_ON(1)
#define LAN2_OFF            LAN_OFF(2)

#define LAN3_ON             LAN_ON(2)
#define LAN3_OFF            LAN_OFF(3)

#define LAN4_ON             LAN_ON(3)
#define LAN4_OFF            LAN_OFF(4)

#define LED40_ON            "gpio 40 func 0","gpio 40 out 1"//预留运行LED#1
#define LED40_OFF           "gpio 40 func 0","gpio 40 out 0"

#define LED42_ON            "gpio 42 out 1"//预留运行LED#3
#define LED42_OFF           "gpio 42 out 0"

#define LED48_ON            "gpio 48 out 1"//system运行灯
#define LED48_OFF           "gpio 48 out 0"							 


#define LED_CMD	             LED40_ON,LED42_ON,LED48_ON,   \
							 LED48_OFF,LED40_OFF,LED42_OFF,\
							 LAN1_ON,LAN1_OFF,LAN2_ON,LAN2_OFF,\
							 LAN3_ON,LAN3_OFF,LAN4_ON,LAN4_OFF
							 //LAN_ON(0),LAN_OFF(1),LAN_ON(1),LAN_OFF(2)
							 //LAN_ON(2),LAN_OFF(3),LAN_ON(3),LAN_OFF(4)
#if 0
#define CHANGE_TIMES	3
#define LED_COLORFUL_CMD   LED48_ON,LED42_ON,LED40_ON,     \
							 LED40_OFF,LED42_OFF,LED48_OFF,  \
							 LED40_ON,LED42_ON,LED48_ON,\
							 LAN1_ON,LAN2_ON,LAN3_ON,LAN4_ON
#endif
/*****************************************************************/

extern DEV_TEST_GLOBAL_DATA_T stGlobalData;
COMMON_ERROR_ENUM led_test(DEV_TEST_INFO_T *pstDevTestInfo)
{	
	if(NULL == pstDevTestInfo)
    {
    	debug_msg("[%s][%d][Show Info] led_test is error", __func__, __LINE__);
		return CommonError_NullPointer;
    }
	debug_msg("[%s][%d][Show Info] 00000", __func__, __LINE__);
	
	char *apcCtrlLedCmdList[] = {LED_CMD};

	int iLoop ,iCmdNum;

	iCmdNum = sizeof(apcCtrlLedCmdList)/sizeof(int *)

	//COMMON_ERROR_ENUM enComRet;

	for(iLoop=0; iLoop < iCmdNum ; iLoop++)
	{
		SystemCall(apcCtrlLedCmdList[iLoop]);
		debug_msg("[%s][%d][Show Info] 11111:%s", __func__, __LINE__,apcCtrlLedCmdList[iLoop]);
	}	

#if 0	
	int times = CHANGE_TIMES;
	for(;times > 0; times--)
	{
		sleep(1);
		char *apcCtrlLedCmdList[LED_COLORFUL_CMD_NUM] = {LED_COLORFUL_CMD};
		for(iLoop=0; iLoop < iCmdNum; iLoop++)
		{	
			debug_msg("[%s][%d][Show Info] 22222", __func__, __LINE__);
			if((LED_COLORFUL_CMD_NUM/2) == iLoop)
			{
				sleep(1);				
			}
			SystemCall(apcCtrlLedCmdList[iLoop]);
			debug_msg("[%s][%d][Show Info] SystemCall: %s\n", __func__, __LINE__, apcCtrlLedCmdList[iLoop]);			
		}
	}
#endif
    return CommonError_OK;
}

