#include "dev_so_common.h"

int g_iDebugMode = 0;
char acTmpProgList[128] = "";
//------------------------------------------------------------------------------
inline int debug_msg(char* szFormat, ...)
{
    char acMsg[DEBUG_MSG_LEN] = "";
    va_list vaMsg;
    if (1 == g_iDebugMode)
    {
        va_start(vaMsg, szFormat);
        vsprintf(acMsg, szFormat, vaMsg);
        va_end(vaMsg);
        printf("\r%s\n\n", acMsg);
    }
    return 0;
}
//------------------------------------------------------------------------------
int Split_Str(char *pcBegin, char *pcNode,char cBegin, char cEnd)
{
    //找到第一个字符位置，并把空格去掉
    char *pcEnd = NULL;
    while(*pcBegin != '\0')
    {
	 if(*pcBegin == cBegin)
	 {
//		pcBegin++;
		while(isspace(*pcBegin))
		{
			pcBegin++;
		}
		break;
	 }
	 pcBegin++;
    }
    if(*pcBegin == '\0')
    {
	  return -1;
    }

    //找到第二个字符位置，并把空格去掉
    pcEnd = pcBegin;
    while(*pcEnd != '\0')
    {
    	 pcEnd++;
	 if(*pcEnd == cEnd)
	 {
		break;
	 }
    }
    if(*pcEnd == '\0' && cEnd != '\0')
    {
	 return -1;
    }
    pcEnd--;
    while(isspace(*pcEnd))
    {
	 pcEnd--;
    }
    *(++pcEnd) = '\0';

    debug_msg("[%s][%d][Show Info] pcBegin:%s", __func__, __LINE__, pcBegin);
    while('\0' != *pcBegin)
    {
	 *pcNode = *pcBegin;
	  pcBegin++;
	  pcNode++;
    }
    *pcNode = '\0';
    return 0;
	
}


//------------------------------------------------------------------------------
int Split_Str_P2P(char **pcBegin, char cBegin, char cEnd)
{
    //找到第一个字符位置，并把空格去掉
    char *pcEnd = NULL;
    while(**pcBegin != '\0')
    {
	 if(**pcBegin == cBegin)
	 {
		(*pcBegin)++;
		while(isspace(**pcBegin))
		{
			(*pcBegin)++;
		}
		break;
	 }
	 (*pcBegin)++;
    }
    if(**pcBegin == '\0' || **pcBegin == cEnd)
    {
	  return -1;
    }

    //找到第二个字符位置，并把空格去掉
    pcEnd = *pcBegin;
    while(*pcEnd != '\0')
    {
    	 pcEnd++;
	 if(*pcEnd == cEnd)
	 {
		break;
	 }
    }
    if(*pcEnd == '\0' && cEnd != '\0')
    {
	 return -1;
    }
    pcEnd--;
    while(isspace(*pcEnd))
    {
	 pcEnd--;
    }
    *(++pcEnd) = '\0';
    return 0;
}

//------------------------------------------------------------------------------
char * TrimRightSpace(char *szIn)
{
    int iLoop = 0;
    int iLen = strlen(szIn);
	
    for (iLoop = iLen-1; iLoop>0; iLoop--)
    {
        if (isspace(szIn[iLoop]))
        {
            szIn[iLoop] = '\0';
        }
        else
        {
            break;
        }
    }
    return szIn;
}

//------------------------------------------------------------------------------
inline COMMON_ERROR_ENUM SystemCall(char *pcSysCmd)
{
	if( NULL == pcSysCmd)
	{
		printf("\nSysCmd Pointer NULL!\n");
		return CommonError_NullPointer;
	}
	
	int status;
	/* 这里是替换tmp中的命令，已实现
	int iLoop = 0;
	int iHeadLoop = 0;
	int i = 0;
	int j = 0;
	char acCmdHead[64] = "";
	char *acCmdDup = NULL;
	char acTmpProgName[36] = "";
	char pcaaa[128] = "";
	
	//拷贝命令副本
	acCmdDup = strdup(pcSysCmd);
	
	//首先去掉开头的空格
	while(isspace(acCmdDup[iLoop]))
	{
		iLoop++;
	}
	//截取调用的程序名称
	while( !isspace(acCmdDup[iLoop]) && '\0' != acCmdDup[iLoop] && iLoop < strlen(acCmdDup) )
	{
		acCmdHead[iHeadLoop] = acCmdDup[iLoop];
		iLoop++;
		iHeadLoop++;
	}
	
	printf("acCmdHead: %s",acCmdHead);
	
	if(0 < strlen(acTmpProgList))
	{
		if(strstr(acTmpProgList,acCmdHead))
		{
			sprintf(acTmpProgName,"/tmp/%s",acCmdHead);
			if(0 == access(acTmpProgName,F_OK))
			{
			//	memset(pcSysCmd, 0, sizeof(pcSysCmd));
			//	sprintf(pcSysCmd,"%s %s",acTmpProgName,acCmdBody);
				for(iLoop=0;iLoop<strlen(acCmdDup); iLoop++)
	{
		for(i=0; i<iHeadLoop; i++)
		{
			if(acCmdDup[iLoop+i]!=acCmdHead[i])
			{
				break;
			}
			if((i+1)==iHeadLoop)
			{
				printf("\nfind!!!!!!!!!\n");
				i = 0;
				while(i<iLoop)
				{
					pcaaa[i]=acCmdDup[i];
					i++;
				}
				j = 0;
				while(j<strlen(acTmpProgName))
				{
					pcaaa[i]=acTmpProgName[j];
					i++;
					j++;
				}
				j= iLoop+iHeadLoop;
				while(j<strlen(acCmdDup))
				{
					pcaaa[i]=acCmdDup[j];
					i++;
					j++;
				}
				pcaaa[i] = '\0';
				i=0;
				while(i<strlen(pcaaa))
				{
					acCmdDup[i] = pcaaa[i];
					i++;
				}
				acCmdDup[i] = '\0';
				iLoop=iLoop+strlen(acTmpProgName)-1;
				break;
			}
		}
	}
				printf("new cmd: %s",acCmdDup);
			}
			else
			{
				printf("\nno %s such file, I will use default %s\n",acTmpProgName,acCmdHead);
			}
		}
	}
	printf("\nSysCmd: %s\n",pcSysCmd);
      */
	
	status = system(pcSysCmd);
	printf("pcSysCmd==%s\n", pcSysCmd);
	if (-1 == status)
	{
                printf("system error!");
		   return CommonError_SysCallError;
	}
	else
	{
       //         printf("exit status value = [0x%x]\n", status);        
                if(WIFEXITED(status))  
                {  
                                if (0 == WEXITSTATUS(status))  
                                {  
                                  //              printf("system call successfully.\n");
							   return CommonError_OK;
                                }  
                                else  
                                {  
                                                printf("system call failed with exit code: %d\n", WEXITSTATUS(status));
							   return CommonError_SysCallException;
                                }  
                }  
                else  
                {  
                 	    printf("child process abnormally exit with status = %d\n", WIFEXITED(status));
			    return CommonError_SysCallAbnormallyExit;
                }
	}  
}

//------------------------------------------------------------------------------
COMMON_ERROR_ENUM NvramSet(char *nvramvar, char *value, char cCommitFlag)
{
	if ( NULL == nvramvar || NULL == value )
	{
		return CommonError_NullPointer;
	}
	COMMON_ERROR_ENUM enComRet;
	char acCmd[NVRAM_CMD_LEN] = "";
	sprintf(acCmd, "%s set %s=%s", NVRAM_CMD_PREFIX, nvramvar, value);
	enComRet = SystemCall(acCmd);
	if(enComRet != CommonError_OK)
	{
		return enComRet;
	}
	if(NVRAM_NEED_COMMIT == cCommitFlag)
	{
		enComRet = SystemCall(NVRAM_CMD_PREFIX" commit");
	}
	return enComRet;
}
//------------------------------------------------------------------------------
COMMON_ERROR_ENUM NvramUnset(char *nvramvar, char cCommitFlag)
{
	if ( NULL == nvramvar )
	{
		return CommonError_NullPointer;
	}

	COMMON_ERROR_ENUM enComRet;
	char acCmd[NVRAM_CMD_LEN] = "";
	
	sprintf(acCmd, "%s unset %s", NVRAM_CMD_PREFIX, nvramvar);
	enComRet = SystemCall(acCmd);
	if(enComRet != CommonError_OK)
	{
		return enComRet;
	}
	if(NVRAM_NEED_COMMIT == cCommitFlag)
	{
		enComRet = SystemCall(NVRAM_CMD_PREFIX" commit");
	}
	return enComRet;
}
//------------------------------------------------------------------------------

COMMON_ERROR_ENUM NvramGet(char *nvramvar, char *value, int flag)
{
	if(NULL == nvramvar || NULL == value)
	{
		return CommonError_NullPointer;
	}
	
	char acBuf[64] = "";
	char *pcRes = NULL;
	sprintf(acBuf, "%s get %s > /tmp/nvram_getres", NVRAM_CMD_PREFIX, nvramvar);
	system(acBuf);
	memset(acBuf, 0, sizeof(acBuf));
	if(0 != ReadOneRowFromFile("/tmp/nvram_getres", acBuf, 64))
	{
		return CommonError_NvramVarNotExist;
	}
	pcRes = strchr(acBuf,'=');
	if(NULL == pcRes)
	{
		return CommonError_NvramVarNotExist;
	}
	if('\0' == *(++pcRes))
	{
		return CommonError_NvramVarNotExist;
	}
	pcRes = TrimRightSpace(pcRes);
	strncpy(value,pcRes,strlen(pcRes));
	return CommonError_OK;
}


//------------------------------------------------------------------------------
int stat_file_size( char * pcFilePath )
{
      struct stat f_stat;
		
      if( stat( pcFilePath, &f_stat ) == -1 )
      {
            return -1;
      }
       return (int)f_stat.st_size;
}

//------------------------------------------------------------------------------
void LowerToUpper(char *str)
{
	int iLoop;
	for(iLoop=0; iLoop<strlen(str); iLoop++)
	{
		if(str[iLoop]>='a' && str[iLoop]<='z')
		{
			str[iLoop] = str[iLoop] - 32;
		}
	}
}
//------------------------------------------------------------------------------
void SplitStrByIndex(char *pcStr, int iStartIndex, int iEndIndex, char *pcTargetStr) //包含首尾
{
	for(;iStartIndex<=iEndIndex;iStartIndex++)
	{
		*(pcTargetStr++) = pcStr[iStartIndex];
	}
}

//------------------------------------------------------------------------------
int ReadOneRowFromFile(char *FilePath, char *pcStr, int len)
{
	FILE *pFile;
	pFile = fopen(FilePath, "r");
	if(!pFile)
	{
		return -1;
	}
	if(0 >= fread(pcStr,1,len,pFile))
	{
		fclose(pFile);
		return -1;
	}
	fclose(pFile);
	return 0;
}
