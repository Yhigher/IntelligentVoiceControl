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


//�����
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

//����˵�������
endPointDesc_t GenericApp_epDesc;

//������������ȼ�
byte GenericApp_TaskID; 

//���巢��������ţ�������
byte GenericApp_TransID;  // This is the unique message ID (counter)



//�����ʼ��ϵͳ��ʼ����ʱ�򣬻ᱻ����
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
  
  
  
  
 
 //��Ӧ�Ĵ������õĽṹ��
  halUARTCfg_t uartConfig;
//�Ƿ�����   ���á�HalUARTOpen()������ʱ���Զ�����.configured��������ΪTRUE��
//����.configured��=TURE���ٵ��á�HalUARTOpen()��������ͬһ������ʱ��
//����Զ�������ڵ�RX��TX����ʹ������á�uartRecord�����������á��˴���������ΪTRUE��
  uartConfig.configured = true; 

  uartConfig.baudRate =HAL_UART_BR_115200;// ���ò�����Ϊ115200

  //Ӳ�������ƣ�TRUEΪ����Ӳ�����أ�FALSEΪ�ر�Ӳ�����ء�
  //��Ӳ�����ع��ܵĿ��Կ���Ӳ�����أ��˴���������ΪFALSE���ر�Ӳ�����ع��ܡ�
  uartConfig.flowControl = false; //����Ҫ���ء���Ӧ��flowControlThreshold��idleTimeout����Ҫ����

  
  //�˲�����ʾRX����ﵽ��maxRxBufSize��֮ǰ���ж����ֽڿ��ࡣ��RX���浽�maxRxBufSize �C flowControlThreshold��ʱ��
  //�ᴥ����Ӧ��Ӧ���¼�����HAL_UART_RX_ABOUT_FULL�����˴���������Ϊ64��һ������Ϊ��maxRxBufSize����һ�롣
  uartConfig.flowControlThreshold = 64;
  
  //����豸�����յ�����֮���ڡ�idleTimout��ʱ����RXû���յ��µ������ˣ�
  //���ᴥ����Ӧ���¼���HAL_UART_RX_TIMEOUT������ʱӦ�ó������ѡ���������RX��ֵ����һ���ֵ�ֵ��
  //��λ�����롣�˴���������Ϊ6ms���������յ����ݺ�6ms��û�����յ��µ����ݣ��򴥷���HAL_UART_RX_ABOUT_FULL���¼���
  uartConfig.idleTimeout = 6;             // 6ms�󴮿ڿ������ʹ��ڿ����¼�,����������Ϊ0
 
  //rx������halUARTBufControl_t�����ݽṹ�����ڲ���RX ��������
  //�����յ��ֽ������rx.maxBufSize��ʱ���������HAL_UART_RX_FULL���¼����˴���������Ϊ128���ֽ�
  uartConfig.rx.maxBufSize = 128;
  
  //tx������halUARTBufControl_t�����ݽṹ�����ڲ���TX ��������
  //�����յ��ֽ������tx.maxBufSize��ʱ���������HAL_UART_RX_FULL���¼����˴���������Ϊ128���ֽ�
  uartConfig.tx.maxBufSize = 128;
  
  //�����ж�ʹ�ܣ�TRUEΪʹ�ܴ����жϹ��ܣ�FALSEΪʧ�ܴ����жϹ��ܡ��˴���������ΪTRUE��ʹ�ܴ����жϹ���
  uartConfig.intEnable = true; //ʹ���ж�    rxChRvdTime Ϊ���յ�ʱ����Ĭ�ϼ���

  //�ص�������Ӧ�ó�����Ը���RX��TX�����Ĳ�ͬ�¼����д���
  uartConfig.callBackFunc = rxCB;  //���յĻص�����
  
  //�򿪶�Ӧ�Ĵ���
  HalUARTOpen(0,&uartConfig);
  

  
  
  
  
  
  
  
  


}


UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
  afIncomingMSGPacket_t *MSGpkt;  //��Ϣ����ָ��

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


//�����ص������������ܵ���Ƶ����������Ϣ�Ĵ�����Ϣ��
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


//���ڽ��յĻص�����
static void rxCB(uint8 port ,uint8 event)
{
  uint8 buf[50];
  uint8 rxLength = 0;//���յ��ַ��Ĵ�С
  rxLength = Hal_UART_RxBufLen(0);  //�����ַ����ĸ���
  if(rxLength > 0)
  {
    HalUARTRead(0,buf,rxLength);//��ȡ�����ֵ�buf��
    //HalUARTWrite(0,buf,rxLength);//��buf��д����������
    GenericApp_SendTheMessage((char *)buf,rxLength);
    
    
  }
}


void GenericApp_SendTheMessage(char *theMessageData,byte len)
{
  afAddrType_t GenericApp_DstAddr;
  GenericApp_DstAddr.addr.shortAddr = 0xffff;   //�̵�ַ���߼�/���磩
  GenericApp_DstAddr.addrMode = AddrBroadcast;    //ͨ�ŵ�ģʽ  ��Ե�
  GenericApp_DstAddr.endPoint  = GENERICAPP_ENDPOINT;   //Ŀ�ĵض˵�� 
 
  
   AF_DataRequest( &GenericApp_DstAddr,     //Ŀ�ĵ�ַ
                       &GenericApp_epDesc,    //�˵������������Ͷˣ�
                       GENERICAPP_CLUSTERID,   //����ţ���ID��
                       len,//��Ϣ�ĳ���
                       (byte *)theMessageData, //��Ϣ����
                       &GenericApp_TransID,   //�������
                       AF_DISCV_ROUTE, AF_DEFAULT_RADIUS );

}










