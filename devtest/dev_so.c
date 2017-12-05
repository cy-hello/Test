#include "dev_so.h"

#define DEVTEST_LTESO_VER "1.0.0"

extern int g_iDebugMode;
extern char acTmpProgList[128];

static DEV_TEST_DATA_CMD_T astDataCmd[] = {
								                {"usb_emmc_test", usb_emmc_test, "", ""},
								                //{"sd_test", sd_test, "dev_sd_test_res", "dev_sd_test_fail_reason"},
								                //{"sim_test", sim_test, "dev_sim_test_res", "dev_sim_test_fail_reason"},
								                //{"lte_test", lte_test, "dev_lte_test_res", "dev_lte_test_fail_reason"},
								                {"led_test",led_test,"",""},
								                //{"simbox_test",simbox_test,"dev_simbox_test_res","dev_simbox_test_fail_reason"},
								                //{"sdbox_test",sdbox_test,"dev_sdbox_test_res","dev_sdbox_test_fail_reason"},
								                //{"gpsbox_test",gpsbox_test,"dev_gpsbox_test_res","dev_gpsbox_test_fail_reason"},
								                //{"setsn_test",setsn_test,"dev_setsn_test_res","dev_setsn_test_fail_reason"},
								                {"phy_test", phy_test, "", ""},
								                //{"lte_reset_test", lte_reset_test, "dev_lte_reset_test_res", "dev_lte_reset_test_fail_reason"},
								                {"button_test", button_test,"",""},
								             };

DEV_TEST_GLOBAL_DATA_T stGlobalData = {0};
//------------------------------------------------------------------------------
void SoHelpInfo()//∞Ô÷˙–≈œ¢
{
    printf("---------------------------------------------------------\n");
    printf("------so version:%s------\n", DEVTEST_LTESO_VER);
    printf("-d: debug mode\n");
    printf("-soInfo: show so information\n");
    printf("support items for '-t' option:\n");
    printf("                                      1. usb_emmc_test\n");
	printf("                                          -us   1   usb_test\n");
	printf("                                                2   emmc_test\n");
	printf("                                                3   usb&emmc_test\n");
    //printf("                                      2. sd_test\n");
    printf("                                      2. led_test\n");
    printf("                                          -ot:LED light time\n");
    printf("                                      3. button_test &\n");
    //printf("                                      5. simbox_test\n");
    //printf("                                          -dt: dial times\n");
   // printf("                                      6. gpsbox_test\n");
	//printf("                                      7. setsn_test\n");
	printf("                                      4. phy_test\n");
	printf("                                          -pn: packet num\n");
    printf("                                          -pl: packet length\n");
    printf("---------------------------------------------------------\n");
}
//------------------------------------------------------------------------------
COMMON_ERROR_ENUM SoParseCmdLine(int argc, char **argv, DEV_TEST_INFO_T *pstDevTestInfo)
{
	int iLoop = 0;
	for(iLoop = 1; iLoop < argc; iLoop++)
	{
		if(0 == strcmp(argv[iLoop], "-soInfo"))
		{
			SoHelpInfo();
		}
		else if(0 == strcmp(argv[iLoop], "-soV"))
		{
			printf("devtest_lte.so version:%s\n", DEVTEST_LTESO_VER);
			exit(0);
		}
		else if(0 == strcmp(argv[iLoop], "-t"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acTestItem, "%s", argv[iLoop]);
		}
/*		else if(0 == strcmp(argv[iLoop], "-dn"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acDevNode, "/dev/%s", argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-l"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acLicence, "%s", argv[iLoop]);
		} */ 
		else if(0 == strcmp(argv[iLoop],"-ot"))
		{
			iLoop++;
			pstDevTestInfo->iLedOnTime = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-us"))
		{
			iLoop++;
			pstDevTestInfo->iUsbAndSdTest = atoi(argv[iLoop]);
			if(pstDevTestInfo->iUsbAndSdTest <= 0 || pstDevTestInfo->iUsbAndSdTest > 3)
				return CommonError_IllegalParameter;
		}
/*		else if(0 == strcmp(argv[iLoop],"-usb"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acUsbNode, "%s", argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop],"-sd"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acSdNode, "%s", argv[iLoop]);
		} */

		/*
		else if(0 == strcmp(argv[iLoop],"-pn"))
		{
			iLoop++;
			pstDevTestInfo->iPacketNum = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop],"-pl"))
		{
			iLoop++;
			pstDevTestInfo->iPacketLen = atoi(argv[iLoop]);
		}
		*/
		else if(0 == strcmp(argv[iLoop],"-s"))
		{	
			iLoop++;
			continue;
		}
		else if(0 == strcmp(argv[iLoop], "-d"))
		{
			g_iDebugMode = 1;
		}
		else if(0 == strcmp(argv[iLoop], "-tmp"))
		{
			iLoop++;
			sprintf(acTmpProgList, "%s", argv[iLoop]);
		}
		/*
		else if(0 == strcmp(argv[iLoop], "-ph"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acBoxSimTestPingHost,"%s",argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-ls"))
		{
			iLoop++;
			pstDevTestInfo->iBoxSimTestLossStandard = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-spn"))
		{
			iLoop++;
			pstDevTestInfo->iBoxSimTestPacketNum = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-spl"))
		{
			iLoop++;
			pstDevTestInfo->iBoxSimTestPacketLen = atoi(argv[iLoop]);
		}
		*/
		else if(0 == strcmp(argv[iLoop], "-da"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acBoxSimTestDialApn, "%s", argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-dt"))
		{
			iLoop++;
			pstDevTestInfo->iBoxSimTestDialTimes = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-dst"))
		{
			iLoop++;
			pstDevTestInfo->iBoxSimTestSleepTime = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-ic"))
		{
			iLoop++;
			pstDevTestInfo->iCheckIccidSwitch = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-is"))
		{
			iLoop++;
			pstDevTestInfo->iCheckSimStateSwitch = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-um"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acUserInputMac, "%s", argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-cs"))
		{
			iLoop++;
			sprintf(pstDevTestInfo->acCustomerSn, "%s", argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop], "-ms"))
		{
			iLoop++;
			pstDevTestInfo->iMacStartAddr = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop],"-pn"))
		{
			iLoop++;
			pstDevTestInfo->iPacketNum = atoi(argv[iLoop]);
		}
		else if(0 == strcmp(argv[iLoop],"-pl"))
		{
			iLoop++;
			pstDevTestInfo->iPacketLen = atoi(argv[iLoop]);
		}
		/*
		else if(0 == strcmp(argv[iLoop], "-gct"))
		{
			iLoop++;
			pstDevTestInfo->iBoxGpsTestGetComTimeout = atoi(argv[iLoop]);
			debug_msg("[%s][%d][Show Info] gps identify com info timeout : %d", __func__, __LINE__, pstDevTestInfo->iBoxGpsTestGetComTimeout);
		}
		else if(0 == strcmp(argv[iLoop], "-grt"))
		{
			iLoop++;
			pstDevTestInfo->iBoxGpsTestReadDataTimeout = atoi(argv[iLoop]);
			debug_msg("[%s][%d][Show Info] gps read data timeout : %d", __func__, __LINE__, pstDevTestInfo->iBoxGpsTestReadDataTimeout);
		}
		*/
		else
		{
			stGlobalData.enLastError = LteSoError_UnexpectOption;
			return CommonError_IllegalParameter;
		}
	}
	return CommonError_OK;
}

//------------------------------------------------------------------------------
unsigned int GetVersion(void)
{
	int iVersionSum = 0;
	return iVersionSum;
}
//------------------------------------------------------------------------------
void FillTestResult(DEV_TEST_INFO_T *pstDevTestInfo, char result, char *reason)
{
	debug_msg("[%s][%d][Show Error] I will fill test result", __func__, __LINE__);
	pstDevTestInfo->cTestRes = result;
	sprintf(pstDevTestInfo->acTestFailReason, "%s", reason);
	debug_msg("[%s][%d][Show Error] %s", __func__, __LINE__,reason);
}

//------------------------------------------------------------------------------
int GetLastError(void)
{
	printf("\n");
	switch(stGlobalData.enLastError)
	{
		case LteSoError_OK:
			printf("lte SO execute success");
			break;
			
		case LteSoError_UsbTestFail:
			printf("lte SO usb_test fail");
			break;
			
		case LteSoError_SdTestFail:
			printf("lte SO sd_test fail");
			break;
			
		case LteSoError_LteTestFail:
			printf("lte SO lte_test fail");
			break;
			
		case LteSoError_SimTestFail:
			printf("lte SO sim_test fail");
			break;
		/*	
		case LteSoError_PhyTestFail:
			printf("lte SO phy_test fail");
			break;
		*/	
		case LteSoError_LedTestFail:
			printf("lte SO led_test fail");
			break;
		/*
		case LteSoError_ButtonTestFail:
			printf("lte SO button_test fail");
			break;
		*/
		case LteSoError_UnexpectOption:
			printf("lte SO shell command contains unexpect option");
			break;

		case LteSoError_UnsupportedItem:
			printf("lte SO shell command contains unsupported item after '-t' ");
			break;
		
		case LteSoError_SaveTestResultFail:
			printf("lte SO save test result fail");
			break;
		
		case LteSoError_ReadLteIMEIFail:
			printf("lte SO read lte IMEI fail");
			break;

		case LteSoError_SaveLteIMEIFail:
			printf("lte SO save lte IMEI fail");
			break;

		case LteSoError_ReadLteIccidFail:
			printf("lte SO read lte iccid fail");
			break;

		case LteSoError_SaveLteIccidFail:
			printf("lte SO save lte iccid fail");
			break;

		case LteSoError_SaveLte4gRssiFail:
			printf("lte SO save lte 4g rssi fail");
			break;
		
		case LteSoError_BoxSimTestFail:
			printf("lte SO simbox_test fail");
			break;
		
		case LteSoError_BoxSdTestFail:
			printf("lte SO sdbox_test fail");
			break;
		
		case LteSoError_BoxGpsTestFail:
			printf("lte SO gpsbox_test fail");
			break;
		
		case LteSoError_SetSnTestFail:
			printf("lte SO setsn_test fail");
			break;
		
		default:
			break;
	}
	printf("\n");
	return 0;
}

//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	int iLoop= 0;
	COMMON_ERROR_ENUM enComRet;
//	LTE_SO_ERROR_ENUM enSoRet;
	DEV_TEST_INFO_T stDevTestInfo;

	memset(&stDevTestInfo, 0, sizeof(stDevTestInfo));
	
	int TestItem_Count = sizeof(astDataCmd) / sizeof(astDataCmd[0]);
	
	enComRet = SoParseCmdLine(argc, argv, &stDevTestInfo);
	if (CommonError_OK != enComRet)
	{
		SoHelpInfo();
		return enComRet;
	}
	if(0 == strlen(stDevTestInfo.acTestItem))
	{
		debug_msg("[%s][%d][Show Error] I did not get any test item name!", __func__, __LINE__);
		SoHelpInfo();
		return CommonError_IllegalParameter;
	}
	
	debug_msg("[%s][%d][Show Info] I get test item name: %s!", __func__, __LINE__, stDevTestInfo.acTestItem);

	for(iLoop=0; iLoop < TestItem_Count; iLoop++)
	{
		if(0 == strcmp(stDevTestInfo.acTestItem, astDataCmd[iLoop].acTestName))
		{
			debug_msg("[%s][%d][Show Info] I will execute: %s!", __func__, __LINE__, astDataCmd[iLoop].acTestName);
			
			enComRet = astDataCmd[iLoop].TestFunction(&stDevTestInfo);
			
			if( CommonError_OK == enComRet || CommonError_SoPrivateError == enComRet )
			{
				if(DEV_TEST_OK == stDevTestInfo.cTestRes)
				{
					if ( 0 < strlen(astDataCmd[iLoop].acResultVar) )
					{
					//	enComRet = NvramSet(astDataCmd[iLoop].acResultVar, "pass");
						if ( CommonError_OK != NvramSet(astDataCmd[iLoop].acResultVar, "pass", NVRAM_NO_COMMIT) )
						{
							stGlobalData.enLastError = LteSoError_SaveTestResultFail;
							return CommonError_SoPrivateError;
						}
					}

					if ( 0 < strlen(astDataCmd[iLoop].acReasonVar) )
					{
					//	enComRet = NvramUnset(astDataCmd[iLoop].acReasonVar);
						if ( CommonError_OK != NvramUnset(astDataCmd[iLoop].acReasonVar, NVRAM_NEED_COMMIT) )
						{
							stGlobalData.enLastError = LteSoError_SaveTestResultFail;
							return CommonError_SoPrivateError;
						}
					}
				}

				else if(DEV_TEST_FAIL == stDevTestInfo.cTestRes)
				{
					if ( 0 < strlen(astDataCmd[iLoop].acResultVar) )
					{
					//	enComRet = NvramSet(astDataCmd[iLoop].acResultVar, "fail");
						if ( CommonError_OK != NvramSet(astDataCmd[iLoop].acResultVar, "fail", NVRAM_NO_COMMIT) )
						{
							stGlobalData.enLastError = LteSoError_SaveTestResultFail;
							return CommonError_SoPrivateError;
						}
					}

					if ( 0 < strlen(astDataCmd[iLoop].acReasonVar) )
					{
					//	enComRet = NvramSet(astDataCmd[iLoop].acReasonVar, stDevTestInfo.acTestFailReason);
						if( CommonError_OK != NvramSet(astDataCmd[iLoop].acReasonVar, stDevTestInfo.acTestFailReason, NVRAM_NEED_COMMIT) )
						{
							stGlobalData.enLastError = LteSoError_SaveTestResultFail;
							return CommonError_SoPrivateError;
						}
					}
				}
			}
			break;
		}
	}
	
	if(TestItem_Count == iLoop)
	{
		debug_msg("[%s][%d][Show Error] This SO does not support '%s' !", __func__, __LINE__, stDevTestInfo.acTestItem);
		SoHelpInfo();
		stGlobalData.enLastError = LteSoError_UnsupportedItem;
		return CommonError_IllegalParameter;
	}
	
	printf("\nJobLoader_done\n");
	return enComRet;
}
