#include "dev_so.h"


extern DEV_TEST_GLOBAL_DATA_T stGlobalData;

COMMON_ERROR_ENUM usb_emmc_nvramset(int iNvramSign)
{
	char acBuf[128] = "";
	COMMON_ERROR_ENUM enComRet;
	debug_msg("[%s][%d][Show Info] iNvramSign:%d", __func__, __LINE__, (iNvramSign & 1));
	//debug_msg("[%s][%d][Show Info] iNvramSign:%d", __func__, __LINE__, ((iNvramSign >> 1) & 1));

	if(iNvramSign & 1)
	{
		//sprintf(acBuf, "usb_sd_test_sd_res");
		sprintf(acBuf, "usb_emmc_test_emmc_res");
		enComRet = NvramSet(acBuf, "pass", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] emmc pass", __func__, __LINE__);//sd ->emmc
	}
	else
	{
		memset(acBuf, 0, sizeof(acBuf));
		//sprintf(acBuf, "usb_sd_test_sd_res");
		sprintf(acBuf, "usb_emmc_test_emmc_res");
		enComRet = NvramSet(acBuf, "fail", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] emmc fail:", __func__, __LINE__);//sd ->emmc
	}
/*
	if((iNvramSign >> 1) & 1)
	{
		memset(acBuf, 0, sizeof(acBuf));
		sprintf(acBuf, "usb_emmc_test_usb_res");
		enComRet = NvramSet(acBuf, "pass", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] usb pass:", __func__, __LINE__);
	}
	else
	{
		memset(acBuf, 0, sizeof(acBuf));
		sprintf(acBuf, "usb_emmc_test_usb_res");
		enComRet = NvramSet(acBuf, "fail", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] usb fail:", __func__, __LINE__);
	}
*/
	
	if(CommonError_OK != enComRet)
	{
		return enComRet;
	}
	else
		return CommonError_OK;
}

COMMON_ERROR_ENUM usb_nvramset(int iNvramSign)//add
{
	char acBuf[128] = "";
	COMMON_ERROR_ENUM enComRet;
	//debug_msg("[%s][%d][Show Info] iNvramSign:%d", __func__, __LINE__, (iNvramSign & 1));
	debug_msg("[%s][%d][Show Info] iNvramSign:%d", __func__, __LINE__, ((iNvramSign >> 1) & 1));
	if((iNvramSign >> 1) & 1)
	{
		memset(acBuf, 0, sizeof(acBuf));
		//sprintf(acBuf, "usb_sd_test_usb_res");
		sprintf(acBuf, "usb_emmc_test_usb_res");
		enComRet = NvramSet(acBuf, "pass", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] usb pass:", __func__, __LINE__);
	}
	else
	{
		memset(acBuf, 0, sizeof(acBuf));
		//sprintf(acBuf, "usb_sd_test_usb_res");
		sprintf(acBuf, "usb_emmc_test_usb_res");
		enComRet = NvramSet(acBuf, "fail", NVRAM_NO_COMMIT);
		debug_msg("[%s][%d][Show Info] usb fail:", __func__, __LINE__);
	}
}

void next_str(char **str)
{
	char *strend=*str;
	while(!(isspace(*strend++)));
	while(isspace(*strend++));
	*str = strend-1;
	while(!(isspace(*strend++)));
	strend--;
	*strend = '\0';
}


COMMON_ERROR_ENUM usb_emmc_test(DEV_TEST_INFO_T *pstDevTestInfo)
{
	if(NULL == pstDevTestInfo)
    {
	  return CommonError_NullPointer;
    }
	
	/*FILE *pstFp = NULL;
	FILE *pfStringOfPartitions=NULL;
    COMMON_ERROR_ENUM enComRet;
    
	char acPartitionStr[64];
    char acMountDev[64];
    char acUmountDev[64];
    char acFileStr[128];
	char acSDname[64];
    char acNodeStr[2][32];
    int  iMountFlag = 0;
	int  iNvramSign = 0;//第2位usb，第1位sd
	char *pcFileStr;
	int  iUsbFlag = 0;
	int  iEmmcFlag = 0;
	
	
	memset(acUmountDev, 0 ,sizeof(acUmountDev));
	memset(acFileStr, 0 ,sizeof(acFileStr));
	memset(acSDname, 0 ,sizeof(acSDname));
	memset(acPartitionStr, 0 ,sizeof(acPartitionStr));
	
    pstFp = popen("dmesg", "r");
  	if(pstFp == NULL)
	{
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "popen_/tmp/d_mesg_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }
	memset(acFileStr, 0 ,sizeof(acFileStr));
	while(fgets(acFileStr, 128, pstFp))
    {
    	debug_msg("[%s][%d][Show Info] next line", __func__, __LINE__);
		if(0 == strlen(acFileStr))
		{
			fclose(pstFp);
			FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "read_/tmp/nodelist_failed");
			return CommonError_SoPrivateError;
		}
		pcFileStr = strstr(acFileStr, "Ultra");
		if(NULL != pcFileStr)
		{
			DELETE_NEXT_LINE(acFileStr);
			debug_msg("[%s][%d][Show Info] I will split Str:%s", __func__, __LINE__, acFileStr);
			next_str(&pcFileStr);
			debug_msg("[%s][%d][Show Info] I will split Str:%s", __func__, __LINE__, pcFileStr);
			debug_msg("[%s][%d][Show Info] %d", __func__, __LINE__, strcmp(pcFileStr,"HS-COMBO"));
			if(0 == strcmp(pcFileStr,"HS-COMBO"))
			{
				memset(acFileStr, 0 ,sizeof(acFileStr));
				fgets(acFileStr, 128, pstFp);
				debug_msg("[%s][%d][Show Info] I will split Str:%s", __func__, __LINE__, acFileStr);
				pcFileStr = strstr(acFileStr, "sd");
				pcFileStr += 2;
				if(strstr(pcFileStr, "sd"))
				{
					DELETE_NEXT_LINE(pcFileStr);
					debug_msg("[%s][%d][Show Info] I will split Str:%s", __func__, __LINE__, pcFileStr);
					if(0 == Split_Str(pcFileStr, acSDname, 's', ']'))
					{
						debug_msg("[%s][%d][Show Info] I will split Str:%d", __func__, __LINE__, strcmp(acSDname,acNodeStr[0]));
					}
				}
			}
		}
	}	
	
	pclose(pstFp);
	
    enComRet = SystemCall("mkdir -p /tmp/usb");
    if (CommonError_OK != enComRet)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/usb_failed");
		usb_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }	
	
/*	enComRet = SystemCall("mkdir -p /tmp/emmc1");
    if (CommonError_OK != enComRet)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/emmc_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }

	enComRet = SystemCall("mkdir -p /tmp/emmc2");
    if (CommonError_OK != enComRet)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/emmc_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }
	
	enComRet = SystemCall("mkdir -p /tmp/emmc3");
	  if (CommonError_OK != enComRet)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/emmc_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }
	
	enComRet = SystemCall("mkdir -p /tmp/emmc4");
	  if (CommonError_OK != enComRet)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/emmc_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }*/



	
	/*pstFp = popen("cat /proc/partitions", "r");

    if(pstFp == NULL)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "popen_/proc/partitions_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }
	
	pfStringOfPartitions = fopen("/tmp/fdisk_auto.sh","r");
	
	  if(pfStringOfPartitions == NULL)
    {
		FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "open_/tmp/fdisk_auto.sh_failed");
		usb_emmc_nvramset(iNvramSign);
		return CommonError_SoPrivateError;
    }
	
	memset(acNodeStr, 0, sizeof(acNodeStr));
	memset(acFileStr, 0 ,sizeof(acFileStr));
	
    while(fgets(acFileStr, 128, pstFp))
    {
    	debug_msg("[%s][%d][Show Info] next line", __func__, __LINE__);
		if(0 == strlen(acFileStr))
		{
		//	fclose(pstFp);
			FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "read_/proc/partitions_failed");
			usb_emmc_nvramset(iNvramSign);
			pclose(pstFp);
			fclose(pfStringOfPartitions);
			return CommonError_SoPrivateError;
		}
		
		if(strstr(acFileStr, "sd"))
		{
			DELETE_NEXT_LINE(acFileStr);
			debug_msg("[%s][%d][Show Info] I will split Str:%s", __func__, __LINE__, acFileStr);
			if(0 == Split_Str(acFileStr, acNodeStr[iMountFlag], 's', '\0'))
			{
				if (strlen(acNodeStr[iMountFlag]) != 3)
				{
					continue;					
				}
				debug_msg("[%s][%d][Show Info] Node:%s", __func__, __LINE__, acNodeStr[iMountFlag]);	
				memset(acMountDev, 0 ,sizeof(acMountDev));
				if(0==strcmp(acSDname,acNodeStr[iMountFlag]))
				{
					if((2 == pstDevTestInfo->iUsbAndSdTest) || (3 == pstDevTestInfo->iUsbAndSdTest))
					{
						debug_msg("[%s][%d][Show Info] I find EMMC in %s", __func__, __LINE__, acNodeStr[iMountFlag]);
						if(fgets(acPartitionStr, 64, pfStringOfPartitions) <= 0)	//if(-1 == read(pfStringOfPartitions,acPartitionStr,64))
						{
							FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "/tmp/fdisk_auto.sh_is_ERROR");
							usb_emmc_nvramset(iNvramSign);
							return CommonError_SoPrivateError;
						}
						
						debug_msg("[%s][%d][Show Info] I  %s", __func__, __LINE__,acPartitionStr);
						
						sprintf(acMountDev, "/tmp/fdisk_auto /dev/%s %s",acNodeStr[iMountFlag],acPartitionStr);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
					
						enComRet = SystemCall(acMountDev);
						if(CommonError_OK != enComRet)
						{
							FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "partition_failed");
							usb_emmc_nvramset(iNvramSign);
							pclose(pstFp);
							return enComRet;
						}
						memset(acMountDev, 0 ,sizeof(acMountDev));
							
						
						/*
						sprintf(acMountDev, "mount -t ext4 -rw /dev/%s1 /tmp/emmc1", acNodeStr[iMountFlag]);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
						enComRet = SystemCall(acMountDev);
						memset(acMountDev, 0 ,sizeof(acMountDev));
					
						sprintf(acMountDev, "mount -t ext4 -rw /dev/%s2 /tmp/emmc2", acNodeStr[iMountFlag]);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
						
						enComRet = SystemCall(acMountDev);
						memset(acMountDev, 0 ,sizeof(acMountDev));
					
						sprintf(acMountDev, "mount -t ext4 -rw /dev/%s3 /tmp/emmc3", acNodeStr[iMountFlag]);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
						enComRet = SystemCall(acMountDev);
						memset(acMountDev, 0 ,sizeof(acMountDev));
						
						sprintf(acMountDev, "mount -t ext4 -rw /dev/%s4 /tmp/emmc4", acNodeStr[iMountFlag]);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
						enComRet = SystemCall(acMountDev);
						memset(acMountDev, 0 ,sizeof(acMountDev));
						*/


						/*int iEmmcNum = 1;
						int iPartitionNum = atoi(acPartitionStr);
						
						debug_msg("[%s][%d][Show Info] iPartitionNum:%d", __func__, __LINE__, iPartitionNum);
						//debug_msg("[%s][%d][Show Info] 222", __func__, __LINE__);
						for(iEmmcNum;iEmmcNum <= iPartitionNum;iEmmcNum++ )
						{	
							sprintf(acFileStr, "mkdir -p /tmp/emmc%d",iEmmcNum);
							enComRet = SystemCall(acFileStr);
							
						    if (CommonError_OK != enComRet)
						    {
								FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mkdir_/tmp/emmc_failed");
								usb_emmc_nvramset(iNvramSign);
								return CommonError_SoPrivateError;
						    }
							
							
							sprintf(acMountDev, "mount -t ext4 -rw /dev/%s%d /tmp/emmc%d", acNodeStr[iMountFlag],iEmmcNum,iEmmcNum);
							debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
							enComRet = SystemCall(acMountDev);
							memset(acMountDev, 0 ,sizeof(acMountDev));
							
							if(CommonError_OK != enComRet)
							{
								FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mount_emmc1_failed");
								usb_emmc_nvramset(iNvramSign);
								pclose(pstFp);
								return enComRet;
							}
						}
						
						iNvramSign |= 1;
						iEmmcFlag++;
					}
					else
						debug_msg("[%s][%d][Show Info] [no emmc] or must [usb_emmc_test -us 2] or [usb_emmc_test -us 3]", __func__, __LINE__);
				}
				else
				{
					if((1 == pstDevTestInfo->iUsbAndSdTest) || (3 == pstDevTestInfo->iUsbAndSdTest))
					{
						sprintf(acMountDev, "mount -t vfat -rw /dev/%s /tmp/usb", acNodeStr[iMountFlag]);
						debug_msg("[%s][%d][Show Info] Mount:%s", __func__, __LINE__, acMountDev);
						enComRet = SystemCall(acMountDev);
						
						if(CommonError_OK == enComRet)
						{
							debug_msg("[%s][%d][Show Info] I find USB in %s", __func__, __LINE__, acNodeStr[iMountFlag]);
#ifdef GET_USB_SIZE
							memset(acCmd, 0, sizeof(acCmd));
							sprintf(acCmd,"df -h /dev/%s | grep \"%s\" | awk '{print $2}' > /tmp/usb_size_file",acNodeStr[iMountFlag],acNodeStr[iMountFlag]);
							system(acCmd);
#endif
							//sprintf(acUmountDev, "umount /dev/%s", acNodeStr[iMountFlag]);
							//debug_msg("[%s][%d][Show Info] uMount:%s", __func__, __LINE__, acUmountDev);
							//sleep(1);
							//SystemCall(acUmountDev);
							iNvramSign |= 2;
						}
						else
						{
							FillTestResult(pstDevTestInfo, DEV_TEST_FAIL, "mount_usb_failed");
							usb_nvramset(iNvramSign);//usb_sd_nvramset(iNvramSign)
							pclose(pstFp);
							return enComRet;
						}

						iUsbFlag++;
					}
					else
						debug_msg("[%s][%d][Show Info] [no usb] or [no usb_emmc_test -us 1]", __func__, __LINE__);
				}

				iMountFlag++;

				if((1 == pstDevTestInfo->iUsbAndSdTest))//1->  usb
				{
					if(1 == iUsbFlag)
						break;
				}
			    else if((2 == pstDevTestInfo->iUsbAndSdTest))//2->  emmc
				{
					if(1 == iEmmcFlag)
						break;
				}
				else if((3 == pstDevTestInfo->iUsbAndSdTest))//3-> usb and emmc
				{
					if((1 == iEmmcFlag) && (1 == iUsbFlag))
						break;
				}
			}
		}

		memset(acFileStr, 0 ,sizeof(acFileStr));
		memset(acPartitionStr, 0 ,sizeof(acPartitionStr));
    }
    pclose(pstFp);
	pclose(pfStringOfPartitions);
	
	debug_msg("[%s][%d][Show Info] iNvramSign:%d", __func__, __LINE__, iNvramSign);
	switch(pstDevTestInfo->iUsbAndSdTest){
		case 1:
			usb_nvramset(iNvramSign);//show usb_res
			break;
		case 2:
			usb_emmc_nvramset(iNvramSign);//show emmc_res
			break;
		case 3:
			usb_emmc_nvramset(iNvramSign);//show usb_emmc_res
			usb_nvramset(iNvramSign);
			break;
		default:
			break;
	}
*/
	return CommonError_OK;
}
					
