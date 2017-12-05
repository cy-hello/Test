#include "dev_so.h"
//===============================================================================

#define BUTTONNUM	1
#define LEVELNUM	18

#define GPIO_TOOL "gpio"

#define BUTTON_RES(x,y) 	\
            sprintf(x, "button_test_""%s""_res", y)
#define BUTTON_REA(x,y)		\
            sprintf(x, "button_test_""%s""_fail_reason", y)

typedef struct
{
    int  iButGpio; 
    char cHLSign;//最低位表示低电平，第二位表示高电平
    char *pcButName;
}DEV_BUTTON_TEST_T;


			
//===============================================================================

COMMON_ERROR_ENUM button_test(DEV_TEST_INFO_T *pstDevTestInfo)
{
    DEV_BUTTON_TEST_T astDevButtonTest[]={ 
                                        {18, 1, "default"}, 
                                         };
	COMMON_ERROR_ENUM enComRet;
	char acBuf[128];
	char acTmp[16]={0};
	int iLoop,iPass = 0;
	FILE *fp;
	
    for(iLoop = 0; iLoop < BUTTONNUM; iLoop++)
	{
		sprintf(acBuf, "%s %d in", GPIO_TOOL, astDevButtonTest[iLoop].iButGpio);
		enComRet = SystemCall(acBuf);
		if(CommonError_OK != enComRet)
		{
			return enComRet;
		}
		
		memset(acBuf, 0, sizeof(acBuf));
		BUTTON_REA(acBuf,astDevButtonTest[iLoop].pcButName);
		NvramUnset(acBuf,NVRAM_NO_COMMIT);
		memset(acBuf, 0, sizeof(acBuf));
		BUTTON_RES(acBuf,astDevButtonTest[iLoop].pcButName);
		enComRet = NvramSet(acBuf, "fail", NVRAM_NO_COMMIT);
		if(CommonError_OK != enComRet)
	 	{
			return enComRet;
		}
		memset(acBuf, 0, sizeof(acBuf));
	}
	while(1)
	{
		for(iLoop = 0; iLoop < BUTTONNUM; iLoop++)
		{
            if(3 != astDevButtonTest[iLoop].cHLSign)
            {
                sprintf(acBuf, GPIO_TOOL" %d", astDevButtonTest[iLoop].iButGpio);
                fp =popen(acBuf, "r");
                if(NULL == fp)
				{
					BUTTON_REA(acBuf, astDevButtonTest[iLoop].pcButName);
					enComRet = NvramSet(acBuf, "popen_open_file_fail", NVRAM_NO_COMMIT);
					memset(acBuf, 0, sizeof(acBuf));
					if(CommonError_OK != enComRet)
	 				{
						return enComRet;
				 	}
				}
				memset(acBuf, 0, sizeof(acBuf));
                if(fgets(acBuf, sizeof(acBuf), fp) == NULL)
				{
					BUTTON_REA(acBuf, astDevButtonTest[iLoop].pcButName);
					enComRet = NvramSet(acBuf, "gpio_cmd_error", NVRAM_NO_COMMIT);
					memset(acBuf, 0, sizeof(acBuf));
					if(CommonError_OK != enComRet)
	 				{
						return enComRet;
					}
				}
				if(NULL != strstr(acBuf, "GPIO"))
				{
                    sscanf(acBuf, "%*[^ ] %*[^ ] %*[^ ] %*[^ ] %s", acTmp);
                    if(0 == atoi(acTmp))
                    {
                        astDevButtonTest[iLoop].cHLSign |= 1;
                    }
                    else if(1 == atoi(acTmp))
                    {
                        astDevButtonTest[iLoop].cHLSign |= 2;
                    }
				}

                pclose(fp);			
			}
		}
		sleep(1);
		for(iLoop = 0; iLoop < BUTTONNUM; iLoop++)
		{
		    if(3 == astDevButtonTest[iLoop].cHLSign)
		    {	
				BUTTON_RES(acBuf,astDevButtonTest[iLoop].pcButName);
				enComRet = NvramSet(acBuf, "pass", NVRAM_NO_COMMIT);
				if(CommonError_OK != enComRet)
				{
					return enComRet;
		 		}
				memset(acBuf, 0, sizeof(acBuf));	
				iPass++;
		    }
		}
		if(BUTTONNUM == iPass)
		{
			break;
		}
		else
		{
			iPass = 0;
		}
	}
	return CommonError_OK ;
}

