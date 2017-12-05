/******************************************************************************

                  ��Ȩ���� (C), 2001-2017, �Ϻ�徴�ͨ�Źɷ����޹�˾

 ******************************************************************************
  �� �� ��   : Dev_phy_test.c
  �� �� ��   : ����
  ��    ��   : CaoYang
  ��������   : 2017��11��14�� ���ڶ�
  ����޸�   :
  ��������   : ͨ��4���ػ�ͷ ��ʽ,  �������ڻػ�����
               ˵��: һ��4������,ÿ���������в���
  �����б�   :
  
  �޸���ʷ   :
  1.��    ��   : 2017��11��14�� ���ڶ�
    ��    ��   : CaoYang
    �޸�����   : �����ļ�

******************************************************************************/


//------------------------------------------------------------------------------
#include "dev_so.h"

//------------------------------------------------------------------------------
//�汾��Ϣ
#define DEV_PHY_TEST_VER "dev_phy_test_v1.0"
#define DEFAULT_PACKET_NUM 3000
#define DEFAULT_PACKET_LEN  10

//------------------------------------------------------------------------------
//���ڶ���
#define PORT_MAX_NUM 4
#define LAN1 "LAN1"
#define LAN2 "LAN2"
#define LAN3 "LAN3"
#define LAN4 "LAN4"
//����һ�׷�������
#define DOWNPORT "DOWNPORT"

#define PHY_FUNC(flag) (flag?("phy"):("phybox"))

#define LAN1_RES(flag) (flag?("phy_test_lan1_res"):("phybox_test_lan1_res"))
#define LAN1_REA(flag) (flag?("phy_test_lan1_fail_reason"):("phybox_test_lan1_fail_reason"))

#define LAN2_RES(flag) (flag?("phy_test_lan2_res"):("phybox_test_lan2_res"))
#define LAN2_REA(flag) (flag?("phy_test_lan2_fail_reason"):("phybox_test_lan2_fail_reason"))

#define LAN3_RES(flag) (flag?("phy_test_lan3_res"):("phybox_test_lan3_res"))
#define LAN3_REA(flag) (flag?("phy_test_lan3_fail_reason"):("phybox_test_lan3_fail_reason"))

#define LAN4_RES(flag) (flag?("phy_test_lan4_res"):("phybox_test_lan4_res"))
#define LAN4_REA(flag) (flag?("phy_test_lan4_fail_reason"):("phybox_test_lan4_fail_reason"))

#define DOWNPORT_RES(flag) (flag?("phy_test_downport_res"):("phybox_test_downport_res"))
#define DOWNPORT_REA(flag) (flag?("phy_test_downport_fail_reason"):("phybox_test_downport_fail_reason"))

#define WAN_RES(flag) (flag?("phy_test_wan_res"):("phybox_test_wan_res"))
#define WAN_REA(flag) (flag?("phy_test_wan_fail_reason"):("phybox_test_wan_fail_reason"))



//#define WAN "WAN"
//------------------------------------------------------------------------------

/*****************************************************************************
 �� �� ��  : lan_looptest_configuration
 ��������  : ����LAN�ڻػ�����ģʽ
 �������  :int  LAN_NUM
 �������  : ��
 �� �� ֵ  : CommonError_OK
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��11��14�� ���ڶ�
    ��    ��   : Cao Yang
    �޸�����   : �����ɺ���

*****************************************************************************/

COMMON_ERROR_ENUM lan_looptest_configuration(int LAN_NUM)
{
	COMMON_ERROR_ENUM enComRet;
	char acLooptestCmd[64];

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 29 0xb",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}						 

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 30 0x3c80",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 29 0x11",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 30 0x7553",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 0 0x8140",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}

	memset(acLooptestCmd, 0, sizeof(acLooptestCmd));
	sprintf(acLooptestCmd,"ssdk_sh debug phy set %d 0 0x140",LAN_NUM);
	debug_msg("[%s][%d][Show Info] looptest configuration: %s", __func__, __LINE__, acLooptestCmd);
	enComRet = SystemCall(acLooptestCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}
	
	return CommonError_OK;
}


/*****************************************************************************
 �� �� ��  : phy_test
 ��������  :  LAN��������лػ�����
 �������  : DEV_TEST_INFO_T *pstDevTestInfo
 �������  : ��
 �� �� ֵ  : CommonError_OK
 ���ú���  : SystemCall()  �� NvramUnset() ��
 			     lan_looptest_configuration()
 ��������  : 
 �޸���ʷ      :
  1.��    ��   : 2017��11��14�� ���ڶ�
    ��    ��   : Cao Yang
    �޸�����   : �����ɺ���

*****************************************************************************/
COMMON_ERROR_ENUM phy_test(DEV_TEST_INFO_T *pstDevTestInfo)    //���ڲ���
{
    if(NULL == pstDevTestInfo)
    {
		return CommonError_NullPointer;
    }
	pstDevTestInfo->iPhyFlag=1;
    switch(pstDevTestInfo->iPhyFlag)
    {
    		//0:phybox_test   1:phy_test
		case 0:
			debug_msg("[%s][%d][Show Error] phybox_test with PhyFlag : %d\n", __func__, __LINE__,pstDevTestInfo->iPhyFlag);
			break;
		case 1:
			debug_msg("[%s][%d][Show Error] phy_test with PhyFlag : %d\n", __func__, __LINE__,pstDevTestInfo->iPhyFlag);
			break;
		default:
			pstDevTestInfo->iPhyFlag = 1;
			debug_msg("[%s][%d][Show Error] phy_test with default_PhyFlag : %d\n", __func__, __LINE__,pstDevTestInfo->iPhyFlag);
			break;
    }
	
	
    COMMON_ERROR_ENUM enComRet;
    int iLoop = 0;
	char *apcPhyNvramVar[PORT_MAX_NUM*2] = {0};
	char *apcPortName[PORT_MAX_NUM] = {0};
	//int iPortNum;
	char *apcNvramVar[PORT_MAX_NUM*2] = {
								LAN1_RES(pstDevTestInfo->iPhyFlag),LAN1_REA(pstDevTestInfo->iPhyFlag),
								LAN2_RES(pstDevTestInfo->iPhyFlag),LAN2_REA(pstDevTestInfo->iPhyFlag),
								LAN3_RES(pstDevTestInfo->iPhyFlag),LAN3_REA(pstDevTestInfo->iPhyFlag),
								LAN4_RES(pstDevTestInfo->iPhyFlag),LAN4_REA(pstDevTestInfo->iPhyFlag)
						   };
	memset(apcPhyNvramVar, 0 ,sizeof(apcPhyNvramVar));
	memcpy(apcPhyNvramVar, apcNvramVar, sizeof(apcNvramVar));
	
	char *apcPort[4] = {LAN1, LAN2, LAN3, LAN4};
	memset(apcPortName, 0, sizeof(apcPortName));
	memcpy(apcPortName, apcPort, sizeof(apcPort));


	char acCmd[64] = "";
	memset(acCmd, 0, sizeof(acCmd));
#if 0
	sprintf(acCmd, "%s loopstate %s", PHY_FUNC(pstDevTestInfo->iPhyFlag), apcPortName[0]);
	debug_msg("[%s][%d][Show Info] reread: %s", __func__, __LINE__, acCmd);
	enComRet = SystemCall(acCmd);
	if( CommonError_OK != enComRet )
	{
		return enComRet;
	}
#endif

    for(iLoop = 0; iLoop < PORT_MAX_NUM*2; iLoop++)
    {
		enComRet = NvramUnset(apcPhyNvramVar[iLoop],NVRAM_NO_COMMIT);
		if (CommonError_OK != enComRet)
		{
			debug_msg("[%s][%d][Show Error] unset nvram variable of phy_test failed!", __func__, __LINE__);
			return enComRet;
		}
    }
	
	SystemCall(NVRAM_CMD_PREFIX" commit");
	
    if (0 >= pstDevTestInfo->iPacketNum)
    {
		pstDevTestInfo->iPacketNum = DEFAULT_PACKET_NUM;
    }
    if (0 >= pstDevTestInfo->iPacketLen)
    {
		pstDevTestInfo->iPacketLen = DEFAULT_PACKET_LEN;
    }

	//debug_msg("[%s][%d][Show Info] 1111111111111111111", __func__, __LINE__);
	//debug_msg("[%s][%d][Show Info] PacketNum: %d, PacketLen:%d", __func__, __LINE__, pstDevTestInfo->iPacketNum, pstDevTestInfo->iPacketLen);

	for(iLoop=0; iLoop < PORT_MAX_NUM; iLoop++)
    {
		
		if(CommonError_OK !=lan_looptest_configuration(iLoop))//���ûػ�����ģʽ
		{
		 	debug_msg("[%s][%d][Show Error] looptest configuration failed", __func__, __LINE__);
			return enComRet;
		}
		sleep(1);
		/*LAN�ڻػ�����*/
		memset(acCmd, 0, sizeof(acCmd));
		//debug_msg("[%s][%d][Show Info] PortName: %s", __func__, __LINE__, apcPortName[iLoop]);
		sprintf(acCmd, "%s looptest %s %d %d", PHY_FUNC(pstDevTestInfo->iPhyFlag), apcPortName[iLoop], pstDevTestInfo->iPacketNum, pstDevTestInfo->iPacketLen);
		debug_msg("[%s][%d][Show Info] Cmd1: %s", __func__, __LINE__, acCmd);
		enComRet = SystemCall(acCmd);
		if(CommonError_OK != enComRet)
		{
			debug_msg("[%s][%d][Show Info] phy_looptest_LAN%d_error", __func__, __LINE__,iLoop+1);
			return enComRet;
		}

		sleep(1);
		//debug_msg("[%s][%d][Show Info] g222222222222222223", __func__, __LINE__);
		
		/*��ȡ�������*/
		memset(acCmd, 0, sizeof(acCmd));
		sprintf(acCmd, "%s loopstate %s", PHY_FUNC(pstDevTestInfo->iPhyFlag), apcPortName[iLoop]);
		debug_msg("[%s][%d][Show Info] Cmd2: %s", __func__, __LINE__, acCmd);
		enComRet = SystemCall(acCmd);
		if( CommonError_OK != enComRet )
		{
			debug_msg("[%s][%d][Show Info] phy_loopstate_LAN%d_error", __func__, __LINE__,iLoop+1);
			return enComRet;
		}

		//debug_msg("[%s][%d][Show Info] g3333333333333333333333", __func__, __LINE__);

		/*�µ�LAN�ڣ��Ӷ��ر�looptest�ػ�ģʽ*/
		memset(acCmd, 0, sizeof(acCmd));
		sprintf(acCmd, "ssdk_sh port poweroff set %d",iLoop+1 );
		debug_msg("[%s][%d][Show Info] poweroff LAN: %s", __func__, __LINE__, acCmd);
		enComRet = SystemCall(acCmd);
		if( CommonError_OK != enComRet )
		{
			return enComRet;
		}
		//sleep(1);
    }
	
    return CommonError_OK;
}


