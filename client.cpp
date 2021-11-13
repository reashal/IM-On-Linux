#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<netdb.h>
#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<sys/types.h>
#include<arpa/inet.h>    
#include<sys/socket.h>
#include<netinet/in.h>
using namespace std;
char ip_address[20],mess[2222],msg_rec[2222],l_ip[20]="";
int soc_cli,soc_rec,con_rec,fin,l_len;
struct sockaddr_in  servaddr,cliaddr,localaddr;
pthread_t rcv;

void in_ip_defult()
{
  char ip_defult[]="47.94.1.16";
  stpcpy(ip_address,ip_defult);
  // the defult ip in Aliyun  
  return ;
}

void in_ip(char ip_input[])
{
  stpcpy(ip_address,ip_input);
  /* If you run the server program locally, illegal input other than the IP will still connect local successfully.
     but if run in the server,the illegal input will not successfully connect.
     ( illegal input such as:"hhh" )*/
  return ;
}

int con_ser()
{
  soc_cli=socket(AF_INET,SOCK_STREAM,0);
  // set socket | return socket description | error -1
  // AF_INET:ipv4  SOCK_STREAM:full duplex  0:automatic choose agreement of type(2)
  if(soc_cli==-1)
  {
    printf("--failed to create socket\n");
    return 0;
  }
  // init
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  // choose ipv4 but not ipv6
  servaddr.sin_port=htons(6666);
  // defult ip  port
  if(inet_pton(AF_INET,ip_address,&servaddr.sin_addr)==-1)
  {
    printf("--failed to inet_tion\n");
    return 0;
  }
  // transform the ip address to binary
  if(connect(soc_cli,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
  //        (description,server socket address,length of socket address)
  {
    printf("--failed to connection\n");
    return 0;
  }
  //printf("--connection success!\n");
  return 1;
}

int send_info()
{
	while(1)
	{
		fgets(mess,2222,stdin);
		// buffer | stop when '\n' what want to send 
		
		if(send(soc_cli,mess,strlen(mess),0)==-1)
		// (socket description,buffer,length,0)
		{
			printf("--failed to send this  message!\n");
			return 0;
		}
		if(mess[0]=='!'&&mess[1]=='q')
		{
			/*
			close(soc_cli);
			kill(getppid(),SIGUSR1);
			exit(EXIT_SUCCESS);
			return 0;
			*/
			break;
		}
	}
	close(soc_cli);
	kill(getppid(),SIGUSR1);
	exit(EXIT_SUCCESS);
//	善后工作,关闭套接字/对接父进程
	return 1;
}

void con_recv()
{
//	printf("----I'm listening the server program\n");
	while(1)
	{
		bzero(msg_rec,sizeof(msg_rec));
		// The string is zeroed out each time a message is received
		fin=read(soc_cli,msg_rec,sizeof(msg_rec));
		if(!fin)
		{
			printf("--The server program is close\n");
			break;
		}
		printf("--Msg from server:");
		fputs(msg_rec,stdout);
		printf("\n");
	}
}

int main()// 功能实现按数字标号,附注释
{
  /* 1.选择默认ip或者自定义ip,如果指向非本机的客户端,会检测ip输入是否合法*/
  in_ip_defult();
  // 默认ip,阿里云,后期调试/考核看情况去该函数里改
  /*
  scanf("%s",ip_address);
  std::cin.ignore();
  in_ip(ip_address);
  // QT选择自定义ip,传参需要 **字符数组** 形式,用指针会报错
  // 字符读入的时候需要ignore掉\n,否则会当成第一条消息发送
  */
  
  /* 2.与服务器的连接部分,返回1则连接成功,返回0则图形界面自行决定处理逻辑,这里选择退出不进行重连
  printf("--please wait to see if the connection is succeed.\n");
  printf("--you will get message in 2s if success\n");
  */
  if(!con_ser()) return 0;

  //sleep(1); 非必须,仅Shell测试时为获取成功信息时美观设置
  
  /* 3.父进程接收消息*/
  pid_t k=fork();
  if(k>0) con_recv();
  
  /* 4.子进程发送消息*/
  if(!k)
	  send_info();
  close(soc_cli);
  // 关闭套接字,否则服务端陷入接收消息的死循环
  return 0;
}