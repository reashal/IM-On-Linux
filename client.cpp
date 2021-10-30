#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<typeinfo>
#include<iostream>
using namespace std;
char ip_address[20],mess[2222];
int soc_cli;
struct sockaddr_in  servaddr;

void in_ip()
{
  printf("--please input the server ip address:\n");
  scanf("%s",ip_address);
  std::cin.ignore();
  // ignore \n
  return;
}

int con_ser()
{
  soc_cli=socket(AF_INET,SOCK_STREAM,0);
  // set socket | error-1
  // AF_INET:ipv4  SOCK_STREAM:full duplex  0:automatic choose agreement of type(2)
  if(soc_cli==-1)
  {
    printf("--failed to create socket\n");
    return 0;
  }
  servaddr.sin_family=AF_INET;
  // choose ipv4 but not ipv6
  servaddr.sin_port=htons(6666);
  // ip  port
  if(inet_pton(AF_INET,ip_address,&servaddr.sin_addr)==-1)
  {
    printf("--failed to inet_tion\n");
    return 0;
  }
  // transform the ip address to binary
  if(connect(soc_cli,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
  // (description,server socket address,length of socket address)
  {
    printf("--failed to connection\n");
    return 0;
  }
  // the client connect to the server
  printf("--connection success!\n");
  return 1;
}

int send_info()
{
  fgets(mess,2222,stdin);
  // buffer | stop when '\n'
  if(send(soc_cli,mess,strlen(mess),0)==-1)
  // (socket description,buffer,length,0)
  {
    printf("--failed to sene message!\n");
    return 0;
  }
  return 1;
}

int main()
{
  // init
  memset(&servaddr,0,sizeof(servaddr));
  // input server ip address
  in_ip();
  // wait for result
  printf("--please wait to see if the connection is succeed.\n");
  if(!con_ser()) return 0;
  sleep(1); 
  // connect buffer for success
  printf("--now you can send your message: \n");
  // if(!send_info()) return 0;
  while(1)
  {
    if(!send_info()) break;
  }
  close(soc_cli);
  // close socket
  return 0;
}
