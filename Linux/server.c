#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "usart.h"





unsigned char cmd[][5]={
	{0xdd,0x03,0x01,0x00,0x00},
	{0xdd,0x03,0x01,0x00,0x01},
	{0xdd,0x03,0x01,0x00,0x02},
	{0xdd,0x03,0x01,0x00,0x03},
	{0xdd,0x03,0x01,0x00,0x04},
	{0xdd,0x03,0x01,0x00,0x05},
};



struct FDS{

	int cfd;
	int uart_fd;
};



void *func(void *arg)
{
	

	struct FDS FD = *(struct FDS  *)arg;


	while(1)
	{
		//每次读数据缓存区
		char buf[200] ={0};
		//每次读数据的大小
		int size = 0;
		size = read(FD.cfd,buf,sizeof(buf));
		if(strcmp(buf,"beeOn") == 0)
		{ 
			//向下位机对应指令
			UART0_Send(FD.uart_fd,cmd[2],5);
		
		}

		else if(strcmp(buf,"beeOff") == 0)
		{
			UART0_Send(FD.uart_fd,cmd[3],5);
		}
		else if(strcmp(buf,"ledOn") == 0)
		{
			UART0_Send(FD.uart_fd,cmd[0],5);
		}else if(strcmp(buf,"ledOff") == 0)
		{
			UART0_Send(FD.uart_fd,cmd[1],5);
		}else if(strcmp(buf,"fanOn") == 0)
		{
			UART0_Send(FD.uart_fd,cmd[4],5);
		}else if(strcmp(buf,"fanOff") == 0)
		{
			UART0_Send(FD.uart_fd,cmd[5],5);
		}

		//进行内存清零
		memset(buf,0,sizeof(buf));
	}
}



int main(int argc, const char *argv[])
{ 
	unsigned char buf2[200] = {0};
	char temp[100];
	

	if(argc < 4)
	{
		fprintf(stderr,"%s ip port devID\n",argv[1]);
		return -1;
	}

	struct FDS FD;


	pthread_t pid[1024];
	//套接字
	int sfd = 0;
	//保存对应ip和port的结构体   man 7 ip
	struct sockaddr_in sfd_addr;
	//结构体的大小
	socklen_t addrlen = 0;
	//接受对应判断
	int ret = 0;


	
	int uart_fd = 0;

	//打开串口
	uart_fd = UART0_Open(uart_fd,argv[3]);
	//配置串口
	if (UART0_Set(uart_fd,115200,0,8,1,'N') == FALSE)    
    {                                                             
        return FALSE;    
    }    






	addrlen = sizeof(struct sockaddr_in);


	//填充的协议族
	sfd_addr.sin_family = AF_INET;
	//填充的式端口号，   atoi  字符串转整型  htons 对应主机字节序转网络字节序 man 3 htons
	sfd_addr.sin_port = htons(atoi(argv[2]));
	//填充ip地址    inet_addr 主机转网络 man 3 inet_addr
	sfd_addr.sin_addr.s_addr = inet_addr(argv[1]);

	//创建套接字  ipv4  流式套接字 具体协议
	sfd =  socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfd)
	{
		perror("socket");
		return -1;
	}
	//绑定对应的套接字 man 2 bind    
    ret = bind(sfd, (struct sockaddr *)&sfd_addr,addrlen);
	if(-1 == ret)
	{
		perror("bind");
		return -1;
	}
	//设置为监听模式
	ret = listen(sfd,10);
	if(-1 == ret)
	{
		perror("listen");
		return -1;
	}
	printf("litening....\n");
	
	
	//等待客户端的连接 是个阻塞的函数
	int cfd = accept(sfd,NULL,NULL);
	FD.cfd = cfd;
	FD.uart_fd = uart_fd;

	printf("the client is online\n");
	while(1)
	{	

		pthread_create(&pid[cfd],NULL,func,(void*)&FD);
		int rev = read (uart_fd,buf2,36);
		if(rev == -1){
			perror ("rev");
			return -1;
		}
		printf("温度: %d,湿度：%d  light:%d\n",buf2[5],buf2[7],buf2[8]);
		sprintf(temp,"%d-%d-%d",buf2[5],buf2[7],buf2[8]);
		write(cfd,temp,strlen(temp));	
	}
	close(sfd);
	return 0;
}
