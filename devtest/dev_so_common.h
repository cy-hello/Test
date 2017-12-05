#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>

#define DEV_SO_COMMON_VER "1.0.0"
#define DEBUG_MSG_LEN 1024
#define NVRAM_CMD_LEN 256
#define NVRAM_CMD_PREFIX "factory_env"
#define NVRAM_NO_COMMIT 0
#define NVRAM_NEED_COMMIT 1
#define MAX_READ_FILE_LEN 128

typedef enum{
	CommonError_OK,					  	/*0*/
	CommonError_LackOfSoName,			/*1*/
	CommonError_LoadSoFail,				/*2*/
	CommonError_LoadSoFuncFail,			/*3*/
	CommonError_NullPointer,				/*4*/
	CommonError_IllegalParameter,			/*5*/
	CommonError_SysCallError,				/*6*/
	CommonError_SysCallAbnormallyExit,		/*7*/
	CommonError_SysCallException,			/*8*/
	CommonError_SoPrivateError,				/*9*/
	CommonError_NvramVarNotExist,			/*10*/
	
	CommonError_Size						/*11*/
}COMMON_ERROR_ENUM;


#define DELETE_NEXT_LINE(msg) do{\
		if(msg[strlen(msg)-1]=='\n') msg[strlen(msg)-1] = '\0';\
}while(0)

#define FREE_CPU()  (usleep(100000))

inline int debug_msg(char * szFormat,...);
int Split_Str(char *pcBegin, char *pcNode,char cBegin, char cEnd);
int Split_Str_P2P(char **pcBegin, char cBegin, char cEnd);
void SplitStrByIndex(char *pcStr, int iStartIndex, int iEndIndex, char *pcTargetStr);
inline COMMON_ERROR_ENUM SystemCall(char *pcSysCmd);
COMMON_ERROR_ENUM NvramSet(char *nvramvar, char *value, char cCommitFlag);
COMMON_ERROR_ENUM NvramUnset(char *nvramvar, char cCommitFlag);
COMMON_ERROR_ENUM NvramGet(char *nvramvar, char *acResult, int flag);
int stat_file_size( char * pcFilePath );
int ReadOneRowFromFile(char *FilePath, char *pcStr, int len);
void LowerToUpper(char *str);
char * TrimRightSpace(char *szIn);