#include "dev_so_common.h"

#define GPIO_LED_NUM 6
#define GPIOEX_LED_NUM 2
#define DOUBLE_COLOR_LED_NUM 2
//#define DEFAULT_LED_ON_TIME 5

#define GPIO_RUN_LED  4
#define GPIO_WAN_LED  13
#define GPIO_LAN1_LED 14
#define GPIO_LAN2_LED 15
#define GPIO_LAN3_LED 16
#define GPIO_LAN4_LED 17

#define GPIOEX_LTE_LED_G 9
#define GPIOEX_LTE_LED_R 10
#define GPIOEX_WLAN_LED  14
#define GPIOEX_WPS_LED   15 

#define USB0 "/dev/ttyUSB0"
#define USB1 "/dev/ttyUSB1"
#define USB2 "/dev/ttyUSB2"
#define ACM0 "/dev/ttyACM0"

#define DEFAULT_SIM_DIAL_MAX_TIMES 1
#define DEFAULT_MI900_SIM_DIAL_SLEEP_TIME 10
#define LTE_LONGCHEER "longcheer"
#define LTE_LEADCORE "leadcore"
#define LTE_MI900 "mi900"

#define DEFAULT_GPS_READ_TIME 10
#define DEFAULT_GPS_SLEEP_TIME 3

#define LTE_IMEI_FILE "/tmp/atimei"
#define LEADCORE_IMEI_AT_CMD "AT+CGSN\r"
#define LEADCORE_IMEI_SUFFIX "+CGSN:"
#define LONGCHEER_IMEI_AT_CMD "AT+LCTSN=0,7\r"
#define LONGCHEER_IMEI_SUFFIX "+LCTSN:"

//#define DEFAULT_USB0_IP_ADDR "169.254.0.10"
#define NVRAM_LTE_IMEI_VAR "dev_simbox_test_lte_IMEI"
#define NVRAM_LTE_ICCID_VAR "dev_simbox_test_lte_iccid"
//#define NVRAM_LTE_BRAND_VAR "dev_simbox_test_lte_brand"
#define NVRAM_LTE_RSSI_VAR "dev_simbox_test_lte_rssi"

#define TMP_CALDATA_FILE "/tmp/CaldataCopy"
#define TMP_CUSTOMER_SN_FILE "/tmp/CustomerSnCopy"
#define DEVTEST_CUSTOMER_SN "dev_setsn_test_customer_sn"

//#define SD_NODE "/dev/sda1"
#define LTE_NODE_NUM 3
#define SIM_NODE_NUM 3
//------------------------------------------------------------------------------
//变量长度
#define TEST_ITEM_NAME_LEN 16
#define TEST_FAIL_REASON_LEN 64
#define MAX_READ_FILE_LEN 128
#define NVRAM_VAR_NAME_LEN 128
//------------------------------------------------------------------------------
//平台信息

#define DEV_TEST_DEFAULT -1
#define DEV_TEST_OK 1
#define DEV_TEST_FAIL 2

//------------------------------------------------------------------------------
/*
#define DELETE_NEXT_LINE(msg) do{\
		if(msg[strlen(msg)-1]=='\n') msg[strlen(msg)-1] = '\0';\
}while(0)
*/
//------------------------------------------------------------------------------
typedef enum{
	LteSoError_OK,					  	/*0*/
	LteSoError_UsbTestFail,				
	LteSoError_SdTestFail,				
	LteSoError_LteTestFail,				
	LteSoError_SimTestFail,			
	//LteSoError_PhyTestFail,			
	LteSoError_LedTestFail,		
	//LteSoError_ButtonTestFail,		
	LteSoError_UnexpectOption,			
	LteSoError_UnsupportedItem,			
	LteSoError_SaveTestResultFail,
	LteSoError_ReadLteIMEIFail,	
	LteSoError_SaveLteIMEIFail,			
	LteSoError_ReadLteIccidFail,		
	LteSoError_SaveLteIccidFail,		
	LteSoError_SaveLte4gRssiFail,
	LteSoError_BoxSimTestFail,		
	LteSoError_BoxSdTestFail,			
	LteSoError_BoxGpsTestFail,
	LteSoError_SetSnTestFail,
	LteSoError_CheckInfIpFail,
	LteSoError_LteResetTestFail,
	LteSoError_Size						
}LTE_SO_ERROR_ENUM;


//------------------------------------------------------------------------------
typedef struct _DEV_TEST_INFO_T
{
    char acTestItem[TEST_ITEM_NAME_LEN]; //测试项名称
	
    char cTestRes;//测试结果
    char acTestFailReason[TEST_FAIL_REASON_LEN];//失败原因
    int iLedOnTime;
    int iPhyFlag;
    int iPacketNum;
    int iPacketLen;

	char acBoxSimTestDialApn[32];
    int iBoxSimTestDialTimes;
    int iBoxSimTestSleepTime;
	int iCheckIccidSwitch;
	int iCheckSimStateSwitch;
	
	int iMacStartAddr;
	char acUserInputMac[13];
	char acCustomerSn[64];
	int iUsbAndSdTest;
    //int iBoxGpsTestGetComTimeout;
    //int iBoxGpsTestReadDataTimeout;
    /*
    int iBoxSimTestLossStandard;
    int iBoxSimTestPacketNum;
    int iBoxSimTestPacketLen;
    char acBoxSimTestPingHost[64];
    */
}DEV_TEST_INFO_T;

typedef struct _DEV_TEST_DATA_CMD_T
{
	char acTestName[TEST_ITEM_NAME_LEN];
	COMMON_ERROR_ENUM (*TestFunction)(DEV_TEST_INFO_T *pstDevTestInfo);
	char acResultVar[NVRAM_VAR_NAME_LEN];
	char acReasonVar[NVRAM_VAR_NAME_LEN];
}DEV_TEST_DATA_CMD_T;

typedef struct _DEV_TEST_GLOBAL_DATA_T
{
	LTE_SO_ERROR_ENUM enLastError;
	
}DEV_TEST_GLOBAL_DATA_T;
//------------------------------------------------------------------------------
void SoHelpInfo();
COMMON_ERROR_ENUM SoParseCmdLine(int argc, char **argv, DEV_TEST_INFO_T *pstDevTestInfo);
int main(int argc, char **argv);
COMMON_ERROR_ENUM led_test(DEV_TEST_INFO_T *pstDevTestInfo);
void GetLteRssi(void);
void FillTestResult(DEV_TEST_INFO_T *pstDevTestInfo, char result, char *reason);
int GetLastError(void);
unsigned int GetVersion(void);
COMMON_ERROR_ENUM usb_emmc_test(DEV_TEST_INFO_T *pstDevTestInfo);
COMMON_ERROR_ENUM phy_test(DEV_TEST_INFO_T *pstDevTestInfo);
COMMON_ERROR_ENUM button_test(DEV_TEST_INFO_T *pstDevTestInfo);