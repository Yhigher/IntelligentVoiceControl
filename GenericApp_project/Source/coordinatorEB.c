#include "coordinatorEB.h"
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "ZDProfile.h"
#include "DebugTrace.h"

#if !defined( WIN32 )
  #include "OnBoard.h"
#endif

/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"
#include "MT_UART.h"

extern void GenericApp_Init( byte task_id );
extern UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events );
void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt );
void GenericApp_SendTheMessage(char *theMessageData,byte len);
static void rxCB(uint8 port ,uint8 event);


//输入簇
// This list should be filled with Application specific Cluster IDs.
const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
{
  GENERICAPP_CLUSTERID  
};

const SimpleDescriptionFormat_t GenericApp_SimpleDesc =
{
  GENERICAPP_ENDPOINT,              //  int Endpoint;
  GENERICAPP_PROFID,                //  uint16 AppProfId[2];
  GENERICAPP_DEVICEID,              //  uint16 AppDeviceId[2];
  GENERICAPP_DEVICE_VERSION,        //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                 //  int   AppFlags:4;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,  //  byte *pAppInClusterList;
  GENERICAPP_MAX_CLUSTERS,          //  byte  AppNumInClusters;
  (cId_t *)GenericApp_ClusterList,   //  byte *pAppInClusterList;
};

//定义端点描述符
endPointDesc_t GenericApp_epDesc;

//定义任务的优先级
byte GenericApp_TaskID; 

//定义发送数据序号（计数）
byte GenericApp_TransID;  // This is the unique message ID (counter)



//任务初始化系统初始化的时候，会被调用
void GenericApp_Init( byte task_id )
{
  MT_UartInit();
  
  
  
  GenericApp_TaskID = task_id;


  // Fill out the endpoint description.
  GenericApp_epDesc.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc.task_id = &GenericApp_TaskID;
  GenericApp_epDesc.simpleDesc
            = (SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
  GenericApp_epDesc.latencyReq = noLatencyReqs;

  // Register the endpoint description with the AF
  afRegister( &GenericApp_epDesc );
  
  
  
  
 
 //对应的串口配置的结构体
  halUARTCfg_t uartConfig;
//是否配置   调用“HalUARTOpen()”函数时会自动将“.configured”参数置为TRUE；
//若“.configured”=TURE，再调用“HalUARTOpen()”函数打开同一个串口时，
//则会自动清除串口的RX、TX缓存和串口配置“uartRecord”再重新配置。此处我们设置为TRUE。
  uartConfig.configured = true; 

  uartConfig.baudRate =HAL_UART_BR_115200;// 配置波特率为115200

  //硬件流控制，TRUE为开启硬件流控，FALSE为关闭硬件流控。
  //有硬件流控功能的可以开启硬件流控，此处我们设置为FALSE，关闭硬件流控功能。
  uartConfig.flowControl = false; //不需要流控。对应的flowControlThreshold和idleTimeout不需要配置

  
  //此参数表示RX缓存达到“maxRxBufSize”之前还有多少字节空余。当RX缓存到达“maxRxBufSize – flowControlThreshold”时，
  //会触发相应的应用事件：“HAL_UART_RX_ABOUT_FULL”。此处我们设置为64，一般设置为“maxRxBufSize”的一半。
  uartConfig.flowControlThreshold = 64;
  
  //如果设备串口收到数据之后在“idleTimout”时间内RX没有收到新的数据了，
  //将会触发相应的事件“HAL_UART_RX_TIMEOUT”，这时应用程序可以选择读出所有RX的值或者一部分的值，
  //单位：毫秒。此处我们设置为6ms，当串口收到数据后，6ms内没有再收到新的数据，则触发“HAL_UART_RX_ABOUT_FULL”事件。
  uartConfig.idleTimeout = 6;             // 6ms后串口空闲则发送串口空闲事件,参数不可设为0
 
  //rx包含“halUARTBufControl_t”数据结构，用于操作RX 缓冲区。
  //当接收的字节数到达“rx.maxBufSize”时，会产生“HAL_UART_RX_FULL”事件。此处我们设置为128个字节
  uartConfig.rx.maxBufSize = 128;
  
  //tx包含“halUARTBufControl_t”数据结构，用于操作TX 缓冲区。
  //当接收的字节数到达“tx.maxBufSize”时，会产生“HAL_UART_RX_FULL”事件。此处我们设置为128个字节
  uartConfig.tx.maxBufSize = 128;
  
  //串口中断使能，TRUE为使能串口中断功能，FALSE为失能串口中断功能。此处我们设置为TRUE，使能串口中断功能
  uartConfig.intEnable = true; //使能中断    rxChRvdTime 为接收的时间用默认即可

  //回调函数，应用程序可以根据RX、TX出发的不同事件进行处理。
  uartConfig.callBackFunc = rxCB;  //接收的回调函数
  
  //打开对应的串口
  HalUARTOpen(0,&uartConfig);
  

  
  
  
  
  
  
  
  


}


UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;  //消息包的指针

  if ( events & SYS_EVENT_MSG )
  {
    MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    while ( MSGpkt )
    {
      switch ( MSGpkt->hdr.event )
      {
   

        case AF_INCOMING_MSG_CMD:
          GenericApp_MessageMSGCB( MSGpkt );
          break;

        default:
          break;
      }

      // Release the memory
      osal_msg_deallocate( (uint8 *)MSGpkt );
      // Next
      MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( GenericApp_TaskID );
    }
    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }
  return 0;
}


//拷贝回调函数，（接受到射频传过来的消息的处理消息）
void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt )
{
  uint8 buf[64];
  uint16 len;
  switch ( pkt->clusterId )
  {
    case GENERICAPP_CLUSTERID:
      // "the" message
    len = pkt->cmd.DataLength;
    if (len > 0) {
    osal_memcpy(buf, pkt->cmd.Data, len);
    buf[len] = 0;
    
    HalUARTWrite(HAL_UART_PORT_0,buf,len);
    
  } 
      break;
  }
}


//串口接收的回调函数
static void rxCB(uint8 port ,uint8 event)
{
  uint8 buf[50];
  uint8 rxLength = 0;//接收到字符的大小
  rxLength = Hal_UART_RxBufLen(0);  //接收字符串的个数
  if(rxLength > 0)
  {
    HalUARTRead(0,buf,rxLength);//读取到保持到buf中
    //HalUARTWrite(0,buf,rxLength);//从buf中写到电脑里面
    GenericApp_SendTheMessage((char *)buf,rxLength);
    
    
  }
}


void GenericApp_SendTheMessage(char *theMessageData,byte len)
{
  afAddrType_t GenericApp_DstAddr;
  GenericApp_DstAddr.addr.shortAddr = 0xffff;   //短地址（逻辑/网络）
  GenericApp_DstAddr.addrMode = AddrBroadcast;    //通信的模式  点对点
  GenericApp_DstAddr.endPoint  = GENERICAPP_ENDPOINT;   //目的地端点号 
 
  
   AF_DataRequest( &GenericApp_DstAddr,     //目的地址
                       &GenericApp_epDesc,    //端点描述符（发送端）
                       GENERICAPP_CLUSTERID,   //命令号（簇ID）
                       len,//消息的长度
                       (byte *)theMessageData, //消息内容
                       &GenericApp_TransID,   //发送序号
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );

}










